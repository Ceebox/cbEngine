#ifndef PIXEL_H
#define PIXEL_H

struct Pixel
{
    public:
        Pixel(int r, int b, int g);
        void Set(int r, int b, int g);

        int r;
        int g;
        int b;
};

#endif