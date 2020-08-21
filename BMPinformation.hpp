#include <stdint.h>
#include <iostream>
#include <fstream>

#pragma pack(push,1)

namespace reader {

const uint16_t BMPmagic = ((uint16_t)'B') + (((uint16_t)'M') << 8);
struct Header {

    uint16_t signature;
    uint32_t sizeOfFile;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetPixelArray;


public:

void fromFile(std::ifstream& imageFile) {
    
    imageFile.read((char *) this,sizeof(Header));

    if (signature != BMPmagic) {
        return; /*exception*/
    }
    size_t pos = imageFile.tellg();
    imageFile.seekg(0, std::ios::end);
    size_t end = imageFile.tellg();
    imageFile.seekg(pos, std::ios::beg);
    if (sizeOfFile != end) {
            return; /*exception*/
    }
    
    
}
       
};

struct DIBHeader
{

    uint32_t sizeOfHeader;
    uint32_t width;
    uint32_t height;
    uint16_t constant;
    uint16_t bytesPerPixel;
    uint32_t compressionIndex1;
    uint32_t compressionIndex2;
    uint32_t reserved1;
    uint32_t reserved2;
    uint32_t colorsInColorPallete;
    uint32_t reserved3;

public: 
    
void fromFile(std::ifstream& imageFile) {
    
    imageFile.read((char *) this,sizeof(DIBHeader));
    if(this->sizeOfHeader != sizeof(*this)) {
          return; /*exception*/
    }
    if (this->colorsInColorPallete != 0 && this->bytesPerPixel != 8) {
         return; /*exception*/
    }
    if (this->colorsInColorPallete == 8) {
        if (this->bytesPerPixel == 0) {
            this->colorsInColorPallete = 2 ^ this->bytesPerPixel;
        }
    }
    
}


};

struct colorTupple {

    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t pedding;
};

struct fullColorPixel
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;

};
struct pixelAbstract
{

};

struct pixel24Bits : public pixelAbstract
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct pixel8Bits : public pixelAbstract
{
    uint8_t intensity;
};

const size_t palleteSize8Bits = 256;

template <size_t T> struct CollorPallete
{
    colorTupple pallete[T];
};

typedef struct CollorPallete<palleteSize8Bits> CollorPallete8Bits;

#pragma pack(pop)
class bitMapAbstract{

private:
    Header headerInfo;
    DIBHeader DIBHeaderInfo;
    CollorPallete8Bits* pointerPallete = nullptr;
    pixelAbstract* bitMapArray = nullptr;

public:
    static /*bitMapAbstract&*/ void fromFile(const std::string& imagePath) {

        std::ifstream imageFile;
        imageFile.open(imagePath, std::ios::binary);
        if (!imageFile.is_open()) {
           return; /* write an exception class*/
        }

        Header header;
        DIBHeader dibInfo;
        
        header.fromFile(imageFile);

        dibInfo.fromFile(imageFile);
        
       
    }

};

class bitMap8Bits : public bitMapAbstract {

    typedef pixel8Bits pixelType;
};

class bitMap24Bits : public bitMapAbstract {

    typedef pixel24Bits pixelType;
};




}