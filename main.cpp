#include <iostream>
#include "Simple_Image.h"

using namespace cimg_library;

int main()
{
	const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 }, black[] = { 0,0,0 }, white[] = { 255,255,255 }, gray[] = {128, 128, 128};

	Simple_Image simple_red(600, 600), simple_green(600, 600), simple_blue(600, 600);

	simple_red.fill(red);
	simple_green.fill(green);
	simple_blue.fill(blue);

	simple_red.save("Red.bmp");
	simple_green.save("Green.bmp");
	simple_blue.save("Blue.bmp");



    Simple_Image
    simple_magenta = simple_red + simple_blue, // Combine red and blue to make magenta
    simple_yellow = simple_red + simple_green, // Combine red and green to make yellow
    simple_cyan = simple_blue + simple_green;  // Combine blue and green to make cyan

// Save the composite color images to BMP files
    simple_magenta.save("Magenta.bmp");
    simple_yellow.save("Yellow.bmp");
    simple_cyan.save("Cyan.bmp");

// Create an image called stripes with dimensions 600x600
    Simple_Image stripes(600,600);
// Loop through each pixel in the stripes image

    for(int i = 0; i < 600;i++){
        for(int j = 0;j < 600;j++){
            // Set the left third of the image to red
            if (j < 200){
                stripes.set_point(i,j,red);
            }
                // Set the middle third of the image to green
            else if(j < 400 && j >= 200){
                stripes.set_point(i,j,green);
            }
                // Set the right third of the image to blue
            else{
                stripes.set_point(i,j,blue);
            }
        }
    }

// Save the stripes image to a BMP file
    stripes.save("Stripes.bmp");

// Creating variations of the stripes image by adding primary colors
    Simple_Image
    stripes_red = stripes + simple_red,    // Add red to the entire stripes image
    stripes_green = stripes + simple_green,// Add green to the entire stripes image
    stripes_blue = stripes + simple_blue;  // Add blue to the entire stripes image

// Save the modified stripes images to BMP files
    stripes_red.save("Red_Stripes.bmp");
    stripes_blue.save("Blue_Stripes.bmp");
    stripes_green.save("Green_Stripes.bmp");

// Create a gray image for later use in subtraction
    Simple_Image simple_gray(600,600);
    simple_gray.fill(gray); // Fill the entire image with gray color

// Create a faded version of the stripes_green image by subtracting gray
    Simple_Image faded = stripes_green - simple_gray;
// Save the faded image to a BMP file
    faded.save("Faded_Green_Stripes.bmp");


	return 0;
}