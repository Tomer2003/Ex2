#pragma once
#include "ErrorCode.h"
namespace Exceptions {

class ErrorExceedMatrix {
public:
    void printException();
};

class ErrorCantAdd {
public:
    void printException();
};

class ErrorCantMult {
public:
    void printException();
};

class ErrorNullMatrix {    
public:
    void printException();
};

class ErrorCantAllocateMatrix {
public:
    void printException();
};

class ErrorMatrixSizeNotAppopriate {
public:
    void printException();
};

void throwAppopriateError(ErrorCode code);
}