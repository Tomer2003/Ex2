#include "BMPinformation.hpp"

int main() {

std::unique_ptr<BitMapManipulator::bitMapAbstract> BitMap = BitMapManipulator::BitMapFactory::fromFile("lena.bmp");




return 0;
}