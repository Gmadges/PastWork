///
///  @file camera.cpp
///  @brief functions used by camera class.

#include "world.h"
#include "Vec4.h"
#include "GLFunctions.h"
#include <SDL.h>
#include <SDL_image.h>
#ifdef LINUX
	#include <GL/gl.h>
#endif
#ifdef DARWIN
	#include <OpenGL/gl.h>
#endif

#include <iostream>

//the commented tops and bottoms are all relative
//to where i want the textures to be viewed from

void World::drawFloor() const
{
  //create a walls using quads

  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, texID[FLOOR]);

  //Half values to make it easier, because it is being placed round the origin
  GLfloat w= m_width/2.0f;
  GLfloat d=m_depth/2.0f;
  glPushMatrix();
    glBegin(GL_QUADS);
      // Bottom face
      glNormal3f(0,1,0);
      //bottom left
      glTexCoord2i(0,1);  glVertex3f(-w,0,d);
      //top left
      glTexCoord2i(0,0);  glVertex3f(-w,0,-d);
      //bottom right
      glTexCoord2i(1,0);  glVertex3f(w,0,-d);
      //top right
      glTexCoord2i(1,1);  glVertex3f(w,0,d);
    glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void World::drawWalls() const
{
  //create a floor plane

  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, texID[FLOOR]);

  //Half values to make it easier, because it is being placed round the origin
  GLfloat w= m_width/2.0f;
  GLfloat h= m_height;
  GLfloat d=m_depth/2.0f;
  glPushMatrix();
    glBegin(GL_QUADS);

/*    Front wall ---------------
      glNormal3f(0,0,-1);
      //top left
      glTexCoord2i(0,0);  glVertex3f(-w,h,d);
      //top right
      glTexCoord2i(1,0);  glVertex3f(w,h,d);
      //bottom right
      glTexCoord2i(1,1);  glVertex3f(w,0,d);
      //bottom left
      glTexCoord2i(0,1);  glVertex3f(-w,0,d);
  */

      //Back wall ---------------
      glNormal3d(0,0,1);
      //top left
      glTexCoord2i(0,0);  glVertex3f(-w,h,-d);
      //top right
      glTexCoord2i(1,0);  glVertex3f(w,h,-d);
      //bottom right
      glTexCoord2i(1,1);  glVertex3f(w,0,-d);
      //bottom left
      glTexCoord2i(0,1);  glVertex3f(-w,0,-d);


      //Left wall ---------------
      glNormal3f(-1,0,0);
      //top left
      glTexCoord2i(0,0);  glVertex3f(-w,h,d);
      //top right
      glTexCoord2i(1,0);  glVertex3f(-w,h,-d);
      //bottom right
      glTexCoord2i(1,1);  glVertex3f(-w,0,-d);
      //bottom left
      glTexCoord2i(0,1);  glVertex3f(-w,0,d);


      //Right wall ---------------
      glNormal3f(1,0,0);
      //top left
      glTexCoord2i(0,0);  glVertex3f(w,h,-d);
      //top right
      glTexCoord2i(1,0);  glVertex3f(w,h,d);
      //bottom right
      glTexCoord2i(1,1);  glVertex3f(w,0,d);
      //bottom left
      glTexCoord2i(0,1);  glVertex3f(w,0,-d);

    glEnd();
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);

}

void World::loadTextures()
{

  glGenTextures(1, texID);

  World::loadTexture("textures/FloorTex.png", texID[0]);
  World::loadTexture("textures/WallTex.png", texID[1]);
  World::loadTexture("textures/Menu.png", texID[2]);
  World::loadTexture("textures/Player1WinTex.png", texID[3]);
  World::loadTexture("textures/Player2WinTex.png", texID[4]);
  World::loadTexture("textures/Crash.png", texID[5]);

}

void World::loadTexture(const char *filename,const GLuint texID) const
{

  //use SDL to load image.
  SDL_Surface *surface;
  int mode;

  surface = IMG_Load(filename);

  if (!surface)
  {
    std::cout<<"Error: Could not load image."<<"\n";
    return;
  }

  // check whether it has an alpha or not to change the mode.
  if (surface->format->BytesPerPixel == 3)      { mode = GL_RGB;  }
  else if (surface->format->BytesPerPixel == 4) { mode = GL_RGBA; }
  else
  {
    std::cout<<"Error: image is not 24byte or 32byte format."<<"\n";
    SDL_FreeSurface(surface);
    return;
  }

  //bind the image with the texture id.
  glBindTexture(GL_TEXTURE_2D, texID);

  glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

  //texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  //free the surface
  SDL_FreeSurface(surface);
}

// draw a quad and place texture on it.
void World::drawDisplay(const GLuint ID) const
{
    float h = 1;
    float w = 1;
    float d = 1;

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texID[ID]);

    glPushMatrix();
    glBegin(GL_QUADS);
        glNormal3d(0,0,1);
        //top left
        glTexCoord2i(0,0);  glVertex3f(-w,h,-d);
        //top right
        glTexCoord2i(1,0);  glVertex3f(w,h,-d);
        //bottom right
        glTexCoord2i(1,1);  glVertex3f(w,-h,-d);
        //bottom left
        glTexCoord2i(0,1);  glVertex3f(-w,-h,-d);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

//run a loop with with specific textured quad. Wait for specific input.
bool World::display(SDL_Window *window,const int type) const
{
    bool state= false;
    bool loop = false;
    SDL_Event event;
    Vec4 white(1,1,1);

      while(!loop)
      {
        while ( SDL_PollEvent(&event) )
        {
          switch (event.type)
          {
            // this is the window x being clicked.
            case SDL_QUIT : state = false; return false; break;
            // if the window is re-sized pass it to the ngl class to change gl viewport
            // note this is slow as the context is re-create by SDL each time

            // now we look for a keydown event
            case SDL_KEYDOWN:
            {
              switch(type)
                case W_MENU:
                {
                  switch(event.key.keysym.sym)
                  {
                    case SDLK_m : state = true;   return state; break;
                    case SDLK_s : state = false;  return state; break;
                  }
                }
                case W_PLAY1_WIN:
                {
                  switch(event.key.keysym.sym)
                  {
                    case SDLK_SPACE :  state = false;return state; break;
                    case SDLK_ESCAPE : state = true; return state; break;
                  }
                }
                case W_PLAY2_WIN:
                {
                  switch(event.key.keysym.sym)
                  {
                    case SDLK_SPACE :  state = false;return state; break;
                    case SDLK_ESCAPE : state = true; return state; break;
                  }
                }
                case W_CRASHED:
                {
                  switch(event.key.keysym.sym)
                  {
                    case SDLK_SPACE :  state = false;return state; break;
                    case SDLK_ESCAPE : state = true; return state; break;
                  }
                }
                default:break;
              } // end of keydown
            } // end of event switch
          } // end of poll events

        white.colourGL();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLFunctions::lookAt(Vec4(0,0,1),Vec4(0,0,0),Vec4(0,1,0));

        switch(type)
        {
          case W_MENU:      { World::drawDisplay(MENU);    break; }
          case W_PLAY1_WIN:  { World::drawDisplay(PLAY1WIN);break; }
          case W_PLAY2_WIN:  { World::drawDisplay(PLAY2WIN);break; }
          case W_CRASHED:   { World::drawDisplay(CRASH);   break; }
        }
        SDL_GL_SwapWindow(window);
    }

    return false;
}







