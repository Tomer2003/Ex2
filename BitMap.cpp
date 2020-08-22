#include "BitMap.hpp"
#include <cstring>
namespace BitMap{
    bitMapAbstract::bitMapAbstract(const Headers::Header& headerInfo, const Headers::DIBHeader& DIBHeaderInfo)
    : headerInfo(headerInfo), DIBHeaderInfo(DIBHeaderInfo){ }


    void bitMapAbstract::fromFile(std::ifstream& imageFile) {
          size_t colorPalleteSize = 0;
        if (DIBHeaderInfo.colorsInColorPallete == 0) {
        colorPalleteSize = this->getColorPalleteSize();
        } else {
        colorPalleteSize = DIBHeaderInfo.colorsInColorPallete;
        }

        /*ColorPalleteType& colorPallete = getColorPallete();
        colorPallete.resize(colorPalleteSize);*/
        colorPallete.resize(colorPalleteSize);

        int i = imageFile.tellg();//////
        imageFile.read((char *) &colorPallete[0], colorPalleteSize * sizeof(Headers::colorTupple));
        if (!imageFile) {
            return; /*exception*/
        }
        i = imageFile.tellg();///////
        size_t width = this->getWidth();
        size_t height = this->getHeight();
        size_t bytesPerPixel = this->getBytesPerPIxel();
        /*IntensityType& bitMapArray = getBitMapArray();*/

        byteArray.resize(height * width * bytesPerPixel);
        size_t peddingPerLine = 0;
        if (width % 4 != 0) {
            peddingPerLine = 4 - (width % 4);
        }

        for(size_t row = 0; row < height; ++row) {
            imageFile.read((char *) &byteArray[width * row * bytesPerPixel], width * bytesPerPixel);
            size_t pos = imageFile.tellg();//////
            imageFile.seekg(peddingPerLine, std::ios_base::cur);
        }
    }

    
    void bitMapAbstract::toFile(const std::string imagePath) {
        std::ofstream imageFile;
        imageFile.open(imagePath, std::ios::binary | std::ios::trunc);
        if (!imageFile.is_open()) {
           return; /* write an exception class*/
        }

        if ((headerInfo.signature != Headers::BMPmagic) || (DIBHeaderInfo.sizeOfHeader != Headers::Size0fDIBHeader)) {
            return; /* write an exception class*/
        }

        imageFile.write((char*) &headerInfo, sizeof(Headers::Header));
        imageFile.write((char*) &DIBHeaderInfo, sizeof(Headers::DIBHeader));
        size_t collorPalleteSize = colorPallete.size();
        if (collorPalleteSize > 0) {
            imageFile.write((char*) &colorPallete[0], sizeof(Headers::colorTupple) * collorPalleteSize);
        }

        size_t width = this->getWidth();
        size_t height = this->getHeight();
        size_t bytesPerPixel = this->getBytesPerPIxel();
        
        //max size of the pedding each line is 3 bytes
        const char pedding[3] = {0, 0, 0};
        size_t peddingPerLine = 0;
        if (width % 4 != 0) {
            peddingPerLine = 4 - (width % 4);
        }

        for (int row = 0; row < height; ++row) {
            imageFile.write((char*) &byteArray[row * width * bytesPerPixel], width * bytesPerPixel);
            imageFile.write(pedding, peddingPerLine);////////////////////////////////////////////////
        } 
    }

    void bitMapAbstract::setBitMapWidth(const uint32_t width){
        DIBHeaderInfo.width = width;
    }

    void bitMapAbstract::setBitMapHeight(const uint32_t height){
        DIBHeaderInfo.height = height;
    }

    void bitMapAbstract::rotate90Degrees() {
        IntensityType tempByteArray;
        tempByteArray.resize(byteArray.size());
        size_t height = DIBHeaderInfo.height;
        size_t width = DIBHeaderInfo.width;
        size_t bytesPerPixel = DIBHeaderInfo.bitesPerPixel / 8;
        setBitMapHeight(width);
        setBitMapWidth(height);

        //rotating the matix of the pixels by 90 degrees
        //the calculations inside the for switch the locations of the pixels inside the matrix
        for (int row = 0; row < width; ++row) {
            for (int col = 0; col < height; ++col) {
                uint8_t* src = &byteArray[(col * width + width - row) * bytesPerPixel];
                uint8_t* des = &tempByteArray[(row * height + col) * bytesPerPixel];
                memcpy(des, src, bytesPerPixel);
            }
        }
        memcpy(&byteArray[0], &tempByteArray[0], byteArray.size());
    }

    size_t bitMapAbstract::getHeight() const{
        return this->DIBHeaderInfo.height;
    }
    size_t bitMapAbstract::getWidth() const{
        return this->DIBHeaderInfo.width;
    }
    bitMapAbstract::ColorPalleteType& bitMapAbstract::getColorPallete() {
        return this->colorPallete;
    }
    size_t bitMapAbstract::getBytesPerPIxel() const {
        return this->DIBHeaderInfo.bitesPerPixel / 8;
    }
    bitMapAbstract::IntensityType& bitMapAbstract::getBitMapArray() {
        return this->byteArray;
    }

    uint8_t bitMapAbstract::getRGBToGray(const uint8_t blue, const uint8_t green, const uint8_t red) const {
        double result = (0.2126) * red + (0.7152) * green + (0.0722) * blue;
        return (uint8_t)result;
    }

    bitMap8Bits::bitMap8Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader)
    :bitMapAbstract::bitMapAbstract(header, dibHeader){}

    size_t bitMap8Bits::getColorPalleteSize() const {
        return ColorPalleteSize;
    }

    void bitMap8Bits::convertToGray(){
        ColorPalleteType& theColorPallete = getColorPallete();
        for (Headers::colorTupple& colorPallete : theColorPallete) {
            uint8_t result = getRGBToGray(colorPallete.blue, colorPallete.green, colorPallete.red);
            colorPallete.blue = result;
            colorPallete.green = result;
            colorPallete.red = result;
        }
    }

    bitMap24Bits::bitMap24Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader)
    :bitMapAbstract::bitMapAbstract(header, dibHeader) {}

    size_t bitMap24Bits::getColorPalleteSize() const {
        return ColorPalleteSize;
    }

    void bitMap24Bits::convertToGray() {
        size_t height = getHeight();
        size_t width = getWidth();
        size_t bytesPerPixel = getBytesPerPIxel();
        IntensityType& BitmapArray = getBitMapArray();
        for (int row = 0; row < height ; ++row) {
            for (int col = 0; col < width * bytesPerPixel; col +=3) {
                uint8_t blue = BitmapArray[(row * width) *  bytesPerPixel + col];
                uint8_t green = BitmapArray[(row * width) * bytesPerPixel + col + 1];
                uint8_t red = BitmapArray[(row * width) * bytesPerPixel + col + 2];

                uint8_t result = getRGBToGray(blue, green, red);
                BitmapArray[(row * width) * bytesPerPixel + col] = result;
                BitmapArray[(row * width) * bytesPerPixel + col + 1] = result;
                BitmapArray[(row * width) * bytesPerPixel + col + 2] = result;
            }
        }
    }
}