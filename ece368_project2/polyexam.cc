// FILE: polyexam.cc
// Non-interactive test program for the polynomial class

#include <cmath>     // Provides fabs
#include <cstdlib>   // Provides rand
#include <cstring>   // Provides memcpy
#include <iostream>  // Provides cout
#include "poly.h"
using namespace std;
const unsigned int TESTSIZE = 6;

// Descriptions and points for each of the tests:
const size_t MANY_TESTS = 12;
const int POINTS[MANY_TESTS+1] = {
     80, // Total points for all tests.
     24, // Test 1 points
     5,  // Test 2 points
     5,  // Test 3 points
     5,  // Test 4 points
     8,  // Test 5 points
     5,  // Test 6 points
     5,  // Test 7 points
     5,  // Test 8 points
     4,  // Test 9 points
     4,  // Test 10 points
     5,  // Test 11 points
     5,  // Test 12 points
};

const char DESCRIPTION[MANY_TESTS+1][256] = {
    "tests for polynomial class",
    "Testing constructors and destructor",
    "Testing clear function",
    "Testing reserve function",
    "Testing reduce function",
    "Testing assign_coef and add_to_coef",
    "Testing coefficient function",
    "Testing next_term function",
    "Testing operator ()",
    "Testing operator +",
    "Testing operator -",
    "Testing operator *",
    "Testing operator <<"
};


// **************************************************************************
// bool close(double a, double b)
//   Returns true if a is within EPSILON of b.
// **************************************************************************
bool close(double a, double b)
{
    const double EPSILON = 0.0001;

    return (fabs(a-b) < EPSILON) || (fabs(1-a/b) < EPSILON);
}

// **************************************************************************
// bool correct(const polynomial& test, unsigned int d, double c[ ])
//   This function determines if the polynomial (test) is "correct" according
//   to these requirements:
//   a. it's degree is d
//   b. For each i in the range 0...(degree), test.coefficient(i) is c[i].
// **************************************************************************
bool correct(const polynomial& test, unsigned int d, double count[])
{
    size_t i;
    bool answer = true;
    if (test.degree( ) != d)
    {
	cout << "Incorrect degree. " << endl;
        answer = false;
    }
    else
    {
        for (i = 0; i <= d; ++i)
	{
            if (!close(count[i], test.coefficient(i)))
	    {
		cout << "Incorrect coefficient(" << i << ")" << endl;
		answer = false;
	    }
	}
	for (i = d+1; i <= TESTSIZE; ++i)
	{
	    if (!close(test.coefficient(i), 0))
	    {
		cout << "Incorrect-coefficient(" << i << ")" << endl;
		answer = false;
	    }
	}
	cout << (answer ? " Test passed.\n" : "Test failed.\n") << endl;
    }
    return answer;
}

