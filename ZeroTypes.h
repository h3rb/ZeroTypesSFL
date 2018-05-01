/*

 ZeroTypes Library
 Open source license: BSD 
 (http://github.com/h3rb/ZeroTypes)

 Author: H. Elwood Gilliland III
 Copyright (c) 2007-2017

*/
/*
 * Modifications copyright (c) 2017 Smith Micro Software, Inc.  All rights reserved.
 * Author: H. Gilliland (hgilliland@smithmicro.com)
 */
#pragma once
#pragma warning (disable:4100)
#pragma warning (disable:4101)

// Call this on application startup.  Inits work strings and the seeder.
void InitZeroTypesLibrary();

void ZIndexed_Rigorous_Test();

#include <string>
#include <cmath>

#if !defined(DEBUG) && defined(_DEBUG)
#define DEBUG _DEBUG
#endif

#ifdef DEBUG
#define OUTPUT(str,...) output__(str, ##__VA_ARGS__)
#else
#define OUTPUT(std,...) 
#endif

// having, true-or-false (diminished meaning of bool) parameter specifiers...
// Used to mark a parameter being presented a bool as a signal rather than a parameter-as-tested-value signal.  (See implementation...)
typedef bool trueorfalse;
typedef bool having; // symbol name idea came after reading about /using/ C++ keyword on http://stackoverflow.com/questions/10747810/what-is-the-difference-between-typedef-and-using-in-c11
// Sometimes the implementation uses the presence of a bool typed parameter to allow for a quick variant of a function/method of same name
// Example can be seen in GridSplitter where presence of "columns_instead_of_rows" parameter activates the feature whether presented with true or false.
// This is a slight brainly optimization that adds functionality where it was already present, and the typedef(s) above simplify programmer interface by
// embedding the nuance right in the code.  Most compilers would treat this as an alias, so bool and Zbool can still be provided when cast,
// but if you see /having/, passing it a bool variable isn't meaningful, you must test its value if it is to mean something.  The alternative
// would be to collude the code with cryptic numbers like "Concatenate2..." ... which is also done in some places, but is avoided where-ever possible.
// Prior to creating these typedefs, the implementation did not specify when true or false would lead to the feature being activated at the parameter level.


// Basic cross-platform soft error reporting function.
// Put a breakpoint on the calls to this to catch your issues with the debugger in debug mode.
void output__(const char *fmt, ...);

// Basic cross-platform string formatting printf style
std::string FMT(const char *fmt, ...);

// POD-type replacements
#define Zb Zbool
#define Zi Zint
#define Zf Zfloat
#define Zd Zdouble
#define Zui Zuint
#define Zus Zushort

// Divide by zero protection and report

#define DIV_BY_ZERO_PROTECTION 1

#if !defined(DIV_BY_ZERO_REPORTING) && ( defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_OUTPUT) )
//#define DIV_BY_ZERO_REPORTING 1
  //  Use /D compiler option to set
#endif

// Unsigned subtraction "wrap" protection and report

#define UNSIGNED_SUBTRACTION_WRAP_PROTECTION 1

#if !defined(UNSIGNED_SUBTRACTION_WRAP_REPORTING) && ( defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_OUTPUT) )
#define UNSIGNED_SUBTRACTION_WRAP_REPORTING 1
#endif

// Unsigned addition "wrap" protection and report

#define UNSIGNED_ADDITION_WRAP_PROTECTION 1

#if !defined(UNSIGNED_ADDITION_WRAP_REPORTING) && ( defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_OUTPUT) )
#define UNSIGNED_ADDITION_WRAP_REPORTING 1
#endif

// Unsigned multiplication "wrap" protection and report

#define UNSIGNED_MULTIPLY_WRAP_PROTECTION 1

#if !defined(UNSIGNED_MULTIPLY_WRAP_REPORTING) && ( defined(_DEBUG) || defined(DEBUG) || defined(DEBUG_OUTPUT) )
#define UNSIGNED_MULTIPLY_WRAP_REPORTING 1
#endif

/// Zbool /////////////////////////////////////////////////////////////////////////////////////////// start

class Zbool {
public:
 bool value;
 Zbool() { value=false; }
 Zbool( bool b ) { this->value=b; }
 operator bool *() { return &value; }
 Zbool *operator()() { return this; }
 Zbool& operator= ( const bool b ) { value=b; return *this; }
 Zbool& operator|= ( const bool b ) { value|=b; return *this; }
 Zbool& operator&= ( const bool b ) { value&=b; return *this; }
 const bool operator-() { return !value; }
 operator bool() { return value; }
};

/// Zbool /////////////////////////////////////////////////////////////////////////////////////////// end

/// Zwas //////////////////////////////////////////////////////////////////////////////////////////// start

class Zwas {
public:
 bool value,was;
 Zwas() { value=was=false; }
 Zwas( bool b ) { this->value=b; was=false; }
 operator bool *() { return &value; }
 Zwas *operator()() { return this; }
 Zwas& operator= ( const bool b ) { was=value; value=b; return *this; }
 Zwas& operator|= ( const bool b ) { value|=b; return *this; }
 Zwas& operator&= ( const bool b ) { value&=b; return *this; }
 void Store() {
  was=value;
 }
 const bool operator-() { return !value; }
 operator bool() { return value; }
};

/// Zwas //////////////////////////////////////////////////////////////////////////////////////////// end

// Forward declarations
class Zbyte;
class Zushort;
class Zuint;
class Zint;
class Zdouble;

/// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// start

class Zfloat {
public:
 float value;
 Zfloat() { value=0.0f; }
 Zfloat( float value ) { this->value=value; }
 std::string toString() { return std::to_string(value);} 
 float abs() { return std::abs(value); }
 operator std::string() { return toString(); }
 operator float() { return value; }
 operator float *() { return &value; }
 Zfloat *operator()() { return this; }
 float operator()( int i ) { return value=(float)i; }
 float operator()( float f ) { return value=f; }
 float operator()( double d ) { return value=(float)d; }
 float operator()( Zbyte &b );
 float operator()( Zuint &i );
 float operator()( Zint &i );
 float operator()( Zfloat &f );
 float operator()( Zdouble &d );
 Zfloat& operator= ( const unsigned char b ) { value=(float) b; return *this; }
 Zfloat& operator= ( const unsigned int i ) { value=(float) i; return *this; }
 Zfloat& operator= ( const int i ) { value=(float) i; return *this; }
 Zfloat& operator= ( const float f ) { value=f; return *this; }
 Zfloat& operator= ( const double d ) { value=(float) d; return *this; }
 Zfloat& operator= ( const Zbyte& b );
 Zfloat& operator= ( const Zuint& i );
 Zfloat& operator= ( const Zint& i );
 Zfloat& operator= ( const Zfloat& f ) { value=f.value; return *this; }
 Zfloat& operator= ( const Zdouble& d );
 Zfloat& operator= ( const std::string& s );
 Zfloat& operator+= ( const Zfloat& f ) { value+=f.value; return *this; }
 Zfloat& operator-= ( const Zfloat& f ) { value-=f.value; return *this; }
 Zfloat& operator*= ( const Zfloat& f ) { value*=f.value; return *this; }
 Zfloat& operator/= ( const Zfloat& f ) { value/=f.value; return *this; }
 Zfloat& operator+= ( const Zint& i );
 Zfloat& operator-= ( const Zint& i );
 Zfloat& operator*= ( const Zint& i );
 Zfloat& operator/= ( const Zint& i );
 Zfloat& operator+= ( const unsigned char f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const unsigned char f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const unsigned char f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const unsigned char f ) { value/=(float)f; return *this; }
 Zfloat& operator+= ( const unsigned short f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const unsigned short f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const unsigned short f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const unsigned short f ) { value/=(float)f; return *this; }
 Zfloat& operator+= ( const int f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const int f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const int f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const int f ) { value/=(float)f; return *this; }
 Zfloat& operator+= ( const unsigned int f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const unsigned int f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const unsigned int f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const unsigned int f ) { value/=(float)f; return *this; }
 Zfloat& operator+= ( const float f ) { value+=f; return *this; }
 Zfloat& operator-= ( const float f ) { value-=f; return *this; }
 Zfloat& operator*= ( const float f ) { value*=f; return *this; }
 Zfloat& operator/= ( const float f ) { value/=f; return *this; }
 Zfloat& operator+= ( const double f ) { value+=(float)f; return *this; }
 Zfloat& operator-= ( const double f ) { value-=(float)f; return *this; }
 Zfloat& operator*= ( const double f ) { value*=(float)f; return *this; }
 Zfloat& operator/= ( const double f ) { value/=(float)f; return *this; }
 Zfloat& operator++ (int) { value+=1.0f; return *this; }
 Zfloat& operator-- (int) { value-=1.0f; return *this; }
 const float operator-() { return -value; }
 bool operator !() { return ( value == 0.0f ); }
// Not used intentionally to create warning:
// operator double() { return (double) value; }
// operator int() { return (int) value; }
// Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
// (mixed type comparisons require explicit casts) is described in the test:
// operator double() { return (double) value; }
// operator int() { return (int) value; }
};

// Mixed type interactions
float operator+ ( const Zfloat& a, const Zint& b );
float operator+ ( const Zint& a, const Zfloat& b );
float operator* ( const Zfloat& a, const Zint& b );
float operator* ( const Zint& a, const Zfloat& b );
// Float and itself
float operator+ ( const Zfloat& a, const Zfloat& b );
float operator- ( const Zfloat& a, const Zfloat& b );
float operator* ( const Zfloat& a, const Zfloat& b );
float operator/ ( const Zfloat& a, const Zfloat& b );
/* Creates C2593 for some reason...
float operator+ ( Zfloat a, Zfloat b );
float operator- ( Zfloat a, Zfloat b );
float operator* ( Zfloat a, Zfloat b );
float operator/ ( Zfloat a, Zfloat b );
*/
// Casted int operations
float operator+ ( const Zfloat& a, int b );
float operator- ( const Zfloat& a, int b );
float operator* ( const Zfloat& a, int b );
float operator/ ( const Zfloat& a, int b );
float operator+ ( int b, const Zfloat& a );
float operator- ( int b, const Zfloat& a );
float operator* ( int b, const Zfloat& a );
float operator/ ( int b, const Zfloat& a );
// Float operations
float operator+ ( const Zfloat& a, float b );
float operator- ( const Zfloat& a, float b );
float operator* ( const Zfloat& a, float b );
float operator/ ( const Zfloat& a, float b );
float operator+ ( float b, const Zfloat& a );
float operator- ( float b, const Zfloat& a );
float operator* ( float b, const Zfloat& a );
float operator/ ( float b, const Zfloat& a );
// Casted double operations (leans toward double precision)
float operator+ ( const Zfloat& a, double b );
float operator- ( const Zfloat& a, double b );
float operator* ( const Zfloat& a, double b );
float operator/ ( const Zfloat& a, double b );
float operator+ ( double b, const Zfloat& a );
float operator- ( double b, const Zfloat& a );
float operator* ( double b, const Zfloat& a );
float operator/ ( double b, const Zfloat& a );
// Boolean operations
bool operator>= ( const Zfloat& a, const Zfloat& b );
bool operator>= ( const Zfloat& a, const Zbyte& b );
bool operator>= ( const Zfloat& a, const Zushort& b );
bool operator>= ( const Zfloat& a, const Zuint& b );
bool operator>= ( const Zfloat& a, const Zint& b );
bool operator>= ( const Zfloat& a, const Zdouble& b );
bool operator>= ( const Zbyte& a, const Zfloat& b );
bool operator>= ( const Zushort& a, const Zfloat& b );
bool operator>= ( const Zuint& a, const Zfloat& b );
bool operator>= ( const Zint& a, const Zfloat& b );
bool operator>= ( const Zdouble& a, const Zfloat& b );
bool operator>= ( const Zfloat& a, int b );
bool operator>= ( const Zfloat& a, float b );
bool operator>= ( const Zfloat& a, double b );
bool operator>= ( int a, const Zfloat& b );
bool operator>= ( float a, const Zfloat& b );
bool operator>= ( double a, const Zfloat& b );
bool operator== ( const Zfloat& a, const Zfloat& b );
bool operator== ( const Zfloat& a, const Zbyte& b );
bool operator== ( const Zfloat& a, const Zushort& b );
bool operator== ( const Zfloat& a, const Zuint& b );
bool operator== ( const Zfloat& a, const Zint& b );
bool operator== ( const Zfloat& a, const Zdouble& b );
bool operator== ( const Zbyte& a, const Zfloat& b );
bool operator== ( const Zushort& a, const Zfloat& b );
bool operator== ( const Zuint& a, const Zfloat& b );
bool operator== ( const Zint& a, const Zfloat& b );
bool operator== ( const Zdouble& a, const Zfloat& b );
bool operator== ( const Zfloat& a, int b );
bool operator== ( const Zfloat& a, float b );
bool operator== ( const Zfloat& a, double b );
bool operator== ( int a, const Zfloat& b );
bool operator== ( float a, const Zfloat& b );
bool operator== ( double a, const Zfloat& b );
bool operator!= ( const Zfloat& a, const Zfloat& b );
bool operator!= ( const Zfloat& a, const Zbyte& b );
bool operator!= ( const Zfloat& a, const Zushort& b );
bool operator!= ( const Zfloat& a, const Zuint& b );
bool operator!= ( const Zfloat& a, const Zint& b );
bool operator!= ( const Zfloat& a, const Zdouble& b );
bool operator!= ( const Zbyte& a, const Zfloat& b );
bool operator!= ( const Zushort& a, const Zfloat& b );
bool operator!= ( const Zuint& a, const unsigned int b );
bool operator!= ( const Zuint& a, const int b );
bool operator!= ( const Zuint& a, const Zfloat& b );
bool operator!= ( const Zint& a, const Zfloat& b );
bool operator!= ( const Zdouble& a, const Zfloat& b );
bool operator!= ( const Zfloat& a, int b );
bool operator!= ( const Zfloat& a, float b );
bool operator!= ( const Zfloat& a, double b );
bool operator!= ( int a, const Zfloat& b );
bool operator!= ( float a, const Zfloat& b );
bool operator!= ( double a, const Zfloat& b );
bool operator<= ( const Zfloat& a, const Zfloat& b );
bool operator<= ( const Zfloat& a, const Zbyte& b );
bool operator<= ( const Zfloat& a, const Zushort& b );
bool operator<= ( const Zfloat& a, const Zuint& b );
bool operator<= ( const Zfloat& a, const Zint& b );
bool operator<= ( const Zfloat& a, const Zdouble& b );
bool operator<= ( const Zbyte& a, const Zfloat& b );
bool operator<= ( const Zushort& a, const Zfloat& b );
bool operator<= ( const Zuint& a, const Zfloat& b );
bool operator<= ( const Zint& a, const Zfloat& b );
bool operator<= ( const Zdouble& a, const Zfloat& b );
bool operator<= ( const Zfloat& a, int b );
bool operator<= ( const Zfloat& a, float b );
bool operator<= ( const Zfloat& a, double b );
bool operator<= ( int a, const Zfloat& b );
bool operator<= ( float a, const Zfloat& b );
bool operator<= ( double a, const Zfloat& b );
bool operator> ( const Zfloat& a, const Zfloat& b );
bool operator> ( const Zfloat& a, const Zbyte& b );
bool operator> ( const Zfloat& a, const Zushort& b );
bool operator> ( const Zfloat& a, const Zuint& b );
bool operator> ( const Zfloat& a, const Zint& b );
bool operator> ( const Zfloat& a, const Zdouble& b );
bool operator> ( const Zbyte& a, const Zfloat& b );
bool operator> ( const Zushort& a, const Zfloat& b );
bool operator> ( const Zuint& a, const Zfloat& b );
bool operator> ( const Zint& a, const Zfloat& b );
bool operator> ( const Zdouble& a, const Zfloat& b );
bool operator> ( const Zfloat& a, int b );
bool operator> ( const Zfloat& a, float b );
bool operator> ( const Zfloat& a, double b );
bool operator> ( int a, const Zfloat& b );
bool operator> ( float a, const Zfloat& b );
bool operator> ( double a, const Zfloat& b );
bool operator< ( const Zfloat& a, const Zfloat& b );
bool operator< ( const Zfloat& a, const Zbyte& b );
bool operator< ( const Zfloat& a, const Zushort& b );
bool operator< ( const Zfloat& a, const Zuint& b );
bool operator< ( const Zfloat& a, const Zint& b );
bool operator< ( const Zfloat& a, const Zdouble& b );
bool operator< ( const Zbyte& a, const Zfloat& b );
bool operator< ( const Zushort& a, const Zfloat& b );
bool operator< ( const Zuint& a, const Zfloat& b );
bool operator< ( const Zint& a, const Zfloat& b );
bool operator< ( const Zdouble& a, const Zfloat& b );
bool operator< ( const Zfloat& a, int b );
bool operator< ( const Zfloat& a, float b );
bool operator< ( const Zfloat& a, double b );
bool operator< ( int a, const Zfloat& b );
bool operator< ( float a, const Zfloat& b );
bool operator< ( double a, const Zfloat& b );

/// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zbyte ////////////////////////////////////////////////////////////////////////////////////////// start

