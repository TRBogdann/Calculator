#include "str_functions.h"
#include "math_functions.h"
#include <cstring>

bool str_functions::containsCharacter(char *str,int len,char character)
{
    int i=0;
    while(i<len)
    {
        if(str[i]==character)
         return 1;

        i++;
    }
    return 0;
}

double str_functions::string_to_double(char *str,int len)
{
    double res=0;
    bool dot=0;
    int p=10;
    for(int i=0;i<len;i++)
    {
        
        if(str[i]=='.')dot=1;
        else
         {
            double num=str[i]-'0';
            if(!dot)
                res=res*10+num;
            else
            {
                res+=num/p;
                p*=10;
            }
         };
    }
    return res;
};

char* str_functions::double_to_string(double number)
{
    const double fix=0.00000000001;
    number+=fix;
    char *str;
    int len=0;
    long long  int_part=(long long)(number);
    double decimal_part=number-int(number);
    bool sign=0;

    if(number<0)
    {
        len++;
        sign=1;
        number=math_functions::abs(number);
    }

    if(number==0)
    {
        char* str=new char[2];
        str[0]='0';
        str[1]=0;
        return str;
    }
    
    

    if(!int_part)len++;

    while(int_part>0)
    {
        int_part/=10;
        len++;
    }

    int rev=len;
    
    
    if(decimal_part)
    {
        len++;
        int rest=0;
        int addUp=0;
        for(int i=0;i<9;i++)
        {
            decimal_part*=10;
            
            if(((long long)(decimal_part))%10==0)
            {
                rest++;
            }
            else{
                addUp++;
                addUp+=rest;
                rest=0;
            }
        }
        len+=addUp;
        
    }

    str=new char[len+1];
    int_part=(long long)(number);
    decimal_part=number-(long long)(number);

    int i=rev;
    while(i>0)
    {   
        str[i-1]=int_part%10+'0';
        int_part/=10;
        i--;
    }

    decimal_part*=10;

    for(i=rev;i<len;i++)
    {
        if(i==rev)str[i]='.';

        else{
            str[i]=int(decimal_part)%10+'0';
            decimal_part=decimal_part*10;
        }
    }
str[len]=0;
if(str[len-1]=='.')str[len-1]=0;

return str;
    

    
}


void str_functions::printSegment(char *str,int len)
{
    for(int i=0;i<len;i++)
    {
        std::cout<<str[i];
    }
    std::cout<<'\n';
}

void str_functions::add_to_str(char *str1, char*str2, int len)
{
    int n=strlen(str1);
    for(int i=0;i<len;i++)
    {
        str1[i+n]=str2[i];
    }
    str1[len+n]='\0';
}
//012345678
//abcdefghi alb begin=2 end=5  left=ab0 str2=alb right=ghi0
// l1=new char[begin+1]  l2=new char[strlen(str1)-end] 
//ab alb ghi 0-9

void str_functions::strReplace(char *&str1,int begin,int end,char *str2)
{   
    char *finalEq=0;
    char *left=0;
    char *right=0;
   
    if(begin+strlen(str2)+end-1>1)
        finalEq=new char[begin+strlen(str2)+end+2];

    if(begin+1>1)
        left=new char[begin+1];

    if(strlen(str1)-end>1)
        right=new char[strlen(str1)-end];
  
    if(finalEq!=0)
    strcpy(finalEq,"");


if(left!=0){
    if(begin==0)
        strcpy(left,"");
    else 
    {
        strncpy(left,str1,begin);
        left[begin]=0;
    }
    }

if(right!=0){
    if(end!=strlen(str1)-1)
        strcpy(right,str1+end);
    else
        strcpy(right,"");
}

if(finalEq){
   if(left)strcat(finalEq,left);
   strcat(finalEq,str2);
   if(right)strcat(finalEq,right);
  
    delete[] str1;

    str1=new char[strlen(finalEq)+1];
    strcpy(str1,finalEq);
}


if(left!=0){

    delete[] left;

}
if(right!=0)
    delete[] right;

if(finalEq!=0)
    delete[] finalEq;

}

void str_functions::remove_spaces(char *str)
{
    int i=0;
    while(i<strlen(str))
    {
        if(str[i]==' ')
            strcpy(str+i,str+i+1);

        else i++;
    }
}

unsigned int str_functions::findChr(char *str,char ch)
{
    int pos=-1;
    int i=0;
    while(i<strlen(str) && pos==-1)
    {
        if(str[i]==ch)
            pos=i;
        i++;
    }
    return pos;
}
