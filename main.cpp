  

#include "Headers.hpp"
#include "BitMap.hpp"
#include "BitMapFactory.hpp"
#include <memory>
#include <iostream>
#include <fstream>
#include <iostream>
int main() {
    BitMap::bitMapAbstract* a = Factory::BitMapFactory::fromFile("tsaban.bmp");
//std::cout << "hhh" << std::endl;
//std::unique_ptr<BitMap::bitMapAbstract> BitMap = Factory::BitMapFactory::fromFile("tsaban.bmp");
//std::cout << "hhh" << std::endl;
//BitMap->rotate90Degrees();
//std::cout << "hhh" << std::endl;
//BitMap->convertToGray();
//BitMap->toFile("capara.bmp");
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

