#include "bigint.h"
#include <iostream>
#include <valarray>

using namespace std;


bigint::bigint()
{   // default empty constructor resize with length zero
    this->number.resize(0);
}

bigint::bigint( string numberStr )
{   // parameterize constructor take number in string type
    setNumber( numberStr );
}

bigint::bigint( long long int numberLL )
{
    // parameterize constructor take number in long long int type
    setNumber( intToStr( numberLL ) );
}

string bigint::intToStr( long long int num )
{
    // function that convert the int value to string
    string numberStr = ""; //creates empty string
    if ( num == 0 ) numberStr = "0"; //checks the zero condition
    while( num ) //loops until number isnt bigger than zero
    {
        int rem = num%10; //gets left most digit
        num /= 10; //removes left most digit
        numberStr = char( rem + '0' ) + numberStr; //transfers digit to string
    }
    return numberStr;
}

bool    bigint::valid( string numberStr ) //checks if number is valid
{
    if ( !(numberStr[0] == '+' || numberStr[0] == '-' || isdigit( numberStr[0] ) == true) ) //returns true if valid number
    {
        return false;
    }
    for ( int i = 1; i < numberStr.length(); i++ )
    {
        if ( isdigit( numberStr[ i ] ) == false ) //returns false if there is an unvalid number in the string
        {
            return false;
        }

    }
    return true;
}

void    bigint::setNumber( string numberStr  )
{
    while ( valid( numberStr ) == false ) //lets him re-enter the number if it wasnt unvalid until it is valid
    {
        cin  >> numberStr;
        cout << "Invalid Number \n enter another number :  ";
    }

    int sign = 0; // default sign
    if ( numberStr[0] == '-' ) sign = 1; // change sign if it negative
    if ( !isdigit( numberStr[0] ) )
        numberStr.erase( 0,1 ); //erases the negative

    this->_size = numberStr.length() + 1;
    this->number.resize( this->_size );
    this->number[ numberStr.length() ] = sign;

    for ( int i = 0; i < numberStr.length(); i++ )
        this->number[i] = numberStr[i] - '0';
}

void    bigint::setNumber( long long int numberLL )
{
    // set the long long int into val array to make process on it
    int sign = 0;
    if ( numberLL < 0 ) sign = 1; // detect sign
    numberLL = abs( numberLL );

    this->_size = ceil( log10( numberLL ) ) + 1; // set size of valarray
    this->number.resize( _size ); // resize the array

    this->number[ this->_size - 1 ] = sign;
    for ( int i = this->_size - 2; i > -1; i-- )
    {
        int rem   = numberLL%10;
        numberLL /= 10;

        this->number[ i ] = rem;
    }
}
string  bigint::getNumber()
{
    // function to return the result number as string type
    string numberStr = "";
    if ( this->number[ this->number.size()-1 ] == 0 )
        numberStr += '+';
    else
        numberStr += '-';

    // concatenate the string
    for ( int i = 0; i < this->number.size()-1; i++ )
        numberStr += char( this->number[i] + '0' );

    int counter = 0; char sign = numberStr[0];
    for ( int i = 1; i < numberStr.length(); i++ )
    {
        if ( numberStr[ i ] == '0' ) counter++;
        else
            break;
    }

    // delete the leading zeros
    if ( counter == numberStr.length()-1 ) counter--;

    numberStr.erase( 0 , ++counter );
    numberStr = sign + numberStr;

    return numberStr;
}

int     bigint::getSize()
{
    return this->_size; //returns size of bigint
}

valarray < int > bigint :: getArr()
{
    return this->number; // return the valarray
}


bigint bigint::operator+    ( bigint object )
{
    bigint maximum_object = *this;  //sets first object to maximum
    bigint minimum_object = object; //sets first object to minimum
    bigint sum;                     //creates a new big int to store the sum in it



    equal_length( maximum_object , minimum_object );//makes the length of the two objects equal

    maximum( maximum_object , minimum_object );//puts the bigger object in maximum
    int sign1 = maximum_object.number.size()-1; //sign of maximum object
    int sign2 = minimum_object.number.size()-1;
    int sign_object1 = this->getSize()-1; //sign of first object (the object to the left of the sign)
    int sign_object2 = object.getSize()-1;

//conditions:

    if (this->number[sign_object1] == object.number[sign_object2]) //("+" + "+") or ("-" + "-")
    {
        sum = addition( maximum_object , minimum_object); // addition two numbers
        sum.number[sum.number.size()-1] = maximum_object.number[sign1]; // detect sign of result
    }

    else if (this->number[sign_object1] != object.number[sign_object2]) //("+" + "-") or ("-" + "+")
    {
        sum = subtraction( maximum_object , minimum_object ); // subtract two numbers
        sum.number[sum.number.size()-1] = maximum_object.number[sign1]; // detect sign of result
    }


    return sum;
}

