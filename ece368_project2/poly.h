// FILE: poly.h
// CLASS PROVIDED: polynomial
//     A polynomial has one variable x, real number coefficients, and
//     non-negative integer exponents. Such a polynomial can be viewed
//     as having the form:
//       A[n]*x^n + A[n-1]*x^(-n-1) + ... A[2]*x^2 + A[1]*x + A[0]
//     where the A[n] are the real number coefficients and x^i represents
//     the variable x raised to the ith power. The coefficient A[0] is
//     called the "constant" or "zeroth" term of the polynomial.
//
//
// CONSTRUCTORS and DESTROCTOR for the polynomial class
//   polynomial( )
//     POSTCONDITION: This polynomial is initiated as a constant 0
//     i.e., coef = [0], current_degree = 0.
//
//   polynomial(double c, unsigned int exponent = 0)
//     POSTCONDITION: This polynomial has been create with all zero
//     coefficients, except for coefficient c for the specified exponent.
//	   If c!=0, current_degree = exponent; otherwise current_degree = 0.
//
//	 polynomial(const double* coef_array, unsigned int size)
//	   POSTCONDITION: The items in coef_array is used to set the polynomial coefficients.
//
//   polynomial(const polynomial& source)
//     POSTCONDITION: This polynomial has been created as a copy of the source.
//
//   ~polynomial()
//     POSTCONDITION: The memory for coef is released.
//
// MODIFICATION MEMBER FUNCTIONS for the polynomial class
//   void clear( )
//     POSTCONDITION: The polynomial is cleared to the default polynomial
//     i.e., coef = [0], current_degree = 0.
//
//   void reserve(unsigned int number)
//     POSTCONDITION: The size of the array for coefficients has been changed to
//     the requested number (but not less that the size needed to store the
//     current non-zero coefficients). In effect, this guarantees that member
//     functions will not need to allocate new memory for exponents through
//     at least number-1. The content of the coef array is initialized to 0.0;
//	   and current_degree is set to number-1.
//
//	 void reduce( )
//	   POSTCONDITION: If the coefficient of current_degree term is 0.0,
//     then find the highest degree term with a non-zero coefficient, update
//	   current_degree, and free unnecessary memory spaces.
//
//   void assign_coef(double new_coefficient, unsigned int exponent)
//     POSTCONDITION: Sets the coefficient for the specified exponent.
//	   If exponent > current_degree, please use the reserve function to
//	   allocate more space for coef.
//
//   void add_to_coef(double amount, unsigned int exponent)
//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent. If exponent > current_degree, please use the reserve
//	   function to allocate more space for coef.
//
// MODIFICATION OPERATORS for the polynomial class
//   polynomial& operator =(const polynomial& source)
//     POSTCONDITION: This polynomial is exactly the same as the  parameter.
//	   The return value is a reference to this polynomial.
//
//   polynomial& operator =(double c)
//     POSTCONDITION: This polynomial is set to the polynomial with only the
//     constant term c. The other coefficients (for x, x^2, x^3...) are all zero.
//
// CONSTANT MEMBER FUNCTIONS for the polynomial class
//   unsigned int degree( ) const
//     POSTCONDITION: Returns current_degree.
//
//   double coefficient(unsigned int exponent) const
//     POSTCONDITION: If exponent <= current_degree, returns coefficient at
//	   specified exponent of this polynomial; otherwise, return 0.0
//
//   unsigned int next_term(unsigned int e) const
//     POSTCONDITION: If e is less than the degree, then the return value is
//     the next exponent n which is after e such that coefficient(n) != 0.
//     If e is greater than or equal to the degree, then the return value is 0
//
// CONSTANT OPERATORS for the polynomial class
//   double operator( ) (double x) const
//     POSTCONDITION: The return value is the value of this polynomial with the
//     given value for the variable x. Please use the next_term function.
//
// NON-MEMBER OPERATORS for the polynomial Class
//   polynomial operator -(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal the difference of the coefficients of p1 & p2 for any given
//     exponent. Please use the next_term and assign_coef/add_to_coef functions.
//
//   polynomial operator +(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal the sum of the coefficients of p1 & p2 for any given
//     exponent. Please use the next_term and assign_coef/add_to_coef functions.
//
//   polynomial operator *(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//     and the answer is the sum of all these term-by-term products.
//     For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//     return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
//     Please use the next_term and assign_coef/add_to_coef functions.
//
//   ostream& operator << (ostream& out, const polynomial& p)
//     POSTCONDITION: The polynomial has been printed to ostream out, which,
//     in turn, has been returned to the calling function.
//	   Please use the next_term function.
#ifndef POLY_H
#define POLY_H
#include <iostream>
using namespace std;

class polynomial {
    
public:
    static const int DEFAULT_CAPACITY = 200;
    // CONSTRUCTORS and DESTRUCTOR
    polynomial();
    polynomial(double c, unsigned int exponent);
    polynomial(const polynomial& source);
    polynomial(const double* coef_array, unsigned int number);
    ~polynomial();
    
   	// MODIFICATION MEMBER FUNCTIONS
    void clear();
    void reserve(unsigned int number);
    void reduce();
    void assign_coef(double new_coefficient, unsigned int exponent);
    void add_to_coef(double amount, unsigned int exponent);
    
    // MODIFICATION OPERATORS
    polynomial& operator =(const polynomial& source);
    polynomial& operator =(double c)
    { clear( ); assign_coef(c, 0); return *this; }
    
    // CONSTANT MEMBER FUNCTIONS
    unsigned int degree() const { return current_degree; }
    double coefficient(unsigned int exponent) const;
    unsigned int next_term(unsigned int e) const;
    double operator( ) (double x) const;
    
private:
    double* coef;
    unsigned int current_degree;
    unsigned int size;
};

// NON-MEMBER OPERATORS
polynomial operator +(const polynomial& p1, const polynomial& p2);
polynomial operator -(const polynomial& p1, const polynomial& p2);
polynomial operator *(const polynomial& p1, const polynomial& p2);
ostream& operator << (ostream& out, const polynomial& p);

#endif
