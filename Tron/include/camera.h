/// \file camera.h
/// \brief class for camera functions
/// \author George Madges
/// \version 1.0
/// \date 03/04/2014

#ifndef CAMERA_H
#define CAMERA_H

#include "GLFunctions.h"
#include "Vehicle.h"
#include "world.h"

class Camera
{

private:

    /// @brief m_camPos
    Vec4 m_camPos;

    /// @brief m_offset
    float m_offset;

public:
    /**
     * @brief Camera ctor
     * @brief set default to 150.
     * @param _offset
     */
    Camera(float _offset=150.0f):
        m_offset(_offset){;}

    /**
     * @brief SetCameraFollow
     * @param [in] _V is the vehicle that the camera follow.
     */
    void setCameraFollow(const Vehicle &_V);
    /**
     * @brief MultiplayerCam
     * @brief Sets the camera to a suitable position/angle to view both players.
     * @param [in] _W world class.
     */
    void multiplayerCam(const World &_W);


};

#endif // CAMERA_H
