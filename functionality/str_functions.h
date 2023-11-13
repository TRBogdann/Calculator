
namespace str_functions {
    bool containsCharacter(char *str,int len,char character);
    double string_to_double(char *str,int len);
    char* double_to_string(double number);
    void printSegment(char *str,int len);
    void add_to_str(char *str1, char*str2, int len);
    void strReplace(char *&str1,int begin,int end,char *str2);
    void remove_spaces(char*str);
    unsigned int findChr(char *str,char ch);
}