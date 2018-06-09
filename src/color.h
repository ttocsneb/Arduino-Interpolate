#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

class SignedColor;

/**
 * This is used primarily for the Interpolate class if you need to interpolate colors.
 * 
 * I use it for color interpolation with NeoPixels, so it has a function that makes it 
 * easier to send color to the NeoPixel class: Color::to32()
 * 
 * There is a signed version of this class which is used for subtraction in the interpolate class.
 * I may in the future add more operators for more advanced color operations, but for now, there 
 * is just enough for the Interpolate class.
 * 
 * You may use this class as a template for creating your own interpolateable classes.  I found that
 * if your class is unsigned, you will need to have a signed version for interpolation to work properly
 * 
 */
class Color {
public:

    uint8_t r;
    uint8_t g;
    uint8_t b;

    /**
     * Create a new Color object
     * 
     * @param r red
     * @param g green
     * @param b blue
     */
    Color(uint8_t r=0, uint8_t g=0, uint8_t b=0);

    /**
     * Converts the Color object to a uint32_t type.
     * 
     * This can be used with the Adafruit NeoPixel library
     * 
     * @return Color compatible with NeoPixels
     */
    uint32_t to32();

    //These operators are intended for the Interpolate class.

    Color operator+(const Color &opperand);
    SignedColor operator-(const Color &opperand);
    Color operator*(const float f);

};

/**
 * The SignedColor class is used for subtraction in the Interpolation class
 * 
 * The interpolation class, when moving down, will at some point be negative.
 * standard numbers are fine as they are normally are casted to singed numbers, 
 * but the color class needs an equivelent singed class to work properly.
 * 
 */
class SignedColor {
public:
    int16_t r;
    int16_t g;
    int16_t b;

    operator Color() const;
    SignedColor operator+(SignedColor &b);
    SignedColor operator+(Color &b);
    SignedColor operator-(SignedColor &b);
    SignedColor operator-(Color &b);
    SignedColor operator*(const float f);
};


#endif