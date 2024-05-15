#include <stdio.h>

double Factorial( double Mathematicians )
{
    double Math = 1;
    if ( Mathematicians == Math )
    {
        return Math;
    }

    return Mathematicians * Factorial(Mathematicians - Math);
}

int main()
{
    double Mathematicians;
    scanf( "%lf", &Mathematicians );
    double Answer = 0;

    if ( Mathematicians == Answer )
    {
        double TheOne = 1;
        Answer = TheOne;
    }
    else
    {
        Answer = Factorial( Mathematicians );
    }

    printf("%lf\n", Answer);
}