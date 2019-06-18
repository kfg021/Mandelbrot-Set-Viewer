#include "m_set.hpp"
#include <ctime>

namespace mandelbrot {
    void gen_mandelbrot(const Complex& box_start, double box_width, double box_height, int rows, int cols, Display& d, int max_iterations){
        clock_t start = clock();

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                double re = box_start.real + (j * box_width) / cols;
                double im = box_start.imag + (i * box_height) / rows;
                Complex z(re, im);
                FinalValue fv = evaluate(z, max_iterations);
                d.set_pixel(j, i, fv);
           }
        }
        
        clock_t finish = clock();
        
        double time = (double(finish) - double(start)) / CLOCKS_PER_SEC;
        std::cout << time << " seconds elapsed" << std::endl;
    }
    
    FinalValue evaluate(const Complex& c, int max_iterations){
        Complex z(0, 0);
        int iterations = 0;
        while(z.squaredMagnitude() <= 4 && iterations < max_iterations){
            z = z * z + c;
            iterations++;
        }
        
        FinalValue fv;
        fv.num = z;
        fv.iterations = iterations;
        return fv;
    }
}
