#include <ostream>
#include <string>
#include <thread>

class EquationHandler
{
   public:

   EquationHandler(unsigned int _buffer_size);
   EquationHandler(const EquationHandler& handler);
   EquationHandler& operator=(const EquationHandler& handler);
   ~EquationHandler();

   //friend std::ostream& operator<<(std::ostream &os,const EquationHandler& handler);
   //friend std::istream& operator>>(std::istream &os,const EquationHandler& handler);

   static double powerOfX(char *str,int len,char unk);
   bool paranthesisAreClosed(unsigned int number=1);
   bool onePairClosed(unsigned int number=1);
   bool findFirstSegment(char* str,char operator1, char operator2,unsigned int number=1);
   bool findLastSegment(char* str,int len,char operator1, char operator2,unsigned int number=1);
   bool findInnerEquation(char* str,unsigned int number=1);
   void clearBuffer(unsigned int number=1);


   void setEquation(char* equation);
   void setBufferSize(unsigned int newBufferSize);
   void setUnk(char unknown);
   void setSegment(int start,int end,unsigned int number=1);
   void setParanthesisBuffer(int buffer[6],unsigned int number=2);
   
   double getCoeficientOf(unsigned int power);
   std::string getRunTimeError();
   char* getEquation();
   int getBufferSize();
   int* getParanthesisBuffer(unsigned int number);
   int getSegmentBegining(unsigned int number);
   int getSegmentEnd(unsigned int number);

   private: 
   int updateParanthesisBuffer(char ch,unsigned int number=1);
   void simplifyEcuation(char* &equation,char unk);
   void multiplyEcuations(char* &str1,char* eq1,char* eq2);
   void modifyEcuation(char* &equation,char unk);

   const static char paranthesis[7];
   std::string runTimeError;
   unsigned int buffer_size;
   char unk;
   int paranthesis1[6];
   int paranthesis2[6];
   char* leftHandEquation;
   char* rightHandEquation;
   int start1=0;
   int end1=0;
   int start2=0;
   int end2=0;

};