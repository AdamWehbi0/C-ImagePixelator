#pragma once
#include "CImg.h"
using namespace cimg_library;

class Simple_Image
{
public:
	Simple_Image(int, int);
	~Simple_Image();
	void set_point(int, int, const unsigned char[]);
	void fill(const unsigned char color[]);
	Simple_Image operator+(const Simple_Image&) const;
	Simple_Image operator-(const Simple_Image&) const;
	void save(const char *);
	void display();

private:
	unsigned char*** pixels;
	int x;
	int y;
	CImg<unsigned char> toCImg();
};

