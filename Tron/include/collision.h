/// \file collision.h
/// \brief class that handles collision checks.
/// \author George Madges
/// \version 1.0
/// \date 03/04/2014


#ifndef COLLISION_H
#define COLLISION_H

#ifdef LINUX
    #include <GL/gl.h>
#endif
#ifdef DARWIN
    #include <OpenGL/gl.h>
#endif

#include <vector>
#include "Vehicle.h"
#include "world.h"

class Collision
{

  private:
    /**
     * @brief setBBoxValues
     * @brief function that updates the bounding box
     * @brief based on the position of the vehicle.
     * @param Vehicle for it position
     * @return returns updated bounding box data.
     */
    bBoxData setBBoxValues(const Vehicle &_V) const;
    /**
     * @brief checkTrailIntersect
     * @brief checks whether a vehicle and trail are intersecting.
     * @param Trail
     * @param Vehicle
     * @return bool. True for intersection, else false.
     */
    bool checkTrailIntersect(const std::vector<Vec4> &_trail,const Vehicle &_V) const;
    /**
     * @brief checkWorldIntersect
     * @brief checks whether Vehicle is out of bounds
     * @param World
     * @param Vehicle
     * @return bool. True for out of bounds, else false.
     */
    bool checkWorldIntersect(const World &_W,const Vehicle &_V) const;
    /**
     * @brief checkVehicleIntersect
     * @param Vehicle 1
     * @param Vehicle 2
     * @return bool. True for intersection, else false.
     */
    bool checkVehicleIntersect(const Vehicle &_V1, const Vehicle &_V2) const;

  public:

    /// @brief ctor.
    Collision();
    /**
     * @brief checkAllIntersect
     * @brief Encapsulates other functions, for use with singleplayer.
     * @param World
     * @param Vehicle
     * @return
     */
    bool checkAllIntersect(const World &_W,const Vehicle &_V) const;
    /**
     * @brief checkPlayerIntersect
     * @brief For use with multiplayer
     * @param World
     * @param Vehicle 1
     * @param Vehicle 2
     * @return
     */
    bool checkPlayerIntersect(const World &_W,const Vehicle &_V1,const Vehicle &_V2) const;
};

#endif // COLLISION_H
