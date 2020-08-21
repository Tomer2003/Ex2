#include <stdint.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>


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

void fromfStream(std::ifstream& imageFile) {
    
    imageFile.read((char *) this,sizeof(Header));
    if (!imageFile) {
        return; /*exception*/
    }
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
    
void fromfStream(std::ifstream& imageFile) {
    
    imageFile.read((char *) this,sizeof(DIBHeader));
    if (!imageFile) {
        return; /*exception*/
    }
    if(this->sizeOfHeader != sizeof(*this)) {
          return; /*exception*/
    }
    if (this->colorsInColorPallete != 0 && this->bytesPerPixel != 8) {
         return; /*exception*/
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

#pragma pack(pop)
class bitMapAbstract{


protected:
    typedef std::vector<colorTupple> ColorPalleteType;
    typedef std::vector<uint8_t> IntensityType;

private:
    Header headerInfo;
    DIBHeader DIBHeaderInfo;
    ColorPalleteType collorPallete;
    IntensityType byteArray;


public:
    bitMapAbstract(const Header& headerInfo, const DIBHeader& DIBHeaderInfo, std::ifstream& imageFile) 
    : headerInfo(headerInfo), DIBHeaderInfo(DIBHeaderInfo) {
        this->fromFile(imageFile);
    }


    static /*bitMapAbstract&*/ void fromFile(const std::string& imagePath) {

        std::ifstream imageFile;
        imageFile.open(imagePath, std::ios::binary);
        if (!imageFile.is_open()) {
           return; /* write an exception class*/
        }

        Header header;
        DIBHeader dibInfo;
        
        header.fromfStream(imageFile);

        dibInfo.fromfStream(imageFile);

        size_t bitsPerPixel = dibInfo.bytesPerPixel;
        std::unique_ptr<bitMapAbstract> bitMap = nullptr;
        if (bitsPerPixel == 8) {
            bitMap = std::make_unique<bitMap8Bits>(header, dibInfo, imageFile);
        } else if (bitsPerPixel == 24) {
            bitMap = std::make_unique<bitMap24Bits>(header, dibInfo, imageFile);
        } else {
            return; /* write an exception class*/
        }
    
    }

    void fromFile(std::ifstream& imageFile) {

        size_t colorPalleteSize = this->getColorPaleeteSize();
        ColorPalleteType& colorPallete = getColorPallete();
        colorPallete.resize(colorPalleteSize);
        
        imageFile.read((char *) &colorPallete[0], colorPalleteSize * sizeof(colorTupple));
        if (!imageFile) {
            return; /*exception*/
        }
        
        size_t width = this->getWidth();
        size_t height = this->getHeight();
        size_t bytesPerPixel = this->getBytesPerPIxel();
        IntensityType& bitMapArray = getBitMapArray();

        bitMapArray.resize(height * width * bytesPerPixel);
        for(size_t row = 0; row < height; ++row) {
            imageFile.read((char *) &bitMapArray[width * row], width);
            size_t pos = imageFile.tellg();
            imageFile.seekg(4 - (width % 4), std::ios_base::cur);
        }
    }

    size_t getHeight() const{
        return this->DIBHeaderInfo.height;
    }
    size_t getWidth() const{
        return this->DIBHeaderInfo.width;
    }
    ColorPalleteType& getColorPallete() {
        return collorPallete;
    }
    size_t getBytesPerPIxel() const {
        return this->DIBHeaderInfo.bytesPerPixel;
    }
    IntensityType& getBitMapArray() {
        return this->byteArray;
    }
    size_t virtual getColorPaleeteSize() const = 0;
};

class bitMap8Bits : public bitMapAbstract {
private:
    const size_t ColorPalleteSize = 256;
public:
    bitMap8Bits(const Header& header, const DIBHeader& dibHeader, std::ifstream& imageFile)
    :bitMapAbstract::bitMapAbstract(header, dibHeader, imageFile) {
    }

    size_t virtual getColorPaleeteSize() const {
        return ColorPalleteSize;
    }

};

class bitMap24Bits : public bitMapAbstract {
private:
    typedef pixel24Bits pixelType;
    const size_t ColorPalleteSize = 0;
public:
    bitMap24Bits(const Header& header, const DIBHeader& dibHeader, std::ifstream& imageFile)
    :bitMapAbstract::bitMapAbstract(header, dibHeader, imageFile) {
    }

    size_t virtual getColorPaleeteSize() const {
        return ColorPalleteSize;
    }


};




}