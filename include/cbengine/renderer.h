#ifndef CBENGINE_RENDERER_H
#define CBENGINE_RENDERER_H


#include "pixel.h"


namespace cbengine {
    class Renderer {
    public:
        Renderer(const Renderer& _renderer) = delete;
        Renderer();
        ~Renderer();

        Renderer& operator =(const Renderer& _renderer) = delete;

        const Pixel getPixel(int _x, int _y) const;
        void setPixel(const Pixel& _pixel, int _x, int _y);
    };
}

#endif // CBENGINE_RENDERER_H
