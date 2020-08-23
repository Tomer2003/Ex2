#include "bmp_tester.hpp"
#include "BitMapFactory.hpp"
#include "BitMap.hpp"

void rotate_image(const std::string& imagePath, const std::string& outputPath) {

BitMap::bitMapAbstract* bitMap = Factory::BitMapFactory::fromFile("lena-color.bmp");
bitMap->rotate90Degrees();
bitMap->toFile(outputPath);


}
void convert_to_grayscale(const std::string& imagePath, const std::string& outputPath) {

BitMap::bitMapAbstract* bitMap = Factory::BitMapFactory::fromFile("lena-color.bmp");
BitMap::bitMapAbstract::convertToGray(bitMap);
bitMap->toFile(outputPath);


}



