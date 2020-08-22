#pragma once
#include <stdint.h>
#include <iostream>
#include <fstream>

#pragma pack(push,1)

namespace BitMapManipulator {

const uint16_t BMPmagic = ((uint16_t)'B') + (((uint16_t)'M') << 8); //BM
const uint16_t Size0fDIBHeader = 40;

struct Header {

    uint16_t signature;
    uint32_t sizeOfFile;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetPixelArray;


public:

void fromfStream(std::ifstream& imageFile);
       
};

struct DIBHeader
{

    uint32_t sizeOfHeader;
    uint32_t width;
    uint32_t height;
    uint16_t constant;
    uint16_t bitesPerPixel;
    uint32_t compressionIndex1;
    uint32_t compressionIndex2;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t colorsInColorPallete;
    uint32_t reserved3;

public: 
    
void fromfStream(std::ifstream& imageFile);

};


}

#pragma pack(pop)

