//#include "stdio.h"

extern "C" 
{
void _myread(long unsigned cnt, char *buf);
void _mywrite(long unsigned str_len, const char *str_ptr);
void print_str(const char *str);
void print_num(double x);
double input();
void print_int(long unsigned x);

void print_str(const char *str)
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

void print_num(double x)
{
    // printf("%g\n", x);

    if (x < 0)
    {
        print_str("-");
        x = -x;
    }

    unsigned long int_part = (unsigned long) x;
    print_int(int_part);
    print_str(".");

    double non_int_part = x - (double) int_part;

    const int pres = 6;
    char dig[pres+1] = {0};

    for(int i = 0; i < pres; i++)
    {
        non_int_part *= 10;
        int_part = (unsigned long) non_int_part;

        dig[i] = (char) int_part + '0';

        non_int_part -= (double) int_part;
    }

    // find last '0'
    for(int i = pres-1; i >= 0; i--)
    {
        if (dig[i] != '0')
        {
            dig[i+1] = '\0';
            break;
        }
    }

    print_str(dig);
    print_str("\n");
}

inline bool myisspace(char c)
{
    return c == '\n' || c == ' ';
}

inline bool myissep(char c)
{
    return c == ',' || c == '.';
}

inline bool myisdigit(char c)
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

double input()
{
    double res = 0;
    
    //scanf("%lf", &res);
    
    char c = 0;
    double del = 0.1;
    bool neg = false;

    _myread(1, &c);
    while( myisspace(c) )
        _myread(1, &c);

    if (c == '-')
    {
        neg = true;
        _myread(1, &c);
    }

    while (!myissep(c) && !myisspace(c))
    {
        if (!myisdigit(c))
        {
            print_err_msg(c);
            return 0;
        }
        res = res * 10 + (c-'0');
        _myread(1, &c);
    }

    if (myisspace(c))
        return res;


    if (!myissep(c))
    {
        print_err_msg(c);

        return 0;
    }

    _myread(1, &c); // reading sep char

    while (!myisspace(c))
    {
        if (!myisdigit(c))
        {
            print_err_msg(c);
            return 0;
        }
        res += (c - '0')*del;
        del *= 0.1;
        _myread(1, &c);
    }

    if (neg)
        res = -res;

    return res;
}
}