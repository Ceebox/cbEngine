#include "pixel.h"


namespace cbengine {
    Pixel::Pixel(uint8_t _r, uint8_t _g, uint8_t _b):
        _r(_r), _g(_g), _b(_b) {}

    Pixel::Pixel(uint8_t _x):
        _r(_x), _g(_x), _b(_x) {}

    Pixel::Pixel(const Pixel& _pixel):
        _r(_pixel._r), _g(_pixel._g), _b(_pixel._b) {}

    Pixel::Pixel():
        _r(0), _g(0), _b(0) {}

    Pixel::~Pixel() {}

    Pixel& Pixel::operator =(const Pixel& _pixel) {
        this->_r = _pixel._r;
        this->_g = _pixel._g;
        this->_b = _pixel._b;
        return *this;
    }

    void Pixel::set(uint8_t _r, uint8_t _g, uint8_t _b) {
        *this = Pixel(_r, _g, _b);
    }

    void Pixel::set(uint8_t _x) {
        *this = Pixel(_x);
    }

    void Pixel::setR(uint8_t _r) {
        this->_r = _r;
    }

    void Pixel::setG(uint8_t _g) {
        this->_g = _g;
    }

    void Pixel::setB(uint8_t _b) {
        this->_b = _b;
    }

    void Pixel::getRGB(uint8_t* _r, uint8_t* _g, uint8_t* _b) const {
        *_r = this->_r;
        *_g = this->_g;
        *_b = this->_b;
    }

    uint8_t Pixel::getR() const {
        return this->_r;
    }

    uint8_t Pixel::getG() const {
        return this->_g;
    }

    uint8_t Pixel::getB() const {
        return this->_b;
    }
}
