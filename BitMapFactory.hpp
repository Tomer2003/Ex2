#pragma once
#include <memory>
#include <iostream>
#include "BMPinformation.hpp"



namespace BitMapManipulator {

class BitMapFactory {

public:
    static std::unique_ptr<bitMapAbstract> fromFile(const std::string& imagePath);
};

}