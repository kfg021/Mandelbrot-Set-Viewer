#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include<SDL2/SDL.h>
#include "complex.hpp"

namespace mandelbrot{
    struct FinalValue{
        Complex num = Complex(0,0);
        int iterations = 0;
    };
    
    class Display{
    private:
        const int pixel_size = 1;
        SDL_Window* window;
        SDL_Renderer* renderer;
        
        int rows, cols;
        int max_iterations;
        FinalValue* pixel;
        void draw();
        void hsv_to_rgb(const double (&hsv)[3], double (&rgb)[3]);

    public:
        Display(int rows, int cols, int max_iterations);
        ~Display();
        void set_pixel(int x, int y, const FinalValue& fv);
        void loop();
    };
}

#endif
