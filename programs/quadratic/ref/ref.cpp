#include <stdio.h>
#include <math.h>

double Discriminant( double Apples, double Beetroots, double Carrots )
{
    double Discr = 0;
    Discr = Beetroots*Beetroots - 4 * Apples*Carrots;

    return Discr;
}

// ax + b = 0, a != 0
double LinearRoot( double Aubergines, double Beans )
{
    double Result = 0;
    Result = -Beans / Aubergines;
    return Result;
}

// ax + b = 0
void SolvationOfLinear( double Aubergines, double Beans )
{
    double Nothing = 0;
    if ( Aubergines == 0 )
    {
        if ( Beans == 0)
        {
            printf( "Well, there is kinda the whole infinity and a small carriage of roots...\n" );
        }
        else
        {
            printf( "Quite interesting, that's also not a linear equation. It's not an "
                    "equation at all: there are simply no roots, even imaginary ones!\n" );
        }
    }
    else
    {
        double root = LinearRoot( Aubergines, Beans );

        printf( "Here is the only linear root:\n" );
        printf( "%lf\n", root );
    }
}

//! ax^2 + bx + c = 0, a != 0
double QuadraticFirstRoot( double Apples, double Beetroots, double Dicsr)
{
    double Result = 0;
    Result = (-Beetroots + sqrt( Dicsr ) ) / (2 * Apples);

    return Result;
}

double QuadraticNumberOfRoots( double Dicsr )
{
    double Result = 0;
    double Neutral = 1;
    double Nothing = 0;
    if ( Dicsr > 0 )
    {
        Result = 2*Neutral;
        return Result;
    }

    if ( Dicsr == 0 )
    {
        Result = 1*Neutral;
        return Result;
    }

    if ( Dicsr < 0 )
    {
        Result = 0;
        return Result;
    }
}

// ax^2 + bx + c = 0
void SolvationOfQuadratic( double Apples, double Beetroots, double Carrots )
{
    double Nothing = 0;
    double Neutral = 1;
    if ( Apples == 0)
    {
        printf( "Well, that's not quite a quadratic equation, "
                "smells more like a linear one. Anyway...\n" );

        SolvationOfLinear( Beetroots, Carrots );
    }
    else
    {
        double Discr = Discriminant( Apples, Beetroots, Carrots );
        printf( "Here is the discriminant of your equation:\n" );
        printf( "%lf\n", Discr );

        double NumOfRoots = QuadraticNumberOfRoots( Discr );
        printf( "The number of roots is:\n" );
        printf( "%lf\n", NumOfRoots );

        if ( NumOfRoots == 0)
        {
            printf( "No real roots!\n" );
        }
        else
        {
            double FirstRoot = 0;
            FirstRoot = QuadraticFirstRoot( Apples, Beetroots, Discr );

            printf( "Aaaand here is the first root:\n" );
            printf( "%lf\n", FirstRoot );

            if ( NumOfRoots == 2 )
            {
                double SecondRoot = 0;
                SecondRoot = -Beetroots / Apples - FirstRoot;
                printf( "And the second root is:\n" );
                printf( "%lf\n", SecondRoot );
            }
        }
    }
}

int main()
{
    double Neutral = 1;
    double Nothing = 0;

    printf( "Hi, I can solve quadratic equations, like ax^2 + bx + c = 0! "
            "Do you want to make a try? [1/0]\n" );

    double Ans = 0;
    scanf( "%lf", &Ans );

    while ( Ans != Nothing )
    {
        printf( "Please, enter coefficient a:\n" );
        double Apples = 0;
        scanf( "%lf", &Apples );

        printf( "Please, enter coefficient b:\n" );
        double Beetroots = 0;
        scanf( "%lf", &Beetroots );

        printf( "Please, enter coefficient c:\n" );
        double Carrots = 0;
        scanf( "%lf", &Carrots );

        printf( "Here are the entered coefficients:\n" );
        printf("%lf\n", Apples);
        printf("%lf\n", Beetroots);
        printf("%lf\n", Carrots);

        SolvationOfQuadratic( Apples, Beetroots, Carrots );

        printf( "Done! Do you want to solve another equation? [1/0]\n" );
        
        double tmp;
        scanf( "%lf", &tmp );
        Ans = tmp * Neutral;
    }

    printf( "Goodbye!\n" );
}