// Test constructors and destructor
double test1( )
{
    double c[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    double total = 0.0;

    cout << "Testing the default constructor.\n";
	polynomial empty;
    if (correct(empty, 0, c)) total += 4;

    cout << "Testing the constructor with arguments.\n";
	cout << " first non-zero coefficient.\n";
	c[2] = 1.0;
	polynomial x_squared(1.0, 2);
    if (correct(x_squared, 2, c))
    {
        cout << " then zero coefficient, e.g., polynomial p(0.0, 3);\n";
        c[2] = 0.0;
        polynomial also_empty(0.0, 3);
        if (correct(also_empty, 0, c))  total += 4;
    }

	cout << "Testing the constructor with array input.\n";
	double d[ ] = { 10.0, 1.1, -2.2, 3.3, 0.0, -5.5, 0.0 };
	polynomial p(d, 7);
	if (correct(p, 5, d)) total += 4;

	cout << "Testing copy constructor.\n";
    polynomial *ptr = new polynomial(p);
    if (correct(*ptr, 5, d)) total += 4;

	cout << "Testing assignment operator =\n";
    polynomial q = p;
    if (correct(q, 5, d)) total += 4;

	total += 4; // for destructor
	cout << "Note: still need to check the code for correctness of the destructor.\n\n";

    return total;
}

// Test clear function
double test2()
{
    double c[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	polynomial p(0.1, 3);
    p.clear( );
    if (!correct(p, 0, c)) return 0;

	return POINTS[2];
}

// Test reserve function
double test3()
{
    double c[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	polynomial p;

	p.reserve(8);
    if (!correct(p, 7, c)) return 0;

	return POINTS[3];
}

// Test reduce function
double test4()
{
	double c[8] = { 10.0, 1.1, -2.2, 3.3, 0.0, -5.5, 0.0};
	polynomial p(c, 7);
	p.reduce();
    if (!correct(p, 5, c)) return 0;

	return POINTS[4];
}

// Test assign_coef and add_to_coef
double test5()
{
    double c[8] = { 0, 0, 1.0, 0, 0, 0, 0, 0 };
    cout << "Testing assign_coef.\n";
	polynomial p;
    p.assign_coef(1.0, 2);
    if (!correct(p, 2, c)) return 0;

    cout << "Testing add_to_coef.\n";
    p.add_to_coef(2.0, 2);
    c[2] += 2.0;
    if (!correct(p, 2, c)) return 0;

    cout << "Checking that add_to_coef correctly adjusts degree downward." << endl;
    p.assign_coef(1.0, 10);
    p.add_to_coef(-p.coefficient(10), 10);
    if (!correct(p, 2, c)) return 0;

    cout << "Checking that assign_coef correctly adjusts degree downward." << endl;
    p.assign_coef(1.0, 10);
    p.assign_coef(0, 10);
    if (!correct(p, 2, c)) return 0;

    cout << "Inserting " << TESTSIZE << " random coefficients\n";
    double rand_c[TESTSIZE];
    for (unsigned int i = 0; i < TESTSIZE; i++)
    {
		rand_c[i] = ((rand( ) % 1000)/100.0)+1;
		p.assign_coef(rand_c[i], i);
    }
    if (!correct(p, TESTSIZE-1, rand_c)) return 0;

    return POINTS[5];
}

// Test coefficient function
double test6( )
{
    double c[ ] = { 1.0, 2.0, 3.0, 4.0 };
	polynomial p(c, 4);
    if (!close(p.coefficient(2), 3.0)) return 0;
    if (!close(p.coefficient(5), 0.0)) return 0;

	return POINTS[6];
}

// Test next_term function
double test7( )
{
    polynomial p;
    unsigned int i;

    for (i = 0; i <= TESTSIZE; ++i)
    {
		p.assign_coef(((rand( ) % 1000)/100.0)+1, i);
    }
    p.assign_coef(0.0, TESTSIZE/2);

    for (i = 0; i < TESTSIZE; ++i)
    {
		if ((i != (TESTSIZE/2) - 1) && (p.next_term(i) != i+1)) return 0;
    }
    if (p.next_term((TESTSIZE/2)-1) != (TESTSIZE/2)+1) return 0;

    for (i = TESTSIZE; i < 2*TESTSIZE; ++i)
    {
		if (p.next_term(i) != 0) return 0;
    }

    return POINTS[7];
}

// Testing operator()
double test8( )
{
    polynomial p;
    double value = 0.0;
    double power_of_x = 1.0;
    const double X = 3.0;

    for (unsigned int i = 0; i < TESTSIZE; ++i)
    {
		double c = ((rand( ) % 1000)/100.0);
        if (i == TESTSIZE/2) c = 0.0;
		p.assign_coef(c, i);
		value += c * power_of_x;
		power_of_x *= X;
    }
    if (!close(p(X), value)) return 0;

    return POINTS[8];
}

// Test operator +
double test9( )
{
    polynomial p, q;
    double c[TESTSIZE + 1];

    for (unsigned int i = 0; i < TESTSIZE; ++i)
    {
		p.assign_coef(((rand( ) % 1000)/100.0), i);
		q.assign_coef(((rand( ) % 1000)/100.0), i);
		c[i] = p.coefficient(i) + q.coefficient(i);
    }
    p.assign_coef(((rand( ) % 1000)/100.0)+1, TESTSIZE);
    c[TESTSIZE] = p.coefficient(TESTSIZE);

    if (!correct(p+q, TESTSIZE, c)) return 0;

    return POINTS[9];
}

// Test operator -
double test10( )
{
    polynomial p, q;
    double c[TESTSIZE + 1];

    for (unsigned int i = 0; i < TESTSIZE; ++i)
    {
		p.assign_coef(((rand( ) % 1000)/100.0), i);
		q.assign_coef(((rand( ) % 1000)/100.0), i);
		c[i] = p.coefficient(i) - q.coefficient(i);
    }
    p.assign_coef(((rand( ) % 1000)/100.0)+1, TESTSIZE);
    c[TESTSIZE] = p.coefficient(TESTSIZE);

    if (!correct(p-q, TESTSIZE, c)) return 0;

    return POINTS[10];
}

// Test operator *
double test11( )
{
    polynomial p, q;
    double c[2*TESTSIZE + 1];
    unsigned int i,j;

    for (i = 0; i < TESTSIZE; ++i)
    {
		p.assign_coef(((rand( ) % 1000)/100.0), i);
		q.assign_coef(((rand( ) % 1000)/100.0), i);
    }
    p.assign_coef(((rand( ) % 1000)/100.0)+1, TESTSIZE);
    q.assign_coef(((rand( ) % 1000)/100.0)+1, TESTSIZE);

    for (i = 0; i <= 2 * TESTSIZE; ++i)
		c[i] = 0.0;

    for (i = 0; i <= TESTSIZE; ++i)
        for (j = 0; j <= TESTSIZE; ++j)
            c[i+j] += p.coefficient(i) * q.coefficient(j);

    if (!correct(p*q, 2*TESTSIZE, c)) return 0;

    return POINTS[11];
}

// Test operator <<
double test12( )
{
    double c[ ] = {10.0, 1.1, -2.2, 0.0, 3.3, -5.5};
    polynomial p(c, 6);

    cout << "Printing a polynomial for visual inspection: \n"
	 << p
	 << endl;

    return POINTS[12];
}

double run_a_test(int number, const char message[], double test_function( ), int max)
{
    double result;

    cout << endl << "START OF TEST " << number << ":" << endl;
    cout << message << " (" << max << " points)." << endl;
    result = test_function( );
    if (result > 0)
    {
        cout << "Test " << number << " got " << result << " points";
        cout << " out of a possible " << max << "." << endl;
    }
    else
        cout << "Test " << number << " failed." << endl;
    cout << "END OF TEST " << number << "." << endl << endl;

    return result;
}


// **************************************************************************
// int main( )
//   The main program calls all tests and prints the sum of all points
//   earned from the tests.
// **************************************************************************
int main( )
{
    double sum = 0;

    cout << "Running " << DESCRIPTION[0] << endl;

    sum += run_a_test(1, DESCRIPTION[1], test1, POINTS[1]);
    sum += run_a_test(2, DESCRIPTION[2], test2, POINTS[2]);
    sum += run_a_test(3, DESCRIPTION[3], test3, POINTS[3]);
    sum += run_a_test(4, DESCRIPTION[4], test4, POINTS[4]);
    sum += run_a_test(5, DESCRIPTION[5], test5, POINTS[5]);
    sum += run_a_test(6, DESCRIPTION[6], test6, POINTS[6]);
    sum += run_a_test(7, DESCRIPTION[7], test7, POINTS[7]);
    sum += run_a_test(8, DESCRIPTION[8], test8, POINTS[8]);
    sum += run_a_test(9, DESCRIPTION[9], test9, POINTS[9]);
    sum += run_a_test(10, DESCRIPTION[10], test10, POINTS[10]);
    sum += run_a_test(11, DESCRIPTION[11], test11, POINTS[11]);
    sum += run_a_test(12, DESCRIPTION[12], test12, POINTS[12]);

    cout << "If you submit this now, you will have\n";
    cout << sum << " points out of the ";
    cout << POINTS[0];
    cout << " points from this test program.\n";

    return EXIT_SUCCESS;

}

