#include "BitMapFactory.hpp"
#include "Headers.hpp"
#include <iostream>
#include <fstream>
namespace Factory{
BitMap::BitMapAbstract* BitMapFactory::fromFile(const std::string& imagePath){
       std::ifstream imageFile;
        imageFile.open(imagePath, std::ios::in);
        if (imageFile.fail()) {
           std::cout << "error!" << std::endl;
           return nullptr; //////return exception!!!!!!!!!!!!!!!!!!!!!
        }

        Headers::Header header;
        Headers::DIBHeader dibInfo;
        
        header.fromfStream(imageFile);
        dibInfo.fromfStream(imageFile);

        size_t bitsPerPixel = dibInfo.bitesPerPixel;
        BitMap::BitMapAbstract* bitMap = nullptr;

        if (bitsPerPixel == 8) {
            bitMap = new BitMap::BitMap8Bits(header, dibInfo);
        } else if (bitsPerPixel == 24) {
            bitMap = new BitMap::BitMap24Bits(header, dibInfo);
        } else {
            //return nullptr;  write an exception class!!!!!!!!!!!!!!!!!!!!!!
        }
        
        bitMap->fromFile(imageFile);
        return bitMap;
}
}