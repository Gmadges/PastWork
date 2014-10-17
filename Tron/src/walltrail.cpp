#include "WallTrail.h"
#include "Vec4.h"
#include "GLFunctions.h"
#include <iostream>
#ifdef LINUX
    #include <GL/gl.h>
#endif
#ifdef DARWIN
    #include <OpenGL/gl.h>
#endif

/*
WallTrail::WallTrail()
{
}
*/
void WallTrail::AddTrail(Vec4 newPos)
{
    m_trailPos.push_back(newPos.m_x);
    m_trailPos.push_back(newPos.m_y);
    m_trailPos.push_back(newPos.m_z);
}

void WallTrail::DrawTrail()
{
    glBegin(GL_TRIANGLE_STRIP);
    for(unsigned int i = 0; i < m_trailPos.size(); i+=3)
    {
        glVertex3f(  m_trailPos[i],
                     m_trailPos[i+1],
                     m_trailPos[i+2]);
        glVertex3f(  m_trailPos[i],
                     m_trailPos[i+1]+4,
                     m_trailPos[i+2]);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for(unsigned int i = 0; i < m_trailPos.size(); i+=3)
    {
        glVertex3f(  m_trailPos[i]+0.1f,
                     m_trailPos[i+1]+4,
                     m_trailPos[i+2]);
        glVertex3f(  m_trailPos[i]-0.1f,
                     m_trailPos[i+1]+4,
                     m_trailPos[i+2]);
    }
    glEnd();

}
