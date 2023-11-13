//#define _CRT_SECURE_NO_WARNINGS 
#include "checker.h"
#include <cstring> 
#include <iostream>


Checker::Checker()
{

}

Checker::~Checker()
{

}

Checker::Checker(int ch){
    std::cout<<ch<<std::endl;
}

std::ostream& operator<<(std::ostream& os, const Checker& ch){
    os << "<< Overload pt clasa Checker";
    return os;
}

std::istream& operator>>(std::istream& is, Checker& ch){
    
    return is;
}

 bool Checker::checkExit(char *str)
{
  if(strlen(str)==0)
    return 1;

  if(strlen(str)==1 and str[0]=='\n')
    return 1;

  if(strlen(str)==4)
    if(strcmp(str,"exit")==0)
        return 1;
  
  return 0;
}

bool Checker::isOperator(char c)
{
    const char* operators={"*+-/^#."};
    if(strchr(operators,c))
        return 1;
    return 0;
};

bool Checker::isParanthesis(char c)
{
    const char* operators={"(){}[]"};
    if(strchr(operators,c))
        return 1;
    return 0;
};

bool Checker::isLeftParanthesis(char c)
{
    const char* operators={"({["};
    if(strchr(operators,c))
        return 1;
    return 0;
};

bool Checker::isRightParanthesis(char c)
{
    const char* operators={")}]"};
    if(strchr(operators,c))
        return 1;
    return 0;
};

bool Checker::checkDivZero(char *str)
{
  int i=0;
  bool checking=0;
  while(i<strlen(str))
  {
    if(!isLeftParanthesis(str[i]))
    {
       if(checking)
    {
        if(str[i]=='0')return 1;
        checking=!checking;
    }
       else 
            if(str[i]=='/')checking=1;
    }
     i++;
  }
  return 0;
}

bool Checker::checkDots(char *str)
{
    int i=0;
    bool checking=0;

     while(i<strlen(str))
  {

    if(str[i]=='.')
    {
        if(checking){
            //Alex --
            // daca asta e adevarat => si checkDecimals e adevarat automat
            //checkDecimals(str) = true;
            //de asta am comentat checkDecimals, e degeaba pt ca asta deja verifica
            return 1;
        }
        checking=1;
    }

    else if(!(str[i]>='0' && str[i]<='9') && checking==1)checking=0;
        
    
     i++;
  }
    
    return 0;
}

bool Checker::checkCharacters(char *str){
    int i=0;
    while(i<strlen(str))
    {
        if(!isLeftParanthesis(str[i]) && !isRightParanthesis(str[i]) && !isOperator(str[i])) 
        {
            if(('A' <= str[i] && str[i] <= 'Z') || ('a' <= str[i] && str[i] <= 'z' )) return 1;
        }
        i++;
    }
    return 0;
}

bool Checker::checkIfEcuation(char *str){
    int i=0;
    while(i<strlen(str))
  {
    if(strchr("=", str[i])){ //Alex -- overkill daca verificam daca are caractere, si in caz contrar verificam daca egalitatea data de utilizator merge sau nu??
        return 1;
    }
     i++;
  }
  return 0;
}

// bool Checker::checkDecimals(char *str){
//    if(!checkDots(str))
//     return 0;
//     else{
//         int i=0;
//         bool checking =0;
//         while(i < strlen(str)){
//             if(str[i] == '.'){
//                 if(checking) return 1;
//                 checking=1;
//             }
//             else if(!(str[i]>='0' && str[i]<='9') && checking==1) checking=0;
//         }
//     }
// }

//bool Checker::checkSyntax(char *str){} //Alex -- pare deja implementata in checkExpression. Are sens sa facem si aici? 


 char Checker::checkExpression(char *str)
 {
    char type=SIMPLE_EXPRESSION;
    bool found_x=0;
    int count_equals=0;
    int left_countpr=0,right_countpr=0;  //counts () pairs
    int left_countpsq=0,right_countpsq=0; //counts [] pairs
    int left_countpss=0,right_countpss=0; //counts {} pairs

    if(checkExit(str))return EXIT;



   if(!(str[0]>='0' && str[0]<='9') && str[0]!='(' &&  str[0]!='[' 
        && str[0]!='{' && str[0]!='x' && str[0]!='-' && str[0]!=' ')
         {
            if(isOperator(str[0]) || isParanthesis(str[0])) 
                return SYNTAX_ERROR;

            return UNKNOWN_SYMBOL;
         }

    if(str[0]=='(')left_countpr++;
    if(str[0]=='[')left_countpsq++;
    if(str[0]=='{')left_countpss++;
    if(str[0]=='x')
    {
        type=ECUATION;
        found_x=1;
    }

    for(int i=1;i<strlen(str);i++)
    {
      
        if((str[i]>='a' && str[i]<='z')){
            if(str[i]=='x')
            {       
                    if(str[i-1]>='0' && str[i-1]<='9')return SYNTAX_ERROR;
                    if(str[i-1]=='x')return SYNTAX_ERROR;
                    if(str[i-1]=='.')return SYNTAX_ERROR;
                    if(str[i-1]==')')return SYNTAX_ERROR;
                    if(str[i-1]==']')return SYNTAX_ERROR;
                    if(str[i-1]=='}')return SYNTAX_ERROR;
                    type=ECUATION;
                    found_x=1;
            }

            else    
                return UNKNOWN_SYMBOL;
        }
        else 
            if(str[i]<'0' || str[i]>'9')
                if(!isOperator(str[i]) && !isParanthesis(str[i]) && str[i]!='=')
                    return UNKNOWN_SYMBOL;

        if(isOperator(str[i]) && isOperator(str[i-1])) return SYNTAX_ERROR;
        if(isOperator(str[i]) && isLeftParanthesis(str[i-1]) && str[i]!='-')return SYNTAX_ERROR;
        
        if(isRightParanthesis(str[i]) && isOperator(str[i-1]))return SYNTAX_ERROR;
        if(isRightParanthesis(str[i]) && isLeftParanthesis(str[i-1]))return SYNTAX_ERROR;

        if(str[i]=='.' && str[i-1]=='x')return SYNTAX_ERROR;

        if(str[i]=='(')left_countpr++;
        if(str[i]=='[')left_countpsq++;
        if(str[i]=='{')left_countpss++;

        if(str[i]==')')right_countpr++;
        if(str[i]==']')right_countpsq++;
        if(str[i]=='}')right_countpss++;

        if(str[i]=='='){
            count_equals++;
            type=ECUATION;
        }
  

    }

    if(isOperator(str[strlen(str)-1]))return SYNTAX_ERROR;

    if(found_x && count_equals==0)
        return SYNTAX_ERROR;

    if(count_equals>0 && found_x==0)
        return SYNTAX_ERROR;

    if(count_equals>1)
        return SYNTAX_ERROR;

    if(left_countpr!=right_countpr)
    {
        return SYNTAX_ERROR;
    }
    if(left_countpss!=right_countpss)return SYNTAX_ERROR;
    if(left_countpsq!=right_countpsq)return SYNTAX_ERROR;

    if(checkDivZero(str))return DIVISION_BY_ZERO;
    if(checkDots(str))return SYNTAX_ERROR;

    return type;
 }
