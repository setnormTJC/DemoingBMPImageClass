#include "BMPImage.h"
#include <iostream>
#include <fstream>

Color::Color()
	: r(0), g(0), b(0)
{
}

Color::Color(float _r, float _g, float _b)
	: r(_r), g(_g), b(_b)
{
}

Color::~Color()
{
}

BMPImage::BMPImage(int _width, int _height)
	: width(_width), height(_height), colors(std::vector<Color>(width* height))
{
}

BMPImage::~BMPImage()
{
}

Color BMPImage::getColor(int _x, int _y) const
{
	return colors[_y * width + _x];
}

void BMPImage::setColor(const Color& _color, int _x, int _y)
{
	colors[_y * width + _x].r = _color.r;
	colors[_y * width + _x].g = _color.g;
	colors[_y * width + _x].b = _color.b;
}

/*If curious about this func. def., consult:
https://www.youtube.com/watch?v=vqT5j38bWGg
*/
void BMPImage::ExportBMPFile(const char* _path) const
{
	std::ofstream output;
	output.open(_path, std::ios::out | std::ios::binary);

	if (!output.is_open())
	{
		std::cout << "File could not be opened...\n";
		return;
	}

	unsigned char tempPad[3] = { 0, 0, 0 };
	const int padding = ((4 - (width * 3) % 4) % 4);

	const int fileHeaderSize = 14;
	const int informationHeaderSize = 40;
	const int fileSize = fileHeaderSize + informationHeaderSize + width * height * 3 + padding * height;

	unsigned char fileHeader[fileHeaderSize];

	// file type
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';

	// file size
	fileHeader[2] = fileSize;
	fileHeader[3] = fileSize >> 8;
	fileHeader[4] = fileSize >> 16;
	fileHeader[5] = fileSize >> 24;

	// reserved 1 (not used)
	fileHeader[6] = 0;
	fileHeader[7] = 0;

	// reserved 1 (not used)
	fileHeader[8] = 0;
	fileHeader[9] = 0;

	// pixel data offset
	fileHeader[10] = fileHeaderSize + informationHeaderSize;
	fileHeader[11] = 0;
	fileHeader[12] = 0;
	fileHeader[13] = 0;

	unsigned char informationHeader[informationHeaderSize];

	// header size
	informationHeader[0] = informationHeaderSize;
	informationHeader[1] = 0;
	informationHeader[2] = 0;
	informationHeader[3] = 0;

	// image width
	informationHeader[4] = width;
	informationHeader[5] = width >> 8;
	informationHeader[6] = width >> 16;
	informationHeader[7] = width >> 24;

	// image height
	informationHeader[8] = height;
	informationHeader[9] = height >> 8;
	informationHeader[10] = height >> 16;
	informationHeader[11] = height >> 24;

	// planes
	informationHeader[12] = 1;
	informationHeader[13] = 0;

	// bits per pixel 
	informationHeader[14] = 24;
	informationHeader[15] = 0;

	// compression (none)
	informationHeader[16] = 0;
	informationHeader[17] = 0;
	informationHeader[18] = 0;
	informationHeader[19] = 0;

	// image size (no compression)
	informationHeader[20] = 0;
	informationHeader[21] = 0;
	informationHeader[22] = 0;
	informationHeader[23] = 0;

	// x pixels per meter (not specified)
	informationHeader[24] = 0;
	informationHeader[25] = 0;
	informationHeader[26] = 0;
	informationHeader[27] = 0;

	// y pixels per meter (not specified)
	informationHeader[28] = 0;
	informationHeader[29] = 0;
	informationHeader[30] = 0;
	informationHeader[31] = 0;

	// total colors (color pallete not used)
	informationHeader[32] = 0;
	informationHeader[33] = 0;
	informationHeader[34] = 0;
	informationHeader[35] = 0;

	// important colors (generally ignored)
	informationHeader[36] = 0;
	informationHeader[37] = 0;
	informationHeader[38] = 0;
	informationHeader[39] = 0;

	output.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
	output.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			unsigned char r = static_cast<unsigned char>(getColor(x, y).r * 255.0f);
			unsigned char g = static_cast<unsigned char>(getColor(x, y).g * 255.0f);
			unsigned char b = static_cast<unsigned char>(getColor(x, y).b * 255.0f);

			unsigned char color[] = { b, g, r }; //NOTE the somewhat atypical order

			output.write(reinterpret_cast<char*>(color), 3);
		}


		output.write(reinterpret_cast<char*>(tempPad), padding);
	}

	output.close();

	std::cout << "File created and closed, it is located in the project repository \n";
}
