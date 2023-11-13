#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "equation.h"
#include "math_functions.h"
#include "checker.h"
#include <cstring>
#include <iostream>

char Equation::getUnk(){
     return Unk;
}

double* Equation::getParams(){
    return params;
}

int Equation::getdegree(){
     return degree;
}

void Equation::setUnk(char Unk){
    this->Unk=Unk;
}
void Equation::setParams(double *_params){
	if (params) delete[] params;
    params = new double[4];
    for (int i = 0; i < 4; i++)
        params[i] = _params[i];
}

void Equation::setDegree(int degree){
    this->degree=degree;
}

Equation::Equation() {
    params = new double[4];

}

Equation::Equation(const Equation& e){
    this->params=new double[4];
    this->Unk=e.Unk;
    this->params[0]=e.params[0];
    this->params[1]=e.params[1];
    this->params[2]=e.params[2];
    this->params[3]=e.params[3];
    this->degree=e.degree;
}

Equation::Equation(int degree, char Unk, double *params){
    this->params=new double[4];
    for(int i=0; i<4; i++)
        this->params[i] = params[i];
    this->Unk = Unk;
    this->degree = degree;
}

Equation::~Equation(){
    delete[] params;
}

// a*(x^2)+b*x+c=d  -- gr 2
// 0*(x^2)+b*x+c=d  -- gr 1
std::ostream& operator<<(std::ostream& os, const Equation& e){
    switch (e.degree)
    {
    case 1:
        os << e.params[1] << "*" << e.Unk << "+(" << e.params[2] << ")="<<e.params[3]<< "  " << e.degree <<"st degree ecuation"; 
        break;
    case 2:
        os << e.params[0] << "*" << e.Unk <<"^2+("<< e.params[1]<<")*"<<e.Unk<<"+(" << e.params[2] << ")="<<e.params[3]<< "  " << e.degree <<"nd degree ecuation";
        break;
    default:
        os<< "SYNTAX_ERROR Unknown degree!!";
        break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Equation& e) {
    is >> e.degree >> e.Unk;

    if (e.degree == 2)
        is >> e.params[0] >> e.params[1] >> e.params[2] >> e.params[3];
    else if (e.degree == 1)
        is >> e.params[1] >> e.params[2] >> e.params[3];

    return is;
}



Equation& operator!(const Equation& e){
    Equation e1;
    e1.params[0] = (-1)*e.params[0];
    e1.params[1] = (-1)*e.params[1];
    e1.params[2] = (-1)*e.params[2];
    e1.params[3] = (-1)*e.params[3];
    return e1;
}

Equation &operator^(const Equation &e, float y)
{   Equation e1(e);
    e1.params[0] = math_functions::pow(e.params[0], y);
    e1.params[1] = math_functions::pow(e.params[1], y);
    e1.params[2] = math_functions::pow(e.params[2],y);
    e1.params[3] = math_functions::pow(e.params[3],y);
    return e1;
}

Equation& Equation::operator=(const Equation &e){
    Unk=e.Unk;
    degree=e.degree;
    if(params)
        delete[] params;
    params=new double[4];
    for(int i=0; i<4; i++)
        params[i]=e.params[i];
    return *this;
}

double Equation::f_degree(){
    return ((params[2]-params[3])/params[1]);
}

solutii Equation::s_degree(){
    solutii s;
    double delta, sqrt_delta, pp, dp;
    delta = params[1] * params[1] - 4 * params[0] * (params[2]-params[3]);
    std::cout << "CP1 -- s was created\n";
    std::cout<<delta<<'\n';
	sqrt_delta =math_functions::sqrt(delta, 2.0f);
    pp = (-1)*(params[1]) / (2 * params[0]);
    dp = sqrt_delta/(2 * params[0]);
    s.x1 = pp + dp;
    std::cout << "CP2 -- s.x1 was initialized\n";
    s.x2 = pp - dp;
    std::cout << "CP3 -- s.x2 was initialized\n";
    return s;
}
