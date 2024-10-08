#pragma once

#include <vector>

struct Color
{
	float r;
	float g;
	float b;

	Color();
	Color(float _r, float _g, float _b);
	~Color();

};

class BMPImage
{
public:
	BMPImage(int _width, int _height);
	~BMPImage();

	Color getColor(int _x, int _y) const;
	void setColor(const Color& _color, int _x, int _y);

	void ExportBMPFile(const char* _path) const; //when a function header ends with semicolon
	//that is a function DECLARATION (not a defintion) 

private:
	int width;
	int height;
	std::vector<Color> colors; //use of "composition" 
	//BMP image is composed of (at least one) Color 

};

