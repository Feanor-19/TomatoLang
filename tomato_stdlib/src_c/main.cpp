extern "C"
{
void _myread(long unsigned cnt, char *buf);
void _mywrite(long unsigned str_len, const char *str_ptr);
double input();
void print_num(double x);
}

int main(  )
{
    double aaa = input();
    double bbb = input();
    print_num(aaa);
    print_num(bbb);
}