#include "BMPinformation.hpp"


namespace BitMapManipulation {

void fromFile(std::ifstream& imageFile) {
        
        size_t colorPalleteSize = 0;
        if (DIBHeaderInfo.colorsInColorPallete == 0) {
        colorPalleteSize = this->getColorPalleteSize();
        } else {
        colorPalleteSize = DIBHeaderInfo.colorsInColorPallete;
        }

        /*ColorPalleteType& colorPallete = getColorPallete();
        colorPallete.resize(colorPalleteSize);*/
        colorPallete.resize(colorPalleteSize);

        if (!imageFile) {
            return; /*exception*/
        }
        imageFile.read((char *) &colorPallete[0], colorPalleteSize * sizeof(colorTupple));

        size_t width = this->getWidth();
        size_t height = this->getHeight();
        size_t bytesPerPixel = this->getBytesPerPIxel();
        /*IntensityType& bitMapArray = getBitMapArray();*/

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

    void toFile(const std::string imagePath) {
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

        for (int row = 0; row < height; ++row) {
            imageFile.write((char*) &byteArray[row * width * bytesPerPixel], width * bytesPerPixel);
            imageFile.write(pedding, peddingPerLine);////////////////////////////////////////////////
        }
        
    }

    size_t getHeight() {
        return this->DIBHeaderInfo.height;
    }
    size_t getWidth() {
        return this->DIBHeaderInfo.width;
    }
    ColorPalleteType& getColorPallete() {
        return colorPallete;
    }
    size_t getBytesPerPIxel()  {
        return this->DIBHeaderInfo.bitesPerPixel / 8;
    }
    IntensityType& getBitMapArray() {
        return this->byteArray;
    }
};
















}
