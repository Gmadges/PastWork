/// \file objReader.h
/// \brief class to loading in infomation from obj's.
/// \author George Madges
/// \version 2.0
/// \date 03/04/2014 modified from Jon Macey lecture code.

#ifndef OBJREADER
#define OBJREADER
#include <fstream>
#include <string>
#include <vector>
#include "Vec4.h"
#include "Vehicle.h"
#ifdef LINUX
    #include <GL/gl.h>
#endif
#ifdef DARWIN
    #include <OpenGL/gl.h>
#endif

class ObjReader
{
  public :

    ObjReader(const std::string &_file);
    ~ObjReader();
    void parseFile();
    /**
     * @brief CreateArrays
     * @brief reads in obj file and stores all drawing data in Vehicles arrays.
     * @param vert - vector array of verts to store data.
     * @param norm - vector array of verts to store data.
     * @param uv   - vector array of verts to store data.
     */
    void createArrays(std::vector<Vec4> &_vert,
                      std::vector<Vec4> &_norm,
                      std::vector<Vec4> &_uv );
    inline int getNumFaces() const {return m_faceCount;}
    inline int getNumVerts() const {return m_vertCount;}
    inline int getNumNormals() const {return m_normalCount;}
    inline int getNumUVs() const {return m_uvCount;}
    void tokenize(const std::string& _str,std::vector<std::string>& _tokens,const std::string& _delimiters = " ");


  private :
    std::fstream m_stream;
    int m_vertCount;
    int m_faceCount;
    int m_normalCount;
    int m_uvCount;

};

#endif
