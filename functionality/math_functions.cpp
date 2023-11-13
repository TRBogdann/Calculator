
#include "math_functions.h"
#include "checker.h"
#include "str_functions.h"

double math_functions::abs(double number)
{
    if(number<0)return -number;

    return number;
}

double math_functions::log(double number) //using mclaurin series
{

    if(number==1)
        return 0;

    double rest=0;

    //error fix 
    while(number>1) //bacause log(23)=2*ln(10)+ln(0.23), log(1123)=4*log(10)+ln(0.1123)
    {
        rest+=LOG_OF_TEN;
        number/=10.0f;
    }

    //function
    long long  step=2;
    number=number-1; //log(x)=log(1+y)=>y=x-1;

    double currentNr=-number*number;
    double res=number;
    double change=currentNr/step;

    

    while(math_functions::abs(change)>DX) //y-y^2/2+y^3/3-y^4/4+....
    {
        res+=change;

        currentNr*=-number;
        step++;

        change=currentNr/step;
    
    }

    return res+rest;
    

}


double math_functions::pow(double base, double power) //using mclaurin series
{
    
double res=1;

if(base==1)return 1;
if(base==0)return 0;

    if(int(power)==power) // for integer a^n=a*a*a*a...*a (n times)
    {
        if(power>0)
        for(int i=0; i<power; i++)
        {
            res*=base;
        }
        

        else    
             for(int i=0; i>power; i--)
        {
            res/=base;
        }

        return res;
    }   

    power=power*math_functions::log(base); // a ^ x = e ^ (log(a) * x);

    //error fix
    if(power>1)  //ex: 123^2.2=123^2*123^0.2
        return math_functions::pow(EULER_NUMBER,int(power))*math_functions::pow(EULER_NUMBER,power-int(power));
    

    double change=power;
    double currentNr=power;
    long long div=1;
    long long step=1;
    
    while(math_functions::abs(change)>DX) // for real numbers => 1+x+x^2/2!+x^3/3!+x^4/4!+....
    {
        res+=change;

        step++;
        div*=step;
        currentNr*=power;

        change=currentNr/div;

    }

    return res;
}

double math_functions::sqrt(double base, double order) //using mclaurin series
{
    return math_functions::pow(base,1.0f/order);
}

