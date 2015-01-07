#include "drawable.h"

class Triangle: public Drawable
{
public:
	Triangle();

	virtual void render();

	virtual ~Triangle();

private:
	unsigned int vaoHandle;
};