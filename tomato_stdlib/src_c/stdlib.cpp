#include "stdio.h"

extern "C" 
{
void _myread(long unsigned cnt, char *buf);
void _mywrite(long unsigned str_len, const char *str_ptr);
void print_str(const char *str);
void print_num(double x);
double input();
}

extern "C" void print_str(const char *str)
{
    const char *curr = str;
    long unsigned str_len = 0;

    while (*curr != '\0')
    {
        str_len++;
        curr++;
    }
    
    _mywrite(str_len, str);
}

extern "C" void print_num(double x)
{
    printf("%g\n", x);
}

inline bool isspace(char c)
{
    return c == '\n' || c == ' ';
}

inline bool issep(char c)
{
    return c == ',' || c == '.';
}

inline bool isdigit(char c)
{
    return '0' <= c && c <= '9';
}

inline void print_err_msg(char wrong_c)
{
    char err_msg1[] = "Wrong char in the input: ";
    unsigned long str_len1 = sizeof(err_msg1) - 1;
    _mywrite( str_len1, err_msg1 );
    _mywrite(1, &wrong_c);
    char err_msg2[] = "! Meet undefined behaviour...\n"; 
    unsigned long str_len2 = sizeof(err_msg2) - 1;
    _mywrite(str_len2, err_msg2);
}

extern "C" double input()
{
    double res = 0;
    
    //scanf("%lf", &res);
    
    char c = 0;
    double del = 0.1;

    _myread(1, &c);
    while( isspace(c) )
        _myread(1, &c);

    while (!issep(c) && !isspace(c))
    {
        if (!isdigit(c))
        {
            print_err_msg(c);
            return 0;
        }
        res = res * 10 + (c-'0');
        _myread(1, &c);
    }

    if (isspace(c))
        return res;


    if (!issep(c))
    {
        print_err_msg(c);

        return 0;
    }

    _myread(1, &c); // reading sep char

    while (!isspace(c))
    {
        if (!isdigit(c))
        {
            print_err_msg(c);
            return 0;
        }
        res += (c - '0')*del;
        del *= 0.1;
        _myread(1, &c);
    }

    return res;
}