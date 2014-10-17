/// \file Vec4.h
/// \brief a 4d Homogenous Point / Vector object
/// \author George Madges
/// \version 1.0
/// \date 03/04/2014

#ifndef VEC4_H__
#define VEC4_H__
#include <ostream>

class Vec4
{
  public :
    /// @brief ctor
    /// @param [in] _x the x value default is 0.
    /// @param [in] _y the x value default is 0.
    /// @param [in] _z the x value default is 0.
    /// @param [in] _w the x value default is 1.
    Vec4(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=1.0f) :
      m_x(_x), m_y(_y), m_z(_z), m_w(_w){;}


    /// @brief method to print attributes.
    void print() const;

    /// @brief method to find length of vector.
    float length() const;

    /// @brief length ^2.
    float lengthSquared() const;

    /// @brief normalize the vector.
    void normalize();

    /// @brief dot product of vectors.
    float dot(const Vec4 &_b) const;

    /// @brief dot product of vectors(C style).
    float dot(const Vec4 &_a, const Vec4 &_b) const;

    /// @brief cross product of vectors.
    /// @param [in] _b the vector to cross with.
    /// @returns a new vector this cross _b.
    Vec4 cross(const Vec4 &_b) const;

    Vec4 operator *(float _rhs) const;
    Vec4 operator +(const Vec4 &_rhs) const;
    Vec4 operator -(const Vec4 &_rhs) const;

    void operator *=(float _rhs);
    void operator +=(const Vec4 &_rhs);
    void operator -=(const Vec4 &_rhs);

    bool operator ==(const Vec4 &_rhs) const;

    void colourGL() const;
    void normalGL() const;
    void vertexGL() const;

    /// @brief Set Vector values.
    void set(float _x, float _y, float _z);

    union
    {
      struct
      {
        /// @brief the x element of the vector
        float m_x;
        /// @brief the y element of the vector
        float m_y;
        /// @brief the z element of the vector
        float m_z;
        /// @brief the w element of the vector
        float m_w;
      };
      float m_openGL[4];
    };
};

std::ostream & operator<<(std::ostream &_output, const Vec4 &_v);



#endif
