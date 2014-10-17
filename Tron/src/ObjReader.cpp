///
///  @file camera.cpp
///  @brief functions used by camera class.

#include "ObjReader.h"
#include <stdexcept>
#include <iostream>
#include <cstdlib>


ObjReader::ObjReader(const std::string &_filename)
{
  std::cerr<<"ObjReader Attempting to open "<<_filename<<"\n";
  m_stream.open(_filename.c_str(),std::ios::in);
  if (!m_stream.is_open())
  {
    throw std::invalid_argument("Unable to Open File");
  }
  else
  {
    std::cerr<<"file Opened\n";
  }
  m_normalCount=0;
  m_vertCount=0;
  m_faceCount=0;
  m_uvCount=0;
}


ObjReader::~ObjReader()
{
  std::cerr<<"ObjReader dtor called closing file\n";
  m_stream.close();
}

void ObjReader::parseFile()
{
  std::string lineBuffer;
  std::vector <std::string> tokens;
  while(!m_stream.eof())
  {
    // grab a line from the stream
    std::getline(m_stream,lineBuffer,'\n');
    // must clear the tokens before each parse
    tokens.clear();
    // now split it into tokens based on the spaces
    tokenize(lineBuffer,tokens," \n");
    if(tokens.size() !=0)
    {
      // now check for the first line token and add
      if(tokens[0]=="v")
      {
        ++m_vertCount;
      }
      else if(tokens[0]=="vn")
      {
        ++m_normalCount;
      }
      else if(tokens[0]=="vt")
      {
        ++m_uvCount;
      }
      else if(tokens[0]=="f")
      {
        ++m_faceCount;
      }
    }
  }
}

void ObjReader::tokenize(const std::string& _str,std::vector<std::string>& _tokens,const std::string& _delimiters)
{
  // Skip delimiters at beginning.
  std::string::size_type lastPos = _str.find_first_not_of(_delimiters, 0);
  // Find first "non-delimiter".
  std::string::size_type pos     = _str.find_first_of(_delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    // Found a token, add it to the vector.
    _tokens.push_back(_str.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos = _str.find_first_not_of(_delimiters, pos);
    // Find next "non-delimiter"
    pos = _str.find_first_of(_delimiters, lastPos);
  }
}


void ObjReader::createArrays(std::vector<Vec4> &_vert,
                             std::vector<Vec4> &_norm,
                             std::vector<Vec4> &_uv  )
{

  std::string lineBuffer;
  std::vector <std::string> tokens;
  std::vector <Vec4> tmpVert;
  std::vector <Vec4> tmpNorm;
  std::vector <Vec4> tmpUV;
  std::vector <unsigned int> fVert;
  std::vector <unsigned int> fNorm;
  std::vector <unsigned int> fUV;


  while(!m_stream.eof())
  {
    // grab a line from the stream
    std::getline(m_stream,lineBuffer,'\n');
    // must clear the tokens before each parse
    tokens.clear();
    // now split it into tokens based on the spaces
    tokenize(lineBuffer,tokens," \n");
    if(tokens.size() !=0)
    {
      // now check for the first line token and add
      if(tokens[0]=="v")
      {
        tmpVert.push_back(Vec4( atof(tokens[1].c_str()),
                                atof(tokens[2].c_str()),
                                atof(tokens[3].c_str())));
        //Checks through data to find the points needed for the bBox.
      }
      else if(tokens[0]=="vn")
      {
        tmpNorm.push_back(Vec4( atof(tokens[1].c_str()),
                                atof(tokens[2].c_str())));
      }
      else if(tokens[0]=="vt")
      {
        tmpUV.push_back(Vec4( atof(tokens[1].c_str()),
                              atof(tokens[2].c_str()),
                              atof(tokens[3].c_str())));
      }
      else if(tokens[0]=="f")
      {
        for(int i=1; i<=3; i++)
        {
          std::vector <std::string> faceV;
          tokenize(tokens[i], faceV, "/");
          fVert.push_back(atoi(faceV[0].c_str()));
          fNorm.push_back(atoi(faceV[1].c_str()));
          fUV.push_back(atoi(faceV[2].c_str()));
        }
      }
    }
  }
  for(unsigned int i = 0; i < fVert.size(); i++)
  {
    unsigned int vIndex = fVert[i];
    unsigned int nIndex = fNorm[i];
    unsigned int uIndex = fUV[i];

    _vert.push_back(tmpVert[vIndex-1]);
    _norm.push_back(tmpVert[nIndex-1]);
    _uv.push_back(tmpVert[uIndex-1]);
  }

}
