#ifndef VBOTORUS_H
#define VBOTORUS_H

#include "drawable.h"

class Torus : public Drawable
{
private:
    unsigned int vaoHandle;
    int faces, rings, sides;

    void generateVerts(float * , float * ,float *, unsigned int *,
                       float , float);

public:
    Torus(float, float, int, int);

    void render() const;
};

#endif // VBOTORUS_H
