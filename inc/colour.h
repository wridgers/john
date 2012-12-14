#ifndef __COLOUR_H__
#define __COLOUR_H__

class Colour
{
public:
	Colour();
	Colour(int r, int g, int b);
	~Colour();

	int red, green, blue;
};

#endif