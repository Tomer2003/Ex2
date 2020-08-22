#include <memory>
#include <cstring>
#include "BMPinformation.hpp"



namespace BitMapManipulator {
    
typedef std::vector<colorTupple> ColorPalleteType;
typedef std::vector<uint8_t> IntensityType;


void bitMapAbstract::fromFile(std::ifstream& imageFile) {
        
        size_t colorPalleteSize = 0;
        if (DIBHeaderInfo.colorsInColorPallete == 0) {
        colorPalleteSize = this->getColorPalleteSize();
        } else {
        colorPalleteSize = DIBHeaderInfo.colorsInColorPallete;
        }

        colorPallete.resize(colorPalleteSize);

        if (!imageFile) {
            return; /*exception*/
        }
        imageFile.read((char *) &colorPallete[0], colorPalleteSize * sizeof(colorTupple));

        size_t width = this->getWidth();
        size_t height = this->getHeight();
        size_t bytesPerPixel = this->getBytesPerPIxel();
        

        byteArray.resize(height * width * bytesPerPixel);
        size_t peddingPerLine = 0;
        if (width % 4 != 0) {
            peddingPerLine = 4 - (width % 4);
        }

        int positionInFile = imageFile.tellg();
        if (this->headerInfo.offsetPixelArray != positionInFile) {
            return; /*exception*/
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

        if ((headerInfo.signature != BMPmagic) || (DIBHeaderInfo.sizeOfHeader != Size0fDIBHeader)) {
            return; /* write an exception class*/
        }

        imageFile.write((char*) &headerInfo, sizeof(Header));
        imageFile.write((char*) &DIBHeaderInfo, sizeof(DIBHeader));
        size_t collorPalleteSize = colorPallete.size();
        if (collorPalleteSize > 0) {
            imageFile.write((char*) &colorPallete[0], sizeof(colorTupple) * collorPalleteSize);
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

        if (imageFile.tellp() != headerInfo.offsetPixelArray) {
             return; /* write an exception class*/
        }
        for (int row = 0; row < height; ++row) {
            imageFile.write((char*) &byteArray[row * width * bytesPerPixel], width * bytesPerPixel);
            imageFile.write(pedding, peddingPerLine);
        }
        
    }

    size_t bitMapAbstract::getHeight() const{
        return this->DIBHeaderInfo.height;
    }
    size_t bitMapAbstract::getWidth() const{
        return this->DIBHeaderInfo.width;
    }
    ColorPalleteType& bitMapAbstract::getColorPallete() {
        return colorPallete;
    }
    size_t bitMapAbstract::getBytesPerPIxel() const{
        return this->DIBHeaderInfo.bitesPerPixel / 8;
    }
    IntensityType& bitMapAbstract::getBitMapArray() {
        return this->byteArray;
    }

    void bitMapAbstract::setHeight(size_t height) {
        DIBHeaderInfo.height = height;
    }
    void bitMapAbstract::setWidth(size_t width) {
        DIBHeaderInfo.width = width;
    }

    void bitMapAbstract::rotate90Degrees() {
        IntensityType tempByteArray;
        tempByteArray.resize(byteArray.size());
        size_t height = DIBHeaderInfo.height;
        size_t width = DIBHeaderInfo.width;
        size_t bytesPerPixel = DIBHeaderInfo.bitesPerPixel / 8;
        setHeight(width);
        setWidth(height);

        //rotating the matix of the pixels by 90 degrees
        //the calculations inside the for switch the locations of the pixels inside the matrix
        for (int row = 0; row < width; ++row) {
            for (int col = 0; col < height; ++col) {
                uint8_t* src = &byteArray[(col * width + width - row) * bytesPerPixel];
                uint8_t* des = &tempByteArray[(row * height + col) * bytesPerPixel];
                memcpy(des, src, bytesPerPixel);
            }
        }



    }




}