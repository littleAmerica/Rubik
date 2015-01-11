

class Interpolation
{
public:
	virtual void interpolate(int currentTime) = 0;
	virtual bool isValid(int currentTime) = 0;
	virtual ~Interpolation(){};
};