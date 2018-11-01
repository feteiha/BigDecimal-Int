#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <valarray>

using namespace std;

class bigint
{
    public:
        bigint();
        bigint( string numberStr );
        bigint( long long int numberLL );

        bool    valid( string numberStr );

        void    setNumber( string numberStr );
        void    setNumber( long long int numberLL );
        string  getNumber();
        int     getSize();
        valarray < int > getArr();

        friend bigint addition     ( bigint object1 , bigint object2 );
        friend bigint subtraction  ( bigint object1 , bigint object2 );

        bigint operator+    ( bigint object );
        bigint operator-    ( bigint object );

        string intToStr( long long int num );


    protected:
        valarray < int > result;
    private:
        valarray < int > number;
        int _size;
};

void   maximum      ( bigint& maximum_object , bigint& minimum_object );
void   equal_length ( bigint& maximum_object , bigint& minimum_object );
ostream& operator << ( ostream& out , valarray < int > val );
ostream& operator << ( ostream& out , bigint ob );

bigint addition     ( bigint object1 , bigint object2 );
bigint subtraction  ( bigint object1 , bigint object2 );

#endif // BIGINT_H
