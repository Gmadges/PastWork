#ifndef WALLTRAIL_H
#define WALLTRAIL_H
#ifdef LINUX
    #include <GL/gl.h>
#endif
#ifdef DARWIN
    #include <OpenGL/gl.h>
#endif

#include "Vec4.h"
#include <vector>

class WallTrail
{
    private:


    public:
    


        void DrawTrail();
        void AddTrail(Vec4 newPos);

};

#endif // WALLTRAIL_H
