#pragma once
#pragma pack(pop)
#include "Headers.hpp"
#include <vector>
namespace BitMap{

class bitMapAbstract{
protected:
    typedef std::vector<Headers::colorTupple> ColorPalleteType;
    typedef std::vector<uint8_t> IntensityType;

private:
    Headers::Header headerInfo;
    Headers::DIBHeader DIBHeaderInfo;
    ColorPalleteType colorPallete;
    IntensityType byteArray;

public:
    bitMapAbstract(const Headers::Header& headerInfo, const Headers::DIBHeader& DIBHeaderInfo);

    void fromFile(std::ifstream& imageFile);

    void toFile(const std::string imagePath);

    size_t getHeight() const;

    size_t getWidth() const;

    ColorPalleteType& getColorPallete();

    size_t getBytesPerPIxel() const;

    IntensityType& getBitMapArray();

    size_t virtual getColorPalleteSize() const = 0;
};



class bitMap8Bits : public bitMapAbstract {
private:
    const size_t ColorPalleteSize = 256;
public:
    bitMap8Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader);

    size_t virtual getColorPalleteSize() const;
};



class bitMap24Bits : public bitMapAbstract {
private:
    const size_t ColorPalleteSize = 0;
public:
    bitMap24Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader);

    size_t virtual getColorPalleteSize() const;
};
}