
#include "equation.h"
#include "equationHandler.h"
#include "checker.h"
#include "str_functions.h"
#include "math_functions.h"

class Calculator{
public:
//Constructor/ Destructor
Calculator(unsigned int buffer_size);
Calculator(char* expression);
//Calculator(const Calculator&)
//Calculator(...params)
// Calculator& operator=(const Calculator&)
~Calculator();
//Getter
char* getExpr();
Checker getChecker();
std::string getErrorMessage();
double getResult();

//solutii getSolutii();
//char getType();
//get BufferSize();
//get Handler();

//Setteri
//void setHandler(EquationHandler _handler)
//void setBufferSize(int buffer_Size)
// set errorMessage(std::string errorMessage);


void setExpr(char *expr);
void setChecker(Checker checker);

//Overload
friend std::ostream& operator<<(std::ostream& os, const Calculator& c);
friend std::istream& operator>>(std::istream& is, Calculator& c);
//Metode diverse
void evalExpr();
void clear();
void printResult();
void loop();

private:
unsigned int _buffer_size;
Checker checker;
char *expression;
char lastType;
double last_result;
solutii last_sol;
std::string error_message;
EquationHandler handler;
int getPrecision();

};