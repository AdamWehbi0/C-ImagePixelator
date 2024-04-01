#include "Simple_Image.h"

Simple_Image::Simple_Image(int x, int y) : x(x), y(y) {
    pixels = new unsigned char**[y]; // Allocate memory for each row.

    for(int i = 0; i < y; i++){
        pixels[i] = new unsigned char*[x]; // For each row, allocate memory for each column.

        for(int j = 0; j < x; j++){
            pixels[i][j] = new unsigned char[3]; // For each pixel, allocate memory for the RGB channels.

            for(int k = 0; k < 3; k++){
                pixels[i][j][k] = 0; // Initialize each RGB channel to 0 (black).
            }
        }
    }
}

Simple_Image::~Simple_Image() {
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            delete[] pixels[i][j]; // Free the memory allocated for each pixel's RGB values.
        }
        delete[] pixels[i]; // Free the memory allocated for each row.
    }
    delete[] pixels; // Finally, free the memory allocated for the rows array.
}

void Simple_Image::fill(const unsigned char color[]) {
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            for(int k = 0; k < 3; k++){
                pixels[i][j][k] = color[k]; // Set each pixel's RGB channels to the specified color.
            }
        }
    }
}

void Simple_Image::set_point(int x, int y, const unsigned char color[]) {
    for (int channel = 0; channel < 3; ++channel) {
        pixels[y][x][channel] = color[channel]; // Set the RGB values of the pixel at (x, y) to the specified color.
    }
}

Simple_Image Simple_Image::operator+(const Simple_Image& other) const {
    Simple_Image result(x, y); // Create a new image with the same dimensions.
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            for(int k = 0; k < 3; k++){
                int sum = pixels[i][j][k] + other.pixels[i][j][k]; // Add corresponding RGB values.
                result.pixels[i][j][k] = sum > 255 ? 255 : sum; // Clamp the sum to 255.
            }
        }
    }
    return result; // Return the resulting image.
}

Simple_Image Simple_Image::operator-(const Simple_Image& other) const {
    Simple_Image result(x, y); // Create a new image with the same dimensions.

    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            for(int k = 0; k < 3; k++){
                int diff = pixels[i][j][k] - other.pixels[i][j][k]; // Subtract corresponding RGB values.
                result.pixels[i][j][k] = diff < 0 ? 0 : diff; // Clamp the result to 0 to avoid underflow.
            }
        }
    }
    return result; // Return the resulting image.
}


CImg<unsigned char> Simple_Image::toCImg() {
	CImg<unsigned char> res(x,y,1,3,0);
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++) {
			res(i, j, 0) = pixels[i][j][0];
			res(i, j, 1) = pixels[i][j][1];
			res(i, j, 2) = pixels[i][j][2];
		}
	}
	return res;
}

void Simple_Image::save(const char* filename) {
	this->toCImg().save(filename);
}

void Simple_Image::display() {
	CImgDisplay disp(this->toCImg(), "Simple Image");
	while (!disp.is_closed()) {
		disp.wait();
	}
}
