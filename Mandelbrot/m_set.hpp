#ifndef M_SET_HPP
#define M_SET_HPP

#include "display.hpp"
#include "complex.hpp"

namespace mandelbrot {
    void gen_mandelbrot(const Complex& box_start, double box_width, double box_height, int rows, int cols, Display& d, int max_iterations);
    FinalValue evaluate(const Complex& c, const int max_iterations);
}

#endif
