
#include "BitMapFactory.hpp"

namespace BitMapManipulator {


std::unique_ptr<bitMapAbstract> BitMapFactory::fromFile(const std::string& imagePath) {

        std::ifstream imageFile;
        imageFile.open(imagePath, std::ios::binary);
        if (!imageFile.is_open()) {
           return nullptr; /* write an exception class*/
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
            return nullptr; /* write an exception class*/
        }
        bitMap->fromFile(imageFile);
        return bitMap;
    }

}
