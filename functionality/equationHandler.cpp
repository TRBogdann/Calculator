#include "equationHandler.h"
#include <cstring>
#include "str_functions.h"
#include "math_functions.h"

const char EquationHandler::paranthesis[7]="()[]{}";

EquationHandler::EquationHandler(unsigned int _buffer_size):
start1(0),start2(0),end1(0),end2(0),leftHandEquation(0),rightHandEquation(0),
unk('x'),buffer_size(_buffer_size),runTimeError("")
{
    if(buffer_size<1)
        buffer_size=1;

    for(int i=0;i<6;i++)
    {
        paranthesis1[i]=0;
        paranthesis2[i]=0;
    }
};

EquationHandler::EquationHandler(const EquationHandler& handler):
start1(handler.start1),start2(handler.start2),end1(handler.end1),
end2(handler.end2),unk(handler.unk),buffer_size(handler.buffer_size),runTimeError(handler.runTimeError)
{
    this->leftHandEquation=new char[strlen(handler.leftHandEquation)+1];
    this->rightHandEquation=new char[strlen(handler.rightHandEquation)+1];
    strcpy(this->leftHandEquation,handler.leftHandEquation);
    strcpy(this->rightHandEquation,handler.rightHandEquation);
    for(int i=0;i<6;i++)
    {
        this->paranthesis1[i]=handler.paranthesis1[i];
        this->paranthesis2[i]=handler.paranthesis2[i];
    }
}

EquationHandler& EquationHandler::operator=(const EquationHandler& handler)
{
    this->start1=handler.start1;
    this->start2=handler.start2;
    this->buffer_size=handler.buffer_size;
    this->end1=handler.end1;
    this->end2=handler.end2;
    this->unk=handler.unk;
    this->runTimeError=handler.runTimeError;

    this->leftHandEquation=new char[strlen(handler.leftHandEquation)+1];
    this->rightHandEquation=new char[strlen(handler.rightHandEquation)+1];
    strcpy(this->leftHandEquation,handler.leftHandEquation);
    strcpy(this->rightHandEquation,handler.rightHandEquation);
    for(int i=0;i<6;i++)
    {
        this->paranthesis1[i]=handler.paranthesis1[i];
        this->paranthesis2[i]=handler.paranthesis2[i];
    }

    return *this;
}

EquationHandler::~EquationHandler()
{
    if(leftHandEquation)
        delete[] leftHandEquation;
    
    if(rightHandEquation)
        delete[] rightHandEquation;
}

double EquationHandler::powerOfX(char *str,int len,char unk)
{
    double x=0.0f;
    int i=0;
    int search=0;
    int begin=0;

    while(i<len)
    {   
        if(search && (i==len-1 || str[i]=='*'))
        {
                x+=str_functions::string_to_double(str+begin,i-begin+1);
                search=0;
        }

        if(str[i]==unk)
        {
            if(i==len-1 || str[i+1]=='*')
                x++;
            else
            {
                search=1;
                begin=i+2;
            }
        }
        i++;
    }
    return x;

}

double EquationHandler::getCoeficientOf(unsigned int power)
{
    double res=0.0f;
    if(power>2)
         return 0.0f;
    int sign=1;
    int i=0;
    while(i<strlen(this->leftHandEquation))
    {   
        
        findFirstSegment(this->leftHandEquation+i,'+','-');
        if(powerOfX(leftHandEquation+start1+i,end1-start1+1,this->unk)==power)
        {
            if(start1+i!=0)
            {   
                if(leftHandEquation[start1+i-1]=='+'){
                 sign=1.0f;
                }
                else
                 sign=-1.0f;  
            }
            res+=sign*math_functions::evalSeg(leftHandEquation+start1+i,end1-start1+1,0,this->runTimeError);
        }

        
        i+=end1+2;
    }
    clearBuffer();
    sign=-1.0f;
     i=0;
        while(i<strlen(this->rightHandEquation))
    {   
        
        findFirstSegment(this->rightHandEquation+i,'+','-');
        if(powerOfX(rightHandEquation+start1+i,end1-start1+1,this->unk)==power)
        {
            if(start1+i!=0)
            {
                if(rightHandEquation[start1+i-1]=='+')
                 sign=-1.0f;
                else
                 sign=+1.0f;  
            }
            res+=sign*math_functions::evalSeg(rightHandEquation+start1+i,end1-start1+1,0,this->runTimeError);
        }

        
        i+=end1+2;
    }
    clearBuffer();
    return res;
}

void EquationHandler::clearBuffer(unsigned int number)
{
    if(number!=1 && number!=2)
        return;

    for(int i=0;i<6;i++)
    {
        if(number==1)
            this->paranthesis1[i]=0;
        else 
            this->paranthesis2[i]=0;
    }
}

