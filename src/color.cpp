#include "color.h"

#include <stdlib.h>

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

uint32_t Color::to32() {
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

#include <Arduino.h>

void Color::debug() {
    Serial.print("Color:");
    Serial.print(r);
    Serial.print(", ");
    Serial.print(g);
    Serial.print(", ");
    Serial.print(b);
    Serial.print(": ");
    Serial.println(to32(), 16);
}

//Operators

Color Color::operator+(const Color &o) {
    return Color(
        r + o.r,
        g + o.g,
        b + o.b
    );
}

SignedColor Color::operator-(const Color &o) {
    SignedColor c;
    c.r = r - o.r;
    c.g = g - o.g;
    c.b = b - o.b;
    return c;
}

Color Color::operator*(const float f) {
    return Color(
        r * f,
        g * f,
        b * f
    );
}

SignedColor::operator Color() const {
    return Color(abs(r), abs(g), abs(b));
}
SignedColor SignedColor::operator+(SignedColor &o) {
    SignedColor c;
    c.r = r + o.r;
    c.g = g + o.g;
    c.b = b + o.b;
    return c;
}
SignedColor SignedColor::operator+(Color &o) {
    SignedColor c;
    c.r = r + o.r;
    c.g = g + o.g;
    c.b = b + o.b;
    return c;
}
SignedColor SignedColor::operator-(SignedColor &o) {
    SignedColor c;
    c.r = r - o.r;
    c.g = g - o.g;
    c.b = b - o.b;
    return c;
}
SignedColor SignedColor::operator-(Color &o) {
    SignedColor c;
    c.r = r - o.r;
    c.g = g - o.g;
    c.b = b - o.b;
    return c;
}
SignedColor SignedColor::operator*(const float f) {
    SignedColor c;
    c.r = r * f;
    c.g = g * f;
    c.b = b * f;
    return c;
}