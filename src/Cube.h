#ifndef VBOCUBE_H
#define VBOCUBE_H

#include "Drawable.h"

class Cube: public Drawable
{

private:
    unsigned int vaoHandle;

public:
    Cube();

    void render();
};

#endif // VBOCUBE_H
