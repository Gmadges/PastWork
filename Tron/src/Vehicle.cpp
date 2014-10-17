///
///  @file camera.cpp
///  @brief functions used by camera class.

#include "Vehicle.h"
#include "Vec4.h"
#include "Mat4.h"
#ifdef LINUX
    #include <GL/gl.h>
#endif
#ifdef DARWIN
    #include <OpenGL/gl.h>
#endif

Vehicle::Vehicle(Vec4 _pos, float _rot, int _BColour, int _TColour)
{
    m_speed = 1.5f;

    m_dir.set(0.0f,0.0f,-(m_speed));

    Mat4 tmp;
    tmp.rotateY(_rot);

    tmp*=m_dir;

    m_pos = _pos;
    m_rotate = _rot;

    switch(_BColour)
    {
    case V_RED:       m_bikeColour.set(1,0,0);break;
    case V_GREEN:     m_bikeColour.set(0,1,0);break;
    case V_BLUE:      m_bikeColour.set(0,0,1);break;
    case V_PINK:      m_bikeColour.set(1,0,1);break;
    case V_YELLOW:    m_bikeColour.set(1,1,0);break;
    case V_LIGHT_BLUE:m_bikeColour.set(0,1,1);break;
    case V_WHITE:     m_bikeColour.set(1,1,1);break;
    case V_PURPLE:    m_bikeColour.set(0.5,0,0.5);break;
    case V_ORANGE:    m_bikeColour.set(1,0.5,0);break;
    default:          m_bikeColour.set(0,0,1);break;
    }

    switch(_TColour)
    {
    case V_RED:       m_trailColour.set(1,0,0);break;
    case V_GREEN:     m_trailColour.set(0,1,0);break;
    case V_BLUE:      m_trailColour.set(0,0,1);break;
    case V_PINK:      m_trailColour.set(1,0,1);break;
    case V_YELLOW:    m_trailColour.set(1,1,0);break;
    case V_LIGHT_BLUE:m_trailColour.set(0,1,1);break;
    case V_WHITE:     m_trailColour.set(1,1,1);break;
    case V_PURPLE:    m_trailColour.set(0.5,0,0.5);break;
    case V_ORANGE:    m_trailColour.set(1,0.5,0);break;
    default:          m_trailColour.set(0,1,1);break;
    }
}
/*
void Vehicle::speedUp()
{
    if(m_speed <= 3)
    {
        m_speed*1.5f;
        m_dir*1.5f;
    }
}
*/
void Vehicle::turn(float type)
{
    // converts float to int for easier comparision
    int intType = (int)type;
    int intRotate = (int)m_rotate;

    //makes sure that the same button isnt pressed twice
    //or that the player tries to go back the way they came.
    if(intType == intRotate     ||
       intType-180 == intRotate ||
       intType+180 == intRotate   ) {return;}

    Mat4 tmp;

    //reset direction
    m_dir.m_x = 0.0f;
    m_dir.m_y = 0.0f;
    m_dir.m_z = -m_speed;

    //then rotate
    tmp.rotateY(type);
    m_rotate = type;
    tmp*=m_dir;

    //rotates bounding box
    Vehicle::updateBBox();

}

void Vehicle::createBBoxData()
{
    //convert float to int for easier checking
    int intRotate = (int)m_rotate;

    //initialise or crash
    m_bBox.maxX = 0.0f;
    m_bBox.minX = 0.0f;
    m_bBox.maxZ = 0.0f;
    m_bBox.minX = 0.0f;

    //check though all verts and grab the max and mins
    for(unsigned int i=0; i<m_vertices.size(); i++)
    {
      //tried using else if's for slight optimization but it through up bugs.
      if(m_vertices[i].m_z > m_bBox.maxZ) {m_bBox.maxZ = m_vertices[i].m_z;}
      if(m_vertices[i].m_z < m_bBox.minZ) {m_bBox.minZ = m_vertices[i].m_z;}

      if(m_vertices[i].m_x > m_bBox.maxX) {m_bBox.maxX = m_vertices[i].m_x;}
      if(m_vertices[i].m_x < m_bBox.minX) {m_bBox.minX = m_vertices[i].m_x;}
    }

    //updates the bBox values depending on the start direction of the vehicle.
    if(intRotate == 90 || intRotate == -90) {Vehicle::updateBBox();}

}

void Vehicle::updateBBox()
{

    //flips the values around to rotate the shape of the bbox.
    float tmp;
    tmp = m_bBox.maxZ;
    m_bBox.maxZ = m_bBox.maxX;
    m_bBox.maxX = tmp;

    tmp = m_bBox.minZ;
    m_bBox.minZ = m_bBox.minX;
    m_bBox.minX = tmp;
}

