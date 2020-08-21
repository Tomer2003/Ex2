#include <fstream>
#include "BMPinformation.hpp"



reader::Header& reader::Header::setData(const std::ifstream& imageFile, reader::Header header) {

imageFile.read((char *) &header,sizeof(header));

if ((char*)header.signature != "BM") {

}



}


reader::DIBHeader& reader::DIBHeader::setData(const std::ifstream& imageFile, reader::DIBHeader dibHeader) {