#define _CRT_SECURE_NO_WARNINGS
#include "math_functions.h"
#include "checker.h"
#pragma once
//#include <iostream>
#include <cstring>

struct solutii{
    double x1;
    double x2;
};
class Equation{
private:
    char Unk;
    double* params;  //posibil modif in vector double* param = new double[4]
    int  degree;
public:

//Constructori
    Equation();
    Equation(int degree, char Unk, double* params);
    Equation(const Equation& e);
    ~Equation();
//Getteri
    char getUnk();
    double* getParams();
    int getdegree();
//Setteri
    void setUnk(char Unk);
    void setParams(double *_params);
    void setDegree(int degree);
//Overloads
    friend std::ostream& operator<<(std::ostream& os,const Equation& e);
    friend std::istream& operator>>(std::istream& is, Equation& e);
    friend Equation operator!(const Equation& e);
    friend Equation operator^(const Equation &e, float y);
    Equation& operator=(const Equation& e);
//Alte Metode
    double f_degree();
    solutii s_degree();
    //double n_degree(const Equation& e);
};