#include <SDL.h>
#include <SDL_image.h>
#ifdef LINUX
	#include <GL/gl.h>
#endif
#ifdef DARWIN
	#include <OpenGL/gl.h>
#endif

#include <iostream>
#include "GLFunctions.h"
#include "Vehicle.h"
#include "ObjReader.h"
#include "world.h"
#include "camera.h"
#include "collision.h"



/// @brief function to quit SDL with error message
/// @param[in] _msg the error message to send
void SDLErrorExit(const std::string &_msg);

/// @brief initialize SDL OpenGL context
SDL_GLContext createOpenGLContext( SDL_Window *window);

int main()
{   

    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
      // Or die on error
      SDLErrorExit("Unable to initialize SDL");
    }

    // now get the size of the display and create a window we need to init the video
    SDL_Rect rect;
    SDL_GetDisplayBounds(0,&rect);

    //initialize values for framerate stuff
    int FPS = 30;
    int interval = (1*1000)/FPS;
    unsigned int nextTick = 0;

    // now create our window#include <time.h>
    SDL_Window *window=SDL_CreateWindow("Behold! a poorly made Tron ripoff!",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        rect.w*0.75,
                                        rect.h*0.75,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                                       );
    // check to see if that worked or exit
    if (!window)
    {
      SDLErrorExit("Unable to create window");
    }

    // Create our opengl context and attach it to our window

     SDL_GLContext glContext=createOpenGLContext(window);
     if(!glContext)
     {
       SDLErrorExit("Problem creating OpenGL context");
     }
     // make this our current GL context (we can have more than one window but in this case not)
     SDL_GL_MakeCurrent(window, glContext);
    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);
    // now clear the screen and swap whilst NGL inits (which may take time)
    Vec4 white(1,1,1);

    glClear(GL_COLOR_BUFFER_BIT);
    GLFunctions::perspective(45,float(1024/720),0.01,300);

    SDL_GL_SwapWindow(window);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColor3f(1,1,0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);


    // flag to indicate if we need to exit
    bool quit=false;
    // sdl event processing data structure
    SDL_Event event;

    World arena(500,200.0f);
    arena.loadTextures();
    Collision engine;
    Camera cam1;
    Vehicle player1(Vec4(200,0,200),V_LEFT,V_BLUE,V_LIGHT_BLUE);
    Vehicle player2(Vec4(-200,0,-200),V_RIGHT,V_PURPLE,V_PINK);

    bool multiplayer = true;

    // now we create an instance of our ngl class, this will init NGL and setup basic
    // opengl stuff ext. When this falls out of scope the dtor will be called and cleanup
    // our gl stuff

    while(!quit)
    {
      multiplayer = arena.display(window, W_MENU);

      bool P1Collide = false;
      bool P2Collide = false;



      if(multiplayer)
      {
        player1.set(Vec4(200,0,200),V_LEFT,V_LIGHT_BLUE,V_BLUE);
        player2.set(Vec4(-200,0,-200),V_RIGHT,V_PURPLE,V_PINK);

        ObjReader obj1("models/TronBike2.2.obj");
        ObjReader obj2("models/TronBike2.2.obj");

        //need 2 different obj classes dont know why
        obj1.createArrays(player1.m_vertices,player1.m_normals,player1.m_uvs);
        obj2.createArrays(player2.m_vertices,player2.m_normals,player2.m_uvs);
        player1.createBBoxData();
        player2.createBBoxData();
      }
      else
      {
          player1.set(Vec4(0,0,0),V_UP,V_GREEN,V_ORANGE);

          ObjReader obj1("models/TronBike2.2.obj");

          obj1.createArrays(player1.m_vertices,player1.m_normals,player1.m_uvs);
          player1.createBBoxData();
      }

      bool gameOver = false;

      while(!gameOver)
      {
        if(multiplayer == true)
        {
          P1Collide = engine.checkPlayerIntersect(arena,player1,player2);
          if(P1Collide) {gameOver = P1Collide;}
          P2Collide = engine.checkPlayerIntersect(arena,player2,player1);
          if(P2Collide) {gameOver = P2Collide;}
        }
        else
        {
          P1Collide = engine.checkAllIntersect(arena, player1);
          gameOver = P1Collide;
        }


        while ( SDL_PollEvent(&event) )
        {
          switch (event.type)
          {
            // this is the window x being clicked.
            case SDL_QUIT : gameOver = true; quit = true;break;
            // if the window is re-sized pass it to the ngl class to change gl viewport
            // note this is slow as the context is re-create by SDL each time

            // now we look for a keydown event
            case SDL_KEYDOWN:
            {
              switch( event.key.keysym.sym )
              {
                // if it's the escape key quit
                case SDLK_ESCAPE :  gameOver = true; quit = true; break;
                case SDLK_1 : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
                case SDLK_2 : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
                case SDLK_UP :      player1.turn(V_UP); break;
                case SDLK_DOWN :    player1.turn(V_DOWN); break;
                case SDLK_LEFT :    player1.turn(V_LEFT); break;
                case SDLK_RIGHT :   player1.turn(V_RIGHT); break;
                //case SDLK_RSHIFT:   player1.speedUp();
                case SDLK_w :       player2.turn(V_UP); break;
                case SDLK_s :       player2.turn(V_DOWN); break;
                case SDLK_a :       player2.turn(V_LEFT); break;
                case SDLK_d :       player2.turn(V_RIGHT); break;
                //case SDLK_q :       player2.speedUp();
                default : break;
              } // end of key process
            } // end of keydown

            default : break;
          } // end of event switch
        } // end of poll events


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        white.colourGL();
        arena.drawFloor();

        white.colourGL();
        arena.drawWalls();

        // now draw etc
        player1.move();
        player1.drawVehicle();
        player1.drawTrail();

        if(multiplayer == true)
        {
          player2.move();
          player2.drawVehicle();
          player2.drawTrail();
        }

        //update camera
        //cam1.SetCameraFollow(player1);
        if(multiplayer) {cam1.multiplayerCam(arena);}
        else            {cam1.setCameraFollow(player1);}
        // swap the buffers
        SDL_GL_SwapWindow(window);

        //A framerate thing to hopefully make it smoother
        if (nextTick > SDL_GetTicks())
        {
            SDL_Delay(nextTick - SDL_GetTicks());
            nextTick = SDL_GetTicks() + interval;
        }

        }

      if(P1Collide && multiplayer ) {quit = arena.display(window,W_PLAY2_WIN);}
      if(P2Collide && multiplayer ) {quit = arena.display(window,W_PLAY1_WIN);}
      if(P1Collide && !multiplayer) {quit = arena.display(window,W_CRASHED);}
  }
  // now tidy up and exit SDL
 SDL_Quit();
}


SDL_GLContext createOpenGLContext(SDL_Window *window)
{
  // Request an opengl 3.2 context first we setup our attributes, if you need any
  // more just add them here before the call to create the context
  // SDL doesn't have the ability to choose which profile at this time of writing,
  // but it should default to the core profile
  // for some reason we need this for mac but linux crashes on the latest nvidia drivers
  // under centos
  #ifdef DARWIN
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  #endif
  // set multi sampling else we get really bad graphics that alias
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,2);
  // Turn on double buffering with a 24bit Z buffer.
  // You may need to change this to 16 or 32 for your system
  // on mac up to 32 will work but under linux centos build only 16
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  // enable double buffering (should be on by default)
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  //
  return SDL_GL_CreateContext(window);

}

void SDLErrorExit(const std::string &_msg)
{
  std::cerr<<_msg<<"\n";
  std::cerr<<SDL_GetError()<<"\n";
  SDL_Quit();
  exit(EXIT_FAILURE);
}


