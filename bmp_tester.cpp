#include "bmp_tester.hpp"
#include "BitMapFactory.hpp"
#include "BitMap.hpp"

namespace testing {

namespace bmp{

void rotate_image(const std::string& imagePath, const std::string& outputPath) {

BitMap::BitMapAbstract* bitMap = Factory::BitMapFactory::fromFile(imagePath);
bitMap->rotate90Degrees();
bitMap->toFile(outputPath);

}
void convert_to_grayscale(const std::string& imagePath, const std::string& outputPath) {

BitMap::BitMapAbstract* bitMap = Factory::BitMapFactory::fromFile(imagePath);
BitMap::BitMapAbstract::convertToGray(bitMap);
bitMap->toFile(outputPath);

}

}
}

