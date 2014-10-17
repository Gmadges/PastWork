# qt 5 wants this may cause errors with 4
isEqual(QT_MAJOR_VERSION, 5) {cache() }
QT += core
QT +=opengl
TARGET=SDLOpenGL
CONFIG-=app_bundle
DESTDIR=./
OBJECTS_DIR=obj
SOURCES=src/main.cpp \
        src/GLFunctions.cpp \
        src/Vec4.cpp \
        src/Mat4.cpp \
        src/Vehicle.cpp \
        src/world.cpp \
        src/ObjReader.cpp \
        src/camera.cpp \
        src/collision.cpp


HEADERS+=include/GLFunctions.h \
         include/Vec4.h \
         include/Mat4.h \
         include/Vehicle.h \
         include/world.h \
         include/ObjReader.h \
         include/camera.h \
         include/collision.h

# add the ngl lib
# this is where to look for includes
INCLUDEPATH +=include

QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64
linux-g++:QMAKE_CXXFLAGS +=  -march=native
linux-g++-64:QMAKE_CXXFLAGS +=  -march=native

QMAKE_CXXFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system(sdl2-config  --libs)
message(output from sdl2-config --libs added to LIB=$$LIBS)

LIBS+=-lSDL2_image

LIBS += -L/usr/local/lib
macx:LIBS+= -framework OpenGL
macx:DEFINES+=DARWIN
linux-*:DEFINES+=LINUX
# now if we are under unix and not on a Mac (i.e. linux) define GLEW
linux-g++:linux-g++-64 {
    DEFINES += LINUX
    LIBS+= -lGLEW
}
linux-clang {
    DEFINES += LINUX
    LIBS+= -lGLEW
}
