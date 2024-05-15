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
double QuadraticFirstRoot( double a, double b, double discriminant)
{
    double res = (-b + sqrt( discriminant ) ) / (2 * a);
}

double QuadraticNumberOfRoots( double discriminant )
{
    double res = 0;
    if ( discriminant > 0 )
    {
        res = 2;
        return res;
    }

    if ( discriminant == 0 )
    {
        res = 1;
        return res;
    }

    if ( discriminant < 0 )
    {
        res = 0;
        return res;
    }
}

// ax^2 + bx + c = 0
void SolvationOfQuadratic( double a, double b, double c )
{
    if ( a == 0)
    {
        printf( "Well, that's not quite a quadratic equation, "
                "smells more like a linear one. Anyway...\n" );

        SolvationOfLinear( b, c );
    }
    else
    {
        double discriminant = Discriminant( a, b, c );
        printf( "Here is the discriminant of your equation:\n" );
        printf( "%lf\n", discriminant );

        double n_of_roots = QuadraticNumberOfRoots( discriminant );
        printf( "The number of roots is:\n" );
        printf( "%lf\n", n_of_roots );

        if ( n_of_roots == 0)
        {
            printf( "No real roots!\n" );
        }
        else
        {
            double first_root = QuadraticFirstRoot( a, b, discriminant );

            printf( "Aaaand here is the first root:\n" );
            printf( "%lf\n", first_root );

            if ( n_of_roots == 2 )
            {
                double second_root = -b / a - first_root;
                printf( "And the second root is:\n" );
                printf( "%lf\n", second_root );
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
