///
///  @file collision.cpp
///  @brief contains methods for Collision class.

#include "collision.h"
#include "Mat4.h"

Collision::Collision()
{
}

bBoxData Collision::setBBoxValues(const Vehicle &_V) const
{
  bBoxData tmp;

  //add current position to BBOX values
  tmp.maxX = _V.m_pos.m_x + _V.m_bBox.maxX;
  tmp.minX = _V.m_pos.m_x + _V.m_bBox.minX;
  tmp.maxZ = _V.m_pos.m_z + _V.m_bBox.maxZ;
  tmp.minZ = _V.m_pos.m_z + _V.m_bBox.minZ;

  return tmp;
}

bool Collision::checkTrailIntersect(const std::vector<Vec4> &_trail,const Vehicle &_V) const
{
  //crashes otherwise
  if(_trail.size() <=4){return false;}

  //updates values
  bBoxData tmpData = Collision::setBBoxValues(_V);

  //increments by two, because the vectors are saved in columns 2 at a time.
  //Don't check the last couple of values of the trail because
  //they are still within the bounding box.
  for(unsigned int i=0; i<_trail.size()-4; i+=2)
  {
    if((_trail[i].m_x > tmpData.minX) &&
       (_trail[i].m_x < tmpData.maxX) &&
       (_trail[i].m_z < tmpData.maxZ) &&
       (_trail[i].m_z > tmpData.minZ)   ) {return true;}
  }

  return false;
}

bool Collision::checkWorldIntersect(const World &_W, const Vehicle &_V) const
{
  //updates values
  bBoxData tmpData = Collision::setBBoxValues(_V);

  //Checks if Vehicle is out of bounds.
  if((tmpData.maxX > (_W.m_width/2.0f))  ||
     (tmpData.minX < -(_W.m_width/2.0f)) ||
     (tmpData.maxZ > (_W.m_depth/2.0f))  ||
     (tmpData.minZ < -(_W.m_depth/2.0f))   ) {return true;}

  return false;
}

bool Collision::checkVehicleIntersect(const Vehicle &_V1, const Vehicle &_V2) const
{
  //updates values
  bBoxData V1Bounds = Collision::setBBoxValues(_V1);
  bBoxData V2Bounds = Collision::setBBoxValues(_V2);


  //checks for intersections between rectangles.
  if( !(V1Bounds.minZ >= V2Bounds.maxZ ||
        V1Bounds.maxZ <= V2Bounds.minZ ||
        V1Bounds.minX >= V2Bounds.maxX ||
        V1Bounds.maxX <= V2Bounds.minX) ) { return true; }

  return false;
}

bool Collision::checkAllIntersect(const World &_W,const Vehicle &_V) const
{
  bool state = false;
  //check world
  if     (Collision::checkWorldIntersect(_W, _V)) {state = true;}
  //check trails
  else if(Collision::checkTrailIntersect(_V.m_trailPos, _V)) {state = true;}

  return state;
}

bool Collision::checkPlayerIntersect(const World &_W,const Vehicle &_Player1,const Vehicle &_Player2) const
{
  bool state = false;
  //check world
  if     (Collision::checkWorldIntersect(_W, _Player1)) {state = true;}
  //check trails
  else if(Collision::checkTrailIntersect(_Player1.m_trailPos, _Player1)) {state = true;}
  else if(Collision::checkTrailIntersect(_Player1.m_trailPos, _Player2)) {state = true;}
  //check other player
  else if(Collision::checkVehicleIntersect(_Player1, _Player2)) {state = true;}
  return state;
}

