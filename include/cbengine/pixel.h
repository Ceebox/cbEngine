#ifndef CBENGINE_PIXEL_H
#define CBENGINE_PIXEL_H


#include <cstdint>


namespace cbengine {
    class Pixel {
    public:
        Pixel(uint8_t _r, uint8_t _g, uint8_t _b);
        Pixel(uint8_t _x);
        Pixel(const Pixel& _pixel);
        Pixel();
        ~Pixel();

        Pixel& operator =(const Pixel& _pixel);

        void set(uint8_t _r, uint8_t _g, uint8_t _b);
        void set(uint8_t _x);
        void setR(uint8_t _r);
        void setG(uint8_t _g);
        void setB(uint8_t _b);
        void getRGB(uint8_t* _r, uint8_t* _g, uint8_t* _b) const;
        uint8_t getR() const;
        uint8_t getG() const;
        uint8_t getB() const;
    private:
        uint8_t _r;
        uint8_t _g;
        uint8_t _b;
    };
}

#endif // CBENGINE_PIXEL_H
