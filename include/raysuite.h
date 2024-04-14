#ifndef RAYSUITE_H
#define RAYSUITE_H

#include <stddef.h>

#include <raylib.h>

typedef Color Colour;

#ifndef RAYSUITE_NO_MATH
    #include <raymath.h>

    #define SINE(x) ((sinf ((float)x) + 1.0f) / 2.0f)
#endif

#ifndef RAYSUITE_NO_GUI
    #include <raygui.h>
#endif

#endif // RAYSUITE_H
