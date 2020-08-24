#include <memory>
#include <iostream>
#include "BitMap.hpp"
#include "BitMapFactory.hpp"
#include "bmp_tester.hpp"
#include <fstream>
#include <iostream>

int main() {

testing::bmp::convert_to_grayscale("lena.bmp", "d.bmp");

return 0;
}