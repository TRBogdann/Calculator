//errors
#pragma once
#include <iostream>
#define SYNTAX_ERROR 1  //done
#define UNKNOWN_SYMBOL 2 //done
#define NOT_A_FIRST_OR_SECOND_DEGREE_ECUATION 3 //not done
//Alex -- daca avem definite 7, 8 si 9 mai are sens sa definim 3?
#define DIVISION_BY_ZERO 4 //done

//types
#define ECUATION 6
#define FIRST_GRADE_ECUATION 7 //not done
#define SECOND_GRADE_ECUATION 8 //not done
#define SIMPLE_EXPRESSION 9 //not done

//commands
#define EXIT 10 //done

//runtime errors
#define ZERO_POW_ZERO 11
#define ZERO_SQRT_ZERO 12
#define DIV_X 12
#define POW_X 13
#define COMPLEX_RESULT 14



class Checker{
public:
//Constructor/Destructor
Checker();
Checker(int ch);
~Checker();
//Overload
friend std::ostream& operator<<(std::ostream& os, const Checker& ch);
friend std::istream& operator>>(std::istream& is, Checker& ch);
//Metode
bool checkExit(char *str);
bool checkDivZero(char *str);
bool checkDots(char *str);
bool checkIfEcuation(char *str);

char checkExpression(char *str);

static bool checkCharacters(char *str);
static bool isOperator(char c);
static bool isParanthesis(char c);
static bool isLeftParanthesis(char c);
static bool isRightParanthesis(char c);

private:

};