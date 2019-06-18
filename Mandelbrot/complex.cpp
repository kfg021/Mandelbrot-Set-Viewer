#include "complex.hpp"

namespace mandelbrot{
    
    Complex::Complex(double real, double imag){
        this->real = real;
        this->imag = imag;
    }
    Complex::~Complex(){
    }
    
    double Complex::squaredMagnitude() const{
        return real * real + imag * imag;
    }
    double Complex::magnitude() const{
        return sqrt(squaredMagnitude());
    }
    Complex Complex::conjugate() const{
        return Complex(real, -imag);
    }
    
    Complex Complex::operator+(const Complex& num) const{
        return Complex(real + num.real, imag + num.imag);
    }
    Complex Complex::operator-(const Complex& num) const{
         return Complex(real - num.real, imag - num.imag);
    }
    Complex Complex::operator*(const Complex& num) const{
        return Complex(real * num.real - imag * num.imag, real * num.imag + imag * num.real);
    }
    Complex Complex::operator/(const Complex& num) const{
      double mag2 = num.squaredMagnitude();
        return Complex((real * num.real + imag * num.imag) / mag2, (-real * num.imag + imag * num.real) / mag2);
    }
    
    void Complex::operator+=(const Complex& num){
        real += num.real;
        imag += num.imag;
    }
    void Complex::operator-=(const Complex& num){
        real -= num.real;
        imag -= num.imag;
    }
    void Complex::operator*=(const Complex& num){
        real = real * num.real - imag * num.imag;
        imag = real * num.imag + imag * num.real;
    }
    void Complex::operator/=(const Complex& num){
        double mag2 = num.squaredMagnitude();
        real = (real * num.real + imag * num.imag) / mag2;
        imag = (-real * num.imag + imag * num.real) / mag2;
    }
    
    std::ostream& operator<<(std::ostream& os, const Complex& num){
        os << num.real << " + " << num.imag << "i";
        return os;
    }
}