class Zbyte {
public:
 unsigned char value;
 Zbyte() { value=0; }
 Zbyte( unsigned char value ) { this->value=value; }
 operator unsigned char *() { return &value; }
 Zbyte *operator()() { return this; }
 bool Get(const unsigned char bit)          { return ((value) & (1<<(bit))) ? true : false; }
 void Set(const unsigned char bit, const bool on) { value |= (1<<(on?1:0));        }
 unsigned char operator()( unsigned char b ) { return value=b; }
 unsigned char operator()( unsigned int i ) { return value=(unsigned char)i; }
 unsigned char operator()( int i ) { return value=(unsigned char) i; }
 unsigned char operator()( float f ) { return value=(unsigned char) f; }
 unsigned char operator()( double d ) { return value=(unsigned char) d; }
 unsigned char operator()( Zuint &i );
 unsigned char operator()( Zint &i );
 unsigned char operator()( Zfloat &f );
 unsigned char operator()( Zdouble &d );
 Zbyte& operator= ( const unsigned char b ) { value=b; return *this; }
 Zbyte& operator= ( const int i ) { value=(unsigned char)i; return *this; }
 Zbyte& operator= ( const float f ) { value=(unsigned char)f; return *this; }
 Zbyte& operator= ( const double d ) { value=(unsigned char) d; return *this; }
 Zbyte& operator= ( const Zbyte& i ) { value=i.value; return *this; }
 Zbyte& operator= ( const Zuint& i );
 Zbyte& operator= ( const Zint& i );
 Zbyte& operator= ( const Zfloat& f );
 Zbyte& operator= ( const Zdouble& d );
 Zbyte& operator= ( const std::string& s );
 Zbyte& operator+= ( const Zbyte& i ) { value+=i.value; return *this; }
 Zbyte& operator-= ( const Zbyte& i ) { value-=i.value; return *this; }
 Zbyte& operator*= ( const Zbyte& i ) { value*=i.value; return *this; }
 Zbyte& operator/= ( const Zbyte& i ) { value/=i.value; return *this; }
 Zbyte& operator+= ( const unsigned char i ) { value+=i; return *this; }
 Zbyte& operator-= ( const unsigned char i ) { value-=i; return *this; }
 Zbyte& operator*= ( const unsigned char i ) { value*=i; return *this; }
 Zbyte& operator/= ( const unsigned char i ) { value/=i; return *this; }
 Zbyte& operator+= ( const unsigned short i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const unsigned short i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const unsigned short i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const unsigned short i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator+= ( const int i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const int i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const int i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const int i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator+= ( const unsigned int i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const unsigned int i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const unsigned int i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const unsigned int i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator+= ( const float i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const float i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const float i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const float i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator+= ( const double i ) { value+=(unsigned char)i; return *this; }
 Zbyte& operator-= ( const double i ) { value-=(unsigned char)i; return *this; }
 Zbyte& operator*= ( const double i ) { value*=(unsigned char)i; return *this; }
 Zbyte& operator/= ( const double i ) { value/=(unsigned char)i; return *this; }
 Zbyte& operator++ (int) { value+=1; return *this; }
 Zbyte& operator-- (int) { value-=1; return *this; }
 operator unsigned char() { return value; }
 bool operator !() { return ( value == 0 ); }
// Not used intentionally to create warning:
// operator float() { return (float)value; }
// operator double() { return (double)value; }
// Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
// (mixed type comparisons require explicit casts) is described in the test:
// operator float() { return (float) value; }
// operator float() { return (double) value; }
};


unsigned char operator+ ( const Zbyte& a, const Zbyte& b );
unsigned char operator- ( const Zbyte& a, const Zbyte& b );
unsigned char operator* ( const Zbyte& a, const Zbyte& b );
unsigned char operator/ ( const Zbyte& a, const Zbyte& b );
unsigned char operator+ ( Zbyte a, Zbyte b );
unsigned char operator- ( Zbyte a, Zbyte b );
unsigned char operator* ( Zbyte a, Zbyte b );
unsigned char operator/ ( Zbyte a, Zbyte b );
// Casted unsigned int operations
unsigned char operator+ ( const Zbyte& a, unsigned char b );
unsigned char operator- ( const Zbyte& a, unsigned char b );
unsigned char operator* ( const Zbyte& a, unsigned char b );
unsigned char operator/ ( const Zbyte& a, unsigned char b );
unsigned char operator+ ( unsigned char b, const Zbyte& a );
unsigned char operator- ( unsigned char b, const Zbyte& a );
unsigned char operator* ( unsigned char b, const Zbyte& a );
unsigned char operator/ ( unsigned char b, const Zbyte& a );
// Casted int operations
unsigned char operator+ ( const Zbyte& a, int b );
unsigned char operator- ( const Zbyte& a, int b );
unsigned char operator* ( const Zbyte& a, int b );
unsigned char operator/ ( const Zbyte& a, int b );
unsigned char operator+ ( int b, const Zbyte& a );
unsigned char operator- ( int b, const Zbyte& a );
unsigned char operator* ( int b, const Zbyte& a );
unsigned char operator/ ( int b, const Zbyte& a );
// Float operations (leans toward float precision)
unsigned char operator+ ( const Zbyte& a, float b );
unsigned char operator- ( const Zbyte& a, float b );
unsigned char operator* ( const Zbyte& a, float b );
unsigned char operator/ ( const Zbyte& a, float b );
unsigned char operator+ ( float b, const Zbyte& a );
unsigned char operator- ( float b, const Zbyte& a );
unsigned char operator* ( float b, const Zbyte& a );
unsigned char operator/ ( float b, const Zbyte& a );
// Casted double operations (leans toward double precision)
unsigned char operator+ ( const Zbyte& a, double b );
unsigned char operator- ( const Zbyte& a, double b );
unsigned char operator* ( const Zbyte& a, double b );
unsigned char operator/ ( const Zbyte& a, double b );
unsigned char operator+ ( double b, const Zbyte& a );
unsigned char operator- ( double b, const Zbyte& a );
unsigned char operator* ( double b, const Zbyte& a );
unsigned char operator/ ( double b, const Zbyte& a );
// Boolean operations
bool operator>= ( const Zbyte& a, const Zbyte& b );
bool operator>= ( const Zbyte& a, int b );
bool operator>= ( const Zbyte& a, float b );
bool operator>= ( const Zbyte& a, double b );
bool operator>= ( int a, const Zbyte& b );
bool operator>= ( float a, const Zbyte& b );
bool operator>= ( double a, const Zbyte& b );
bool operator== ( const Zbyte& a, const Zbyte& b );
bool operator== ( const Zbyte& a, int b );
bool operator== ( const Zbyte& a, float b );
bool operator== ( const Zbyte& a, double b );
bool operator== ( int a, const Zbyte& b );
bool operator== ( float a, const Zbyte& b );
bool operator== ( double a, const Zbyte& b );
bool operator!= ( const Zbyte& a, const Zbyte& b );
bool operator!= ( const Zbyte& a, int b );
bool operator!= ( const Zbyte& a, float b );
bool operator!= ( const Zbyte& a, double b );
bool operator!= ( int a, const Zbyte& b );
bool operator!= ( float a, const Zbyte& b );
bool operator!= ( double a, const Zbyte& b );
bool operator<= ( const Zbyte& a, const Zbyte& b );
bool operator<= ( const Zbyte& a, int b );
bool operator<= ( const Zbyte& a, float b );
bool operator<= ( const Zbyte& a, double b );
bool operator<= ( int a, const Zbyte& b );
bool operator<= ( float a, const Zbyte& b );
bool operator<= ( double a, const Zbyte& b );
bool operator> ( const Zbyte& a, const Zbyte& b );
bool operator> ( const Zbyte& a, int b );
bool operator> ( const Zbyte& a, float b );
bool operator> ( const Zbyte& a, double b );
bool operator> ( int a, const Zbyte& b );
bool operator> ( float a, const Zbyte& b );
bool operator> ( double a, const Zbyte& b );
bool operator< ( const Zbyte& a, const Zbyte& b );
bool operator< ( const Zbyte& a, int b );
bool operator< ( const Zbyte& a, float b );
bool operator< ( const Zbyte& a, double b );
bool operator< ( int a, const Zbyte& b );
bool operator< ( float a, const Zbyte& b );
bool operator< ( double a, const Zbyte& b );


/// Zbyte ///////////////////////////////////////////////////////////////////////////////////////// end

/// Zushort ////////////////////////////////////////////////////////////////////////////////////////// start

class Zushort {
public:
 unsigned short value;
 Zushort() { value=0; }
 Zushort( unsigned short value ) { this->value=value; }
 operator unsigned short *() { return &value; }
 Zushort *operator()() { return this; }
 unsigned short operator()( unsigned short z ) { return value=(unsigned short)z; }
 unsigned short operator()( unsigned char b ) { return value=(unsigned short)b; }
 unsigned short operator()( unsigned int i ) { return value=(unsigned short)i; }
 unsigned short operator()( int i ) { return value=(unsigned short) i; }
 unsigned short operator()( float f ) { return value=(unsigned short) f; }
 unsigned short operator()( double d ) { return value=(unsigned short) d; }
 unsigned short operator()( Zuint &i );
 unsigned short operator()( Zint &i );
 unsigned short operator()( Zfloat &f );
 unsigned short operator()( Zdouble &d );
 Zushort& operator= ( const unsigned short z ) { value=z; return *this; }
 Zushort& operator= ( const unsigned char b ) { value=(unsigned short)b; return *this; }
 Zushort& operator= ( const int i ) { value=(unsigned short)i; return *this; }
 Zushort& operator= ( const float f ) { value=(unsigned short)f; return *this; }
 Zushort& operator= ( const double d ) { value=(unsigned short) d; return *this; }
 Zushort& operator= ( const Zushort& i ) { value=i.value; return *this; }
 Zushort& operator= ( const Zbyte& i ) { value=(unsigned short)i.value; return *this; }
 Zushort& operator= ( const Zuint& i );
 Zushort& operator= ( const Zint& i );
 Zushort& operator= ( const Zfloat& f );
 Zushort& operator= ( const Zdouble& d );
 Zushort& operator= ( const std::string& s );
 Zushort& operator+= ( const unsigned char i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const unsigned char i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const unsigned char i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const unsigned char i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const unsigned short i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const unsigned short i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const unsigned short i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const unsigned short i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const int i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const int i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const int i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const int i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const unsigned int i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const unsigned int i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const unsigned int i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const unsigned int i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const float i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const float i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const float i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const float i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator+= ( const double i ) { value+=(unsigned short)i; return *this; }
 Zushort& operator-= ( const double i ) { value-=(unsigned short)i; return *this; }
 Zushort& operator*= ( const double i ) { value*=(unsigned short)i; return *this; }
 Zushort& operator/= ( const double i ) { value/=(unsigned short)i; return *this; }
 Zushort& operator++ (int) { value+=1; return *this; }
 Zushort& operator-- (int) { value-=1; return *this; }
 operator unsigned short() { return value; }
 operator int() { return -(int)value; }
 bool operator !() { return ( value == 0 ); }
// Not used intentionally to create warning:
// operator float() { return (float)value; }
// operator double() { return (double)value; }
// Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
// (mixed type comparisons require explicit casts) is described in the test:
// operator float() { return (float) value; }
// operator float() { return (double) value; }
};


unsigned short operator+ ( const Zushort& a, const Zushort& b );
unsigned short operator- ( const Zushort& a, const Zushort& b );
unsigned short operator* ( const Zushort& a, const Zushort& b );
unsigned short operator/ ( const Zushort& a, const Zushort& b );
unsigned short operator+ ( Zushort a, Zushort b );
unsigned short operator- ( Zushort a, Zushort b );
unsigned short operator* ( Zushort a, Zushort b );
unsigned short operator/ ( Zushort a, Zushort b );
// Casted unsigned int operations
unsigned short operator+ ( const Zushort& a, unsigned char b );
unsigned short operator- ( const Zushort& a, unsigned char b );
unsigned short operator* ( const Zushort& a, unsigned char b );
unsigned short operator/ ( const Zushort& a, unsigned char b );
unsigned short operator+ ( unsigned char b, const Zushort& a );
unsigned short operator- ( unsigned char b, const Zushort& a );
unsigned short operator* ( unsigned char b, const Zushort& a );
unsigned short operator/ ( unsigned char b, const Zushort& a );
// Casted int operations
unsigned short operator+ ( const Zushort& a, int b );
unsigned short operator- ( const Zushort& a, int b );
unsigned short operator* ( const Zushort& a, int b );
unsigned short operator/ ( const Zushort& a, int b );
unsigned short operator+ ( int b, const Zushort& a );
unsigned short operator- ( int b, const Zushort& a );
unsigned short operator* ( int b, const Zushort& a );
unsigned short operator/ ( int b, const Zushort& a );
// Float operations (leans toward float precision)
unsigned short operator+ ( const Zushort& a, float b );
unsigned short operator- ( const Zushort& a, float b );
unsigned short operator* ( const Zushort& a, float b );
unsigned short operator/ ( const Zushort& a, float b );
unsigned short operator+ ( float b, const Zushort& a );
unsigned short operator- ( float b, const Zushort& a );
unsigned short operator* ( float b, const Zushort& a );
unsigned short operator/ ( float b, const Zushort& a );
// Casted double operations (leans toward double precision)
unsigned short operator+ ( const Zushort& a, double b );
unsigned short operator- ( const Zushort& a, double b );
unsigned short operator* ( const Zushort& a, double b );
unsigned short operator/ ( const Zushort& a, double b );
unsigned short operator+ ( double b, const Zushort& a );
unsigned short operator- ( double b, const Zushort& a );
unsigned short operator* ( double b, const Zushort& a );
unsigned short operator/ ( double b, const Zushort& a );

/// Zbyte ///////////////////////////////////////////////////////////////////////////////////////// end

/// Zint ////////////////////////////////////////////////////////////////////////////////////////// start

class Zint {
public:
 int value;
 Zint() { value=0; }
 Zint( int value ) { this->value=value; }
 int abs() { return value < 0 ? -value : value; } // Macos does not define abs(int)
 std::string toString() { return std::to_string(value); }
 operator std::string() { return toString(); }
 operator int() { return value; }
 operator int *() { return &value; }
 Zint *operator()() { return this; }
 int operator()( int i ) { return value=i; }
 int operator()( float f ) { return value=(int)f; }
 int operator()( double d ) { return value=(int)d; }
 int operator()( Zbyte &i );
 int operator()( Zuint &i );
 int operator()( Zint &i ) { return value=i.value; }
 int operator()( Zfloat &f );
 int operator()( Zdouble &d );
 Zint& operator= ( const int i ) { value=i; return *this; }
 Zint& operator= ( const float f ) { value=(int)f; return *this; }
 Zint& operator= ( const double d ) { value=(int) d; return *this; }
 Zint& operator= ( const Zint& i ) { value=i.value; return *this; }
 Zint& operator= ( const Zbyte& b );
 Zint& operator= ( const Zuint& i );
 Zint& operator= ( const Zfloat& f );
 Zint& operator= ( const Zdouble& d );
 Zint& operator= ( const std::string& s );
 Zint& operator+= ( const Zint& i ) { value+=i.value; return *this; }
 Zint& operator-= ( const Zint& i ) { value-=i.value; return *this; }
 Zint& operator*= ( const Zint& i ) { value*=i.value; return *this; }
 Zint& operator/= ( const Zint& i ) { value/=i.value; return *this; }
 Zint& operator+= ( const Zfloat& f );
 Zint& operator-= ( const Zfloat& f );
 Zint& operator*= ( const Zfloat& f );
 Zint& operator/= ( const Zfloat& f );
 Zint& operator+= ( const unsigned char i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const unsigned char i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const unsigned char i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const unsigned char i ) { value/=(int)i; return *this; }
 Zint& operator+= ( const unsigned short i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const unsigned short i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const unsigned short i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const unsigned short i ) { value/=(int)i; return *this; }
 Zint& operator+= ( const int i ) { value+=i; return *this; }
 Zint& operator-= ( const int i ) { value-=i; return *this; }
 Zint& operator*= ( const int i ) { value*=i; return *this; }
 Zint& operator/= ( const int i ) { value/=i; return *this; }
 Zint& operator+= ( const unsigned int i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const unsigned int i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const unsigned int i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const unsigned int i ) { value/=(int)i; return *this; }
 Zint& operator+= ( const float i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const float i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const float i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const float i ) { value/=(int)i; return *this; }
 Zint& operator+= ( const double i ) { value+=(int)i; return *this; }
 Zint& operator-= ( const double i ) { value-=(int)i; return *this; }
 Zint& operator*= ( const double i ) { value*=(int)i; return *this; }
 Zint& operator/= ( const double i ) { value/=(int)i; return *this; }
 Zint& operator++ (int) { value+=1; return *this; }
 Zint& operator-- (int) { value-=1; return *this; }
 const int operator-() { return -value; }
// operator size_t() { return (size_t)value; }
 operator unsigned int() { return (unsigned int) value; }
 operator float() { return (float) value; }
 operator double() { return (double) value; }
 bool operator !() { return ( value == 0 ); }
// Not used intentionally to create warning:
// operator float() { return (float)value; }
// operator double() { return (double)value; }
// Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
// (mixed type comparisons require explicit casts) is described in the test:
// operator float() { return (float) value; }
// operator float() { return (double) value; }
};


int operator+ ( const Zint& a, const Zint& b );
int operator- ( const Zint& a, const Zint& b );
int operator* ( const Zint& a, const Zint& b );
int operator/ ( const Zint& a, const Zint& b );
/* Creates C2593 for some reason...
int operator+ ( Zint a, Zint b );
int operator- ( Zint a, Zint b );
int operator* ( Zint a, Zint b );
int operator/ ( Zint a, Zint b );
*/
// Casted int operations
int operator+ ( const Zint& a, int b );
int operator- ( const Zint& a, int b );
int operator* ( const Zint& a, int b );
int operator/ ( const Zint& a, int b );
int operator% ( const Zint& a, int b );
int operator+ ( int b, const Zint& a );
int operator- ( int b, const Zint& a );
int operator* ( int b, const Zint& a );
int operator/ ( int b, const Zint& a );
int operator% ( int b, const Zint& a );
// Float operations (leans toward float precision)
int operator+ ( const Zint& a, float b );
int operator- ( const Zint& a, float b );
int operator* ( const Zint& a, float b );
int operator/ ( const Zint& a, float b );
int operator+ ( float b, const Zint& a );
int operator- ( float b, const Zint& a );
int operator* ( float b, const Zint& a );
int operator/ ( float b, const Zint& a );
// Casted double operations (leans toward double precision)
int operator+ ( const Zint& a, double b );
int operator- ( const Zint& a, double b );
int operator* ( const Zint& a, double b );
int operator/ ( const Zint& a, double b );
int operator+ ( double b, const Zint& a );
int operator- ( double b, const Zint& a );
int operator* ( double b, const Zint& a );
int operator/ ( double b, const Zint& a );
// Modulo
int operator% ( const Zint &a, const Zint &b );
// Boolean operations
bool operator>= ( const Zint& a, const Zint& b );
bool operator>= ( const Zint& a, unsigned int b );
bool operator>= ( const Zint& a, int b );
bool operator>= ( const Zint& a, float b );
bool operator>= ( const Zint& a, double b );
bool operator>= ( unsigned int a, const Zint& b );
bool operator>= ( int a, const Zint& b );
bool operator>= ( float a, const Zint& b );
bool operator>= ( double a, const Zint& b );
bool operator== ( const Zint& a, const Zbyte& b );
bool operator== ( const Zint& a, const Zushort& b );
bool operator== ( const Zint& a, const Zuint& b );
bool operator== ( const Zint& a, const Zdouble& b );
bool operator== ( const Zbyte& a, const Zint& b );
bool operator== ( const Zushort& a, const Zint& b );
bool operator== ( const Zuint& a, const Zint& b );
bool operator== ( const Zdouble& a, const Zint& b );
bool operator== ( const Zint& a, const Zint& b );
bool operator== ( const Zint& a, unsigned int b );
bool operator== ( const Zint& a, int b );
bool operator== ( const Zint& a, float b );
bool operator== ( const Zint& a, double b );
bool operator== ( unsigned int a, const Zint& b );
bool operator== ( int a, const Zint& b );
bool operator== ( float a, const Zint& b );
bool operator== ( double a, const Zint& b );
bool operator!= ( const Zint& a, const Zint& b );
bool operator!= ( const Zint& a, unsigned int b );
bool operator!= ( const Zint& a, int b );
bool operator!= ( const Zint& a, float b );
bool operator!= ( const Zint& a, double b );
bool operator!= ( unsigned int a, const Zint& b );
bool operator!= ( int a, const Zint& b );
bool operator!= ( float a, const Zint& b );
bool operator!= ( double a, const Zint& b );
bool operator<= ( const Zint& a, const Zint& b );
bool operator<= ( const Zint& a, unsigned int b );
bool operator<= ( const Zint& a, int b );
bool operator<= ( const Zint& a, float b );
bool operator<= ( const Zint& a, double b );
bool operator<= ( unsigned int a, const Zint& b );
bool operator<= ( int a, const Zint& b );
bool operator<= ( float a, const Zint& b );
bool operator<= ( double a, const Zint& b );
bool operator> ( const Zint& a, const Zint& b );
bool operator> ( const Zint& a, unsigned int b );
bool operator> ( const Zint& a, int b );
bool operator> ( const Zint& a, float b );
bool operator> ( const Zint& a, double b );
bool operator> ( unsigned int a, const Zint& b );
bool operator> ( int a, const Zint& b );
bool operator> ( float a, const Zint& b );
bool operator> ( double a, const Zint& b );
bool operator< ( const Zint& a, const Zint& b );
bool operator< ( const Zint& a, unsigned int b );
bool operator< ( const Zint& a, int b );
bool operator< ( const Zint& a, float b );
bool operator< ( const Zint& a, double b );
bool operator< ( unsigned int a, const Zint& b );
bool operator< ( int a, const Zint& b );
bool operator< ( float a, const Zint& b );
bool operator< ( double a, const Zint& b );

/// Zint ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zuint ////////////////////////////////////////////////////////////////////////////////////////// start

enum Zuint_bits {
 Zuint_0 =0x1,
 Zuint_1 =0x2,
 Zuint_2 =0x4,
 Zuint_3 =0x8,
 Zuint_4 =0x10,
 Zuint_5 =0x20,
 Zuint_6 =0x40,
 Zuint_7 =0x80,
 Zuint_8 =0x100,
 Zuint_9 =0x200,
 Zuint_10=0x400,
 Zuint_11=0x800,
 Zuint_12=0x1000,
 Zuint_13=0x2000,
 Zuint_14=0x4000,
 Zuint_15=0x8000,
 Zuint_16=0x10000,
 Zuint_17=0x20000,
 Zuint_18=0x40000,
 Zuint_19=0x80000,
 Zuint_20=0x100000,
 Zuint_21=0x200000,
 Zuint_22=0x400000,
 Zuint_23=0x800000,
 Zuint_24=0x1000000,
 Zuint_25=0x2000000,
 Zuint_26=0x4000000,
 Zuint_27=0x8000000,
 Zuint_28=0x10000000,
 Zuint_29=0x20000000,
 Zuint_30=0x40000000,
 Zuint_31=0x80000000
};

class Zuint {
public:
 unsigned int value;
 Zuint() { value=0; }
 Zuint( unsigned int value ) { this->value=value; }
 std::string toString() { return std::to_string(value); }
 operator std::string() { return toString(); }
 operator unsigned int() { return value; }
 operator unsigned int *() { return &value; }
 Zuint *operator()() { return this; }
 unsigned int operator()( unsigned int i ) { return value=i; }
 unsigned int operator()( int i ) { return value=(unsigned int) i; }
 unsigned int operator()( float f ) { return value=(unsigned int)f; }
 unsigned int operator()( double d ) { return value=(unsigned int)d; }
 unsigned int operator()( Zbyte &i );
 unsigned int operator()( Zuint &i ) { return i.value; }
 unsigned int operator()( Zint &i );
 unsigned int operator()( Zfloat &f );
 unsigned int operator()( Zdouble &d );
 bool isOn( unsigned int bitwise_flag ) {
  return ( value & bitwise_flag ) > 0;
 }
 bool isOff( unsigned int bitwise_flag ) { return !isOn(bitwise_flag); }
 void Toggle( unsigned int bitwise_flag, bool on ) {
  if ( on ) value = value | bitwise_flag;
  else value = value & ~bitwise_flag;
 }
 Zuint& operator= ( const unsigned int i ) { value=i; return *this; }
 Zuint& operator= ( const int i ) { value=i; return *this; }
 Zuint& operator= ( const float f ) { value=(int)f; return *this; }
 Zuint& operator= ( const double d ) { value=(int) d; return *this; }
 Zuint& operator= ( const Zuint& i ) { value=i.value; return *this; }
 Zuint& operator= ( const Zbyte& b );
 Zuint& operator= ( const Zint& i );
 Zuint& operator= ( const Zfloat& f );
 Zuint& operator= ( const Zdouble& d );
 Zuint& operator= ( const std::string& s );
 Zuint& operator+= ( const Zuint& i ) { value+=i.value; return *this; }
 Zuint& operator-= ( const Zuint& i ) { value-=i.value; return *this; }
 Zuint& operator*= ( const Zuint& i ) { value*=i.value; return *this; }
 Zuint& operator/= ( const Zuint& i ) { value/=i.value; return *this; }
 Zuint& operator+= ( const Zint& i ) { value+=(unsigned int) i.value; return *this; }
 Zuint& operator-= ( const Zint& i ) { value-=(unsigned int) i.value; return *this; }
 Zuint& operator*= ( const Zint& i ) { value*=(unsigned int) i.value; return *this; }
 Zuint& operator/= ( const Zint& i ) { value/=(unsigned int) i.value; return *this; }
 Zuint& operator+= ( const unsigned char i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const unsigned char i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const unsigned char i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const unsigned char i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator+= ( const unsigned short i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const unsigned short i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const unsigned short i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const unsigned short i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator+= ( const int i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const int i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const int i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const int i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator+= ( const unsigned int i ) { value+=i; return *this; }
 Zuint& operator-= ( const unsigned int i ) { value-=i; return *this; }
 Zuint& operator*= ( const unsigned int i ) { value*=i; return *this; }
 Zuint& operator/= ( const unsigned int i ) { value/=i; return *this; }
 Zuint& operator+= ( const float i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const float i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const float i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const float i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator+= ( const double i ) { value+=(unsigned int) i; return *this; }
 Zuint& operator-= ( const double i ) { value-=(unsigned int) i; return *this; }
 Zuint& operator*= ( const double i ) { value*=(unsigned int) i; return *this; }
 Zuint& operator/= ( const double i ) { value/=(unsigned int) i; return *this; }
 Zuint& operator++ (int) { value+=1; return *this; }
 Zuint& operator-- (int) { value-=1; return *this; }
 operator int() { return (int) value; }
 bool operator !() { return ( value == 0 ); }
// Not used intentionally to create warning:
// operator float() { return (float)value; }
// operator double() { return (double)value; }
// Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
// (mixed type comparisons require explicit casts) is described in the test:
// operator float() { return (float) value; }
// operator float() { return (double) value; }
};

bool operator< ( unsigned int a, const Zuint& b );

unsigned int operator+ ( const Zuint& a, const Zuint& b );
unsigned int operator- ( const Zuint& a, const Zuint& b );
unsigned int operator* ( const Zuint& a, const Zuint& b );
unsigned int operator/ ( const Zuint& a, const Zuint& b );
// Casted unsigned int operations
unsigned int operator+ ( const Zuint& a, int b );
unsigned int operator- ( const Zuint& a, int b );
unsigned int operator* ( const Zuint& a, int b );
unsigned int operator/ ( const Zuint& a, int b );
unsigned int operator+ ( int b, const Zuint& a );
unsigned int operator- ( int b, const Zuint& a );
unsigned int operator* ( int b, const Zuint& a );
unsigned int operator/ ( int b, const Zuint& a );
// Casted int operations
unsigned int operator+ ( const Zuint& a, int b );
unsigned int operator- ( const Zuint& a, int b );
unsigned int operator* ( const Zuint& a, int b );
unsigned int operator/ ( const Zuint& a, int b );
unsigned int operator+ ( int b, const Zuint& a );
unsigned int operator- ( int b, const Zuint& a );
unsigned int operator* ( int b, const Zuint& a );
unsigned int operator/ ( int b, const Zuint& a );
// Float operations (leans toward float precision)
unsigned int operator+ ( const Zuint& a, float b );
unsigned int operator- ( const Zuint& a, float b );
unsigned int operator* ( const Zuint& a, float b );
unsigned int operator/ ( const Zuint& a, float b );
unsigned int operator+ ( float b, const Zuint& a );
unsigned int operator- ( float b, const Zuint& a );
unsigned int operator* ( float b, const Zuint& a );
unsigned int operator/ ( float b, const Zuint& a );
// Casted double operations (leans toward double precision)
unsigned int operator+ ( const Zuint& a, double b );
unsigned int operator- ( const Zuint& a, double b );
unsigned int operator* ( const Zuint& a, double b );
unsigned int operator/ ( const Zuint& a, double b );
unsigned int operator+ ( double b, const Zuint& a );
unsigned int operator- ( double b, const Zuint& a );
unsigned int operator* ( double b, const Zuint& a );
unsigned int operator/ ( double b, const Zuint& a );

/// Zuint ////////////////////////////////////////////////////////////////////////////////////////// end

/// Zdouble ////////////////////////////////////////////////////////////////////////////////////////// start

class Zdouble {
public:
 double value;
 Zdouble() { value=0.0; }
 Zdouble( double value ) { this->value=value; }
 std::string toString() { return std::to_string(value); }
 operator std::string() { return toString(); }
 double abs() { return std::abs(value); }
 operator double() { return value; }
 operator double *() { return &value; }
 Zdouble *operator()() { return this; }
 double operator()( int i ) { return value=(double)i; }
 double operator()( float f ) { return value=(double)f; }
 double operator()( double d ) { return value=d; }
 double operator()( Zbyte &b );
 double operator()( Zuint &i );
 double operator()( Zint &i );
 double operator()( Zfloat &f );
 double operator()( Zdouble &d ) { return d.value; }
 Zdouble& operator= ( const int i ) { value=(double)i; return *this; }
 Zdouble& operator= ( const float f ) { value=(double)f; return *this; }
 Zdouble& operator= ( const double d ) { value=d; return *this; }
 Zdouble& operator= ( const Zbyte& b );
 Zdouble& operator= ( const Zuint& b );
 Zdouble& operator= ( const Zint& i );
 Zdouble& operator= ( const Zfloat& f );
 Zdouble& operator= ( const Zdouble& d ) { value=d.value; return *this; }
 Zdouble& operator= ( const std::string& s );
 Zdouble& operator+= ( const Zbyte& b ) { value+=(double)b.value; return *this; }
 Zdouble& operator-= ( const Zbyte& b ) { value-=(double)b.value; return *this; }
 Zdouble& operator*= ( const Zbyte& b ) { value*=(double)b.value; return *this; }
 Zdouble& operator/= ( const Zbyte& b ) { value/=(double)b.value; return *this; }
 Zdouble& operator+= ( const Zint& i ) { value+=(double)i.value; return *this; }
 Zdouble& operator-= ( const Zint& i ) { value-=(double)i.value; return *this; }
 Zdouble& operator*= ( const Zint& i ) { value*=(double)i.value; return *this; }
 Zdouble& operator/= ( const Zint& i ) { value/=(double)i.value; return *this; }
 Zdouble& operator+= ( const Zuint& i ) { value+=(double)i.value; return *this; }
 Zdouble& operator-= ( const Zuint& i ) { value-=(double)i.value; return *this; }
 Zdouble& operator*= ( const Zuint& i ) { value*=(double)i.value; return *this; }
 Zdouble& operator/= ( const Zuint& i ) { value/=(double)i.value; return *this; }
 Zdouble& operator+= ( const Zfloat& f ) { value+=(double)f.value; return *this; }
 Zdouble& operator-= ( const Zfloat& f ) { value-=(double)f.value; return *this; }
 Zdouble& operator*= ( const Zfloat& f ) { value*=(double)f.value; return *this; }
 Zdouble& operator/= ( const Zfloat& f ) { value/=(double)f.value; return *this; }
 Zdouble& operator+= ( const Zdouble& d ) { value+=d.value; return *this; }
 Zdouble& operator-= ( const Zdouble& d ) { value-=d.value; return *this; }
 Zdouble& operator*= ( const Zdouble& d ) { value*=d.value; return *this; }
 Zdouble& operator/= ( const Zdouble& d ) { value/=d.value; return *this; }
 Zdouble& operator+= ( const unsigned char d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const unsigned char d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const unsigned char d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const unsigned char d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const unsigned short d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const unsigned short d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const unsigned short d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const unsigned short d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const int d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const int d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const int d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const int d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const unsigned int d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const unsigned int d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const unsigned int d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const unsigned int d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const float d ) { value+=(double) d; return *this; }
 Zdouble& operator-= ( const float d ) { value-=(double) d; return *this; }
 Zdouble& operator*= ( const float d ) { value*=(double) d; return *this; }
 Zdouble& operator/= ( const float d ) { value/=(double) d; return *this; }
 Zdouble& operator+= ( const double d ) { value+=d; return *this; }
 Zdouble& operator-= ( const double d ) { value-=d; return *this; }
 Zdouble& operator*= ( const double d ) { value*=d; return *this; }
 Zdouble& operator/= ( const double d ) { value/=d; return *this; }
 Zdouble& operator++ (int) { value+=1.0; return *this; }
 Zdouble& operator-- (int) { value-=1.0; return *this; }
 const double operator-() { return -value; }
 bool operator !() { return ( value == 0.0 ); }
// Not used intentionally to create warning:
// operator float() { return (float) value; }
// operator int() { return (int) value; }
// Causes ambiguity, because this is removed, the resulting issue (no better solution, see C2593)
// (mixed type comparisons require explicit casts) is described in the test:
// operator int() { return (int) value; }
// operator float() { return (float) value; }
};

// Mixed type operations
double operator+ ( const Zdouble& a, const Zfloat& b );
double operator+ ( const Zfloat& a, const Zdouble& b );
double operator+ ( const Zdouble& a, const Zint& b );
double operator+ ( const Zint& a, const Zdouble& b );
double operator* ( const Zdouble& a, const Zfloat& b );
double operator* ( const Zfloat& a, const Zdouble& b );
double operator* ( const Zdouble& a, const Zint& b );
double operator* ( const Zint& a, const Zdouble& b );
// Zdouble and itself
double operator+ ( const Zdouble& a, const Zdouble& b );
double operator- ( const Zdouble& a, const Zdouble& b );
double operator* ( const Zdouble& a, const Zdouble& b );
double operator/ ( const Zdouble& a, const Zdouble& b );
/* Creates C2593 for some reason...
double operator+ ( Zdouble a, Zdouble b );
double operator- ( Zdouble a, Zdouble b );
double operator* ( Zdouble a, Zdouble b );
double operator/ ( Zdouble a, Zdouble b );
*/
// Casted int operations
double operator+ ( const Zdouble& a, int b );
double operator- ( const Zdouble& a, int b );
double operator* ( const Zdouble& a, int b );
double operator/ ( const Zdouble& a, int b );
double operator+ ( int b, const Zdouble& a );
double operator- ( int b, const Zdouble& a );
double operator* ( int b, const Zdouble& a );
double operator/ ( int b, const Zdouble& a );
// Float operations
double operator+ ( const Zdouble& a, float b );
double operator- ( const Zdouble& a, float b );
double operator* ( const Zdouble& a, float b );
double operator/ ( const Zdouble& a, float b );
double operator+ ( float b, const Zdouble& a );
double operator- ( float b, const Zdouble& a );
double operator* ( float b, const Zdouble& a );
double operator/ ( float b, const Zdouble& a );
// Casted double operations (leans toward double precision)
double operator+ ( const Zdouble& a, double b );
double operator- ( const Zdouble& a, double b );
double operator* ( const Zdouble& a, double b );
double operator/ ( const Zdouble& a, double b );
double operator+ ( double b, const Zdouble& a );
double operator- ( double b, const Zdouble& a );
double operator* ( double b, const Zdouble& a );
double operator/ ( double b, const Zdouble& a );
// Boolean operations
bool operator>= ( const Zdouble& a, const Zdouble& b );
bool operator>= ( const Zdouble& a, int b );
bool operator>= ( const Zdouble& a, float b );
bool operator>= ( const Zdouble& a, double b );
bool operator>= ( int a, const Zdouble& b );
bool operator>= ( float a, const Zdouble& b );
bool operator>= ( double a, const Zdouble& b );
bool operator== ( const Zdouble& a, const Zdouble& b );
bool operator== ( const Zdouble& a, int b );
bool operator== ( const Zdouble& a, float b );
bool operator== ( const Zdouble& a, double b );
bool operator== ( int a, const Zdouble& b );
bool operator== ( float a, const Zdouble& b );
bool operator== ( double a, const Zdouble& b );
bool operator!= ( const Zdouble& a, const Zdouble& b );
bool operator!= ( const Zdouble& a, int b );
bool operator!= ( const Zdouble& a, float b );
bool operator!= ( const Zdouble& a, double b );
bool operator!= ( int a, const Zdouble& b );
bool operator!= ( float a, const Zdouble& b );
bool operator!= ( double a, const Zdouble& b );
bool operator<= ( const Zdouble& a, const Zdouble& b );
bool operator<= ( const Zdouble& a, int b );
bool operator<= ( const Zdouble& a, float b );
bool operator<= ( const Zdouble& a, double b );
bool operator<= ( int a, const Zdouble& b );
bool operator<= ( float a, const Zdouble& b );
bool operator<= ( double a, const Zdouble& b );
bool operator> ( const Zdouble& a, const Zdouble& b );
bool operator> ( const Zdouble& a, int b );
bool operator> ( const Zdouble& a, float b );
bool operator> ( const Zdouble& a, double b );
bool operator> ( int a, const Zdouble& b );
bool operator> ( float a, const Zdouble& b );
bool operator> ( double a, const Zdouble& b );
bool operator< ( const Zdouble& a, const Zdouble& b );
bool operator< ( const Zdouble& a, int b );
bool operator< ( const Zdouble& a, float b );
bool operator< ( const Zdouble& a, double b );
bool operator< ( int a, const Zdouble& b );
bool operator< ( float a, const Zdouble& b );
bool operator< ( double a, const Zdouble& b );


/// Zfloat ////////////////////////////////////////////////////////////////////////////////////////// end

// Other ZeroTypes


#define Zp Zpointer
#define Zdis Zdisposable
#define Zdis_manual Zpointer           // Means you gotta dispose yourself.  Used in places where the class wants to use forward declared stuff and can't use Zdis

#ifndef null
#define null nullptr
#else
#error Zpointer.h could not override null as nullptr because null is already defined.
#endif

/// Zpointer //////////////////////////////////////////////////////////////////////////////////////// start

template<class T>
class Zpointer {
public:
 T *pointer;
 Zpointer() { pointer=nullptr; }
 Zpointer( T *value ) { this->pointer=value; }
 ~Zpointer() {
  return;
 }
 Zpointer( Zpointer<T>& p ) { this->pointer=p.pointer; }
 void Delete() {
  if ( pointer ) {
   delete pointer;
   pointer=nullptr;
  }
 }
 void Delete( T *replace ) {
  if ( pointer ) {
   delete pointer;
   pointer=replace;
  }
 }
 operator T*() { return pointer; }
 T operator* ( Zpointer<T>& t ) { return *pointer; }
// T **operator& ( Zpointer<T>& t ) { return &pointer; }
 Zpointer<T>& operator()( T *value ) { pointer=value; return *this; }
 Zpointer<T>& operator()( Zpointer<T>& t ) { pointer=t.pointer; return *this; }
 Zpointer<T>& operator= ( T *value ) { pointer=value; return *this; }
 Zpointer<T>& operator= ( Zpointer<T>& t ) { pointer=t.pointer; return *this; }
 T *operator->() {
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( !pointer ) {
   OUTPUT("Zpointer:->() referenced when null.\n");
  }
#endif
  return pointer;
 }
};

typedef Zpointer<void>   Pvoid;
typedef Zpointer<int>    Pint;
typedef Zpointer<float>  Pfloat;
typedef Zpointer<double> Pdouble;

/*
 * Protected zPointer which only allows itself to be set once,
 * used mainly for debugging.
 */
template<class T>
class pZpointer {
public:
 int set;
 T *pointer;
 pZpointer() { set = 0; pointer = nullptr; }
 pZpointer(T *value) { set = 0; this->pointer = value; }
 ~pZpointer() {
  return;
 }
 pZpointer( pZpointer<T>& p ) { this->pointer=p.pointer; }
 void Delete() {
  if ( pointer ) {
   delete pointer;
   pointer=nullptr;
  }
 }
 operator T*() { return pointer; }
 T operator* ( pZpointer<T>& t ) { return *pointer; }
// T **operator& ( Zpointer<T>& t ) { return &pointer; }
 bool Protected() {
  if ( set == 1 ) {
   OUTPUT("pZpointer Warning: protected pointer assigned twice!\n");
   return false;
  } else set++;
  return true;
 }
 pZpointer<T>& operator()( T *value ) { if (Protected()) return *this; pointer=value; return *this; }
 pZpointer<T>& operator()( Zpointer<T>& t ) { if (Protected()) return *this; pointer=t.pointer; return *this; }
 pZpointer<T>& operator()( pZpointer<T>& t ) { if (Protected()) return *this; pointer=t.pointer; return *this; }
 pZpointer<T>& operator= ( T *value ) { if (Protected()) return *this; pointer=value; return *this; }
 pZpointer<T>& operator= ( Zpointer<T>& t ) { if (Protected()) return *this; pointer=t.pointer; return *this; }
 pZpointer<T>& operator= ( pZpointer<T>& t ) { if (Protected()) return *this; pointer=t.pointer; return *this; }
 T *operator->() {
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( !pointer ) {
   OUTPUT("pZpointer:->() referenced when null.\n");
  }
#endif
  return pointer;
 }
};
#define pZp pZpointer

// Notes from the underground
/*
class Zvoid : public Zpointer<void> {
public:
  Zvoid() { .. }
  Zvoid(void* value) : Zpointer<void>(value) { .. }
  Zvoid(Zvoid& p) : Zpointer<void>(p) { .. } 
  using Zpointer<void>::operator =;
};
 */

// On debugging pointers:  Zpointer could be attached to a historical pointer system
// that keeps track of all assignments, accesses, etc.

/// Zpointer //////////////////////////////////////////////////////////////////////////////////////// end

/// Zdisposable ///////////////////////////////////////////////////////////////////////////////////// start

template<class T>
class Zdisposable {
public:
 T *pointer;
 Zdisposable() {
  pointer=nullptr;
 }
 void I() { Instantiate(); }
 void Instantiate() {
  if ( !pointer ) pointer=new T;
 }
 void Deinstantiate() {
  if ( pointer ) {
   delete pointer;
   pointer=nullptr;
  }
 }
 void Recycle() {
  if ( pointer ) delete pointer;
  pointer=new T;
 }
 void Recycle( T *replacement ) {
  if ( pointer ) delete pointer;
  pointer=replacement;
 }
 operator T*() { return pointer; }
 T *operator= ( T *replacement ) {
  Recycle(replacement);
  return pointer;
 }
 T *operator= ( Zdisposable<T>& t ) {
  if ( pointer ) {
   if ( pointer != t.pointer ) Deinstantiate();
  }
  pointer=t.pointer;
  t.pointer=null;
  return pointer;
 }
 T operator* ( Zdisposable<T>& t ) { return *pointer; }
 T operator& ( Zdisposable<T>& t ) { return &pointer; }
// T **operator& ( Zpointer<T>& t ) { return &pointer; }
 T *operator->() {
  if ( !pointer ) {
   Instantiate();
  }
  return pointer;
 }
 ~Zdisposable() {
  Deinstantiate();
 }
};
#define Zdis Zdisposable

/// Zdisposable ///////////////////////////////////////////////////////////////////////////////////// end

// Lightweight vector.

template<class T>
class ZIndexed {
public:
 T oob;
 T *list;
 size_t unit,length,w,h;
 ZIndexed() {
  list=nullptr;
  w=h=0;
  length=0;
  unit=sizeof(T);
//  ZeroMemory(&oob,(SIZE_T)unit);
  memset(&oob, 0, sizeof(oob));
 }
 ZIndexed( size_t length ) { Size(length); }
 ZIndexed( size_t w, size_t h ) { Size(w,h); }
 bool inBounds( int i ) {
  if ( i < 0 ) return false;
  size_t index=(size_t) i;
  if ( index >= length ) return false;
  return true;
 }
 bool inBounds( int i, int j ) {
  if ( i < 0 || j < 0 ) return false;
  size_t index=(size_t) (i+j*w);
  if ( index >= length ) return false;
  return true;
 }
 void Swap( ZIndexed<T> *values ) {
  T *tempList = list;
  size_t tempLength = length;
  size_t tempW = w;
  size_t tempH = h;
  list=values->list;
  length=values->length;
  w=values->w;
  h=values->h;
  values->list=tempList;
  values->length=tempLength;
  values->w=tempW;
  values->h=tempH;
 }
 T *Increase() {
  size_t newsize=length+1;
  Size(newsize,true);
  return Element((unsigned int) newsize-1);
 }
 void IncreaseW() {
  IncreaseW(w+1);
 }
 void IncreaseH() {
  IncreaseH(h+1);
 }
 void IncreaseW( size_t neww ) {
  if ( neww < w ) { ClipW(neww); return; }
  if ( neww == w ) return;
  if ( h == 0 ) Size(neww,1);
  else {
   size_t desiredLength=neww*h;
   T *newlist;
      try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
   for ( int i=0; i<w; i++ ) for ( int j=0; j<h; j++ ) newlist[i+j*w]=list[i+j*w];
   delete[] list;
   length=desiredLength;
   list=newlist;
   w=neww;
  }
 }
 void IncreaseH( size_t newh ) {
  if ( newh < h ) { ClipH(newh); return; }
  if ( newh == h ) return;
  if ( w == 0 ) Size(1,newh);
  else {
   size_t desiredLength=w*newh;
   T *newlist;
      try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
   for ( int i=0; i<w; i++ ) for ( int j=0; j<h; j++ ) newlist[i+j*w]=list[i+j*w];
   delete[] list;
   length=desiredLength;
   list=newlist;
   h=newh;
  }
 }
 void ClipW() {
  if ( w==1 ) { Size(0); return; }
  else if ( w==0 ) return;
  ClipW(w-1);
 }
 void ClipH() {
  if ( h==1 ) { Size(0); return; }
  else if ( h==0 ) return;
  ClipW(h-1);
 }
 void ClipW( size_t neww ) {
  if ( neww==0 ) Size(0);
  else
  if ( neww > w ) IncreaseW(neww);
  else {
   size_t desiredLength=neww*h;
   T *newlist;
      try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
   for ( int i=0; i<neww; i++ ) for ( int j=0; j<h; j++ ) newlist[i+j*w]=list[i+j*w];
   delete[] list;
   length=desiredLength;
   list=newlist;
   w=neww;
  }
 }
 void ClipH( size_t newh ) {
  if ( newh==0 ) Size(0);
  else
  if ( newh > h ) IncreaseH(newh);
  else {
   size_t desiredLength=w*newh;
   T *newlist;
      try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
   for ( int i=0; i<w; i++ ) for ( int j=0; j<newh; j++ ) newlist[i+j*w]=list[i+j*w];
   delete[] list;
   length=desiredLength;
   list=newlist;
   h=newh;
  }
 }
 void Size( size_t w, size_t h ) {
  Size(w*h);
  this->w=w;
  this->h=h;
 }
 // Cannot have Size(w,h,keep) because it must be arbitrarily made later
 void Size( size_t desiredLength, having keep ) {
  if ( length==desiredLength ) return;
  if ( desiredLength == 0 ) {
   if ( list ) {
    delete[] list;
    list=nullptr;
   }
   length=0;
   return;
  }
  if ( list ) {
   T *newlist;
   try { newlist= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
	return;
   }
   int kept=(int) ( length < desiredLength ? length : desiredLength );
   for ( int i=0; i<kept; i++ ) newlist[i]=list[i];
   delete[] list;
   length=desiredLength;
   list=newlist;
  } else {
   length=desiredLength;
   try { list= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
	return;
   }
  }
 }
 void Size( size_t desiredLength ) {
  if ( length==desiredLength ) return;
  if ( desiredLength == 0 ) {
   if ( list ) delete[] list;
   list=nullptr;
   length=0;
   w=0;
   h=0;
   return;
  }
  if ( list ) {
   delete[] list;
   try { list= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
  } else {
   try { list= new T[desiredLength]; } catch (std::bad_alloc& ba) {
    OUTPUT("NEW: bad_alloc caught: %s requesting %d\n", ba.what(), (int) (sizeof(T)*desiredLength) );
   }
  }
  length=desiredLength;
 }
 T *Element( unsigned int index ) {
  return &list[index];
 }
 T *Element( unsigned int x, unsigned int y ) {
  return &list[x+y*w];
 }
 T *Element( unsigned int index, bool boundaryCheck ) {
  if ( index >= (unsigned int) length ) return nullptr;
  return &list[index];
 }
 T *Element( unsigned int x, unsigned int y, bool boundaryCheck ) {
  unsigned int index=x+y*w;
  if ( index > (unsigned int) length ) return nullptr;
  return &list[index];
 }
 T Value( unsigned int index ) {
  return list[index];
 }
 T Value( unsigned int x, unsigned int y ) { // unbounded
  return list[x+y*w];
 }
 T Value( unsigned int index, bool boundaryCheck ) {
  if ( index >= (unsigned int) length ) return oob;
  return list[index];
 }
 T Value( unsigned int x, unsigned int y, bool boundaryCheck ) {
  int linear=x+y*w;
  if ( linear > (unsigned int) length ) return oob;
  return list[linear];
 }
 T &Wrap(int index) {
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( length == 0 ) {
   OUTPUT("Warning: length was 0 when Indexed<T>.Wrap() was called\n");
   return oob;
  }
#endif
  return (*this)[(index<0?-index:index)%length]; // Macos doesn't have abs(int)
 }
 T &operator[] (unsigned int index) {
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( index >= (unsigned int) length ) {
   OUTPUT("Warning: %d was out of bounds when requested on type %s\n",
    (int) index, typeid(*this).name());
   return oob;
  }
#endif
  return list[index];
 }
 T &operator() (unsigned int x, unsigned int y) {
  unsigned int linear=(unsigned int)(x+y*w);
#if defined(DEBUG) || defined(DEBUG_OUTPUT)
  if ( linear >= (unsigned int) length ) {
   OUTPUT("Warning: %d (%d,%d) was out of bounds when requested on type %s\n",
    linear, (int)x, (int)y, typeid(*this).name());
   return oob;
  }
#endif
  return list[linear];
 }
 T &operator() (unsigned int index) {
  return list[index];
 }
 ~ZIndexed() {
  if ( list ) delete[] list;
 }
};

///////////////////////////////////////////////////////////////////////////

/*******************************************************************
 * Utility macros.
 */
#define PI          3.1415926535897932384626433832795
#define TWO_PI     (3.1415926535897932384626433832795*2.0)
#define HALF_PI    (3.1415926535897932384626433832795/2.0)
#define QUARTER_PI (3.1415926535897932384626433832795/4.0)
#define THREE_QUARTERS_PI HALF_PI+QUARTER_PI

#define PIf          3.1415926535897932384626433832795f
#define TWO_PIf     (3.1415926535897932384626433832795f*2.0f)
#define HALF_PIf    (3.1415926535897932384626433832795f/2.0f)
#define QUARTER_PIf (3.1415926535897932384626433832795f/4.0f)
#define THREE_QUARTERS_PIf HALF_PIf+QUARTER_PIf

#define PI_Simple 3.1415926
#define TWO_PI_Simple 3.1415926*2

#define zEPSILON 1e-6f
#define MACHINE_EPSILON FLT_EPSILON

//#define EPSILON   FLT_EPSILON// 0.000000000000000111022302463

// math
#define BETWEEN(v,A,B)             ( (A)<(B) ? (v) > (A) && (v) < (B) : (v) < (A) && (v) > (B) )
#define BETWEENInclusive(v,A,B)    ( (A)<(B) ? (v) >= (A) && (v) <= (B) : (v) <= (A) && (v) >= (B) )
#define WITHIN(x,y,x1,y1,x2,y2)    ( (x) >= (x1) && (x) <= (x2) && (y) >= (y1) && (y) <= (y2) )
#define WITHIN3D(x,y,z,x1,y1,z1,x2,y2,z2) ( (x) >= (x1) && (x) <= (x2) && (y) >= (y1) && (y) <= (y2) && (z) >= (z1) && (z) <= (z2) )
#define WITHINCLUSIVE(x,y,x1,y1,x2,y2) ( (x) > (x1) && (x) < (x2) && (y) > (y1) && (y) < (y2) )
#define WITHIN75(ar,m)             ( abs( (ar) - (m) ) < (ar)*0.75 )
#define interpolate(l, v0, v32)    ( (v0) + (l) * ((v32)-(v0)) / 32 )
#define INTERPOLATE(min, max, percent)   ( (min) + ((max) - (min) / (percent) == 0 ? 1 : (percent) ) )
#define LERP1(a,b,r)               ( UMIN(a,b) + (UMAX(a,b) - UMIN(a,b)) * r )
#define bLERP1(from,to,r)          ( (to-from) * r )
#define UMIN(a, b)                 ((a) < (b) ? (a) : (b))
#define UMAX(a, b)                 ((a) > (b) ? (a) : (b))
#define URANGE(less, b, more)            ((b) < (less) ? (less) : ((b) > (more) ? (more) : (b))) // clamp B between A and C
#define INRANGE(x,ra,rb,yes,no)    ((x) >= (ra) && (x) <= (rb) ? (yes) : (no))
#define CLAMP(a,b)                 ( (a) < 0 ? 0 : (a) > (b) ? (b) : (a) )
#define CLAMPTO(v,a,b)             ( (v) < (a) ? (a) : ( (v) > (b) ? (b) : (v) ) )
#define UWRAP(a,b,c)               ((b) > (c) ? (b)-(c) : (b) < (a) ? (b)+(c))
#define SQ(a)                      ((a)*(a))
#define SIGN(a)                    ( (a) >= 0 ? 1 : -1 )
#define LINEATE(x,y,x_size)        ( ((x)+(y)*(x_size)) )
#define FINDDESC(x,y,tnum)         ( ((x)*(y)%(tnum)) )
#define NEARBY(a,b,nearness)       ( ((a)-(nearness)) < (b) && ((a)+(nearness)) > b )

#define MIN2MAX(t,a,b) if ( a > b ) { t temp; temp=a; a=b; b=temp; } 
#define MIN2MAXT(t,s,e) if ( s.x > e.x ) { t temp; temp=s.x; s.x=e.x; e.x=temp; } if ( s.y > e.y ) { t temp; temp=s.y; s.y=e.y; e.y=temp; }

#define RANDRANGE(func,max,max2,division) ( ((max)-func(0.0,(max2)))/(func(1.0,division)) )

// Moves numbers toward a value by a delta if not near
#define TOWARDS(v,t,d)         if(BETWEEN(v,(t)-(d),(t)+(d))){}else if((t)>v)v+=(d);else if((t)<(v))v-=(d);
#define TOWARDSTOP(v,t,d)      if(BETWEEN(v,(t)-(d),(t)+(d))){v=t;}else if((t)>v)v+=(d);else if((t)<(v))v-=(d);
//  clip b to a-c
#define RANGE(a, b, c)            ((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
///#define NEARZERO(b)               (RANGE(-EPSILON,b,EPSILON)) /// Does not work!

#define ADIFF(a,b)                 ( (a) < (b) ? ((b)-(a)) : ((a)-(b)) )

////////////////////////////////////////////
// Shorthand used for text input parsing. //
////////////////////////////////////////////
extern bool SKEYDEBUG;
#define SKEYSTARTLOOP    string key; const char *p= st; while(*p!='\0') { p=string_argument_case(p,&key); if ( key.length() < 1 ) continue; /*if ( SKEYDEBUG ) {OUTPUT("-Key: ");OUTPUTLong("###",key,'`');OUTPUT("\n");}*/
#define VSKEYSTART       virtual void fromString( const char *st ) { SKEYSTARTLOOP;
#define SKEYSTART        void fromString( const char *st ) { SKEYSTARTLOOP;
#define SKEYSTARTC(c)    void c::fromString( const char *st ) { SKEYSTARTLOOP;
#define SKEYSTARTNEW(f)  void f( const char *st ) { SKEYSTARTLOOP;
#define SKEYSTARTLU(t)   void fromString t {
#define SKEYPAIR         p=string_argument_case(p,&key); /*if ( SKEYDEBUG ) {OUTPUT( "=Value: ");OUTPUTLong("###",key,'`');OUTPUT("\n");}*/
#define SKEYLIST(t)      SKEYPAIR; Append(new t(key));
#define SKEY(werd,code)  if ( !str_cmp(key.c_str(),werd) ) { code; } else // remove trailing semicolon from call SKEY("this",{that;}) <- no semi on purpose else bugs occur
#define SPARAM(v,t,f)      SKEYPAIR; v=(t) f(key.c_str());
#define SPARAMB(v)         SKEYPAIR; v=( !str_cmp(key.c_str(),"yes") || !str_cmp(key.c_str(),"on") || !str_cmp(key.c_str(),"1") || !str_cmp(key.c_str(),"true") );
#define SPARAMS(v)         SKEYPAIR; v=key;
#define SPARAMString(v)    SKEYPAIR; v=UnStringSpecialCodes(key);
#define SPARAMC(v,b)       SKEYPAIR; FMT(v,b,"%s",key.c_str());
#define SPARAMChar(v)      SKEYPAIR; v=*((char *)key.c_str());
#define SPARAMType(v)      SKEYPAIR; v.fromString(key.c_str());
#define SPARAMZd(t,v)      SKEYPAIR; v->fromString(key.c_str());
#define SPARAMZp(t,v)      SKEYPAIR; v=new t; v->fromString(key.c_str());
#define SPARAMPtr(t,v)     SKEYPAIR; v=new t; v->fromString(key.c_str());
#define SPARAMPtrP(t,u,v)  SKEYPAIR; v=new t u; v->fromString(key.c_str());
#define SPARAMNode(t)      SKEYPAIR; t* X=new t; Append(X); X->fromString(key.c_str());
#define SPARAMNodeD(t,d)   SKEYPAIR; t* X=new t; X->fromString(key.c_str()); if ( d ) Append(X); else delete X;
#define SPARAMImage(v)     SKEYPAIR; v=library.find(key.c_str());
#define SPARAMH(v)         SKEYPAIR; HashCopy(v,(char *)key.c_str());
#define SPARAMVertex(v)    SKEYPAIR; { const char *j=key.c_str(); string k; j=string_argument(j,&k); v.x=(GLfloat)atof((char*)k.c_str()); j=string_argument(j,&k); v.y=(GLfloat)atof((char*)k.c_str()); j=string_argument(j,&k); v.z=(GLfloat)atof((char*)k.c_str()); }
#define SPARAMVertexd(v)   SKEYPAIR; { const char *j=key.c_str(); string k; j=string_argument(j,&k); v.x=(double)atof((char*)k.c_str()); j=string_argument(j,&k); v.y=(double)atof((char*)k.c_str()); j=string_argument(j,&k); v.z=(double)atof((char*)k.c_str()); }
#define SPARAMColor(v)     SKEYPAIR; v.fromString(key.c_str());
#define SPARAMNodePolym(t,f) SKEYPAIR; t* X=f(key); SKEYPAIR; X->fromString(key.c_str()); Append(X);
#define SKEYEND(go)      { if (key.length()>0) {OUTPUT( "%s: Skipping unknown option [%s] ",go,key.c_str());/*OUTPUTLong("###",key,'`');*/OUTPUT("\n");} } } }
#define SKEYENDING(go)   { if (key.length()>0) {OUTPUT( "%s: Skipping unknown option [%s] ",go,key.c_str());/*OUTPUTLong("###",key,'`');*/OUTPUT("\n");} } }
#define SKEYENDER        }
// Used for text output rendering.
#define SOUTSTART         string toString() { string out=string(""); incdent();
#define SOUTSTARTNL       string toString() { string out=string("\n"); incdent();
#define SOUTSTARTB        string toString() { string out=string(""); char buf[4096]; incdent();
#define SOUTSTARTBNL      string toString() { string out=string("\n"); char buf[4096]; incdent();
#define SOUTSTARTBuf(x)   string toString() { string out=string(""); char buf[x]; incdent();
#define SOUTSTARTBufNL(x) string toString() { string out=string("\n"); char buf[x]; incdent();
#define VSOUTSTART         virtual string toString() { string out=string(""); incdent();
#define VSOUTSTARTNL       virtual string toString() { string out=string("\n"); incdent();
#define VSOUTSTARTB        virtual string toString() { string out=string(""); char buf[4096]; incdent();
#define VSOUTSTARTBNL      virtual string toString() { string out=string("\n"); char buf[4096]; incdent();
#define VSOUTSTARTBuf(x)   virtual string toString() { string out=string(""); char buf[x]; incdent();
#define VSOUTSTARTBufNL(x) virtual string toString() { string out=string("\n"); char buf[x]; incdent();
#define SOUT(k,t)         out+=indention+string(k)+string(" {")+t->toString()+string("}\n");
#define SOUTT(k,t)        out+=indention+string(k)+string(" {")+t.toString()+string("}\n");
#define SOUTBE(d,t,b)     out+=indention+string(d)+t->toString()+string(b);
#define SOUTEBE(d,e,b)    out+=indention+string(d)+e+string(b);
#define SOUTbuf           out+=indention+string(buf);
#define SOUTS(k,v)        out+=indention+string(k)+string(" {")+StringSpecialCodes(v)+string("}\n");
#define SOUTB(k,v)        if ( v ) out+=indention+string(k)+string("\n");
#define SOUTInt(k,v)      { char buf2[80]; FMT(buf2,80,"%d",(int)v); out+=indention+string(k)+string(buf2)+string("\n"); }
#define SOUTFloat(k,v)    { char buf2[80]; FMT(buf2,80,"%1.9f",(float)v); out+=indention+string(k)+string(buf2)+string("\n"); }
#define SOUTV(k,t,v,f)    { char buf2[80]; FMT(buf2,80,f,(t)v); out+=indention+string(k)+string(" ")+string(buf2)+string("\n"); }
#define SOUTVx(k,v,f,x)   { char buf2[x]; FMT(buf2,x,f,v); out+=indention+string(k)+string(buf2)+string("\n"); }
#define SOUTEND           decdent(); return out; }

// String IO crib sheet
/*
Input: Stores incoming keys in "string key;", next position (remainder) char *p
SKEYSTARTLOOP       Search Key Start Loop - used internally by other SKEYSTART* variants below, simplest instantiation of fromString method
VSKEYSTART          Virtual Search Key Start - inits the SKEY* variants for input processing, 
SKEYSTART           Search Key Start - simplest form of creating fromString
SKEYSTARTC(c)       Search Key Start (C version) - parameter: c; class name.   Used in .cpp file when the function is deferred in object
SKEYSTARTNEW(f)     Search Key Start "New" - lets you name the function with f parameter
SKEYSTARTLU(t)      Search Skey Start "Look Up" - lets you provide custom parameters, t is the parameters, must start with char *st, must be manually followed by SKEYSTARTLOOP; after you have isolated the string as char *st ex: SKEYSTARTLU( (char *st, bool tInit, Numbers *reference) ) do prep; SKEYSTARTLOOP ... SKEYEND...
SKEYPAIR            Search Key Pair - used internally to these macros by all SPARAM macros, or can be used externally to advance and collect a "key"
SKEYLIST(t)         Search Key List - Used in LinkedList to provide when elements can be allocated with a single string parameter like Append( new t( string ) ) 
SKEY(werd,{code;})  Search Key - lets you pair up a string key with some code, DO NOT PLACE ; AFTER CALLING THIS MACRO, ie: "bill" with code; or use SPARAM encapsulated in {,} like SKEY("bill",{SPARAM(var,type,func);}) etc
SPARAM(v,t,f)       Pair a simple type (t) with a variable (v) by calling function f on the const char *, used with atoi,atof and specialty functions that convert strings to their numeric or enumerated equivalents,ie: SPARAM(x,int,atoi);
SPARAMB(v)          Get boolean values into variable v, where "yes", "on", 1 or "true"
SPARAMS(v)          Load a string without special codes (see StringSpecialCodes function above)
SPARAMString(v)     Load a string with special codes interpreted, use with corresponding output macro SOUTS(k,v)
SPARAMC(v,b)        Fill a static char buffer v[of size b] with the content in the string key;
SPARAMChar(v)       Store the first character of the string key in v
SPARAMType(v)       Call fromString on a type like v.fromString() using the string key
SPARAMPtr(t,v)      Call fromString on a pointer after allocating it
SPARAMPtrP(t,(u),v) Call fromString on a pointer after allocating it using parameters in (u)
SPARAMNode(t)       Allocate and append a new node of type t to a LinkedList (*this) and call fromString(key) on it
SPARAMNodeD(t,d)    Allocate and append a new node of type t to a LinkedList and call fromString(key) on it, then test with expression d and discard in that case.
SPARAMImage(v)      Interpret the string key as a call to library.find();
SPARAMH(v)          Copy the contents of the string key into a Hash() of size 5
SPARAMVertex(v)     Deprecated, use SPARAMType,Ptr - loads a Vertex v using the "simple" style of 3 floats
SPARAMVertexd(v)    Deprecated, use SPARAMType,Ptr - loads a Vertexd v using the "simple" style of 3 doubles
SPARAMColor(v)      Specialty for loading a Crayon v as 4 floats or 4 ints or a color name or a CSS code like #AAFF99 / #AF9
SPARAMNodePolym(t,f)  -- Pass a function name which, based on a string key, returns a newly created, casted polymorphic derived from class t
SKEYEND("go")       go contains a debugger notation if SKEYDEBUG is enabled
SKEYENDING("go")    go contains a debugger notation if SKEYDEBUG is enabled, but lacks the SKEYENDER (final }) leaving room for custom post processing
SKEYENDER           simply the ending } used in conjunction with SKEYENDING if you are doing post-processing
>> Examples are found in the source, search by macro.
Output:
 incdent() increases indention amount
 decdent() decreases indention amount
SOUTSTART           String Out Start - starts the output function increasing indent and allocating string out
SOUTSTARTNL         String Out Start NewLine - starts the output function increasing indent and allocating string out as \n
SOUTSTARTB          String Out Start Buffer - above and allocates a static 'buf' as a char[4096] for use with FMT
SOUTSTARTBNL        String Out Start Buffer New-Line - above with a newline and allocates a static buf[4096] for use with FMT
SOUTSTARTBuf(x)     String Out Start Buffer Size X - lets you set the size of the static buf - warning on stack overflows!
SOUTSTARTBufNL(x)   String Out Start Buffer Size X New-Line - starts the output with a newline and lets you set the size of the static buffer
VSOUTSTART          Virtual version of above
VSOUTSTARTNL        Virtual version of above
VSOUTSTARTB         Virtual version of above
VSOUTSTARTBNL       Virtual version of above
VSOUTSTARTBuf(x)    Virtual version of above
VSOUTSTARTBufNL(x   Virtual version of above
SOUT(k,t)           Adds an indented string key (should match SKEY version) and associated pointer (t->toString() is called)
SOUTPolym(k,t)      Adds an indented string key (should match SKEY version) and associated pointer (t->toString() is called) wrapped in an identity wrapper ie:  base { derived { data } }
SOUTT(k,t)          String Output Type - Same as above but t.toString() is called
SOUTBE(d,t,b)       String Output Begin End - lets you define bookends around the resulting t.toString() 
SOUTEBE(d,e,b)      String Output Expression Begin End - lets you define the expression e instead of t.toString()
SOUTbuf             String Output buf - called after FMT() to append contents of buf, indented
SOUTS(k,v)          String Output String - outputs a k/v pair and calls the StringSpecialCodes() encoder function on v
SOUTB(k,v)          String Output Key if Bool - if v is true then add key k to output
SOUTInt(k,v)        uses a small buffer to write a line containing the k and v like "key 0" where v is an int %d
SOUTFloat(k,v)      uses a small buffer to write a line containing the k and v like "key 0.000f" where v is a float %1.9f
SOUTV(k,t,v,f)      lets you output a simple type t like "key value" where value can be formatted using f for FMT
SOUTVx(k,v,f,x)     x=buf size, output a simple type like "key value" where value can be formatted using f for FMT
SOUTEND             Ends the function, decreasing the indentation level
>> Examples are found in the source, search by macro.
*/


/// Zstring (UTF-8) ("lite" version) ///////////////////////////////////////////////////////////////////////////////////////// start
using namespace std;

class Zstring;
class Strings;

// To keep within stacksize, we must remove bytes, so we'll remove 8k (originally this was 16384)
#define STRING_SIZE          (8192)

extern char buf[STRING_SIZE];
extern char buf2[STRING_SIZE];
extern char buf3[STRING_SIZE];

// strings
#define LOWER(c)                ((c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c))
#define UPPER(c)                ((c) >= 'a' && (c) <= 'z' ? (c)+'A'-'a' : (c))
#define IS_ALPHA(c)             ((c) >= 'A' && (c) <= 'Z' || (c) >= 'a' && (c) <= 'z')
#define IS_VOWEL(c)             ((c) == 'A' || (c) == 'a' || \
                                 (c) == 'E' || (c) == 'e' || \
                                 (c) == 'I' || (c) == 'i' || \
                                 (c) == 'O' || (c) == 'o' || \
                                 (c) == 'U' || (c) == 'u'    )

#define _FILLER(c)     ( c == ' ' || c == ',' || c == '=' || c == '\n' || c == '\r' || c == '\t' )
#define _SEP(c)        ( c == '\'' || c == '"' || c == '\'' )
#define _NESTERS(c)    ( c == '{' || c == '[' || c == '(' )
#define _NESTERE(c)    ( c == '}' || c == ']' || c == ')' )
#define _EXPRESSIVE(c) ( c == '+' || c == '/' || c == '-' || c =='%' || c == '*' || c == '<' || c == '>' )

// Converts common types to strings using FMT()
#define B2S(b) (string(b?"Yes":"No"))
#define I2S(i) (FMT("%d",(int)i).c_str())
#define F2S(f) (FMT("%f",(float)f).c_str())
#define D2S(d) (FMT("%f",(double)d).c_str())
#define F22S(f) (FMT("%1.2f",(float)f).c_str())
#define D22S(d) (FMT("%1.2f",(double)d).c_str())
#define F42S(f) (FMT("%1.4f",(float)f).c_str())
#define D42S(d) (FMT("%1.4f",(double)d).c_str())
#define I2S2(i) (FMT("%d",(int)i))
#define F2S2(f) (FMT("%f",(float)f))
#define D2S2(d) (FMT("%f",(double)d))
#define F22S2(f) (FMT("%1.2f",(float)f))
#define D22S2(d) (FMT("%1.2f",(double)d))
#define F42S2(f) (FMT("%1.4f",(float)f))
#define D42S2(d) (FMT("%1.4f",(double)d))

extern const char string_error;

void rtrim(string& s, const string& delimiters = " \f\n\r\t\v");
void ltrim(string& s, const string& delimiters = " \f\n\r\t\v"); 
void  trim(string& s, const string& delimiters = " \f\n\r\t\v");
// Gather until next substring match or end of string (returns the point right after the substring)
const char *gather_to(const char *argument, const char *substr, string *buf);
// Replace search with substitute one time
void replaceOnce(string& in, string const &search, string const &substitute);
// Replace all with substitute
void replaceAll(string& in, string const &search, string const &substitute);
// Replace all with substitute
string replace_all(const string& in, const string& search, const string& substitute);
// Does the string end with the ending?
bool endsWith(string const &fullString, string const &ending);
// Does the string end with the ending?
bool endsWith(const char *searching, const char *find, bool removePadding);
// Counts the number of "words" (strings of non-spaces separated by spaces) in a string.     Not the best way (should use one_arg)?
int words(const char *argument);
// Compare strings, case insensitive.   * Return true if different (compatibility with historical functions).
bool str_cmp(const char *astr, const char *bstr);
// Compare strings, case insensitive.   * Return true if different (compatibility with historical functions).
bool str_cmp(string astr, string bstr);
// Is the char a digit?
inline bool is_digit(char c);
// Is character in this list of characters
bool char_in(char c, const char *list);
// Compare strings, case sensitive. * Return true if different (compatibility with historical functions).
bool str_cmp_case(const char *astr, const char *bstr);
// Convert to lower case
string lower(string a);
// Return true if an argument is completely numeric.
bool is_integer(const char *arg);
// Return true if an argument is completely numeric.
bool is_decimal(const char *arg);
// Checks for integer using atoi error handling, decimal only (base-10, no floats).  Does not return the value if valid (tiny inefficiency). Source: http://www.gidforums.com/t-17778.html
bool is_int(string k);
// Checks for hexidecimal
bool is_hex(string k);
// checks for float
bool is_float(string k);
// Converts from hex to int
int from_hex(string hex);
// Converts to hex from int
string to_hexidecimal(int i);
// Pick off one argument from a string and return the rest. * Understands quotes and {}=[], treats interim commas and equal signs as space. Uses the stack so not recommended for large strings (use string_argument);
const char *one_argument(const char *args, char *arg_first);
// Pick off one argument from a string and return the rest. * Understands quotes and {}=[], treats interim commas and equal signs as space. Uses the stack so not recommended for large strings (use string_argument);
const char *one_argument_case(const char *args, char *arg_first);
// Pick off one argument from a string and return the rest. * Uses std::string thus dynamic and doesn't use the stack. Understands quotes and {}=[](), treats interim commas and equal signs as space.
const char *string_argument(const char *argument, string *arg_first, bool slash_comments=true, bool pound_comments=true);
// Pick off one argument from a string and return the rest. * Uses std::string thus dynamic and doesn't use the stack. Understands quotes and {}=[](), treats interim commas and equal signs as space.
const char *string_argument(const char *argument, Zstring *arg_firstz);
// Pick off one argument from a string and return the rest without lowering case. * Uses std::string thus dynamic and doesn't use the stack. Understands quotes and {}=[](), treats interim commas and equal signs as space.
const char *string_argument_case(const char *argument, string *arg_first);
// Pick off one argument from a string and return the rest. * Uses std::string thus dynamic and doesn't use the stack. Understands quotes and {}=[](), treats interim commas and equal signs as space.
const char *string_argument_end(const char *argument, string *arg_first, char *sep);
// Compare strings, case insensitive, for prefix matching. * Return true if hay not a prefix of haystack (compatibility with historical functions).
bool str_prefix(const char *astr, const char *bstr);
// Compare strings, case sensitive, for prefix matching. * Return true if astr not a prefix of bstr (compatibility with historical functions).
bool str_prefix_case(const char *astr, const char *bstr);
// Makes a string into its lower-case counterpart
string strtolower(const char *input);
// Compare strings, case insensitive, for match anywhere. * Returns true if shorter string not part of longer string. (compatibility with historical functions).
bool str_infix(const char *astr, const char *bstr);
// Compare strings, case insensitive, for match anywhere. * Returns true if shorter string not part of longer string. (compatibility with historical functions).
bool string_infix(string astr, string bstr);
// Compare strings, case insensitive, for match anywhere. * Returns true if shorter string not part of longer string. (compatibility with historical functions).
bool str_infix_case(const char *astr, const char *bstr);
// Compare strings, case insensitive, for suffix matching. * Return true if astr not a suffix of bstr (compatibility with historical functions).
bool str_suffix(const char *astr, const char *bstr);
// Return a random character from this list, uses uniform()
char randomChar(const char *list);
// Indentation state
extern string indention;
// Increase indentation
void incdent();
// Decrease indentation
void decdent();
// Reset indentation
void nodent();
// Low-brow alphanumeric hash.
string Hash(int len);
// Low-brow hash compare
bool HashCompare5(string *a, string *b);
// Pseudo-
string RomanNumerals(int v);
// Convert forward to back slash
string slash_to_backslash(const char * s);
// Convert backslash to forward slash
string backslash_to_slash(const char * s);
// Make sure there is a trailing forward slash
string trailing_slash(const char *s);
// Make sure there is a trailing back-slash
string trailing_backslash(const char *s);
// Break down a path/filename and get the basename of the deepest element
string basename(const char *path, char sep);


class Zstring {
public:
 string value, result;
 unsigned int length;
 const char *p;
 Zstring() {
  value=string("");
  result=string("");
  length=0;
  p=null;
 }
 Zstring( const char *value ) {
  this->value=string(value);
  result=string("");
  rewind();
 }
 Zstring( const string &value ) {
  this->value=value;
  result=string("");
  rewind();
 }
 Zstring *self() { return this; }
 bool inside( const char * key ) {
  return (value.find(string(key)) != string::npos);
 }
 bool prefix( const char * partial ) {
  return !str_prefix(partial,c_str());
 }
 bool insideCaseless( const char * key ) {
  return str_infix(key,c_str());
 }
 bool is_inside( const char * cloud );
 bool ending( const char *s ) {
  return endsWith(lower(value).c_str(),lower(string(s)).c_str());
 }
 bool Contains( const char *s ) {
  if ( *s == '\0' ) { return true; }
  char start=LOWER(*s);
  rewind();
  const char *w=this->Next();
  while ( *w != '\0' ) {
   if ( (*w) == (start) ) {
    if ( !str_prefix_case(w,s) ) {
     rewind();
     return true;
    }
   }
   w=this->Next();
  }
  rewind();
  return false;
 }
 bool contains( const char *s ) {
  if ( *s == '\0' ) { return true; }
  char start=LOWER(*s);
  rewind();
  const char *w=this->Next();
  while ( *w != '\0' ) {
   if ( LOWER(*w) == (start) ) {
    if ( !str_prefix(w,s) ) {
     rewind();
     return true;
    }
   }
   w=this->Next();
  }
  rewind();
  return false;
 }
 bool contains( char c ) {
  const char *p=value.c_str();
  while ( *p != '\0' ) {
   if ( *p == c ) return true;
   p++;
  }
  return false;
 }
 int count( char c ) {
  int i=0;
  const char *p=value.c_str();
  while ( *p != '\0' ) {
   if ( *p == c ) i++;
   p++;
  }
  return i;
 }
 char At( unsigned int index ) {
  if ( index >= length ) return '\0';
  return value.at(index);
 }
 void Set( unsigned int index, char c ) {
  if ( index == 0 ) {
   value=value.substr(1,length-1);
  } else if ( index == length-1 ) {
   value=value.substr(0,length-2);
   value+=c;
  } else if ( index > length ) return;
  else value=value.substr(0,index-1)+c+value.substr(index+1,length-index-1);
  rewind();
 }
 int first( char c ) {
  const char *p=value.c_str();
  int i=0;
  while ( *p != '\0' ) {
   if ( *p == c ) return i;
   i++;
  }
  return -1;
 }
 const char *first( const Zstring& in ) {
  const char *p=string_argument(in.value.c_str(),&value);
  rewind();
  return p;
 }
 const char *first( const string& in ) {
  const char *p=string_argument(in.c_str(),&value);
  rewind();
  return p;
 }
 const char *first( const char *in ) {
  const char *p=string_argument(in,&value);
  rewind();
  return p;
 }
 char last() { return At(length-1); }
 const char *word( int number, char *out=buf ) {
  rewind();
  for ( int i=0; i<number; i++ ) next(out);
  return out;
 }
 bool word( const char *matches, int number, char *out=buf ) {
  rewind();
  for ( int i=0; i<number; i++ ) next(out);
  return !str_cmp(matches,out);
 }
 char *next( char *out=buf ) {
  p=one_argument(p,out);
  return out;
 }
 char *next_case( char *out=buf ) {
  p=one_argument_case(p,out);
  return out;
 }
 void Limit( const char *in, size_t truncation ) {
  if ( strlen(in) < truncation ) (*this)=in;
  else {
   (*this)="";
   for ( size_t i=0; i<truncation; i++ ) {
    (*this)+=in[i];
   }
  }
 }
 const char *Next() {
  p=string_argument(p,&result);
  return result.c_str();
 }
 const char *Next_case() {
  p=string_argument_case(p,&result);
  return result.c_str();
 }
 const char *Peek() {
  string_argument(p,&result);
  return result.c_str();
 }
 const char *NextSOL() {
  while ( *p != '\0' && *p != '\n' ) p++;
  if ( *p != '\0' && *p == '\n' ) p++;
  if ( *p != '\0' && *p == '\r' ) p++;
  return p;
 }
 void rewind() {
  p=value.c_str();
  length=(unsigned int) this->value.length();
 }
 bool is_number() { return is_integer(value.c_str()) || is_decimal(value.c_str()); }
 int integer() { return atoi(value.c_str()); }
 double decimal() { return atof(value.c_str()); }
 bool Empty() {
  Zstring temp=*this;
  temp/=" ";
  return ( length == 0 || temp.length == 0 );
 }
 void Clear() { value=string(""); length=0; }
 string *operator &() { return &value; } // some debate here
 const char *c_str() { return value.c_str(); }
 operator const char *() { return value.c_str(); }
 operator char *() { return (char *) value.c_str(); }
 operator std::string() { return value; }
 operator std::string*() { return &value; }
 Zstring *operator ++() { return this; }
 void operator= (const char *s ) {
  value=s?string(s):"";
  rewind();
 }
 void operator= (string s) {
  value=s;
  rewind();
 }
 Zstring& operator/= ( string b ) {
  replaceAll(value,b,string(""));
  rewind();
  return *this;
 }
 Zstring& operator/= ( Zstring& b ) {
  replaceAll(value,b,string(""));
  rewind();
  return *this;
 }
 operator int() {
  if (is_decimal(value.c_str())) return (int)(atof(value.c_str()));  // rounding?
  else return (int)atoi(value.c_str());
 }
 int Compare( const char *b ) {  
  const char *p,*q;
  p=value.c_str(); while ( *p != '\0' && !IS_ALPHA(*p) ) p++;
  q=b; while ( *q != '\0' && !IS_ALPHA(*q) ) q++;
  while ( *p!= '\0' && *q!='\0' ) {
   if ( (int) LOWER(*p) > (int) LOWER(*q) ) return 1;
   if ( (int) LOWER(*p) < (int) LOWER(*q) ) return -1;
   p++; while ( *p != '\0' && !IS_ALPHA(*p) ) p++;
   q++; while ( *q != '\0' && !IS_ALPHA(*q) ) q++;
  }
  if ( *p != '\0' ) return 1;
  if ( *q != '\0' ) return -1;
  return 0;
 }
 operator float() { return (float) atof(value.c_str()); }
 operator double() { Zstring result(value); result/="$"; result/=","; return atof(result.value.c_str()); }
 operator unsigned int() { return length; }
 Zstring& operator --(int) { if ( length > 0 ) { value=value.substr(0,value.size()-1); rewind(); } return *this; }
 Zstring& operator --() { if ( length > 0 ) { value=value.substr(1,value.size()); rewind(); } return *this; }
 Zstring& operator +=( unsigned char c ) { value+=c; rewind(); return *this; }
 Zstring& operator +=( char c ) { char buf[2]; buf[0]=c; buf[1]='\0'; value=value+string(buf); rewind(); return *this; }
 Zstring& operator +=( const string& b ) { value+=b; rewind(); return *this; }
 Zstring& operator +=( const Zstring& b ) { value+=b.value; rewind(); return *this; }
 Zstring& operator +=( const char *b ) { value+=string(b); rewind(); return *this; }
 Zstring& operator -=( const Zstring& b ) { replaceOnce(value,b.value,string("")); rewind(); return *this; }
 Zstring& operator -=( const char *b ) { replaceOnce(value,string(b),string("")); rewind(); return *this; }
 Zstring& operator -=( const string& b ) { replaceOnce(value,b,string("")); rewind(); return *this; }
 Zstring& operator -=( char c ) { char buf[2]; buf[0]=c; buf[1]='\0'; replaceAll(value,string(buf),string("")); rewind(); return *this; }
 Zstring& operator /=( char c ) { char buf[2]; buf[0]=c; buf[1]='\0'; replaceOnce(value,string(buf),string("")); rewind(); return *this; }
 Zstring& operator +=( float f ) { value+=FMT(" %1.2f",(float)f); rewind(); return *this; }
 Zstring& operator +=( double d ) { value+=FMT(" %1.4f",(double)d); rewind(); return *this; }
 Zstring& operator +=( int i ) { value+=FMT(" %d",(int)i); rewind(); return *this; }
 Zstring& operator -=( int i ) {
  rewind();
  const char *w=value.c_str();
  while ( i > 0 ) {
   i--;
   w=Next();
  }
  value=string(this->p);
  rewind();
  return *this;
 }
 string Words();
 string LimitTo( int len );
 string WordWrap( int linelen );
 bool operator !() { return ( Empty() ); }
 bool operator () ( const char *partial ) { return !str_prefix(value.c_str(),partial); }
 bool operator () ( const string& partial ) { return !str_prefix(value.c_str(),partial.c_str()); }
 bool operator () ( const char *partial, bool anywhere ) { return !str_infix(value.c_str(),partial); }
 bool operator () ( const string& partial, bool anywhere ) { return !str_infix(value.c_str(),partial.c_str()); }
 char operator[] (unsigned int index) { return At(index); }
 char operator() (unsigned int index) { return At(index%length); }
 Zstring& operator() ( const char *search, const char *replace ) { replaceAll(value,string(search),string(replace)); rewind(); return *this; }
 string operator() ( int start, int count ) {
  return value.substr( start, count );
 }
 void rTrim(const string& delimiters = " \f\n\r\t\v") {
  rtrim(value,delimiters);
  rewind();
 }
 void lTrim(const string& delimiters = " \f\n\r\t\v") {
  ltrim(value,delimiters);
  rewind();
 }
 void Trim(const string& delimiters = " \f\n\r\t\v") {
  trim(value,delimiters);
  rewind();
 }
 bool begins(const char *s) {
  int len=(int)strlen(s);
  if ( len > (int) value.length() ) return false;
  const char *p=value.c_str();
  const char *q=s;
  for ( int i=0; i<len; i++,p++,q++ ) if ( LOWER(*p) != LOWER(*q) ) return false;
  return true;
 }
};

bool operator==( const Zstring& a, const Zstring& b );
bool operator==( const Zstring& a, const char *b );
bool operator==( const char *b , const Zstring& a );
string operator+ ( const Zstring& a, const Zstring& b );
string operator+ ( const Zstring& a, const string& b );
string operator+ ( const string& a, const Zstring& b );
string operator+ ( const Zstring& a, const int& b );
string operator+ ( const Zstring& a, const unsigned int& b );
string operator+ ( const Zstring& a, const float& b );
string operator+ ( const Zstring& a, const double& b );
string operator+ ( const int& a, const Zstring& b );
string operator+ ( const unsigned int& a, const Zstring& b );
string operator+ ( const float& a, const Zstring& b );
string operator+ ( const double& a, const Zstring& b );
string operator+ ( string a, Zint& b );
string operator+ ( string a, Zuint& b );
string operator+ ( string a, Zfloat& b );
string operator+ ( string a, Zdouble& b );
/* Creates C2593
string operator+ ( Zint& a, string b );
string operator+ ( Zuint& a, string b );
string operator+ ( Zfloat& a, string b );
string operator+ ( Zdouble& a, string b );
*/
int operator+ ( Zint& a, Zint& b );
float operator+ ( Zfloat& a, Zfloat& b );
double operator+ ( Zdouble& a, Zdouble& b );
string operator+ ( const Zstring& a, char c );
string operator+ ( char c, const Zstring& a );
string operator- ( const Zstring& a, const Zstring& b );
string operator- ( const Zstring& a, const string& b );
string operator- ( const string& b, const Zstring& a );
string operator- ( const Zstring& a, const char *b );
//string operator- ( const char *b, const Zstring& a );
string operator/ ( const Zstring& a, const Zstring& b );
string operator/ ( const Zstring& a, const string& b );
string operator/ ( const string& b, const Zstring& a );
string operator/ ( const Zstring& a, const char *b );
string operator/ ( const char *b, const Zstring& a );
string operator* ( const Zstring& a, unsigned int i );
int operator* ( const Zstring& a, string b );
int operator* ( string a, const Zstring& b );
int operator* ( const Zstring& a, const char *B );
int operator* ( const Zstring& a, const Zstring& b );

/// Zstring ///////////////////////////////////////////////////////////////////////////////////////// end

// Random Number Stuff, needed for lists to return random elements

void init_seeder(void); // called by InitZeroTypesLibrary();
void reseed(void);
double uniform (void);
double uniform ( bool reseed );
#define PSEUDORAND_MAX 0x7fff
int pseudorandom( unsigned int s, unsigned int x );
double random(double x);
int iround ( float f );
int iround ( double d );
int ilerp( int start, int end, float percent );
int ilerpw( int start, int end, float percent );
int ilerp( int start, int end, double percent );
int ilerpw( int start, int end, double percent );
double double_range( double L, double H );
float float_range( float L, float H );
int number_range( int L, int H );
int upto( int M );
int upto( int M, int seed );
float Gauss();

//////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ListItem and LinkedList

#define CLONE(single,code) single *Duplicate() { single *a=new single; {code} return a; }
#define DUPE(membername) {a->membername=membername;}
#define DUPELIST(membername,membername_single) { EACH(membername->first,membername_single,b) a->membername->Append(b->Duplicate()); }
#define DUPESLIST(membername,membername_single) { EACH(membername.first,membername_single,b) a->membername.Append(b->Duplicate()); }

class ListItem {
public:
 Zint leashes,rtid;
 ListItem *next;
 ListItem *prev;
 ListItem(void) { next=prev=null; }
 virtual ~ListItem() {} // Source: Meyers Effective C++, removed due to vile reprocussions, then re-added due to complaints.
 virtual void Virtual(void) {}
 virtual string identity() { ///RTTI///
  string classname=typeid(*this).name();
  string discard;
  const char *q=string_argument(classname.c_str(),&discard); // discards the words "class or struct"
  return string(q);
 }
 virtual bool is( const char *classnamed ) {
  string id=identity();
  return ( !str_cmp(id.c_str(),classnamed) );
 }
 // Note: there is a bug in MSVC2010EE here that makes the following 'virtual' cause the linker to bust.
 /* virtual */ void fromString( const char *st ) {
  string c=identity();
  OUTPUT("ListItem: fromString() called on base class (RTTI class was: %s).\n",c.c_str());
 }
 virtual string toString() {
  return identity()+string(" default virtual toString");
 }
 //virtual void BinaryRead( BinaryFile *open ) {} // read data from an already open binary file (ifstream method)
 //virtual void BinaryWrite( BinaryFile *open ) {} // write the data to an already open binary file (ifstream method)
 //virtual void KeyedRead( KeyedDataStore *open ) {}
 //virtual void KeyedWrite( KeyedDataStore *open ) {}
 bool isAfter( ListItem *I ) {
  ListItem *c=I;
  while ( c ) {
   c=c->next;
   if ( c==this ) return true;
  }
  return false;
 }
 bool isBefore( ListItem *I ) {
  ListItem *c=I;
  while ( c ) {
   c=c->prev;
   if ( c==this ) return true;
  }
  return false;
 }
};


#define CLONES(single,plural) void Duplicate( plural *in ) { EACH(in->first,single,s) Append(s->Duplicate()); }

// Unfortunately, the following macro does not work. See COLLECTION() as a legacy example of the root of this ONE-MANY-DONE concept.
//#define PLURAL(single,plural,definition) class plural : public LinkedList { public: CLEARLISTRESET(single); definition };
// So, we're going to use triplets instead.

// MSVC 2015 NOTE:  Sometimes the linter will incorrectly lint the MANY() _MANY() PLURAL() and related clauses with "Expected a declaration"  This usually goes away eventually, however it may indicate a problem in the cpp related to the collection class


// These are just renamings of the of the referenced ones below.
// Anonymous
#define _ONE(type_name,code1)        SINGLE(type_name,code1)    
#define _MANY(single,plural,code2)   PLURAL(single,plural,code2)
#define _DONE(type_name)             ENDSET(type_name)          
// Named (usually preferred)
#define ONE(type_name,code1)                                           SINGLE_NAMED(type_name,code1)
#define MANY(single,singleHandle,singleHandles,keyname,plural,code2)   PLURAL_NAMED(single,singleHandle,singleHandles,keyname,plural,code2)
#define DONE(type_name)                                                ENDSET_NAMED(type_name)    

#define VERYMANY(single,singleHandle,singleHandles,singleHandlesHandle,singleHandlesHandles,keyname,plural,code2)  \
 ENDITEM(single); HANDLES(single,singleHandle,singleHandles,keyname); \
 HANDLEHANDLES(singleHandles,singleHandlesHandle,singleHandlesHandles,keyname); \
 LIST(plural,code2) single *named(const char *k) { FOREACH(single,s) if ( !str_cmp(s->name.c_str(),k) ) return s; return null; } single *firstNamed( const char *k ) { FOREACH(single,s) if ( s->name.inside(k) ) return s; return null; } void nameSearch( singleHandles *out, const char *k ) { FOREACH(single,s) if ( s->name.inside(k) ) out->Add(s); } void nameMatches( singleHandles *out, const char *k ) { FOREACH(single,s) if ( !str_cmp(k,s->name.c_str()) ) out->Add(s); } void nameGroup( singleHandles *out, const char *k ) { FOREACH(single,s) if ( s->name.begins(k) ) out->Add(s); }
// Add Zint id; after ONE(), after MANY() use this to generate NextID
#define AUTOKEY(single) int GetNextAvailableID() { int next_id=0; bool found=true; while ( found ) { next_id++; found=false; FOREACH(single,p) if ( p->id == next_id ) { found=true; break; } } return next_id; } single *GetByID( int id ) { FOREACH(single,s) if ( s->id == id ) return s; return null; }
#define ADDAPPEND(single) single *Add() { single *p=new single; p->id=GetNextAvailableID(); Append(p); return p; }
#define DROPHANDLED(single,handle,handles) void Drop( handles *in ) { EACH(in->first,handle,h) { Remove(h->p); delete h->p; } in->Clear(); }
// For childs of ListItem
#define C_ONE(type_name,child,code1) CSINGLE(type_name,child,code1)    
// Childs named (usually preferred)
#define CONEN(type_name,child,code1) CSINGLE_NAMED(type_name,child,code1)    

// Indexed by id (not sorted)
#define IONE(type_name,code1)                                           SINGLE_NAMED(type_name,code1) Zint id;
#define IMANY(single,singleHandle,singleHandles,keyname,plural,code2)   PLURAL_NAMED(single,singleHandle,singleHandles,keyname,plural,code2) AUTOKEY(single); ADDAPPEND(single); KEYWORDSGroup(keyname,single); WORDKEYSGroup(keyname,single); DROPHANDLED(single,singleHandle,singleHandles);
#define IDONE(type_name)                                                ENDSET_NAMED(type_name)    

// Instead of using a template, use these macros to quickly define 'blocks' of one-and-many collection code.
// One
#define ITEM(type_name,code1)  class type_name : public ListItem { public: type_name() : ListItem() { {code1} }
#define ENDITEM(type_name)     };
// Many
#define LIST(type_name,code1)  class type_name : public LinkedList { public: type_name() : LinkedList() { {code1} }
#define ENDLIST(type_name)     CLEARLISTRESET(type_name) };
// Custom Child of One
#define CITEM(type_name,child,code1)  class type_name : public child { public: type_name() : child() { {code1} }
#define CENDITEM(type_name)     };
// One-Many-Done structure
#define SINGLE(type_name,code1)     ITEM(type_name,code1)
#define PLURAL(single,plural,code2) ENDITEM(single); LIST(plural,code2)
#define ENDSET(type_name)           ENDLIST(type_name)
// You can use the following to create a named instance instead of an anonymous instance (default) which is searchable by some default properties.
#define SINGLE_NAMED(type_name,code1)      ITEM(type_name,code1) Zstring name; type_name( const char *n ) { name=n; {code1} } 
#define PLURAL_NAMED(single,singleHandle,singleHandles,keyname,plural,code2)  ENDITEM(single); HANDLES(single,singleHandle,singleHandles,keyname); LIST(plural,code2) single *named(const char *k) { FOREACH(single,s) if ( !str_cmp(s->name.c_str(),k) ) return s; return null; } single *firstNamed( const char *k ) { FOREACH(single,s) if ( s->name.inside(k) ) return s; return null; } void nameSearch( singleHandles *out, const char *k ) { FOREACH(single,s) if ( s->name.inside(k) ) out->Add(s); } void nameMatches( singleHandles *out, const char *k ) { FOREACH(single,s) if ( !str_cmp(k,s->name.c_str()) ) out->Add(s); } void nameGroup( singleHandles *out, const char *k ) { FOREACH(single,s) if ( s->name.begins(k) ) out->Add(s); }
#define ENDSET_NAMED(type_name)            ENDLIST(type_name)

// These are used to expedite override of fromString() code, WORD and TAG are strung together with elses
#define KEYWORDS(code)                  void fromString( const char *s, const char *path_prefix="" ) { OUTPUT("in[%s] ",(typeid(*this).name()) ); Zstring _in(s); const char *w=_in.Next(); while ( *w != '\0' ) { {code} NEXTWORD } }
#define NEXTWORD w=_in.Next();
#define KEYWORD(constcharstring,code)   if ( !str_cmp(w,constcharstring) ) { NEXTWORD {code} }
#define SUBWORDdis(constcharstring,zdis) KEYWORD(constcharstring,{zdis.Recycle(); zdis->fromString(w);})
#define SUBWORD(constcharstring,object)  KEYWORD(constcharstring,{object.fromString(w);})
#define SSUBWORD(constcharstring,object) KEYWORD(constcharstring,{object.fromString(w);})
#define KEYTAG(constcharstring,code)    if ( !str_cmp(w,constcharstring) ) {code}
#define TAGWORD(constcharstring,zbool)   KEYTAG(constcharstring,{zbool=true;})
#define NUMWORD(constcharstring,zvalue)  KEYWORD(constcharstring,{zvalue=w;})
#define TXTWORD(constcharstring,zvalue)  KEYWORD(constcharstring,{zvalue=b64k_decode(w);})
#define ENUMWORD(constcharstring,value,type)   KEYWORD(constcharstring,{value=(type)atoi(w);})
#define SUBFILE(constcharstring,object)  KEYWORD(constcharstring,{string fs=file_as_string(w);object.fromString(fs.c_str());})
#define KEYWORDS_INCLUDE(filenam3,staticclassvar) { OUTPUT("<--Loading file:`%s`---\n",filenam3);  string f=file_as_string(filenam3); staticclassvar.fromString(f.c_str()); }
#define KEYWORDS_PATH_INCLUDE(pathnam3,staticclassvar) { OUTPUT("<--Loading all files from path:`%s`---\n",pathnam3); Strings *list=ls(pathnam3,true,true,true); if ( !list ) return; EACH(list->first,String,s) KEYWORDS_INCLUDE(s->s.c_str(),staticclassvar); delete list; }
// Same as above but lets you put some code for post processing after the key-scanning loop
#define KEYWORDS_POST(code,post) void fromString( const char *s, const char *path_prefix="" ) { OUTPUT("in[%s] ",(typeid(*this).name()) ); Zstring _in(s); const char *w=_in.Next(); while ( *w != '\0' ) { {code} /* do not call NEXTWORD to support KEYWORDS_INCLUDE, call manually */ } {post} }
#define BADKEY(t)                       { OUTPUT("\n>< %s:fromString() Bad keyword `%s`, advancing to next\n",t,w); }
#define BADKEYWORD                      { OUTPUT("\n>< Bad keyword `%s`, advancing to next\n",w); }
// Just some aliases
#define WORD(constcharstring,code) KEYWORD(constcharstring,code)
#define TAG(constcharstring,code)  KEYTAG(constcharstring,code)

// Now for toString() code
#define WORDKEYS(code)                  string toString( const char *path_prefix="" ) { OUTPUT("out[%s] ",(typeid(*this).name()) ); Zstring _out; {code} return _out.value; }
#define WORDKEY(constcharstring,value)  { _out+=constcharstring+string(" {")+value+string("}\n"); }
#define TXTKEY(constcharstring,value)   { if ( strlen(value.c_str()) > 0 ) { _out+=constcharstring+string(" {")+b64k_encode(value.c_str())+string("}\n"); } }
#define NUMBKEY(constcharstring,value)  { _out+=constcharstring+string(" {")+value.toString()+string("}\n"); }
#define ENUMKEY(constcharstring,value)  { _out+=constcharstring+FMT(" %d",(int)value)+string("\n"); }
#define TAGKEY(constcharstring,value)   { if ( value ) _out+=constcharstring+string("\n"); }
#define SUBKEY(constcharstring,object)  { _out+=constcharstring+string(" {")+object->toString()+string("}\n"); }
#define SUBKEYCustom(constcharstring,object,call) { _out+=constcharstring+string(" {")+object->call()+string("}\n"); }
#define SSUBKEY(constcharstring,object) { _out+=constcharstring+string(" {")+object.toString()+string("}\n"); }
#define SSUBKEYCustom(constcharstring,object,call) { _out+=constcharstring+string(" {")+object.call()+string("}\n"); }
#define SUBSETKEY(constcharstring,set,handle) { Zstring subset; EACH(set.first,handle,s) subset+=s->SingleKey()+string(" {")+s->p->toString()+string("}\n"); _out+=constcharstring+string(" {")+subset+string("}\n"); }
#define SUBSETFILE(filenam3,set,handle) { OUTPUT("---Saving file:`%s`-->\n",filenam3); Zstring subset; EACH(set.first,handle,s) subset+=s->SingleKey()+string(" {")+s->p->toString()+string("}\n"); string_as_file(subset.c_str(),filenam3); }
#define SUBSETPATH(pathnam3,prefix,postfix,set,handle) { OUTPUT("---Saving files to path:`%s`-->\n",pathnam3); Zstring subset; Zstring filenam3; int fi=0; EACH(set.first,handle,s) { fi++; subset=s->SingleKey()+string(" {")+s->p->toString()+string("}\n"); filenam3=string(pathnam3)+string(prefix)+I2S(fi)+string(postfix); string_as_file(subset.c_str(),filenam3.c_str()); } }

// Same as above but let you provide a name for the function instead of the default toString and fromString
#define NKEYWORDS(fun,code) void fun( const char *s ) { Zstring in(s); const char *w=in.c_str(); while ( *w != '\0' ) { {code} NEXTWORD } }
#define NWORDKEYS(fun,code) string fun() { Zstring _out; {code} return _out.value; }

#define KEYWORDSGroup(keyname,type) void fromString( const char *s ) { OUTPUT("in<<%s<< ",(typeid(*this).name()) ); int loaded=0; Zstring in(s); const char*w=in.Next(); while ( *w != '\0' ) { if ( !str_cmp(w,keyname) ) { w=in.Next(); type *k=new type; k->fromString(w); Append(k); loaded++; } w=in.Next(); OUTPUT(" < Loaded %d %s\n",loaded,keyname ); } }
#define WORDKEYSGroup(keyname,type) string toString() { OUTPUT("out>>%s>> ",(typeid(*this).name()) ); string out=string("\n"); FOREACH(type,k) out+=keyname+string(" {")+k->toString()+string("}\n"); OUTPUT(" > Saved %d %s\n",count.value,keyname ); return out; }
#define KEYSWORDSGroups(keyname,type) KEYWORDSGroup(keyname,type) WORDKEYSGroup(keyname,type)

// These macros do not work due to problems with Parent->Child virtuals not being called...
//#define SORTABLE(single,code) int Compare( ListItem *a, ListItem *b ) { single *A=(single *)a; single *B=(single *)b; int result=0; {code} return result; }
//#define COMPARABLE(single,code,comparator) int Compare( ListItem *a, ListItem *b, void *value ) { single *A=(single *)a; single *B=(single *)b; comparator *comparing=(comparator *)value; int result=0; {code} return result; }
// The below macro works, because it implements the function on the list.  Better because you can have multiple sorts on the same list.
// Use in the following way:  SORTING(NameOfSort,{/*precomputation*/},{}
#define SORTING(single,SortName,precomputation,compare_neg1_means_earlier,postcomputation)   void SortName() {                    \
  {precomputation}                    \
  if ( count < 2 ) return;            \
  LinkedList list;                    \
  list.first=first; first=null;       \
  list.last=last; last=null;          \
  list.count=count; count=0;          \
  ListItem *q=list.first;             \
  list.Remove(q);                     \
  Append(q);                          \
  while(list.first) {                 \
   ListItem *a=list.first;            \
   list.Remove(a);                    \
   bool inserted=false;               \
   EACH(this->first,ListItem,b) {     \
    int result=0;                     \
    single *A=(single *)a;            \
    single *B=(single *)b;            \
    {compare_neg1_means_earlier}      \
    if ( result < 0 ) {               \
     this->InsertBefore(a,b);         \
     inserted=true;                   \
     break;                           \
    }                                 \
   }                                  \
   if ( !inserted ) Append(a);        \
  }                                   \
  {postcomputation}                   } 


// Class template:
// SINGLE_NAMED();
// PLURAL_NAMED();
// ENDSET_NAMED();
// results in NAMED() class instantiator, which does not work due to C++ language constraints.
// evidence: #define NAMED(single,construct1,class1,plural,construct2,class2) SINGLE_NAMED(single,construct1); class1 PLURAL_NAMED(single,plural,construct2); class2 ENDSET_NAMED(single);

// This version permits a child:
#define CSINGLE(type_name,child,code1)       CITEM(type_name,child,code1)
// For named searchable lists:
#define CSINGLE_NAMED(type_name,child,code1) CITEM(type_name,child,code1) Zstring name; type_name( const char *n ) { name=n; code1 } 

// Example usage and base override:
// SINGLE(single,{});          (put methods,etc relevant to a single element here)
// PLURAL(single,plural,{});   (put methods,etc relevant to the group here)
// ENDSET(plural);             (ends the section)
// HANDLED(single,...          (extension functions for creation secondary reference, auto generates code for you)
// HANDLED(plural,...          (" ")

#define CLEARLIST(t)   void Clear() { \
   t *n; for ( t *p=(t *) first; p; p=n ) { \
    n=(t *)(p->next); delete p; \
   } \
  }
#define CLEARLISTRESET(t)   void Clear() { \
   t *n; for ( t *p=(t *) first; p; p=n ) { \
    n=(t *)(p->next); delete p; \
   } \
   first=null; last=null; count=0; \
  }
#define ADDLIST(t,r,h)  void Add( t *p ) { h *s= new h(); s->r=p; Append(s); }
#define ADDLISTNAMED(a,t,r,h) void Add( t *p ) { h *s= new h(); s->r=p; s->name=a; Append(s); }
#define FOREACH(t,v)  for ( t *v=(t *) first; v; v=(t *) v->next )
/* Will not work: ??? */
#define FOREACHN(t,v,c) { t *n; for ( t *v=(t *) first; v; v=n ) { n=(t *) v->next; {c} } }
#define FOREACHREV(t,v) for ( t *v=(t *) last; v; v=(t *) v->prev )
#define EACH(head,t,v)  for ( t *v=(t *) head; v; v=(t *) v->next )
#define EACHREV(last,t,v)  for ( t *v=(t *) last; v; v=(t *) v->prev )
#define EACHN(head,t,v,c) { t *n; for ( t *v=(t *) head; v; v=n ) { n=(t *) v->next; {c} } }
#define EACHPAIR(head1,t,v,head2,tt,v2,c)  { t *v=(t *) head1; tt *v2=(tt *)head2; \
 while ( v && v2 ) { \
 {c} \
 v=(t *)v->next; v2=(tt *)v2->next; \
 } }

/* Does not work: */
//#define EACH2(head,t,v,head2,t2,v2,c)  { t *v=(t *) head; t2 *v2=(t2 *)head2; while ( v && v2 ) { c { v=(t *)v->next; v2=(t2 *)v2->next ); } }; }

// These macros are the way to make all objects in a list call the same simple function, such as Between() or Render() or Init() etc.
#define CALLEACH(single,function) void function() { FOREACH(single,s) s->function(); }
#define CALLEACH1(single,function,code_after) void function() { FOREACH(single,s) { s->function(); } code_after }
#define CALLEACH2(single,function,code_each) void function() { FOREACH(single,s) { s->function(); code_each } }
#define CALLEACH3(single,function,code_each,code_after) void function() { FOREACH(single,s) { s->function(); code_each } code_after }
#define CALLEACH4(single,_prototype,_call,code_after) void _prototype { FOREACH(single,s) { _call } code_after }

// These macros do the same as above but preserve the 'next' pointer so that the object can be removed from the list in-transit.
#define CALLEACHN(single,function) void function() { FOREACHN(single,s) s->function(); }
#define CALLEACHN1(single,function,code_after) void function() { FOREACHN(single,s) { s->function(); } code_after }
#define CALLEACHN2(single,function,code_each) void function() { FOREACHN(single,s) { s->function(); code_each } }
#define CALLEACHN3(single,function,code_each,code_after) void function() { FOREACHN(single,s) { s->function(); code_each } code_after }
#define CALLEACHN4(single,_prototype,_call,code_after) void _prototype { FOREACHN(single,s) { _call } code_after }

// Specialized versions of callback used in the scripting language (see references)
#define RENDERLIST(ts,t) class ts : public LinkedList { public: CLEARLISTRESET(t); void Render( GLWindow *surface ) { FOREACH(t,g) g->Render(surface); } void Between() { FOREACH(t,g) g->Between(); } };
#define RENDERLIST2(t) RENDERLIST(ts,t);

// Legacy version of the ONE MANY DONE concept.
#define COLLECTION(t,i) class t : public LinkedList { public: CLEARLISTRESET(i); }

// Allows you to define a simple customized sort method for a collection. // Old Style: Use SORTING() now.
#define LL_SORTER(sort,plural,single,compare) \
 void sort() { \
  if ( count < 2 ) return; \
  plural list; list.first=first; list.last=last; list.count=count; \
  single *q=(single *) list.first; list.Remove(q); Append(q); \
  while(list.first) { \
   single *p=(single *) list.first; list.Remove(p); \
   bool inserted=false; \
   EACH(this->first,single,t) { \
    int result=this->compare(p,t); \
    if ( result <= 0 ) { \
     this->InsertBefore(p,t); inserted=true; break; \
    } \
   } \
   if ( !inserted ) Append(p); \
  } \
 }

class LinkedList : public ListItem {
public:
	Zint count;
	ListItem *first;
	ListItem *last;

	LinkedList(void) : ListItem() { first=last=null; }

//virtual void BinaryRead( BinaryFile *open ); // default works in most cases
//virtual void BinaryWriteData( BinaryFile *open ) {}
//virtual void BinaryReadData( BinaryFile *open ) {}
//virtual void ReadAppend( BinaryFile *open ) {}
//virtual void BinaryWrite( BinaryFile *open ); // default works in most cases

 virtual string identity() { ///RTTI///
  string classname=string(typeid(*this).name());
  string discard;
  const char *q=string_argument((char *)classname.c_str(),&discard); // discards the words "class or struct"
  return string(q);
 }
 virtual string identity( bool useChar ) { ///RTTI///
  const char *classname=typeid(*this).name();
  string discard;
  const char *q=string_argument(classname,&discard); // discards the words "class or struct"
  return string(q);
 }
 bool ListIteminList( ListItem *item ) {
  FOREACH(ListItem,i) if ( i==item ) return true;
  return false;
 }
 void sendBack(ListItem *L) { if ( !L->prev ) return; Remove(L); Prepend(L); }
 void sendFront(ListItem *L) { if ( !L->next ) return; Remove(L); Append(L); }
 void sendUp(ListItem *L, bool wrap=true);
 void sendDown(ListItem *L, bool wrap=true);
 virtual void Append(ListItem *L);
 void _Append(ListItem *L);
 void Prepend(ListItem *L);
 ListItem *Element(int i);
 ListItem *Element(int i, bool wrap);
 int Element(ListItem *item);
 virtual ListItem *Any() {
  if ( count==0 ) return null;
  if ( count==1 ) return first;
  return Element(upto((int)count*1234)%count.value);
 }
 virtual ListItem *Any( int seed );
 // Returns i==count on failure to find, use ListIteminList()
 int IndexOf( ListItem *L ) { int i=0; FOREACH(ListItem,item) { if ( item == L ) break; i++; } return i; }
 void InsertBefore(ListItem *insert,ListItem *before);
 void InsertAfter(ListItem *insert, ListItem *after);
 void InsertAt(ListItem *insert, int i);
 void _Remove(ListItem *L);
 void Remove(ListItem *L) { _Remove(L); }
 void RemoveAll(void);
 ListItem *ReplaceListItem(ListItem *L,ListItem *N) {
  N->prev=L->prev;
  N->next=L->next;
  if ( N->prev ) N->prev->next=N;
  if ( N->next ) N->next->prev=N;
  L->next=null;
  L->prev=null;
  delete L;
  return N;
 }
 void Delete(ListItem *L);
 void Delete(ListItem **L);
 void AppendAndDispose( LinkedList *toAppend ) {
  Concat(toAppend);
  delete toAppend;
 }
 //void DeleteAll(void);//never, use CLEARLIST(class) macro

 void RandomizeOrder();
 void RandomizeOrder(int seed);
 void ReverseOrder() {
  LinkedList temporary;
  EACHN(first,ListItem,L,{
   Remove(L);
   temporary.Prepend(L);
  });
  this->first=temporary.first;
  this->last=temporary.last;
  this->count=temporary.count;
  temporary.first=temporary.last=NULL;
  temporary.count=0;
 }
 // Moves L to current list, empties L
 void Concat( LinkedList *L ) {
  if ( L->count <= 0 ) return;
  if ( count == 0 ) {
   count=L->count;
   first=L->first;
   last=L->last;
  } else {
   count+=L->count;
   last->next=L->first;
   L->first->prev=last;
   last=L->last;
  }
  L->first=null;
  L->last=null;
  L->count=0;
 }

 virtual void Clear() {
//#if defined(DEBUG)
  if ( first ) EACHN(first,ListItem,L,{
   Remove(L);
   delete L;
  });
  count=0;
  last=first=null;
//#endif
 }
 virtual ~LinkedList() { 
  Clear();
 }
};

/// HANDLES, lists of specialty classes that point to list items of specific classes ONE..MANY..DONE automatically creates these ///

// Internal unnamed handles
#define HANDLING(single,handle,singlekey) \
 class handle:public ListItem{public: \
  Zp<single> p; \
  handle():ListItem() { } \
  void fromString(char *st) { \
   p.Delete(); \
   p=new single; \
   p->fromString(st); \
  } \
  std::string SingleKey() { return string(singlekey); }\
  virtual string toString() { \
   if(p) return p->toString(); \
   else return string(""); \
  } \
 };

#define HANDLINGS(single,handle,handles,singlekey) \
 class handles:public LinkedList{public: \
  virtual handle*Add(single*q) { \
   handle*n=new handle; \
   n->p=q; \
   Append(n); \
   return n; \
  } \
  virtual handle*Add(single*q,handle *after) { \
   handle*n=new handle; \
   n->p=q; \
   InsertAfter(n,after); \
   return n; \
  } \
  single *find(single *q) { FOREACH(handle,s) if ( s->p==q ) return s->p; return null; } \
  handle *find(single *q, having returnHandle) { FOREACH(handle,s) if ( s->p==q ) return s; return null; } \
  std::string SingleKey() { return std::string(singlekey); }\
  bool Includes(single *q) { FOREACH(handle,s) if ( s->p==q ) return true; return false; } \
  void Delete(single*r){ FOREACH(handle,n) if(n->p==r){ Remove(n);delete n;return;} } \
  void Drop(single*r){ FOREACH(handle,n) if(n->p==r){ Remove(n);delete n;return;} } \
  CLEARLISTRESET(handle); \
 };
// \ // needs a fix on mac SKEYSTART SKEY(singlekey,{SPARAMNode(single);}) SKEYEND(identity(true)); \

// Mega-handle without names
#define HANDLED(single,handle,handles,handleshandle,handleshandles) \
 class handles; class handleshandle; class handleshandles; \
 class handle:public ListItem{ public:\
  Zp<single> p; \
  Zp<handles> parent; \
  virtual void fromString(char *st) { p->fromString(st); } \
  virtual void fromString(string k) { p->fromString((char*)k.c_str()); } \
  virtual string toString() { return p->toString(); } \
 }; \
 class handles:public LinkedList{ public:\
  virtual handle*Add(single*q) {\
   handle*n=new handle; \
   n->p=q; \
   n->parent=this; \
   Append(n); \
   return n; \
  } \
  virtual handle*Add(single*q,handle *after) {\
   handle*n=new handle; \
   n->p=q; \
   n->parent=this; \
   InsertAfter(n,after); \
   return n; \
  } \
  single *find(single *q) { FOREACH(handle,s) if ( s->p==q ) return s->p; return null; } \
  handle *find(single *q,bool returnHandle) { FOREACH(handle,s) if ( s->p==q ) return s; return null; } \
  bool Includes(single *q) { FOREACH(handle,s) if ( s->p==q ) return true; return false; } \
  void Delete(single*r){ FOREACH(handle,n) if(n->p==r){Remove(n);delete n;return;} } \
  void Drop(single*r){ FOREACH(handle,n) if(n->p==r){Remove(n);delete n;return;} } \
  CLEARLISTRESET(handle); \
  ~handles(){Clear();} \
 }; \
 class handleshandle:public ListItem{ public:\
  Zp<handles> p; \
  Zp<handleshandles> parent; \
 }; \
 class handleshandles:public LinkedList{ public: \
  handleshandle*Add(handles*q){ \
   handleshandle*n=new handleshandle; \
   n->p=q; \
   n->parent=this; \
   Append(n); \
   return n; \
  } \
  handles *find(handles *q) { FOREACH(handleshandle,s) if ( s->p==q ) return s->p; return null; } \
  handles *find(handles *q,bool returnHandle) { FOREACH(handleshandle,s) if ( s->p==q ) return s; return null; } \
  void Delete(handles *r) { FOREACH(handleshandle,s)if(s->p==r){Remove(s);delete s;return;} } \
  void Drop(handles *r) { FOREACH(handleshandle,s)if(s->p==r){Remove(s);delete s;return;} } \
  CLEARLISTRESET(handleshandle); \
  ~handleshandles(){Clear();} \
 };

// Class Name, Class Handle Class Name, Plural Handle Class Name, Plural Plural Handles Class Name
#define HANDLES(single,handle,handles,singlekey) HANDLING(single,handle,singlekey) HANDLINGS(single,handle,handles,singlekey);
#define HANDLEHANDLES(single,handle,handles,singlekey) HANDLES(single,handle,handles,singlekey);

// Defines classes under a named handle
#define NAMED(single,handle,handles) \
 class handles; \
 class handle:public ListItem{ public: \
  Zstring name; \
  Zp<single> p; \
  Zp<handles> parent; \
 }; \
 class handles:public LinkedList{ public: \
 virtual handle*Add(single*q,string m) { \
  handle*n=new handle; \
  n->name=m; \
  n->p=q; \
  n->parent=this; \
  Append(n); \
  return n; \
 } \
 handle*find(string k){ \
  FOREACH(handle,n) if(!str_cmp((char*)n->name.c_str(),(char*)k.c_str())) return n; \
  return null; \
 } \
 void Delete(single*r){ \
  FOREACH(handle,n) if(n->p==r){Remove(n);delete n;return;} \
 } \
 CLEARLISTRESET(handle); \
 ~handles(){Clear();} \
 };

// Generic Handle
HANDLES(ListItem,ListItemHandle,ListItemHandles,"ListItem");

// Optimization for real-time type information
#define RONE(type_name,rtid_code,code1)   SINGLE_NAMED(type_name,{ rtid=rtid_code; code1 })
#define RC_ONE(type_name,rtid_code,childof,code1) C_ONE(type_name,childof,{ rtid=rtid_code; code1})

//////////////////////////////////////////////////////////////////////// End ListItem / LinkedList

//////////////////////////////////////////////////////////////////////// String/Strings collection class

string UnStringSpecialCodes( string k );
string StringSpecialCodes( string k );

#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include <string>
using namespace std;

class String : public ListItem {
public:
 string s;
 int integer;
 float floating;
 char c;
 String() : ListItem() {
  s = string("");
  integer=0;
  floating=0.0f;
  c='\0';
 } 
 String( const char *i ) : ListItem() {
  s=string(i);
  integer=0;
  floating=0.0f;
  c='\0';
 }
 String( string i ) : ListItem() {
  s=i;
  integer=0;
  floating=0.0f;
  c='\0';
 }
 String( string i, bool UsesSpecialCodes ) : ListItem() {
  s = UnStringSpecialCodes(i);
  integer=0;
  floating=0.0f;
  c='\0';
 }
 String( String *t ) : ListItem() {
  s=t->s;
  integer=t->integer;
  floating=t->floating;
  c='\0';
 }
 String *Duplicate() { return new String(this); }
 String( const char *k, int i ) {
  integer=i;
  s = string(k);
  prev=next=null;
 }
 const char *c_str(void); // converts the node to a C-str
 virtual ListItem *Copy() {
  return (ListItem *) new String( this );
 }
 virtual void fromString( const char *s ) {
  string key; const char *p= s;
  bool carryover = false;
  while(*p!='\0') {
   if (carryover) carryover = false;
   else p=string_argument_case(p,&key);
   if ( key.length() < 1 ) continue; 
   this->s=UnStringSpecialCodes(key);
   p=string_argument_case(p,&key); 
   if ( is_integer((char *) key.c_str()) ) {
    integer=atoi(key.c_str());
    p=string_argument_case(p,&key); 
   } else if ( is_decimal((char *) key.c_str()) ) {
    floating=(float)atof(key.c_str());
   } else carryover = true;
   if ( is_decimal((char *) key.c_str()) ) {
    floating=(float)atof(key.c_str());
    p=string_argument_case(p,&key); 
   } else carryover = true;
  }
 }
 virtual string toString() {
  string out=string("");
  out+=indention+string("{")+StringSpecialCodes(this->s)+string("}");
  if ( integer != 0 ) {
   char buf[80];
   FMT(buf,80," %d",(int) integer);
   out+=string(buf);
  }
  if ( floating != 0.0f ) {
   char buf[80];
   FMT(buf,80," %1.9f",(float) floating);
   out+=string(buf);
  }
  return out;
 }
};

class KeyValuePair : public String {
public:
 VSKEYSTART
  this->s=UnStringSpecialCodes(key);
  SKEYPAIR; this->value=UnStringSpecialCodes(key); if ( is_integer((char *) key.c_str()) ) { integer=atoi(key.c_str()); } else if ( is_decimal((char *) key.c_str()) ) { floating=(float)atof(key.c_str()); }
  SKEYPAIR; if ( is_decimal((char *) key.c_str()) ) { floating=(float)atof(key.c_str()); } else if ( is_integer((char *) key.c_str()) ) { integer=atoi(key.c_str()); }
 SKEYEND("KeyValuePair");
 virtual string toString() {
  return string("{")+s+string("} \"")+value+string("\"");
 }
 string value;
 KeyValuePair() {
  s = string("");
  value = string("");
  prev=next=null;
 }
 KeyValuePair( KeyValuePair *t ) {
  prev=next=null;
  s=t->s;
  integer=t->integer;
  floating=t->floating;
  value=t->value;
 }
 KeyValuePair( const char *k, const char *v ) {
  s = string(k);
  value = string(v);
  prev=next=null;
 }
 KeyValuePair( const char *k, int i ) {
  static char buf[1024];
  integer=i;
  s = string(k);
  FMT( buf,1024, "%d", (int) i );
  value=string(buf);
  prev=next=null;
 }
 KeyValuePair( const char *k, float f ) {
  static char buf[1024];
  floating =f;
  s = string(k);
  FMT( buf,1024,  "%f", (float) f );
  value=string(buf);
  prev=next=null;
 }
 void Set( int i ) {  
  static char buf[1024];
  integer=i;
  FMT( buf,1024, "%d", (int) i );
  value=string(buf);
 }
 void Set( float f ) {  
  static char buf[1024];
  floating =f;
  FMT( buf,1024,  "%f", (float) f );
  value=string(buf);
 }
 void Set( const char *v ) {
  value=string(v);
 }
 void Set( const char *k, const char *v ) {
  s=string(k);
  value=string(v);
 }
 virtual ListItem *Copy() {
  return new KeyValuePair( this );
 }
};

class Strings : public LinkedList {
public:
 SKEYSTART
  SKEY("string",   { SKEYPAIR; String *s=new String; s->fromString(key.c_str()); Append(s); })
  SKEY("keyvalue", { SKEYPAIR; KeyValuePair *s=new KeyValuePair; s->fromString((char *)key.c_str()); Append(s); })
  SKEY("kv",       { SKEYPAIR; KeyValuePair *s=new KeyValuePair; s->fromString((char *)key.c_str()); Append(s); })
  SKEY("key",      { SKEYPAIR; KeyValuePair *s=new KeyValuePair; s->fromString((char *)key.c_str()); Append(s); })
  SKEY("assign",   { SKEYPAIR; KeyValuePair *s=new KeyValuePair; s->fromString((char *)key.c_str()); Append(s); })
 SKEYEND("Strings");
 void DuplicateAsStrings( Strings *out ) {
  FOREACH(String,x) out->Add(x->c_str(),x->integer,x->floating);
 }
 // Populate with a list of files in a folder (non-recursive).
 void ls_( const char *targetPath, bool listFiles=true, bool prependPath=true, bool filterOSFiles=true );
 void files( const char *t ) { ls_(t); }
 void folder( const char *t ) { ls_(t); }
 void fromSimpleString( const string& in ) {
  string piece=string("");
  const char *p=string_argument(in.c_str(),&piece);
  while ( piece.length() > 0 ) {
   this->Add(piece);
   p=string_argument(p,&piece);
  }
 }
 void fromSimpleString( const char *in ) {
  string piece=string("");
  const char *p=string_argument(in,&piece);
  while ( *p != '\0' ) {
   this->Add(piece);
   p=string_argument(p,&piece);
  }
 }
 void Output() { OUTPUT("%s", toString().c_str() ); }
 virtual string toStringList() {
  string out=string("");
  FOREACH(String,s) {
   out+=string("{")+s->s+string("}\n");
  }
  return out;
 }
 void fromStringList( const char * s ) {
  Zstring in(s);
  const char *w=in.Next();
  while ( *w != '\0' ) {
   String *str=new String(w);
   Append(str);
   w=in.Next();
  }
 }
 virtual string toStringDecimalList() {
  string out=string("");
  FOREACH(String,s) { out+=string("{")+s->s+string("} ")+FMT("%1.2f",s->floating)+string("\n"); }
  return out;
 }
 void fromStringDecimalList( const char * s ) {
  Zstring in(s);
  const char *w=in.Next();
  while ( *w != '\0' ) {
   String *str=new String(w);
   w=in.Next();
   str->floating=(float)atof(w);
   Append(str);
   w=in.Next();
  }
 }
 virtual string toStringIntegerList() {
  string out=string("");
  FOREACH(String,s) {
   out+=string("{")+s->s+string("} ")+FMT("%1.2f",s->integer)+string("\n");
  }
  return out;
 }
 void fromStringIntegerList( const char * s ) {
  Zstring in(s);
  const char *w=in.Next();
  while ( *w != '\0' ) {
   String *str=new String(w);
   w=in.Next();
   str->integer=atoi(w);
   Append(str);
   w=in.Next();
  }
 }
 string toString() {
  string out=string("");
  incdent();
  FOREACH(String,s) {
   string classname=typeid(*s).name();
   string discard;
   const char *q=string_argument(classname.c_str(),&discard); // discards the words "class or struct"
   if ( !str_cmp(q,"String") ) out+=indention+string("string {\n")+s->toString()+string("}\n");
   else
   if ( !str_cmp(q,"KeyValuePair") ) {
    KeyValuePair *kv=(KeyValuePair *)s;
    out+=indention+string("kv {\n")+kv->toString()+string("}\n");
   }
  }
  decdent();
  return out;
 }
 int longest() {
  int candidate=0;
  FOREACH(String,s) if ( (int)s->s.length() < candidate ) candidate=(int)s->s.length();
  return candidate;
 }
 String *Longest() {
  String *candidate=null;
  FOREACH(String,s) if ( candidate ) candidate=s;
  return candidate;
 }
 Strings() : LinkedList() {}
// Strings( const char *filename ) : LinkedList() {  Load(filename); } /* Returns a list of lines */
 String *Add( const char *s ) {
  String *S=new String(s);
  S->integer=count;
  Append(S);
  return S;
 }
 String *Add( string s ) {
  String *S=new String(s);
  S->integer=count;
  Append(S);
  return S;
 }
 String *Add( const char *s, char c ) {
  Append(new String(s));
  String *L=(String *) last;
  L->c=c;
  return L;
 }
 String *Add( char c, const char *s ) {
  Append(new String(s));
  String *L=(String *) last;
  L->c=c;
  return L;
 }
 String *Add( string s, char c ) {
  Append(new String(s));
  String *L=(String *) last;
  L->c=c;
  return L;
 }
 String *Add( char c, string s ) {
  Append(new String(s));
  String *L=(String *) last;
  L->c=c;
  return L;
 }
 String *Add( const char *s, int i ) {
  Append(new String(s));
  String *L=(String *) last;
  L->integer=i;
  return L;
 }
 String *Add( string s, int i ) {
  Append(new String(s));
  String *L=(String *) last;
  L->integer=i;
  return L;
 }
 String *Add( const char *s, float i ) {
  Append(new String(s));
  String *L=(String *) last;
  L->floating=i;
  return L;
 }
 String *Add( string s, float i ) {
  Append(new String(s));
  String *L=(String *) last;
  L->floating=i;
  return L;
 }
 String *Add( string s, int i, float f ) {
  Append(new String(s));
  String *L=(String *) last;
  L->integer=i;
  L->floating=f;
  return L;
 }
 String *Add( const char *s, int i, float f ) {
  Append(new String(s));
  String *L=(String *) last;
  L->integer=i;
  L->floating=f;
  return L;
 }
 KeyValuePair *addKeyValue( const char *s, const char *v ) {
  KeyValuePair *k=new KeyValuePair( s, v );
  Append(k);
  return k;
 }
 KeyValuePair *addKeyValue( const char *s, int v ) {
  KeyValuePair *k=new KeyValuePair( s, v );
  Append(k);
  return k;
 }
 KeyValuePair *addKeyValue( const char *s, float v ) {
  KeyValuePair *k=new KeyValuePair( s, v );
  Append(k);
  return k;
 }
// void Load( const char *filename );  /* Returns a list of lines */
// void Save( const char *filename );
 bool inList( string s );
 String *matchPrefix( const char *s );
 void matchesPrefix( const char *s, Strings *out );
 // caseless match or returns null
 String *match( const char *s );
 String *find( string s );
 String *find( const char *s );
 String *find( const char c ) {
  FOREACH(String,s) if ( s->c==c ) return s;
  return null;
 }
 String *find( int i ) {
  FOREACH(String,s) if ( s->integer==i ) return s;
  return null;
 }
 const char *AnyChar() {
  String *ele=(String *)Any();
  if ( !ele ) {
  OUTPUT("Strings:AnyChar() found no random element (is the list empty?)\n");
  }
  return ele->c_str();
 }
 const char *AnyChar( int seed ) {
  String *ele=(String *)Any(seed);
  if ( !ele ) {
  OUTPUT("Strings:AnyChar(%d) found no random element (is the list empty?)\n", (int) seed);
  }
  return ele->c_str();
 }
 const char *Chars( int i ) {
  FOREACH(String,s) if ( s->integer==i ) return s->s.c_str();
  OUTPUT("Strings:Chars(%d) reports no such element in list, returning empty string\n", (int) i);
  return &string_error;
 }
 // Gets the value or empty string if none
 string Get( int i ) {
  String *s=(String *) Element(i);
  if ( s ) return s->s;
  return string("");
 }
 // Gets the value or empty string if none, wraps
 string Get( int i, having modulo ) {
  String *s=(String *) Element(i % count.value);
  if ( s ) return s->s;
  return string("");
 }
 string strings( int i ) {
  FOREACH(String,s) if ( s->integer==i ) return s->s;
  return string("");
 }
 bool includes( Strings *all_of_these ) {
  FOREACH(String,s) EACH(all_of_these->first,String,t) if ( str_cmp(s->s.c_str(),t->s.c_str()) ) return false;
  return true;
 }
 bool is_included( Strings *cloud ) {
  EACH(cloud->first,String,t) FOREACH(String,s) if ( str_cmp(s->s.c_str(),t->s.c_str()) ) return false;
  return true;
 }
 String *findCaseless( string s );
 String *findCaseless( const char *s );
 String *findSubstring( const char *s );
 String *findNextSubstring( String *start, const char *s );
 string concatToNextSubstring( String *start, const char *end );
 int IndexOf( String *s );
 string Concatenate( having Seamless ); // Returns duplicated concatenations of Strings
 string Concatenate( char seperator='\n' ); // Returns duplicated concatenations of Strings
 void appendFromString( const char *s, char c );
 void appendFromString( string s, char c );
 void show(void);
 void show( const char *sep, const char *end );
 // Splits using string_argument
 void SplitPush( const char *s );
 // Splits by seperator char
 void SplitPush( string s, char seperator );
 // Splits by char_isof, ex. delimiters of newline/space="\n "
 void SplitPush( const char *s, const char *delimiters );
 // Splits by seperator char
 void SplitPush( const char *s, char seperator );
 // Splits by script language rules
 void ScriptPush( const char *s );
 void Push( string s );
 void Push( const char *s );
 String *PushAndGet( const char *s );
 void DuplicateAndPush( const char * s );
 void DuplicateAndPush( Strings *in ) { Copy(in); }
 void Copy( Strings *ss ) {
  EACH(ss->first,String,s) Append( s->Copy() );
 }
 void ClearThenCopy( Strings *ss ) {
  Clear();
  Copy(ss);
 }
 void printf( const char * fmt, ...) {
  static char buf [32768];
  va_list args;
  va_start (args, fmt);
  vsprintf_s(buf, fmt, args);
  va_end (args);
  Push(buf);
 }
 SORTING(String,SortAZ,{},{
  const char *p=A->c_str(); while ( *p != '\0' && !IS_ALPHA(*p) ) p++;
  const char *q=B->c_str(); while ( *q != '\0' && !IS_ALPHA(*q) ) q++;
  while ( *p!= '\0' && *q!='\0' ) {
   if ( (int) LOWER(*p) > (int) LOWER(*q) ) { result=1; break; }
   if ( (int) LOWER(*p) < (int) LOWER(*q) ) { result=-1; break; }
   p++; while ( *p != '\0' && !IS_ALPHA(*p) ) p++;
   q++; while ( *q != '\0' && !IS_ALPHA(*q) ) q++;
  }
  if ( result ==0 && *p != '\0' ) result=1;
  if ( result ==0 && *q != '\0' ) result=-1;
 },{});
 bool NotMatchesKeyValues( Strings *pairs ) {
  FOREACH(KeyValuePair,k) {
   KeyValuePair *kv=(KeyValuePair *) pairs->find(k->s);
   if ( kv->value != k->value ) return true;
  }
  return false;
 }
 virtual CLEARLISTRESET(String);
 ~Strings(void) { Clear(); }
};

Strings *ls( const char *targetPath, bool listFiles=true, bool prependPath=true, bool filterOSFiles=true );
Strings *ls( const char *targetPath, bool listFiles, bool prependPath, Strings *filters );

/**
 * \class Cartesian
 * \brief Implements simple cartesian operations common to UI and graphics
 * Used by this framework to process 2D and some 3D geometry related to interfaces and graphics
 */
enum CartesianForms {
 cartesian_default=-1,
 cartesian_none,
 cartesian_point,
 cartesian_line_rect,
 cartesian_box,
 cartesian_triangle,
 cartesian_circle,
 cartesian_sphere,
};

class CoplanarLinesResult;
class CoplanarLinesResults;
struct BoxCollisionResults;
class Cartesians;
class CartesianApproximation;
ONE(Cartesian, { Zero(); })
public:
 CartesianForms form;
 double 
  // Top left far point, or 2D point A
  x, y, z,
  // Cubic size (width, height, depth)
  w, h, d,       
  // Bottom right near point, or 2D point B
  x2, y2, z2,    
  // Result of the Angle() line angle calculation, or an angle provided for use later
  a,             
  // "Radius" for spheres and circles
  R,             
  // the "W" coordinate, not width, for four dimensional points
  W,             
  // Result of a distance calculation
  length,        
  // For rectangular areas
  area,          
  // For cubic volumes
  volume;        
 // Used by collision methods to mark whether or not a point exists, could also be considered "valid" indicator.
 Zbool exists;   
 // Used to approximate a circle, geometric figure or curve (a list of lines or triangles)
 Zdis<CartesianApproximation> approximation; 
 static int PntOnLine(int px, int py, int qx, int qy, int tx, int ty);
 Cartesian( Cartesian *in ) : ListItem() {
  x = in->x;  y = in->y;  z = in->z;
  w = in->w;  h = in->h;  d = in->d;
  x2 = in->x2;  y2 = in->y2;  z2 = in->z2;
  a = in->a;  R = in->R;  W = in->W;
  length = in->length;  area = in->area;  volume = in->volume;
  exists = in->exists;
 }
 Cartesian( Cartesian &in ) : ListItem() {
  x = in.x;  y = in.y;  z = in.z;
  w = in.w;  h = in.h;  d = in.d;
  x2 = in.x2;  y2 = in.y2;  z2 = in.z2;
  a = in.a;  R = in.R;  W = in.W;
  length = in.length;  area = in.area;  volume = in.volume;
  exists = in.exists;
 }
 Cartesian(int x, int y) : ListItem() { Set(x, y); form = cartesian_point; }
 Cartesian(double x, double y) : ListItem() { Set(x, y); form = cartesian_point; }
 Cartesian(int x, int y, int z) : ListItem() { Set(x, y, z); form = cartesian_point; }
 Cartesian(double x, double y, double z) : ListItem() { Set(x, y, z); form = cartesian_point; }
 Cartesian(int x, int y, int w, int h) : ListItem() { Set(x, y, w, h); form = cartesian_line_rect; }
 Cartesian(having corners, int x, int y, int x2, int y2) : ListItem() { Corners(x, y, x2, y2); form = cartesian_line_rect; }
 Cartesian(having corners, double x, double y, double x2, double y2) : ListItem() { Corners(x, y, x2, y2); form = cartesian_line_rect; }
 Cartesian(double x, double y, double w, double h) : ListItem() { Set(x, y, w, h); form = cartesian_line_rect; }
 Cartesian(int x, int y, int z, int w, int h, int d) : ListItem() { Cube(x, y, z, w, h, d); form = cartesian_box; }
 Cartesian(having corners, int x, int y, int z, int w, int h, int d) : ListItem() { Corners(x, y, z, w, h, d); form = cartesian_box; }
 Cartesian(double x, double y, double z, double w, double h, double d) : ListItem() { Cube(x,y,z,w,h,d); form = cartesian_box; }
 Cartesian(having corners, double x, double y, double z, double w, double h, double d) : ListItem() { Corners(x, y, z, w, h, d); form = cartesian_box; }
 void Zero() { form = cartesian_none; x = y = z = w = h = d = x2 = y2 = z2 = a = R = W = length = 0.0; exists = false; }
 void Reset() { Zero(); }
 void Set( const Cartesian *in ) {
  x = in->x;  y = in->y;  z = in->z;  w = in->w;  h = in->h;  d = in->d;  x2 = in->x2;  y2 = in->y2;  z2 = in->z2;
  area = in->area;  length = in->length;  volume = in->volume;  exists = in->exists;
 }
 void Set( Cartesian *in ) {
  x = in->x;  y = in->y;  z = in->z;  w = in->w;  h = in->h;  d = in->d;  x2 = in->x2;  y2 = in->y2;  z2 = in->z2;
  area = in->area;  length = in->length;  volume = in->volume;  exists = in->exists;
 }
 void Set( Cartesian &in ) {
  x = in.x;  y = in.y;  z = in.z;  w = in.w;  h = in.h;  d = in.d;  x2 = in.x2;  y2 = in.y2;  z2 = in.z2;
  area = in.area;  length = in.length;  volume = in.volume;  exists = in.exists;
 }
 void Set( int x, int y ) {
  this->x  = (double)(x);
  this->y  = (double)(y);
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  Distance();
 }
 void Set( double x, double y ) {
  this->x  = x;
  this->y  = y;
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  Distance();
 }
 void Set( double x, double y, double z ) {
  this->x  = x;
  this->y  = y;
  this->z  = z;
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  this->z2 = this->z + this->d;
  Distance();
 }
 void Set( double x, double y, double w, double h ) {
  this->x  = x;
  this->y  = y;
  this->w  = w;
  this->h  = h;
  this->x2 = x + w;
  this->y2 = y + h;
  Distance();
  form = cartesian_line_rect;
 }
 void Set( int x, int y, int w, int h ) {
  this->x  = (double)(x);
  this->y  = (double)(y);
  this->w  = (double)(w);
  this->h  = (double)(h);
  this->x2 = (double)(x + w);
  this->y2 = (double)(x + h);
  Distance();
  form = cartesian_line_rect;
 }
 void Corners( int x, int y, int x2, int y2 ) {
  this->x  = (double)(x < x2 ? x : x2);
  this->y  = (double)(y < y2 ? y : y2);
  this->x2 = (double)(x < x2 ? x2 : x);
  this->y2 = (double)(y < y2 ? y2 : y);
  this->w  = (double)(this->x2 - this->x);
  this->h  = (double)(this->y2 - this->y);
  Distance();
  form = cartesian_line_rect;
 }
 void Set( int x, int y, int z ) {
  this->x  = (double)(x < x2 ? x : x2);
  this->y  = (double)(y < y2 ? y : y2);
  this->z  = (double)(z < z2 ? z : z2);
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  this->z2 = this->z + this->d;
  Distance();
 }
 void Set(int x, int y, int z, int w, int h, int d) { Cube(x, y, z, w, h, d); }
 void Set(double x, double y, double z, double w, double h, double d) { Cube(x, y, z, w, h, d); }
 void Cube( int x, int y, int z, int w, int h, int d ) {
  this->x  = (double)(x);
  this->y  = (double)(y);
  this->z  = (double)(z);
  this->w  = (double)(w);
  this->h  = (double)(h);
  this->d  = (double)(d);
  this->x2 = (double)(x + w);
  this->y2 = (double)(y + h);
  this->y2 = (double)(z + d);
  form = cartesian_box;
  Distance();
 }
 void Cube( double x, double y, double z, double w, double h, double d ) {
  this->x  = x;
  this->y  = y;
  this->z  = z;
  this->w  = w;
  this->h  = h;
  this->d  = d;
  this->x2 = this->x + this->w;
  this->y2 = this->y + this->h;
  this->z2 = this->z + this->d;
  form = cartesian_box;
  Distance();
 }
 void Line(double x, double y, double x2, double y2) { Corners(x, y, x2, y2); }
 void Corners( double x, double y, double x2, double y2 ) {
  this->x  = x < x2 ? x : x2;
  this->y  = y < y2 ? y : y2;
  this->x2 = x < x2 ? x2 : x;
  this->y2 = y < y2 ? y2 : y;
  this->w  = this->x2 - this->x;
  this->h  = this->y2 - this->y;
  form = cartesian_line_rect;
  Distance();
 }
 void Corners( int x, int y, int z, int x2, int y2, int z2 ) {
  this->x  = (double)(x < x2 ? x : x2);
  this->y  = (double)(y < y2 ? y : y2);
  this->z  = (double)(z < z2 ? z : z2);
  this->x2 = (double)(x < x2 ? x2 : x);
  this->y2 = (double)(y < y2 ? y2 : y);
  this->z2 = (double)(z < z2 ? z2 : z);
  this->w  = (double)(this->x2 - this->x);
  this->h  = (double)(this->y2 - this->y);
  this->d  = (double)(this->z2 - this->z);
  form = cartesian_box;
  Distance();
 }
 void Corners( double x, double y, double z, double x2, double y2, double z2 ) {
  this->x  = x < x2 ? x : x2;
  this->y  = y < y2 ? y : y2;
  this->z  = z < z2 ? z : z2;
  this->x2 = x < x2 ? x2 : x;
  this->y2 = y < y2 ? y2 : y;
  this->z2 = z < z2 ? z2 : z;
  this->w  = this->x2 - this->x;
  this->h  = this->y2 - this->y;
  this->d  = this->z2 - this->z;
  form = cartesian_box;
  Distance();
 }
 //! Returns the minimum x-value of x or x2 (when treating a AA)
 double MinX() { return (x < x2 ? x : x2); }
 //! Returns the minimum y-value of y or y2 (when treating a AA)
 double MinY() { return (y < y2 ? y : y2); }
 //! Returns the minimum z-value of z or z2 (when treating a AA)
 double MinZ() { return (z < z2 ? z : z2); }
 //! Returns the maximum x-value of x or x2 (when treating a AA)
 double MaxX() { return (x > x2 ? x : x2); }
 //! Returns the maximum y-value of y or y2 (when treating a AA)
 double MaxY() { return (y > y2 ? y : y2); }
 //! Returns the maximum z-value of z or z2 (when treating a AA)
 double MaxZ() { return (z > z2 ? z : z2); }
 //! Exports the maximum point
 Cartesian *Max() {
  double mx = MaxX(), my = MaxY(), mz = MaxZ();
  return new Cartesian(mx,my,mz);
 }
 //! Exports the minimum point
 Cartesian *Min() {
  double mx = MinX(), my = MinY(), mz = MinZ();
  return new Cartesian(mx,my,mz);
 }
 //! Calculates the area of the rectangular region described herein
 double Area() { return area = w*h; }
 //! Calculates the volume of the AA cubic region described herein
 double Volume() { return volume = w*h*d; }
 int _X() { return (int)(x); }
 int _Y() { return (int)(y); }
 int _Z() { return (int)(z); }
 int _W() { return (int)(w); }
 int _H() { return (int)(h); }
 int _D() { return (int)(d); }
 int _X2() { return (int)(x2); }
 int _Y2() { return (int)(y2); }
 int _Z2() { return (int)(z2); }
 //! Is tx, ty within this rectangle?
 bool Within( int tx, int ty ) {
  double dtx = (double)(tx);
  double dty = (double)(ty);
  return dtx >= x && dtx < x2 && dty >= y && dty < y2;
 }
 //! Is tx, ty, tz within this cube?
 bool Within( int tx, int ty, int tz ) {
  double dtx = (double)(tx);
  double dty = (double)(ty);
  double dtz = (double)(tz);
  return dtx >= x && dtx < x2 && dty >= y && dty < y2 && dtz >= z && dtz < z2;
 }
 //! Is tx, ty within this rectangle?
 bool Within( double dtx, double dty ) {
  return dtx >= x && dtx < x2 && dty >= y && dty < y2;
 }
 //! Is tx, ty, tz within this cube?
 bool Within( double dtx, double dty, double dtz ) {
  return dtx >= x && dtx < x2 && dty >= y && dty < y2 && dtz >= z && dtz < z2;
 }
 //! Is tx, ty within this rectangle?
 bool WithinInside(double dtx, double dty) {
  return dtx > x && dtx < x2 && dty > y && dty < y2;
 }
 //! Is tx, ty, tz within this cube?
 bool WithinInside(double dtx, double dty, double dtz) {
  return dtx > x && dtx < x2 && dty > y && dty < y2 && dtz > z && dtz < z2;
 }
 //! Is tx, ty within (inclusively) this rectangle?
 bool WithinInclusive( int tx, int ty ) {
  double dtx = (double)(tx);
  double dty = (double)(ty);
  return dtx >= x && dtx <= x2 && dty >= y && dty <= y2;
 }
 //! Is tx, ty, tz within (inclusively) this cube?
 bool WithinInclusive( int tx, int ty, int tz ) {
  double dtx = (double)(tx);
  double dty = (double)(ty);
  double dtz = (double)(tz);
  return dtx >= x && dtx <= x2 && dty >= y && dty <= y2 && dtz >= z && dtz <= z2;
 }
 //! Is dtx, dty within (inclusively) this rectangle?
 bool WithinInclusive( double dtx, double dty ) {
  return dtx >= x && dtx <= x2 && dty >= y && dty <= y2;
 }
 //! Is dtx, dty, dtz within this cube?
 bool WithinInclusive( double dtx, double dty, double dtz ) {
  return dtx >= x && dtx <= x2 && dty >= y && dty <= y2 && dtz >= z && dtz <= z2;
 }
 //! Calculate naively (use LineBox for verbose) if this cartesian is a line within the provided box
 bool Within( Cartesian box ) { return (box.Within(x, y) && box.Within(x2, y2)); }
 //! Calculate if we as a rectangle overlap b rectangle
 bool Overlaps( Cartesian &b ) { return ! ( x > b.x2 || b.x > x2 || y > b.y2 || b.y > y2); }
 //! Calculate and return the midpoint
 Cartesian *Midpoint() { return new Cartesian( 0.5 * x + 0.5 * x2, 0.5 * y + 0.5 * y2, 0.5 * z + 0.5 * z2 ); }
 //! Calculate and return the centroid
 Cartesian *Centroid() { return Midpoint(); }
 //! Convert degrees to radians
 static double to_rad( double deg ) { return deg * 0.017453292519943; }
 //! Convert radians to degrees
 static double to_deg( double rad ) { return rad * 57.295779513082321; }
 //! Returns a 2d "line angle" (in radians)
 double Angle() { return ( a = atan2( (y2-y), (x2-x) ) ); }
 //! Returns a 3d "spherical angle" where X=(x,y), Y=(y,z) and Z=(z,x)
 Cartesian *Angle3d() { return new Cartesian( Angle(), atan2((y2 - y), (z2 - z)), atan2((x2 - x), (z2 - z)) ); }
 //! Length
 double Magnitude() { return Distance(); }
 //! Distance
 double Magnitude( Cartesian other ) { return Distance(other); }
 //! Magnitude
 double Distance( Cartesian other ) {
  if ( x==other.x && y==other.y ) return 0.0;
  return sqrt( ((x - other.x) * (x - other.x)) + ((y - other.y) * (y - other.y)) ) ;
 }
 //! Distance of line
 double Distance() {
  if ( x==x2 && y==y2 ) return 0.0;
  return length = sqrt( ((x - x2) * (x - x2)) + ((y - y2) * (y - y2)) ) ;
 }
 //! 3D Magnitude (Cubic)
 double Magnitude3d() { return Distance3d(); }
 //! 3D Magnitude (Cubic / 3D Distance)
 double Distance3d() {
  double d2d = Distance();
  if ( x==x2 && y==y2 && z==z2 ) return 0.0;
  return length = sqrt(((d2d*d2d)+((z2-z)*(z2-z))));
 }
 //! Set *this to a point on provided line
 bool PointOn( double t, Cartesian line ) {
  if (t < 0.0 || t > 1.0) return false;
  if (t == 1.0) Set(line.x2,line.y2);
  else if (t == 0.0) Set(line.x,line.y);
  else Set( (1.0 - t) * line.x + t * line.x2, (1.0 - t) * line.y + t * line.y2, (1.0 - t) * line.z + t * line.z2 );
  form = cartesian_point;
  return true;
 }
 //! General utility Lerp function used by other Lerp functions
 static double Lerp(double a, double b, double t) { if (a == b) return a; return (1.0 - t) * a + t * b; }
 //! Lerp between p->p2 in three dimensions
 Cartesian *Lerp( double t ) {
  return new Cartesian( Lerp(x,x2,t), Lerp(y,y2,t), Lerp(z,z2,t) );
 }
 //! Lerp between x,y,z and incoming point b
 Cartesian *Lerp( double t, Cartesian b ) {
  return new Cartesian( true, Lerp(x,b.x,t), Lerp(y,b.y,t), Lerp(z,b.z,t), Lerp(x2,b.x2,t), Lerp(y2,b.y2,t), Lerp(z2,b.z2,t) );
 }
 //! Lerp between and incoming points a and b and set ourself
 void Lerp( double t, Cartesian a, Cartesian b ) {
  Corners( Lerp(a.x,b.x,t), Lerp(b.y,b.y,t), Lerp(b.z,b.z,t), Lerp(b.x2,b.x2,t), Lerp(b.y2,b.y2,t), Lerp(b.z2,b.z2,t) );
 }
 //! Set the size of the cubic region, relative to the original x,y,z point
 void Size( double w, double h, double d ) { Cube(this->x, this->y, this->z, w, h, d); }
 //! Scale the region from x,y,z point to a new size relative the original size
 void Scale( double factor ) { Set( x,y,z,w*factor,h*factor,d*factor ); }
 //! Scale the region maintaining the center's location
 void Scale( having same_center, double factor ) {
  Cartesian *center = Midpoint();
  Set(0.0, 0.0, 0.0, w*factor, h*factor, d*factor);
  MoveBy(center->x - w / 2.0, center->y - h / 2.0, center->z - d / 2.0);
  delete center;
 }
 //! Offset the region by a delta
 void MoveBy(int dx, int dy) { Set(x + (double)(dx), y + (double)(dy), z, w, h, d); }
 //! Offset the region by a delta
 void MoveBy(int dx, int dy, int dz) { Set(x + (double)(dx), y + (double)(dy), z + (double)(dz), w, h, d); }
 //! Offset the region by a delta
 void MoveBy(double dx, double dy) { Set(x + dx, y + dy, z, w, h, d); }
 //! Offset the region by a delta
 void MoveBy(double dx, double dy, double dz) { Set(x + dx, y + dy, z + dz, w, h, d); }
 //! Packs a triangle into the Cartesian class.
 void Triangle( int ax, int ay, int az, int bx, int by, int bz, int cx, int cy, int cz ) {
  Triangle( (double)(ax), (double)(ay), (double)(az), (double)(bx), (double)(by), (double)(bz), (double)(cx), (double)(cy), (double)(cz) );
 }
 //! Packs a triangle into the Cartesian class.
 void Triangle( double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz ) {
  Ax(ax); Ay(ay); Az(az); Bx(bx); By(by); Bz(bz); Cx(cx); Cy(cy); Cz(cz);  
 }
 //! Unpacks triangular point values
 double Ax() { return x; } double Bx() { return x2; } double Cx() { return w; }
 double Ay() { return y; } double By() { return y2; } double Cy() { return h; }
 double Az() { return z; } double Bz() { return z2; } double Cz() { return d; }
 //! Packs triangle point values
 void Ax( int i ) { double v = (double)(i); x=v; }
 void Ay( int i ) { double v = (double)(i); y=v; }
 void Az( int i ) { double v = (double)(i); z=v; }
 void Bx( int i ) { double v = (double)(i); x2=v; }
 void By( int i ) { double v = (double)(i); y2=v; }
 void Bz( int i ) { double v = (double)(i); z2=v; }
 void Cx( int i ) { double v = (double)(i); w=v; }
 void Cy( int i ) { double v = (double)(i); h=v; }
 void Cz( int i ) { double v = (double)(i); d=v; }
 //! Packs triangle point values
 void Ax( double v ) { x=v; } void Ay( double v ) { y=v; } void Az( double v ) { z=v; }
 void Bx( double v ) { x2=v; } void By( double v ) { y2=v; } void Bz( double v ) { z2=v; }
 void Cx( double v ) { w=v; } void Cy( double v ) { h=v; } void Cz( double v ) { d=v; }
 //! Retrieves a packed triangle.
 void Triangle( Cartesian &A, Cartesian &B, Cartesian &C ) {
 }
 //! Packs a circle
 void Circle(int x, int y, double R) { Set(x, y); this->R = R; w = R * 2.0; form=cartesian_circle; }
 //! Packs a circle
 void Circle(double x, double y, double R) { Set(x, y); this->R = R; w = R * 2.0; form=cartesian_circle; }
 //! Uses the approximation Cartesian list to approximate a circle at a given precision
 void ApproximateCircle( int precision=16 );
 //! Performs validation and calculation of box parameters
 void Box();
 //! Packs a sphere
 void Sphere(int x, int y, int z, double R) { Set(x, y, z); this->R = R; w = h = d = R*2.0; form=cartesian_sphere; }
 //! Packs a sphere
 void Sphere(double x, double y, double z, double R) { Set(x, y, z); this->R = R; w = h = d = R*2.0; form=cartesian_sphere; }
 //! Returns true if a circle and a line are colliding.  If !enter.exists, line starts inside the circle, if !exit.exists, line ended inside circle
 bool CircleLine(Cartesian line, Cartesian &enter, Cartesian &exit, int precision=16);
 //! Returns true if an AA box and a line are colliding.  If !enter.exists, line started outside rectangle, if !exit exists, line ended inside rectangle
 bool RectLine( Cartesian box, BoxCollisionResults &out);
 //! Returns true if the AA box and Line are colliding.  If !enter.exists, line started inside box, if !exit.exists, line ended inside box
 bool LineRect( Cartesian line, BoxCollisionResults &out);
 //! Returns true if a point is inside a circle
 bool PointCircle(Cartesian circle);
 //! Returns true if a line and a line are crossing.  Will not manipulate "point" if !collided, otherwise will write the point of crossing
 bool LineLine( Cartesian otherLine, Cartesian &point);
 //! Returns true if a circle and a circle are colliding.  Returns the intersection points as a line.
 bool CircleCircle(Cartesian circle, Cartesian &intersection);
 //! TODO: Returns true if a sphere and a sphere are colliding.  Returns the overlap.
 bool SphereSphere( Cartesian box, Cartesian &overlap);
 //! Returns true if the 2d rect and 2d rect are colliding.  Returns the overlap.
 bool RectRect(Cartesian b, CoplanarLinesResults &out, Cartesian &overlap);
 //! Distance Point Line (based on code by Paul Bourke), returns intersection (closest point on line to point, perpendicular) and the distance
 bool DistancePointLine(double px, double py, double pz, Cartesian &intersectionOut, double &distOut);
 //! Distance Point Line (based on code by Paul Bourke), returns intersection (closest point on line to point, perpendicular) and the distance
 bool DistancePointLine(Cartesian point, Cartesian &intersectionOut, double &distOut);
 void operator= (const Cartesian& in) { Set(&in); }
 CLONE(Cartesian,{
  DUPE(x);  DUPE(w);  DUPE(x2);
  DUPE(y);  DUPE(h);  DUPE(y2);
  DUPE(z);  DUPE(d);  DUPE(z2);
  DUPE(exists);
  DUPE(W);  DUPE(R);  a->a = this->a;
  DUPE(length);
  DUPE(area);
  DUPE(volume);
 })
MANY(Cartesian, CartesianHandle, CartesianHandles, "Cartesian", Cartesians, {})
 //! Treating the list as a series of coplanar lines, test another line against it, sorted by distance
 bool Collides( Cartesian line, CoplanarLinesResults &out );
 //! Treating the list as a series of coplanar lines, test another line against it but sort results in reverse distance
 bool Collides( Cartesian line, CoplanarLinesResults &out, bool reverseSort );
 //! Treating the list as a series of coplanar lines, test another series of lines against it
 bool Collides(Cartesians *lines, CoplanarLinesResults &out);
 // Returns the first encountered (not the least) point-to-line test within Tolerance
 Cartesian *OnEdge( double x, double y, double z, double Tolerance, Cartesian &intersection ) {
  Cartesian tpoint(x,y,z);
  FOREACH(Cartesian,L) {
   double D;
   bool onSegment=L->DistancePointLine(tpoint,intersection,D);
   if ( D <= Tolerance ) return L;
  }
  return null;
 }
 Cartesian *Add(double x, double y) { Cartesian *a = new Cartesian(x, y); Append(a); return a; }
 Cartesian *Add(double x, double y, double z) { Cartesian *a = new Cartesian(x, y, z); Append(a); return a; }
 Cartesian *Add(double x, double y, double w, double h) { Cartesian *a = new Cartesian(x, y, w, h); Append(a); return a; }
 Cartesian *Add(double x, double y, double z, double w, double h, double d) { Cartesian *a = new Cartesian(x, y, z, w, h, d); Append(a); return a; }
 Cartesian *Add(having corners, double x, double y, double x2, double y2) { Cartesian *a = new Cartesian(true, x, y, x2, y2); Append(a); return a; }
 Cartesian *Add(having corners, double x, double y, double z, double x2, double y2, double z2) { Cartesian *a = new Cartesian(true, x, y, z, x2, y2, z2); Append(a); return a; }
 Cartesian *Add(int x, int y) { Cartesian *a = new Cartesian(x, y); Append(a); return a; }
 Cartesian *Add(int x, int y, int z) { Cartesian *a = new Cartesian(x, y, z); Append(a); return a; }
 Cartesian *Add(int x, int y, int w, int h) { Cartesian *a = new Cartesian(x, y, w, h); Append(a); return a; }
 Cartesian *Add(int x, int y, int z, int w, int h, int d) { Cartesian *a = new Cartesian(x, y, z, w, h, d); Append(a); return a; }
 Cartesian *Add(having corners, int x, int y, int x2, int y2) { Cartesian *a = new Cartesian(true, x, y, x2, y2); Append(a); return a; }
 Cartesian *Add(having corners, int x, int y, int z, int x2, int y2, int z2) { Cartesian *a = new Cartesian(true, x, y, z, x2, y2, z2); Append(a); return a; }
DONE(Cartesian);

bool operator == ( Cartesian& a, Cartesian& b );

ONE(CoplanarLinesResult,{ Reset(); })
 Zdouble x,y;
 Cartesian segment;
 Zdouble d;
 Cartesian onEdge;
 Zdouble edgeDistance;
 void Reset() {
  x=y=d=edgeDistance=0.0;
  segment.Set(0.0,0.0,0.0,0.0,0.0,0.0);
  onEdge.Set(0.0,0.0,0.0,0.0,0.0,0.0);
 }
 double Distance( double sx, double sy ) { return (double) (d=Cartesian(x,y,sx,sy).Distance()); }
MANY(CoplanarLinesResult,CoplanarLinesResultHandle,CoplanarLinesResultHandles,"CoplanarLinesResult",CoplanarLinesResults,{})
 Zp<Cartesian> onEdge;
 Zdouble sx,sy;
 //! Sets incoming pointer to the minimum point in the list.
 void Min( Cartesian *min ) {
  if ( count == 0 ) return;
  CoplanarLinesResult *one=(CoplanarLinesResult *)first;
  min->Set(one->x,one->y);
  FOREACH(CoplanarLinesResult,c) {
   if ( c->x < min->x ) min->x=c->x;
   if ( c->y < min->y ) min->y=c->y;
  }
 }
 //! Sets incoming pointer to the maximum point in the list.
 void Max( Cartesian *max ) {
  if ( count == 0 ) return;
  CoplanarLinesResult *one=(CoplanarLinesResult *)first;
  max->Set(one->x,one->y);
  FOREACH(CoplanarLinesResult,c) {
   if ( c->x > max->x ) max->x=c->x;
   if ( c->y > max->y ) max->y=c->y;
  }
 }
 //! All incoming are read-only, new result is added to list
 void Add( Cartesian *line, Cartesian *collision ) {
  CoplanarLinesResult *result=new CoplanarLinesResult;
  result->x=collision->x;
  result->y=collision->y;
  result->segment.Set(line->x,line->y,line->z,line->x2,line->y2,line->z2);
  Append(result);
 }
 SORTING(CoplanarLinesResult,SortDistance,
  { FOREACH(CoplanarLinesResult,L) L->Distance(sx,sy); },
  { if ( A->d < B->d ) result=-1; },
  {}
 );
DONE(CoplanarLinesResult);

struct BoxCollisionResults {
public:
 Zint collisions;
 Zbool collided,startsInside,endsInside,within;
 Zbool top,left,right,bottom;
 Zdouble x,y,x2,y2;
 Zp<Cartesian> onEdge;
 CoplanarLinesResults results;
 void Reset() {
  collisions=0;
  collided=startsInside=endsInside=false;
  top=left=right=bottom=false;
  x=y=x2=y2=0.0;
  onEdge=null;
  within=false;
  results.Clear();
 }
};

class CartesianApproximation : public Cartesians {
public:
 Zp<Cartesian> left, right, top, bottom;
 Cartesian centroid;
};