int EquationHandler::updateParanthesisBuffer(char ch,unsigned int number)
{
    if(number!=1 && number!=2)
        return 0;
    
    int position=-1;
    int i=0;
    while(i<6)
    {   
        if(paranthesis[i]==ch)
        {
            position=i;
        }
        i++;
    }
    if(position<0)
            return 0;

    if(number==1)
        this->paranthesis1[position]++;
    
    else
        this->paranthesis2[position]++;

    if(position%2==0)
        return -1;

    return 1;
}

bool::EquationHandler::paranthesisAreClosed(unsigned int number)
{
    if(number!=1 && number!=2)
     return 0;

    for(int i=0;i<6;i+=2)
    {
        if(number==1){
            if(paranthesis1[i]!=paranthesis1[i+1])
                return 0;
        }
        else
            if(paranthesis2[i]!=paranthesis2[i+1])
                return 0;

    }
    return 1;
}

bool EquationHandler::onePairClosed(unsigned int number)
{
       if(number!=1 && number!=2)
     return 0;

    for(int i=0;i<6;i+=2)
    {
        if(number==1){
            if(paranthesis1[i]>0 && paranthesis1[i+1]>0)
                return 1;
        }
        else
            if(paranthesis2[i]>0 && paranthesis2[i+1]>0)
                return 1;

    }
    return 0;
};

bool EquationHandler::findInnerEquation(char* str,unsigned int number)
{
    if(number!=1 && number!=2)
        return 0;
    
    int i=0;
    int begin=0;
    int end=0;
    bool found=0;
    bool searching=0;

   while(i<strlen(str) && !found)
    {
        int change=updateParanthesisBuffer(str[i],number);
        if(change<0)
        {
            begin=i+1;
            if(!searching)
                searching=!searching;
        }

        if(searching)
        {
            if(onePairClosed(number))
            {
                end=i-1;
                found=1;
            }
        }
        i++;
    }
    if(number==1)
        {
            this->start1=begin;
            this->end1=end;
        }

    else
    {
        this->start2=begin;
        this->end2=end;
    }

    return found;
}

bool EquationHandler::findFirstSegment(char* str,char operator1, char operator2,unsigned int number)
{
    if(number!=1 && number!=2)
        return 0;

int i=0;
int begin=0;
int end=0;
bool found=0;
bool ignore=0;
 while(i<strlen(str) && !found)
            {   
        updateParanthesisBuffer(str[i],number);

        ignore=0;
        if(!paranthesisAreClosed(number))
            ignore=1;

         if(((str[i]==operator1 || str[i]==operator2) && i!=0 && !ignore) || i==strlen(str)-1)
            {
                 if(str[0]=='-')
                    {
                      begin++;
                    }

                  if(i==strlen(str)-1)
                    end=i;
                  
                  else
                    end=i-1;

            found=1;
            }
                i++;
            }


    if(number==1)
        {
            
            this->start1=begin;
            this->end1=end;
        }

    else
    {
        this->start2=begin;
        this->end2=end;
    }

return found;
}

bool EquationHandler::findLastSegment(char* str,int len,char operator1, char operator2,unsigned int number)
{
    if(number!=1 && number!=2)
        return 0;

int i=len-1;
int begin=len-1;
int end=len-1;
bool found=0;
bool ignore=0;
 while(i>-1 && !found)
            {   
        updateParanthesisBuffer(str[i],number);

        ignore=0;
        if(!paranthesisAreClosed(number))
            ignore=1;

         if(((str[i]==operator1 || str[i]==operator2) && !ignore) || i==0)
            {

                  if(i==0)
                    begin=i;
                  
                  else
                    begin=i+1;

            found=1;
            }
                i--;
            }

    if(str[begin]=='-')begin++;

    if(number==1)
        {
            
            this->start1=begin;
            this->end1=end;
        }

    else
    {
        this->start2=begin;
        this->end2=end;
    }

return found;
}


void EquationHandler::setEquation(char* equation)
{
    int breakPoint=str_functions::findChr(equation,'=');
    int len=strlen(equation);
    if(this->leftHandEquation!=0)
        delete[] this->leftHandEquation;

    if(this->rightHandEquation!=0)
        delete[] this->rightHandEquation;

    this->leftHandEquation=new char[breakPoint+1];
    strcpy(this->leftHandEquation,"");
    str_functions::add_to_str(leftHandEquation,equation,breakPoint);

    this->rightHandEquation=new char[len-breakPoint+1];
    strcpy(rightHandEquation,equation+breakPoint+1);

    modifyEcuation(leftHandEquation,unk);
    modifyEcuation(rightHandEquation,unk);

}


