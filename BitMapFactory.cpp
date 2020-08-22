/*#include "BitMapFactory.hpp"
#include <iostream>
namespace Factory{
std::unique_ptr<BitMap::bitMapAbstract> BitMapFactory::fromFile(const std::string& imagePath){
        std::ifstream imageFile;
        imageFile.open(imagePath, std::ios::binary);
        if (!imageFile.is_open()) {
           return nullptr;  
        }

        Headers::Header header;
        Headers::DIBHeader dibInfo;
        
        header.fromfStream(imageFile);
        dibInfo.fromfStream(imageFile);

        size_t bitsPerPixel = dibInfo.bitesPerPixel;
        std::unique_ptr<BitMap::bitMapAbstract> bitMap = nullptr;

        if (bitsPerPixel == 8) {
            bitMap = std::unique_ptr<BitMap::bitMap8Bits>{new BitMap::bitMap8Bits(header, dibInfo)};
            //bitMap = std::make_unique<bitMap8Bits>(new BitMap::bitMap8Bits(header, dibInfo));
        } else if (bitsPerPixel == 24) {
            bitMap = std::unique_ptr<BitMap::bitMap24Bits>{new BitMap::bitMap24Bits(header, dibInfo)};
            //bitMap = std::make_unique<bitMap24Bits>(header, dibInfo, imageFile);
        } else {
            return nullptr;  
        }
        
        bitMap->fromFile(imageFile);
        return bitMap;
}
}
*/
#include "BitMapFactory.hpp"
#include <iostream>
#include <fstream>
namespace Factory{
BitMap::bitMapAbstract* BitMapFactory::fromFile(const std::string& imagePath){
        std::ifstream imageFile;
        imageFile.open(imagePath, std::ios::in);
        if (!imageFile.is_open()) {
           std::cout << "error!" << std::endl;
        }

        Headers::Header header;
        Headers::DIBHeader dibInfo;
        
        header.fromfStream(imageFile);
        dibInfo.fromfStream(imageFile);

        size_t bitsPerPixel = dibInfo.bitesPerPixel;
        BitMap::bitMapAbstract* bitMap = nullptr;

        if (bitsPerPixel == 8) {
            bitMap = new BitMap::bitMap8Bits(header, dibInfo);
            //bitMap = std::make_unique<bitMap8Bits>(new BitMap::bitMap8Bits(header, dibInfo));
        } else if (bitsPerPixel == 24) {
            bitMap = new BitMap::bitMap24Bits(header, dibInfo);
            //bitMap = std::make_unique<bitMap24Bits>(header, dibInfo, imageFile);
        } else {
            //return nullptr;  write an exception class
        }
        
        bitMap->fromFile(imageFile);
        return bitMap;
}
}