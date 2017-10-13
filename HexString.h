//
// Created by guinnrd on 9/26/2017.
//

#ifndef UNTITLED_HEXSTRING_H
#define UNTITLED_HEXSTRING_H

#include <iostream>
#include <cmath>

class HexString
{
private:
    int hexToInt(const char&);
    char intToHex(const int&);
    bool equalsZero(const HexString&);
    bool biggerThan(std::string);
public:
    std::string value;
    bool negative;

    HexString(std::string);
    HexString operator+(const HexString&);
    HexString operator-(const HexString&);
    HexString operator*(const HexString&);
    HexString operator&(const HexString&);
    HexString operator|(const HexString&);
    HexString operator^(const HexString&);
    std::string toString();
};

#endif //UNTITLED_HEXSTRING_H
