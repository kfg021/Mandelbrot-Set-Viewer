#include "display.hpp"

#define COLOR_MODE 2
#define RESIZABLE false

namespace mandelbrot {
    Display::Display(int rows, int cols, int max_iterations){
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, cols * pixel_size, rows * pixel_size, SDL_WINDOW_SHOWN);
        
    #if RESIZABLE
        SDL_SetWindowResizable(window, SDL_TRUE);
    #endif
        
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        this->rows = rows;
        this->cols = cols;
        this->max_iterations = max_iterations;
        
        pixel = new FinalValue[rows * cols];
    }
    Display::~Display(){
        delete[] pixel;
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }
    
    void Display::loop(){
        draw();
        
        const int hertz = 10;
        
        bool running = true;
        SDL_Event e;
        while(running){
            if(SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    running = false;
                }
            }
            else{
                SDL_Delay(1000 / hertz);
            }
        }
    }
    
    void Display::draw(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                SDL_Rect rect;
                rect.x = j * pixel_size;
                rect.y = (rows - i - 1) * pixel_size;
                rect.w = pixel_size;
                rect.h = pixel_size;
            
                FinalValue fv = pixel[j + cols * i];
            #if COLOR_MODE == 0 //grayscale
                double color = (255.0 * fv.iterations) / max_iterations;
                SDL_SetRenderDrawColor(renderer, color, color, color, 255);
            #elif COLOR_MODE == 1 //colored
                double hsv[3];
                if(fv.iterations == max_iterations){
                    hsv[0] = 0; hsv[1] = 0; hsv[2] = 0;
                }
                else{
                    hsv[0] = (360.0 * fv.iterations) /  max_iterations; hsv[1] = 1; hsv[2] = 1;
                }
                double rgb[3];
                hsv_to_rgb(hsv, rgb);
                SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
            #elif COLOR_MODE == 2 //continous coloring
                //nsmooth := n + 1 - Math.log(Math.log(zn.abs()))/Math.log(2)
                double h = 20 * (fv.iterations + 1 - log(log(fv.num.magnitude()))/log(2)) + 0.95;
                while (h > 360.0)
                    h -= 360.0;
                while (h < 0.0)
                    h += 360.0;
                double hsv[3];
                hsv[0] = h; hsv[1] = 1; hsv[2] = 1;
                double rgb[3];
                hsv_to_rgb(hsv, rgb);
                SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
            #endif
                
                SDL_RenderFillRect(renderer, &rect);
            }
        }
        SDL_RenderPresent(renderer);
    }
    
    void Display::hsv_to_rgb(const double (&hsv)[3], double (&rgb)[3]){
        double c = hsv[2] * hsv[1];
        double r1 = 0, g1 = 0, b1 = 0;
        double h1 = hsv[0] / 60.0;
        double x = 1 - abs(fmod(h1, 2) - 1);
        
        if(h1 >= 0 && h1 <= 1){
            r1 = c;
            g1 = x;
        }
        else if(h1 <= 2){
            r1 = x;
            g1 = c;
        }
        else if(h1 <= 3){
            g1 = c;
            b1 = x;
        }
        else if(h1 <= 4){
            g1 = x;
            b1 = c;
        }
        else if(h1 <= 5){
            r1 = x;
            b1 = c;
        }
        else if(h1 <= 6){
            r1 = c;
            b1 = x;
        }
        
        double m = hsv[2] - c;
        rgb[0] = 255 * (r1 + m); rgb[1] = 255 * (g1 + m); rgb[2] = 255 * (b1 + m);
    }
    
    void Display::set_pixel(int row, int col, const FinalValue& fv){
        pixel[row + cols * col] = fv;
    }
    
}
