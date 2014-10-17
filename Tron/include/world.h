/// \file world.h
/// \brief draws world/arena and handles menu's
/// \author George Madges
/// \version 1.0
/// \date 03/04/2014

#ifndef WORLD_H
#define WORLD_H
#include <SDL.h>
#ifdef LINUX
    #include <GL/gl.h>
#endif
#ifdef DARWIN
    #include <OpenGL/gl.h>
#endif

#define W_MENU      0
#define W_PLAY1_WIN 1
#define W_PLAY2_WIN 2
#define W_CRASHED   3


class World
{
    private:
      /// @brief texture iD's
      GLuint texID[5];

      /**
       * @brief loadTexture
       * @param filename
       * @param texID to be linked to the file passed
       */
      void loadTexture(const char *filename,const GLuint texID) const;

      /// @brief Draw a display
      /// @param texture id for menus
      void drawDisplay(const GLuint ID) const;

    public:

      /// @brief enums to make it easier to know which texid you're using. Must be loaded in this order.
      enum textureIDs {FLOOR, WALL,MENU,PLAY1WIN,PLAY2WIN,CRASH};

      /// @brief m_width
      GLfloat m_width;

      /// @brief m_depth
      GLfloat m_depth;

      /// @brief m_height
      GLfloat m_height;

      /**
       * @brief World ctor
       * @param _size
       * @param _h
       */
      World(GLfloat _size=300.0f,GLfloat _h=100.0f):
        m_width(_size),
        m_depth(_size),
        m_height(_h){;}

      /// @brief drawWalls
      void drawWalls() const;

      /// @brief drawFloor
      void drawFloor() const;

      /// @brief loadTextures
      void loadTextures();

      /**
       * @brief displays menu/screens
       * @param window
       * @param type - what needs to be displayed(enum)
       * @return True, False
       */
      bool display(SDL_Window *window,const int type) const;

};

#endif // WORLD_H