void EquationHandler::multiplyEcuations(char* &str1,char* eq1,char* eq2)
{
    char *eq=new char[this->buffer_size+1];
    strcpy(eq,"");
    bool sign1=1;
    bool sign2=1;

    int i=0;
    while(i<strlen(eq1))
    { 
    findFirstSegment(eq1+i,'+','-');

    if(start1+i==1)
            sign1=0;

      int j=0;
      sign2=1;
         while(j<strlen(eq2))
        { 
            findFirstSegment(eq2+j,'+','-',2);
           
            if(start2+j==1)
                    sign2=0;

           
            
            if(sign1==sign2)
            {
                if(strlen(eq)!=0)
                    strcat(eq,"+");
            }
            else 
                strcat(eq,"-");
            
            strncat(eq,eq1+i+start1,end1-start1+1);
            strcat(eq,"*");
            strncat(eq,eq2+j+start2,end2-start2+1);

            j+=end2+2;
            if(eq2[j-1]=='+')
                sign2=1;

            else sign2=0;
        }
            i+=end1+2;
            if(eq1[i-1]=='+')
                sign1=1;

            else sign1=0;
    }
    if(str1) delete[] str1;
    str1=new char[strlen(eq)+1];
    strcpy(str1,eq);
    
    if(eq){
    delete[] eq;
    }
}

void EquationHandler::simplifyEcuation(char* &equation,char unk)
{
    
    char *eq=new char[buffer_size];
    strcpy(eq,"");
    int i=0;
    int sign1=1;
    int sign2=1;
    while(i<strlen(equation))
    {
        findFirstSegment(equation+i,'+','-');

        if(start1+i==1)
                 sign1=0;
        
        sign2=1;

        double power=powerOfX(equation+start1+i,end1-start1+1,unk);
        double coeficient=math_functions::evalSeg(equation+start1+i,end1-start1+1,0,this->runTimeError);

        if(coeficient<0){
            sign2=0;
            coeficient=math_functions::abs(coeficient);
        }

        if(sign1==sign2)
        {
            if(strlen(eq)!=0)
                strcat(eq,"+");
        }
        else 
            strcat(eq,"-");

        
        if(coeficient!=0){
            if(coeficient!=1 || power==0){
            char* coef_formatted=str_functions::double_to_string(coeficient);

            strcat(eq,coef_formatted);
            delete[] coef_formatted;
            }

            if(power!=0){

               if(coeficient!=1) strcat(eq,"*x");

               else strcat(eq,"x");

                if(power!=1){
                        char* power_formatted=str_functions::double_to_string(power);
                        strcat(eq,"^");
                        strcat(eq,power_formatted);
                       
                        delete [] power_formatted;
                        } 
            }
            }
        else strcat(eq,"0");
        
        i+=end1+2;

            if(equation[i-1]=='+')
                sign1=1;

            else sign1=0;
       
    }
    if(equation)
        delete[] equation;
    
    equation=new char[strlen(eq)+1];
    strcpy(equation,eq);

    if(eq)
    {
    delete[] eq;
    }

}

