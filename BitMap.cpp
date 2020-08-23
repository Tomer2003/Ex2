#include "BitMap.hpp"
#include <cstring>
namespace BitMap{
    bitMapAbstract::bitMapAbstract(const Headers::Header& headerInfo, const Headers::DIBHeader& DIBHeaderInfo)
    : headerInfo(headerInfo), DIBHeaderInfo(DIBHeaderInfo){ }

    bitMapAbstract::bitMapAbstract(const Headers::Header& headerInfo, const Headers::DIBHeader& DIBHeaderInfo, ColorPalleteType& colorPallete,
     IntensityType& bitMapArray) : headerInfo(headerInfo), DIBHeaderInfo(DIBHeaderInfo), colorPallete(colorPallete), byteArray(bitMapArray){};

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

    const Headers::Header& bitMapAbstract::getHeader() const{
        return headerInfo;
    }

    const Headers::DIBHeader& bitMapAbstract::getDIBHeader() const{
        return DIBHeaderInfo;
    }

    size_t bitMapAbstract::getHeight() const{
        return DIBHeaderInfo.height;
    }
    size_t bitMapAbstract::getWidth() const{
        return DIBHeaderInfo.width;
    }
    bitMapAbstract::ColorPalleteType& bitMapAbstract::getColorPallete() {
        return colorPallete;
    }
    size_t bitMapAbstract::getBytesPerPIxel() const {
        return DIBHeaderInfo.bitesPerPixel / 8;
    }
    bitMapAbstract::IntensityType& bitMapAbstract::getBitMapArray() {
        return byteArray;
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

    bitMap8Bits::bitMap8Bits(Headers::Header& theNewHeader, Headers::DIBHeader& theNewDIBHeader, ColorPalleteType& theNewPallete,
    IntensityType& theNewBitMapArray) : bitMapAbstract(theNewHeader, theNewDIBHeader, theNewPallete, theNewBitMapArray){};

  /*  void bitMap8Bits::convertToGray(){
        ColorPalleteType& theColorPallete = getColorPallete();
        for (Headers::colorTupple& colorPallete : theColorPallete) {
            uint8_t result = getRGBToGray(colorPallete.blue, colorPallete.green, colorPallete.red);
            colorPallete.blue = result;
            colorPallete.green = result;
            colorPallete.red = result;
        }
    }*/

    bitMap24Bits::bitMap24Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader)
    :bitMapAbstract::bitMapAbstract(header, dibHeader) {}

    size_t bitMap24Bits::getColorPalleteSize() const {
        return ColorPalleteSize;
    }


    void bitMapAbstract::convertToGray(BitMap::bitMapAbstract* bitMap) {
        size_t colorPalleteSize8Bits = 256;
        size_t height = bitMap->getHeight();
        size_t width = bitMap->getWidth();
        size_t bytesPerPixel = bitMap->getBytesPerPIxel	();
        IntensityType& BitmapArray = bitMap->getBitMapArray();

        //initializing the gray-scale color pallete
        ColorPalleteType theNewPallete;
        theNewPallete.resize(colorPalleteSize8Bits);
        for (int i = 0; i < colorPalleteSize8Bits; ++i) {
            theNewPallete[i].red = i;
            theNewPallete[i].green = i;
            theNewPallete[i].blue = i;
        }

        //turning the bitmap  array into a 8 bits bitmapArray
        IntensityType theNewBitMapArray;
        theNewBitMapArray.resize(height * width);
        for (int row = 0; row < height ; ++row) {
            for (int col = 0; col < width * bytesPerPixel; col +=3) {
                uint8_t blue = BitmapArray[(row * width) *  bytesPerPixel + col];
                uint8_t green = BitmapArray[(row * width) * bytesPerPixel + col + 1];
                uint8_t red = BitmapArray[(row * width) * bytesPerPixel + col + 2];

                uint8_t result = bitMap->getRGBToGray(blue, green, red);
                //BitmapArray[(row * width) * bytesPerPixel + col] = result;
                //BitmapArray[(row * width) * bytesPerPixel + col + 1] = result;
                //BitmapArray[(row * width) * bytesPerPixel + col + 2] = result;
                theNewBitMapArray[row * width + (col / bytesPerPixel)] = result;
            }
        }

        //initializing the new header of the bitMap8Bits
        Headers::Header theNewHeader;
        theNewHeader.signature = Headers::BMPmagic;
        theNewHeader.sizeOfFile = sizeof(Headers::Header) + sizeof(Headers::DIBHeader) 
        + theNewPallete.size() * sizeof(Headers::colorTupple) + theNewBitMapArray.size();
        theNewHeader.reserved1 = bitMap->getHeader().reserved1;
        theNewHeader.reserved2 = bitMap->getHeader().reserved2;
        theNewHeader.offsetPixelArray = sizeof(Headers::Header) + sizeof(Headers::DIBHeader)
        + theNewPallete.size() * sizeof(Headers::colorTupple);

        //initializing the new DIBHeader of the bitMap8Bits
        Headers::DIBHeader theNewDIBHeader;
        theNewDIBHeader.sizeOfHeader = Headers::Size0fDIBHeader;
        theNewDIBHeader.height = bitMap->getDIBHeader().height;
        theNewDIBHeader.width = bitMap->getDIBHeader().width;
        theNewDIBHeader.bitesPerPixel = 8;
        theNewDIBHeader.compressionIndex1 = bitMap->getDIBHeader().compressionIndex1;
        theNewDIBHeader.compressionIndex2 = bitMap->getDIBHeader().compressionIndex2;
        theNewDIBHeader.reserved1 = bitMap->getDIBHeader().reserved1;
        theNewDIBHeader.reserved2 = bitMap->getDIBHeader().reserved2;
        theNewDIBHeader.colorsInColorPallete = 0;
        theNewDIBHeader.reserved3 = bitMap->getDIBHeader().reserved3;

        delete bitMap;
        bitMap = new bitMap8Bits(theNewHeader, theNewDIBHeader, theNewPallete, theNewBitMapArray);
        }
    }
