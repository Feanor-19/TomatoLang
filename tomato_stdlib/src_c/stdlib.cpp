#include "stdio.h"

extern "C" void _mywrite(long unsigned str_len, const char *str_ptr);
extern "C" void print_str(const char *str);
extern "C" void print_num(double x);
extern "C" double input();

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

extern "C" double input()
{
    double res = 0;
    scanf("%lf", &res);
    return res;
}