bigint bigint::operator-    ( bigint object )
{
    // default assumption
    bigint maximum_object = *this;
    bigint minimum_object = object;
    bigint difference;

    equal_length( maximum_object , minimum_object ); // add leading zeros
    maximum( maximum_object , minimum_object ); // get maximum number

    int sign1 = maximum_object.number.size()-1;
    int sign2 = minimum_object.number.size()-1;
    int sign_object1 = this->getSize()-1;
    int sign_object2 = object.getSize()-1;

//conditions:

    if ((this->number[sign_object1] == 0) && (object.number[sign_object2] == 1)) // "+" - "-"
    {
        difference = addition ( maximum_object , minimum_object ); //adds the two numbers
        difference.number[difference.number.size()-1] = 0;  //sets sign to positive
    }

    else if((this->number[sign_object1] == 1) && (object.number[sign_object2 == 1]) ) //"-" - "-"
    {
        difference = subtraction( maximum_object , minimum_object ); //adds the two numbers
        difference.number[difference.number.size()-1] = 0; //sets the sign to the sign of the biggest number
    }

    else if((this->number[sign_object1] == 1) && (object.number[sign_object2] == 0)) //"-" - "+"
    {
        difference = addition( maximum_object , minimum_object); // adds the two numbers
        difference.number[difference.number.size()-1] = 1; //Sets sign to negative
    }

    else if((this->number[sign_object1] == 0) && ( object.number[sign_object2] == 0))//"+" - "+"
    {
            difference = subtraction( maximum_object , minimum_object );// subtracts the two numbers
            bigint temp = *this;
            equal_length(temp, maximum_object);
            if (temp.getNumber() == maximum_object.getNumber()){ //checks if left bigger than right
                difference.number[difference.number.size()-1] = 0; //adds positive sign
            }
            else{ //if right is bigger than the left hand side
                difference.number[difference.number.size()-1] = 1; //adds negative sign
            }
    }

    return difference;
 }


void   maximum      ( bigint& maximum_object , bigint& minimum_object )
{
    bool flag = false;

    valarray < int > mx = maximum_object.getArr(); // get valarray
    valarray < int > mn = minimum_object.getArr(); // get valarray

    for ( int i = 0; i <= maximum_object.getSize()-2; i++ )
    {
        if ( mn[ i ] > mx[i] ) // if minimum greater than maximum >> swap
        {
            flag = true;
            break;
        }
        else if ( mx[i] > mn[i] ){ break; }
    }


    if ( flag )
    {
        swap( maximum_object , minimum_object );
    }
}

void   equal_length ( bigint& maximum_object , bigint& minimum_object )
{
    char _sign1 = '+';
    char _sign2 = '+';
    if ( maximum_object.getNumber()[0] == '-' ) _sign1 = '-';
    if ( minimum_object.getNumber()[0] == '-' ) _sign2 = '-';
    long long mxLen = max( maximum_object.getSize() , minimum_object.getSize() );

    string mx = maximum_object.getNumber(); mx = '0' + mx;
    string mn = minimum_object.getNumber(); mn = '0' + mn;
    mxLen++;

    string number1 = ""; number1 += mx[ 0 ];
    string number2 = ""; number2 += mn[ 0 ];

    if ( mx.length() == mxLen )
    {
        for ( int i = 1; i < mx.length(); i++ )
            if ( isdigit( mx[i] ) )
                number1 += mx[i];
    }
    else
    {
        int loop = mxLen - mx.length();
        for ( int i = 0; i < loop; i++ )
        {
            number1 += '0';
        }
        for ( int i = 1; i <= mx.length(); i++ )
        {
            if ( isdigit( mx[i] ) )
                number1 += mx[i];
        }
    }

    if ( mn.length() == mxLen )
    {
        for ( int i = 1; i < mn.length(); i++ )
            if ( isdigit( mn[i] ) )
                number2 += mn[i];
    }
    else
    {
        int loop = mxLen - mn.length();
        for ( int i = 0; i < loop; i++ )
        {
            number2 += '0';
        }
        for ( int i = 1; i < mn.length(); i++ )
        {
            if ( isdigit( mn[i] ) )
                number2 += mn[i];
        }
    }

    maximum_object.setNumber( _sign1 + number1 );
    minimum_object.setNumber( _sign2 + number2 );
}


ostream& operator << ( ostream& out , valarray < int > val )
{
    for ( int i = 0; i < val.size(); i++ )
        out << val[ i ] << " ";
    return out;
}

bigint addition     ( bigint object1 , bigint object2 )
{

    bigint ob3; // object to contain the result
    ob3.number.resize(object1._size );
    ob3._size = object1._size;


    for ( int i = ((object1._size )-2) ; i > -1 ; i-- ){

        // if the sum of two numbers greater than 10
        if (  (object1.number[i]+object2.number[i]) >= 10 ){

            ob3.number[i] = (object1.number[i] + object2.number[i])-10; // sub from 10
            (object1.number[i-1])++; // carry +1 to the next digit
        }
        else
        {
          ob3.number[i] = object1.number[i] + object2.number[i]; // add normally
        }

    }

    return ob3;
}


bigint subtraction  ( bigint object1 , bigint object2 )
{
    bigint ob3;
    ob3.number.resize(object1._size);
    ob3._size = object1._size;

    for ( int i = ((object1._size )-2) ; i > -1 ; i-- )
    {
        // if min number is greater then max number
        if ( object1.number[i] < object2.number[i] )
        {
            (object1.number[i]) += 10; // add 10
            (object1.number[i-1])--; // carry -1 to the next digit

            ob3.number[i] += object1.number[i] - object2.number[i];
        }
        else
            ob3.number[i] += object1.number[i] - object2.number[i]; // sub normally
    }

    return ob3;
}

ostream& operator << ( ostream& out , bigint ob )
{
    string x = ob.getNumber();
    if ( x[0] == '+' ) x.erase( 0,1 );
    out << x << endl;
    return out;
}
