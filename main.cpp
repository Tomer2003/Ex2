#include <memory>
#include <iostream>
#include "BitMap.hpp"
#include "BitMapFactory.hpp"



int main() {
std::unique_ptr<BitMap::bitMapAbstract> BitMap;    
std::cout << "hhh" << std::endl;
BitMap = Factory::BitMapFactory::fromFile("tsaban.bmp");
std::cout << "hhh" << std::endl;
BitMap->rotate90Degrees();
BitMap->convertToGray();
BitMap->toFile("capara.bmp");


return 0;
}