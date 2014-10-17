///
///  @file camera.cpp
///  @brief functions used by camera class.

#include "Vec4.h"
#include <iostream>
#include <cmath>
#include <cassert>
#ifdef LINUX
	#include <GL/gl.h>
#endif
#ifdef DARWIN
	#include <OpenGL/gl.h>
#endif

void Vec4::print() const
{
  std::cout<<"["<<m_x<<","<<m_y<<","<<m_z<<","<<m_w<<"]\n";
}

float Vec4::length() const
{
  return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

float Vec4::lengthSquared() const
{
  return (m_x*m_x + m_y*m_y + m_z*m_z);
}

void Vec4::normalize()
{

  float l=length();
  assert(l != 0.0);
  m_x/=l;
  m_y/=l;
  m_z/=l;

}

float Vec4::dot(const Vec4 &_b) const
{
  return (m_x*_b.m_x + m_y*_b.m_y + m_z*_b.m_z);
}

float Vec4::dot(const Vec4 &_a, const Vec4 &_b) const
{
  return (_a.m_x*_b.m_x + _a.m_y*_b.m_y + _a.m_z*_b.m_z);
}


Vec4 Vec4::cross(const Vec4 &_b) const
{
  Vec4 v;

  v.m_x = ((m_y*_b.m_z) - (m_z*_b.m_y));
  v.m_y = ((m_z*_b.m_x) - (m_x*_b.m_z));
  v.m_z = ((m_x*_b.m_y) - (m_y*_b.m_x));
  v.m_w = 0.0f;

  return v;
}
void Vec4::set(float _x, float _y, float _z)
{
  m_x = _x;
  m_y = _y;
  m_z = _z;
}

Vec4 Vec4::operator *(float _rhs) const
{
  return Vec4(m_x*_rhs, m_y*_rhs, m_z*_rhs, m_w);
}

std::ostream & operator<<(std::ostream &_output, const Vec4 &_v)
{
  return _output<< "["<<_v.m_x<<","<<_v.m_y<<","<<_v.m_z<<","<<_v.m_w<<"]\n";
}

Vec4 Vec4::operator -(const Vec4 &_rhs) const
{
  return Vec4(m_x-_rhs.m_x, m_y-_rhs.m_y, m_z-_rhs.m_z, 0.0f);
}

Vec4 Vec4::operator +(const Vec4 &_rhs) const
{
  return Vec4(m_x+_rhs.m_x, m_y+_rhs.m_y, m_z+_rhs.m_z, 0.0f);
}

void Vec4::operator *=(float _rhs)
{
  m_x*=_rhs;
  m_y*=_rhs;
  m_z*=_rhs;
}

void Vec4::operator -=(const Vec4 &_rhs)
{
  m_x-=_rhs.m_x;
  m_y-=_rhs.m_y;
  m_z-=_rhs.m_z;
}

void Vec4::operator +=(const Vec4 &_rhs)
{
  m_x+=_rhs.m_x;
  m_y+=_rhs.m_y;
  m_z+=_rhs.m_z;
}

bool Vec4::operator ==(const Vec4 &_rhs) const
{
  const static float delta=0.0001f;
  return (
           (((m_x)-delta) <(_rhs.m_x)) && (((m_x)+delta) >(_rhs.m_x)) &&
           (((m_y)-delta) <(_rhs.m_y)) && (((m_y)+delta) >(_rhs.m_y)) &&
           (((m_z)-delta) <(_rhs.m_z)) && (((m_z)+delta) >(_rhs.m_z))
         );
}

void Vec4::colourGL() const
{
  glColor4f(m_x, m_y, m_z, m_w);
}

void Vec4::normalGL() const
{
  glNormal3f(m_x, m_y, m_z);
}

void Vec4::vertexGL() const
{
  glVertex3f(m_x, m_y, m_z);
}








