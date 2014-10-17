///
///  @file camera.cpp
///  @brief methods used by camera class.

#include "camera.h"

void Camera::setCameraFollow(Vehicle const &_V)
{

  // Add the offset to the X and Y values
  m_camPos.m_x = _V.m_pos.m_x;
  m_camPos.m_y = _V.m_pos.m_y + m_offset;
  m_camPos.m_z = _V.m_pos.m_z + m_offset;

  //use lookAt to set cameras position
  GLFunctions::lookAt(m_camPos, _V.m_pos, Vec4(0,1,0));
}


void Camera::multiplayerCam(World const &_W)
{
  //uses the size of the world to set the cameras position
  //so that both players can be seen.
  m_camPos.set(0,(_W.m_width*1.3),(_W.m_depth*0.5));
  GLFunctions::lookAt(m_camPos, Vec4(0,0,0), Vec4(0,1,0));
}
