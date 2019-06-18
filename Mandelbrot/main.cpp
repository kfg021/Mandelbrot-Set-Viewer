#include "display.hpp"
#include "complex.hpp"
#include "m_set.hpp"

using namespace mandelbrot;

int main() {

    Complex start(-2, -1);
    const double width = 3;
    const double height = 2;
    
    const int cols = 600;
    const int rows = cols * height / width;
    
    const int max_iterations = 100;
    
    Display d(rows, cols, max_iterations);
    gen_mandelbrot(start, width, height, rows, cols, d, max_iterations);
    d.loop();
    
    return 0;
}
