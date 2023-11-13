#define DX 0.000001
#define LOG_OF_TEN 2.30258509299
#define EULER_NUMBER 2.71828182846
#define PI 3.14159265359


#include <iostream>

namespace math_functions {
        double abs(double number);
        double log(double number);
        double pow(double base,double power);
        double sqrt(double base, double order);
        double evalSeg(char *str,int len,char flag,std::string &errors);
}