double math_functions::evalSeg(char *str,int len,char flag,std::string &error)
{   
    double res=0;
    double temp;

    int left_countpr=0,right_countpr=0;  //counts () pairs
    int left_countpsq=0,right_countpsq=0; //counts [] pairs
    int left_countpss=0,right_countpss=0; //counts {} pairs

    int i=0;
    bool sign=0;

    //Layer1
    
    if(str[i]=='-' && i==0)
    {
        i++;
        sign=1;
    }
    

    while(i<len && !Checker::isParanthesis(str[i]) && !(Checker::isOperator(str[i]) && str[i]!='.'))i++;
    if(i==len){
        if(str[0]=='x')return 1;
        if(sign) return -str_functions::string_to_double(str+1, len-1);
        return str_functions::string_to_double(str,len);
    }

    //Layer 2,3,4
    int start=0;
    int end;
    char ignore=0;
    char operator1, operator2;
    char newFlag;
    bool prev=0;
    bool insideParantethis=0;
    
    

    if(flag==0)
    {
        operator1='+';
        operator2='-';
    }

        if(flag==1)
    {
        operator1='*';
        operator2='/';
    }
        
         if(flag==2)
    {
        operator1='^';
        operator2='#';
    }

    i=0;
    char originalFlag = flag; 
        newFlag = flag + 1;
    
    
 

    while(i<len)
    {
        
        if((str[i]==operator1 || str[i]==operator2) && !insideParantethis && i!=0) 
        {
            if(ignore==0){
            newFlag=originalFlag;
            end=i-1;
            //printSegment(&str[start],end-start+1);
            if(!prev){
                
                res+=evalSeg(&str[start],end-start+1,0,error);
                
            }

            else 
            switch(str[start-1])
            {
            case '+':
                res+=evalSeg(&str[start],end-start+1,0,error);
                break;
            case '-':
                res-=evalSeg(&str[start],end-start+1,0,error);
                break;
            case '*':
                res*=evalSeg(&str[start],end-start+1,0,error);
                break;

            case '/':
                temp=evalSeg(&str[start],end-start+1,0,error);
                if(temp==0)
                {
                 if(error=="")error="DIV_0";
                 res=0;
                }
                else
                 res/=temp;
                break;

            case '^':
                res=math_functions::pow(res,evalSeg(&str[start],end-start+1,0,error));
                break;
            case '#':
                res=math_functions::sqrt(res,evalSeg(&str[start],end-start+1,0,error));
                break;
            }

        prev=1;
        start=i+1;
            }

             if(ignore==2){
            if(Checker::isParanthesis(str[i-1]))
                end=i-2;

            else
                 {
                start--;
                end=i-1;
            }

            newFlag=originalFlag;

           // printSegment(&str[start],end-start+1);

            if(!prev){
            res+=evalSeg(&str[start],end-start+1,0,error);
            }

            else switch(str[start-2])
            {
            case '+':
                res+=evalSeg(&str[start],end-start+1,0,error);
                break;
            case '-':
                res-=evalSeg(&str[start],end-start+1,0,error);
                break;
            case '*':
                res*=evalSeg(&str[start],end-start+1,0,error);
                break;
            case '/':
                temp=evalSeg(&str[start],end-start+1,0,error);
                if(temp==0)
                {
                 if(error=="")error="DIV_0";
                 res=0;
                }
                else
                 res/=temp;
                break;
            case '^':
                res=math_functions::pow(res,evalSeg(&str[start],end-start+1,0,error));
                break;
            case '#':
                res=math_functions::sqrt(res,evalSeg(&str[start],end-start+1,0,error));
                break;
            }
            prev=1;
            ignore=0;
            start=i+1;
            }
            
            
        }

        switch(str[i])
        {
            case '(':
                if(ignore==0)
                {
                if(i==0 || !(str[i]!=operator1 || str[i]!=operator2))
                {
                ignore=1;
                start=i+1;
                }
                }

                left_countpr++;
                break;

          case ')':
                right_countpr++;
                break;

         case '[':
                if(ignore==0) {
                    if(i==0 || !(str[i]!=operator1 || str[i]!=operator2))
                {
                ignore=1;
                start=i+1;
                }
                }
                left_countpsq++;
                break;

          case ']':
                right_countpsq++;
                break;

         case '{':
                if(ignore==0) {
                  if(i==0 || !(str[i]!=operator1 || str[i]!=operator2))
                {
                ignore=1;
                start=i+1;
                }
                }
                left_countpss++;
                break;

          case '}':
                right_countpss++;
                break;



        }

            insideParantethis=0;
           if(left_countpr!=right_countpr)insideParantethis=1;
           if(left_countpsq!=right_countpsq)insideParantethis=1;
           if(left_countpss!=right_countpss)insideParantethis=1;

        if(ignore==1)
        {   
            ignore=2;
            if(left_countpr!=right_countpr)ignore=1;
            if(left_countpsq!=right_countpsq)ignore=1;
            if(left_countpss!=right_countpss)ignore=1;
        }

        i++;

        if(i==len)
        {
            if(originalFlag==newFlag)
            {
                end=len-1;
                int num=1;
                if(ignore==2)
                {
                    end=len-2;
                    num=2;
                }
            if(start<2)
                res+=evalSeg(&str[start],end-start+1,0,error);
            //printSegment(&str[start],len-start);
             switch(str[start-num])
            {
            case '+':
                res+=evalSeg(&str[start],end-start+1,0,error);
                break;
            case '-':
                res-=evalSeg(&str[start],end-start+1,0,error);
                break;
            case '*':
                res*=evalSeg(&str[start],end-start+1,0,error);
                break;
            case '/':
                temp=evalSeg(&str[start],end-start+1,0,error);
                if(temp==0)
                {
                 if(error=="")error="DIV_0";
                 res=0;
                }
                else
                 res/=temp;
                break;
            case '^':
                res=math_functions::pow(res,evalSeg(&str[start],end-start+1,0,error));
                break;
            case '#':
                res=math_functions::sqrt(res,evalSeg(&str[start],end-start+1,0,error));
                break;
            }
                
            }
        }
    }
    

    
    
    if(newFlag==3)
    {   
        res+=evalSeg(&str[1],len-2, 0,error);
        
    }

    if(newFlag>3) return 0;

   

    if(originalFlag!=newFlag)
        res+=evalSeg(str, len,newFlag,error);


     return res;
}