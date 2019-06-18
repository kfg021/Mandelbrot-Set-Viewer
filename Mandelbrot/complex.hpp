#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include<cmath>
#include<iostream>

namespace mandelbrot {
    struct Complex{
        double real, imag;
        Complex(double real, double imag);
        ~Complex();
        
        //properties
        double squaredMagnitude() const;
        double magnitude() const;
        Complex conjugate() const;
        
        //operatons
        Complex operator+(const Complex& num) const;
        Complex operator-(const Complex& num) const;
        Complex operator*(const Complex& num) const;
        Complex operator/(const Complex& num) const;
        
        void operator+=(const Complex& num);
        void operator-=(const Complex& num);
        void operator*=(const Complex& num);
        void operator/=(const Complex& num);
    };
    
    std::ostream& operator<<(std::ostream& os, const Complex& num);
}

#endif
