#pragma once
#include <stdint.h>
#include <fstream>
#include <vector>
#include "headers.hpp"
#include "colorTupple.hpp"
#include "BitMapFactory.hpp"


/*#pragma pack(push,1)*/

namespace BitMapManipulator {
/*
const uint16_t BMPmagic = ((uint16_t)'B') + (((uint16_t)'M') << 8); //BM
const uint16_t Size0fDIBHeader = 40;
struct Header {

    uint16_t signature;
    uint32_t sizeOfFile;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetPixelArray;


public:

void fromfStream(std::ifstream& imageFile) {
    
    imageFile.read((char *) this,sizeof(Header));
    if (!imageFile) {
        return; //exception
    }
    if (signature != BMPmagic) {
        return; //exception
    }
    size_t pos = imageFile.tellg();
    imageFile.seekg(0, std::ios::end);
    size_t end = imageFile.tellg();
    imageFile.seekg(pos, std::ios::beg);
    if (sizeOfFile != end) {
            return; //exception
    }
    
    
}
       
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
    
void fromfStream(std::ifstream& imageFile) {
    
    imageFile.read((char *) this, sizeof(DIBHeader));
    if (!imageFile) {
        return; //exception
    }
    if(this->sizeOfHeader != sizeof(*this)) {
        return; //exception
    }
    if (this->bitesPerPixel != 8 && this->bitesPerPixel != 24) {
        return; //exception
    }
    if (compressionIndex1 != 0 || compressionIndex2 != 0 || constant != 1) {
        return; //exception
    }
    if (this->colorsInColorPallete != 0 && this->bitesPerPixel != 8) {
        return; //exception
    }

}


};

struct colorTupple {

    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t pedding;
};


#pragma pack(pop)
*/

class bitMap8Bits;
class bitMap24Bits;

class bitMapAbstract{

protected:
    typedef std::vector<colorTupple> ColorPalleteType;
    typedef std::vector<uint8_t> IntensityType;

private:
    Header headerInfo;
    DIBHeader DIBHeaderInfo;
    ColorPalleteType colorPallete;
    IntensityType byteArray;


public:
    bitMapAbstract(const Header& headerInfo, const DIBHeader& DIBHeaderInfo) 
    : headerInfo(headerInfo), DIBHeaderInfo(DIBHeaderInfo) {
    }

    void fromFile(std::ifstream& imageFile);

    void toFile(const std::string imagePath);
    

    size_t getHeight() const;

    size_t getWidth() const;

    ColorPalleteType& getColorPallete();

    size_t getBytesPerPIxel();

    IntensityType& getBitMapArray();

    size_t virtual getColorPalleteSize() const = 0;
};

class bitMap8Bits : public bitMapAbstract {
private:
    const size_t ColorPalleteSize = 256;
public:
    bitMap8Bits(const Header& header, const DIBHeader& dibHeader)
    :bitMapAbstract::bitMapAbstract(header, dibHeader) {
    }

    size_t virtual getColorPalleteSize() const {
        return ColorPalleteSize;
    }

};

class bitMap24Bits : public bitMapAbstract {
private:
    const size_t ColorPalleteSize = 0;
public:
    bitMap24Bits(const Header& header, const DIBHeader& dibHeader)
    :bitMapAbstract::bitMapAbstract(header, dibHeader) {
    }

    size_t virtual getColorPalleteSize() const {
        return ColorPalleteSize;
    }


};

/*class BitMapFactory {
public:
    static std::unique_ptr<bitMapAbstract> fromFile(const std::string& imagePath) {

        std::ifstream imageFile;
        imageFile.open(imagePath, std::ios::binary);
        if (!imageFile.is_open()) {
           return nullptr; // write an exception class
        }

        Header header;
        DIBHeader dibInfo;
        
        header.fromfStream(imageFile);
        dibInfo.fromfStream(imageFile);

        size_t bitsPerPixel = dibInfo.bitesPerPixel;
        std::unique_ptr<bitMapAbstract> bitMap = nullptr;

        if (bitsPerPixel == 8) {
            bitMap = std::unique_ptr<bitMap8Bits>{new bitMap8Bits(header, dibInfo)};
            //bitMap = std::make_unique<bitMap8Bits>(header, dibInfo, imageFile);
        } else if (bitsPerPixel == 24) {
            bitMap = std::unique_ptr<bitMap24Bits>{new bitMap24Bits(header, dibInfo)};
            //bitMap = std::make_unique<bitMap24Bits>(header, dibInfo, imageFile);
        } else {
            return nullptr; // write an exception class
        }
        bitMap->fromFile(imageFile);
        return bitMap;
    }


};
*/




}