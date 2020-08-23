#pragma once
#include "Headers.hpp"
#include <vector>
namespace BitMap{
class BitMap8Bits;
class BitMap24Bits;

class BitMapAbstract{
protected:
    typedef std::vector<Headers::colorTupple> ColorPalleteType;
    typedef std::vector<uint8_t> IntensityType;

private:
    Headers::Header m_headerInfo;
    Headers::DIBHeader m_DIBHeaderInfo;
    ColorPalleteType m_colorPallete;
    IntensityType m_byteArray;

public:
    BitMapAbstract(const Headers::Header& headerInfo, const Headers::DIBHeader& DIBHeaderInfo);

    BitMapAbstract(const Headers::Header& headerInfo, const Headers::DIBHeader& DIBHeaderInfo, ColorPalleteType& colorPallete, IntensityType& bitMapArray);

    void fromFile(std::ifstream& imageFile);

    void toFile(const std::string imagePath);

    size_t getHeight() const;

    size_t getWidth() const;

    ColorPalleteType& getColorPallete();

    size_t getBytesPerPIxel() const;

    IntensityType& getBitMapArray();

    void rotate90Degrees();

    void setBitMapHeight(const uint32_t height);

    void setBitMapWidth(const uint32_t width);

    uint8_t getRGBToGray(const uint8_t blue, const uint8_t green, const uint8_t red) const;

    const Headers::Header& getHeader() const;

    const Headers::DIBHeader& getDIBHeader() const;

    size_t virtual getColorPalleteSize() const = 0;

    static void convertToGray(BitMap::BitMapAbstract* bitMap);

};



class BitMap8Bits : public BitMapAbstract {
private:
    const size_t m_ColorPalleteSize = 256;
public:
    BitMap8Bits(Headers::Header& theNewHeader, Headers::DIBHeader& theNewDIBHeader, ColorPalleteType& theNewPallete, IntensityType& theNewBitMapArray);

    BitMap8Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader);

    size_t virtual getColorPalleteSize() const;
};



class BitMap24Bits : public BitMapAbstract {
private:
    const size_t m_ColorPalleteSize = 0;
public:
    BitMap24Bits(const Headers::Header& header, const Headers::DIBHeader& dibHeader);

    size_t virtual getColorPalleteSize() const;
};
}