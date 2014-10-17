///
///  @file camera.cpp
///  @brief functions used by Mat4 class.

#include "Mat4.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#ifdef LINUX
	#include <GL/gl.h>
#endif
#ifdef DARWIN
	#include <OpenGL/gl.h>
#endif


Mat4::Mat4(float _s)
{
  memset(&m_m,0,sizeof(m_m));
  m_00 = _s;
  m_11 = _s;
  m_22 = _s;
  m_33 = _s;
}

Mat4::Mat4(const Mat4 &_r)
{
  memcpy( m_m, &_r, sizeof(m_m));
}

std::ostream & operator <<(std::ostream &_output, const Mat4 &_v)
{
  std::cout.setf(std::ios::fixed |
                 std::ios::adjustfield |
                 std::ios::showpos
                 );

  std::cout.precision(std::numeric_limits<double>::digits10+1);

  return _output
        <<"["<<_v.m_00<<","<<_v.m_10<<","<<_v.m_20<<","<<_v.m_30<<"]\n"
        <<"["<<_v.m_01<<","<<_v.m_11<<","<<_v.m_21<<","<<_v.m_31<<"]\n"
        <<"["<<_v.m_02<<","<<_v.m_12<<","<<_v.m_22<<","<<_v.m_32<<"]\n"
        <<"["<<_v.m_03<<","<<_v.m_13<<","<<_v.m_23<<","<<_v.m_33<<"]\n";
}

void Mat4::identity()
{
  memset(&m_m,0,sizeof(m_m));
  m_00 = 1.0f;
  m_11 = 1.0f;
  m_22 = 1.0f;
  m_33 = 1.0f;
}

void Mat4::rotateX(float _deg)
{
  float beta = (_deg/180.0f) * M_PI;
  float sr = sin(beta);
  float cr = cos(beta);
  identity();
  m_11 = cr;
  m_21 = -sr;
  m_12 = sr;
  m_22 = cr;
}

void Mat4::rotateY(float _deg)
{
  float beta = (_deg/180.0f) * M_PI;
  float sr = sin(beta);
  float cr = cos(beta);
  identity();
  m_00 = cr;
  m_02 = sr;
  m_20 = -sr;
  m_22 = cr;
}

void Mat4::rotateZ(float _deg)
{
  float beta = (_deg/180.0f) * M_PI;
  float sr = sin(beta);
  float cr = cos(beta);
  identity();
  m_00 = cr;
  m_01 = -sr;
  m_10 = sr;
  m_11 = cr;
}

void Mat4::transpose()
{
  Mat4 t(*this);

  for(int i=0; i<4; i++)
  {
    for(int j=0; j<4; j++)
    {
      m_m[j][i] = t.m_m[i][j];
    }
  }
}

void Mat4::operator *=( Vec4 &_r) const
{
  Vec4 temp(0.0f);
  temp.m_w = 0.0f;

    for(int j=0;j<4;j++)
    {
      for(int i=0;i<4;i++)
      {
        temp.m_openGL[j] += (m_m[i][j] * _r.m_openGL[i]);

      }
    }
    _r=temp;

  //return temp;
}

void Mat4::loadModelView() const
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(&m_openGL[0]);
}

void Mat4::loadProjection() const
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(&m_openGL[0]);
}
