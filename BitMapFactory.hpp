#pragma once
#include "BitMap.hpp"
#include <memory>

namespace Factory{
class BitMapFactory {
public:
    //static std::unique_ptr<BitMap::bitMapAbstract> fromFile(const std::string& imagePath);
    static BitMap::bitMapAbstract* fromFile(const std::string& imagePath);
};
























}