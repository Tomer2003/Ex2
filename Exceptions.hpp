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

/**
 * @brief The function throw appopriate error according error code
 * 
 * @param code - code to ErrorCode
 */
void throwAppopriateError(ErrorCode code);
}