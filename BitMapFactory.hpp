#pragma once
#include "BitMap.hpp"
#include <memory>

namespace Factory{
class BitMapFactory {
public:
    static BitMap::BitMapAbstract* fromFile(const std::string& imagePath);
};
























}