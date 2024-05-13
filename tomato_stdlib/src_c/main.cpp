extern "C"
{
void _myread(long unsigned cnt, char *buf);
void _mywrite(long unsigned str_len, const char *str_ptr);
double input();
void print_num(double x);
void print_int(long unsigned x);
}

int main(  )
{
    print_num(12.345);
}