void Vehicle::drawTrail() const
{
  //height of trail
  float h = 4.0f;
  //offset in width for the top strip
  float offset = 0.3f;

  //draw the tail as a triangle strip
  glPushMatrix();
    m_trailColour.colourGL();
    glNormal3f(0,0,-1);
    glNormal3f(0,0,1);
    glBegin(GL_TRIANGLE_STRIP);
    for(unsigned int i = 0; i < m_trailPos.size(); i+=1)
    {
        glVertex3fv(m_trailPos[i].m_openGL);
        glVertex3f( m_trailPos[i].m_x,
                    m_trailPos[i].m_y+4,
                    m_trailPos[i].m_z);
    }
    glEnd();
  glPopMatrix();

  //draw two strips on top so it can be seen from above and behind
  glPushMatrix();
    m_trailColour.colourGL();
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0,1,0);
    for(unsigned int i = 0; i < m_trailPos.size(); i+=1)
    {
        glVertex3f( m_trailPos[i].m_x+offset,
                    m_trailPos[i].m_y+h,
                    m_trailPos[i].m_z);
        glVertex3f( m_trailPos[i].m_x-offset,
                    m_trailPos[i].m_y+h,
                    m_trailPos[i].m_z);
    }
    glEnd();
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0,1,0);
    for(unsigned int i = 0; i < m_trailPos.size(); i+=1)
    {
        glVertex3f( m_trailPos[i].m_x,
                    m_trailPos[i].m_y+h,
                    m_trailPos[i].m_z+offset);
        glVertex3f( m_trailPos[i].m_x,
                    m_trailPos[i].m_y+h,
                    m_trailPos[i].m_z-offset);
    }
    glEnd();
  glPopMatrix();


}

void Vehicle::drawVehicle() const
{
/*
  glEnableClientState(GL_VERTEX_ARRAY);
  //glEnableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  //glNormalPointer(GL_FLOAT, 0, &normals[0]);
  //glTexCoordPointer(3,GL_FLOAT,0,&uvPoints);

  glDrawArrays(GL_TRIANGLES, 0, num);

  //glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  */


//couldnt get drawArrays working
//so I iterate through and draw each triangle seperatley
  glPushMatrix();
  m_bikeColour.colourGL();

    glTranslatef(m_pos.m_x,m_pos.m_y,m_pos.m_z);

    glRotatef(m_rotate, 0,1,0);
    glBegin(GL_TRIANGLES);
    for(unsigned int i = 0; i < m_vertices.size(); i++)
    {
      glVertex3fv(m_vertices[i].m_openGL);
      glNormal3fv(m_normals[i].m_openGL);

    }
    glEnd(); // GL_TRIANGLES
  glPopMatrix();
}

//the same as the ctor
void Vehicle::set(Vec4 _pos, float _rot, int _BColour, int _TColour)
{
  m_speed = 1.5f;

  m_dir.set(0.0f,0.0f,-(m_speed));

  Mat4 tmp;
  tmp.rotateY(_rot);

  tmp*=m_dir;

  m_pos = _pos;
  m_rotate = _rot;

  switch(_BColour)
  {
  case V_RED:       m_bikeColour.set(1,0,0);break;
  case V_GREEN:     m_bikeColour.set(0,1,0);break;
  case V_BLUE:      m_bikeColour.set(0,0,1);break;
  case V_PINK:      m_bikeColour.set(1,0,1);break;
  case V_YELLOW:    m_bikeColour.set(1,1,0);break;
  case V_LIGHT_BLUE:m_bikeColour.set(0,1,1);break;
  case V_WHITE:     m_bikeColour.set(1,1,1);break;
  case V_PURPLE:    m_bikeColour.set(0.5,0,0.5);break;
  case V_ORANGE:    m_bikeColour.set(1,0.5,0);break;
  default:          m_bikeColour.set(0,0,1);break;
  }

  switch(_TColour)
  {
  case V_RED:       m_trailColour.set(1,0,0);break;
  case V_GREEN:     m_trailColour.set(0,1,0);break;
  case V_BLUE:      m_trailColour.set(0,0,1);break;
  case V_PINK:      m_trailColour.set(1,0,1);break;
  case V_YELLOW:    m_trailColour.set(1,1,0);break;
  case V_LIGHT_BLUE:m_trailColour.set(0,1,1);break;
  case V_WHITE:     m_trailColour.set(1,1,1);break;
  case V_PURPLE:    m_trailColour.set(0.5,0,0.5);break;
  case V_ORANGE:    m_trailColour.set(1,0.5,0);break;
  default:          m_trailColour.set(0,1,1);break;
  }

}



