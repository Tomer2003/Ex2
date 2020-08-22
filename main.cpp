/*#include <memory>
#include <iostream>
#include "BitMap.hpp"
#include "BitMapFactory.hpp"*/
#include <fstream>
#include <iostream>

int main() {
    std::fstream in;
//std::cout << "hhh" << std::endl;
//BitMap::bitMapAbstract* bitMap = Factory::BitMapFactory::fromFile("tsaban.bmp");
//std::unique_ptr<BitMap::bitMapAbstract> BitMap = std::make_unique<BitMap::bitMapAbstract>(Factory::BitMapFactory::fromFile("tsaban.bmp"));    
/*if(typeid(*bitMap) == typeid(BitMap::bitMap8Bits)){
    std::cout << "aaa";
}
else if(typeid(*bitMap) == typeid(BitMap::bitMap24Bits)){
    std::cout << "bbb";
}*/
//std::cout << "hhh" << std::endl;
//std::cout << "hhh" << std::endl;
/*BitMap->rotate90Degrees();
BitMap->convertToGray();
BitMap->toFile("capara.bmp");

*/
return 0;
}