void EquationHandler::modifyEcuation(char* &equation,char unk)
{
 
    bool searching=0;
    bool found=0;
    bool replaced=0;
    bool add_paranthesis=0;
    bool remove_paranthesis=1;
    int left_margin=0;
    int right_margin=0;
    bool direction=1;
    bool rev=0;

    int i=0;
    //First Step
    found=findInnerEquation(equation);
    if(!found)  
    {   
        clearBuffer(1);
        clearBuffer(2);
        simplifyEcuation(equation,unk);
        clearBuffer(1);
        clearBuffer(2);
        return;
    }
    clearBuffer(1);
    clearBuffer(2);
    char *temp=new char[buffer_size+1];
    strcpy(temp,"");
    //Second Step
    if(equation[start1-2]=='*'){
                    direction=0;
                    remove_paranthesis=0;
    }
    
    if(equation[end1+2]=='*' || equation[end1+2]=='/')
    {
        if(direction==0)
        {
            add_paranthesis=1;
            direction=1;
 
        }
        remove_paranthesis=0;

        if(equation[end1+2]=='/')
          rev=1;

    }

    char* res=0;
    char* eq1=0;
    char* eq2=0;
    
    if(equation[end1+2]=='^')
    {
        remove_paranthesis=0;
        left_margin=start1-1;
        right_margin=end1+3;
        switch(equation[end1+3])
        {
            case '0':
            strcat(temp,"1");
            break;

            case '1':
            if(!direction)strcat(temp,"(");
            str_functions::add_to_str(temp,equation+start1,end1-start1+1);
            if(!direction)strcat(temp,")");
            break;

            case '2':
            if(!direction)strcat(temp,"(");
            eq1=new char[end1-start1+2];
            strcpy(eq1,"");
            str_functions::add_to_str(eq1,equation+start1,end1-start1+1);
            multiplyEcuations(res,eq1,eq1);
            strcat(temp,res);
            if(!direction)strcat(temp,")");

            break;
        }

    }
    

    else if(!remove_paranthesis) {
        if(!direction)
        { 
            findLastSegment(equation,start1-2,'+','-',2);
            left_margin=start2;
            right_margin=end1+1;
        }
        else 
        {   
            findFirstSegment(equation+end1+3,'+','-',2);
            this->start2+=end1+3;
            this->end2+=end1+3;
            bool contains=0;
            while(str_functions::containsCharacter(equation+start2,end2-start2+1,')')){
                end2--;
                contains=true;
            }
            if(contains)end2++;
            left_margin=start1-1;
            right_margin=end2;
        }
        if(equation[this->start2]=='(')
        {
            start2++;
            end2--;
        }

        eq1=new char[end1-start1+2];
        strcpy(eq1,"");
        str_functions::add_to_str(eq1,equation+start1,end1-start1+1);

        if(!rev){
        eq2=new char[end2-start2+2];
        strcpy(eq2,"");
        str_functions::add_to_str(eq2,equation+start2,end2-start2+1);
        multiplyEcuations(res,eq1,eq2);
        }

        else  {
        double num=1/math_functions::evalSeg(equation+start2,end2-start2+1,0,this->runTimeError);
        eq2=str_functions::double_to_string(num);
        multiplyEcuations(res,eq1,eq2);
        }

        if(add_paranthesis)strcat(temp,"(");
        str_functions::add_to_str(temp,res,strlen(res));
        if(add_paranthesis)strcat(temp,")");

    }   

    else
    {
        left_margin=start1-1;
        right_margin=end1+1;
        str_functions::add_to_str(temp,equation+start1,end1-start1+1);
    }
    
    if(strlen(temp)>0){
    std::cout<<temp<<"\n";
    str_functions::printSegment(equation+left_margin,right_margin-left_margin+1);
    str_functions::strReplace(equation,left_margin,right_margin+1,temp);
    
    delete[] temp;
   
    }
    if(res)
        delete [] res;

    if(eq1)
        delete [] eq1;

    if(eq2)
        delete [] eq2;
    clearBuffer(1);
    clearBuffer(2);
    modifyEcuation(equation,unk);
     

}

void EquationHandler::setBufferSize(unsigned int _buffer_size)
{
    if(_buffer_size==0)
        return;
    
    this->buffer_size=_buffer_size;

    if(leftHandEquation!=0 && rightHandEquation!=0)
    if(_buffer_size>strlen(leftHandEquation)+1 
     ||_buffer_size>strlen(rightHandEquation)+1)
     {
        delete[] leftHandEquation;
        delete[] rightHandEquation;
        leftHandEquation=0;
        rightHandEquation=0;
     }
}
void EquationHandler::setUnk(char unknown)
{
    if(unknown<'a' || unknown>'z')
        return;
    else
        this->unk=unknown;
}

void EquationHandler::setSegment(int start,int end,unsigned int number)
{
    if(number!=1 || number!=2)
        return ;
    
    if(number==1)
    {
        this->start1=start;
        this->end1=end;
        return;
    }

        this->start2=start;
        this->end2=end;
}

void EquationHandler::setParanthesisBuffer(int buffer[6],unsigned int number)
{   
    if(number!=1 || number!=2)
        return ;
    for(int i=0;i<6;i++)
    {
        if(number==1)
        {
            this->paranthesis1[i]=buffer[i];
        }
        else 
            this->paranthesis2[i]=buffer[i];
    }
}

std::string EquationHandler::getRunTimeError(){ return this->runTimeError;}

char* EquationHandler::getEquation()
{
    char* equation=new char[strlen(leftHandEquation)+strlen(rightHandEquation)+2];
    strcat(equation,leftHandEquation);
    strcat(equation,"=");
    strcat(equation,rightHandEquation);
    return equation;
}

int EquationHandler::getBufferSize(){return this->buffer_size;}
int* EquationHandler::getParanthesisBuffer(unsigned int number)
{
    if(number!=1 || number!=2)
        return 0;

    if(number==1)
         return this->paranthesis1;

    return this->paranthesis2;

}
int EquationHandler::getSegmentBegining(unsigned int number)
{
    if(number!=1 || number!=2)
        return 0;

    if(number==1)
         return this->start1;

    return this->start2;

}

int EquationHandler::getSegmentEnd(unsigned int number)
{
    if(number!=1 || number!=2)
        return 0;

    if(number==1)
         return this->end1;

    return this->end2;

}
