#include <string>
#include <iostream>

namespace Errors {

class ErrorExceedMatrix {

public:
    const char* getDescription() {
        return description;
    }
    void print() {
        std::cout << description << std::endl;
    }

private:
    const char* description = "error: you excced the matrix limits";

};

class ErrorCantAdd {

public:
    const char* getDescription() {
        return description;
    }
    void print() {
        std::cout << description << std::endl;
    }

private:
    const char* description = "error: the sizes of the matrix are'nt equal therefore its impossible to add them";

};

class ErrorCantMult {

public:
    const char* getDescription() {
        return description;
    }
    void print() {
        std::cout << description << std::endl;
    }

private:
    const char* description = "error: the rows number of the left matrix is'nt equal to the columns number of the right matrix therfore its impossible to multiply them";

};

class ErrorNullMatrix {

public:
    const char* getDescription() {
        return description;
    }
    void print() {
        std::cout << description << std::endl;
    }

private:
    const char* description = "error: the given matrix is null";

};

class ErrorCantAllocteMatrix {

public:
    const char* getDescription() {
        return description;
    }
    void print() {
        std::cout << description << std::endl;
    }

private:
    const char* description = "error: the memory allocation has failed";

};























}