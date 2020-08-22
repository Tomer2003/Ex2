
#include <memory>
#include <iostream>
#include "BitMapFactory.hpp"
#include "BMPinformation.hpp"



int main() {

std::unique_ptr<BitMapManipulator::bitMapAbstract> BitMap = BitMapManipulator::BitMapFactory::fromFile("lena-color.bmp");
BitMap->toFile("capara.bmp");


return 0;
}

