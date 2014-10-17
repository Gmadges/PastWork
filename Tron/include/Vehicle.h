/// \file Vehicle.h
/// \brief contains all function needed for vehicles in game.
/// \author George Madges
/// \version 1.0
/// \date 03/04/2014

#ifndef VEHICLE_H
#define VEHICLE_H
#ifdef LINUX
    #include <GL/gl.h>
#endif
#ifdef DARWIN
    #include <OpenGL/gl.h>
#endif

#include "Vec4.h"
#include <vector>

#define V_UP      0.0f
#define V_DOWN   -180.0f
#define V_LEFT   -90.0f
#define V_RIGHT   90.0f

#define V_RED         0
#define V_GREEN       1
#define V_BLUE        2
#define V_PINK        3
#define V_YELLOW      4
#define V_LIGHT_BLUE  5
#define V_WHITE       6
#define V_PURPLE      7
#define V_ORANGE      8


/**
 * @brief The bBoxData struct
 * @brief a struct to store the maximum values of the obj model in X and Z axis.
 */
struct bBoxData
{
  /// @brief maxX
  float maxX;
  /// @brief minX
  float minX;
  /// @brief maxZ
  float maxZ;
  /// @brief minZ
  float minZ;
};

class Vehicle
{    

  private:

    /// @brief Vec4 stores colour of bike
    Vec4 m_bikeColour;

    /// @brief Vec4 stores colour of trail
    Vec4 m_trailColour;

    /// @brief direction of vehicle
    Vec4 m_dir;

    /// @brief m_speed
    float m_speed;

    /// @brief rotation(degrees) of bike
    float m_rotate;
    //bool boost;

    /// @brief Adds more points to trail
    inline void addTrail() {m_trailPos.push_back(m_pos);}

    /// @brief Updates bounding box for when the vehicle is rotated.
    void updateBBox();

  public:

    /// @brief m_pos
    Vec4 m_pos;

    /// @brief m_bBox
    bBoxData m_bBox;

    /// @brief m_trailPos
    std::vector<Vec4> m_trailPos;

    /// @brief m_vertices
    std::vector<Vec4> m_vertices;
    /// @brief m_normals
    std::vector<Vec4> m_normals;
    /// @brief m_uvs
    std::vector<Vec4> m_uvs;

    /**
     * @brief Vehicle ctor
     * @param _pos - set initial position
     * @param _rot - set initial rotation
     * @param _BColour - set colour of bike
     * @param _TColour - set colour of trail
     */
    Vehicle(Vec4 _pos, float _rot, int _BColour, int _TColour);

    /**
     * @brief set values of Vehicle
     * @param _pos - set position
     * @param _rot - set rotation
     * @param _BColour - set bike colour
     * @param _TColour - set trail colour
     */
    void set(Vec4 _pos, float _rot, int _BColour, int _TColour);

    /// @brief move
    inline void move()      {m_pos += m_dir; Vehicle::addTrail();}
    //void speedUp();

    /// @brief turn
    /// @param _type
    void turn(float _type);

    /// @brief drawVehicle
    void drawVehicle() const;

    /// @brief createBBoxData
    void createBBoxData();

    /// @brief drawTail
    void drawTrail() const;

    //void jump();

    /// @brief getDir
    /// @return direction
    inline Vec4 getDir() const    {return m_dir;  }
    //inline int getMass()  {return m_mass; }

    /// @brief getSpeed
    /// @return speed
    inline float getSpeed() const {return m_speed;}

};


#endif // VEHICLE_H
