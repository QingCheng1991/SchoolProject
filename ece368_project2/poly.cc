//programer: Qing Cheng
//Date: September 17, 2017
//Description:this problem is using the dynamic array to let user to add create coefficient array and be
//able to add coefficient anytime, it will print out as math equation when you store the coefficient and
//and exponent. Moreover, user could use "+","-" and "*" to add, subtract and multiply twe sets of coefficient
//array

#include <fstream>  //provides ostream for << operater
#include <cstdlib>
#include <cassert>  //provides assert to check preconditions
#include <cmath>    //provides pow
#include <climits>  //provides UINT_MAX
#include <algorithm>//provides fill_n
#include "poly.h"
#include <cassert>

//to initialized all the privare value in the class
polynomial::polynomial(){
    
    
    
    coef = new double[DEFAULT_CAPACITY];
    current_degree = 0;
}

//to create a list of coefficient to all zero except the exponet with value of c
polynomial::polynomial(double c, unsigned int exponent)
{
    
    //to check if it is over capacity for memory
    if(exponent <= DEFAULT_CAPACITY)
    {
        coef = new double[DEFAULT_CAPACITY];
        size = DEFAULT_CAPACITY;
        //loop through and set evertthing to zero except the number oponent to value of c
        for(int index = 0 ; index < DEFAULT_CAPACITY ; index++){
            //*(coef + index) = 0;
            coef[index]=0;
        }
        
        //*(coef + exponent) = c;
        coef[exponent]=c;
        
        //if there will be exsiting list refresh the list and add the c to the exsiting list
        if(coef[exponent] != 0)
            current_degree = exponent;
        else
            current_degree = 0;
    }
    
    
}

//copy everything to from source and store it into the memory and pointed by the pointer coef
polynomial::polynomial(const polynomial& source)
{
    //to allocate memory ready to use
    coef = new double[DEFAULT_CAPACITY];
    
    //loop through and copy the eaxctly same content into to coef
    for(unsigned int i = 0 ; i <= source.current_degree ; i++)
    {
        //*(coef + i) = source.coef[i];
        coef[i]=source.coef[i];
    }
    
    //update the side and current_degree
    size = size + source.degree();
    
    current_degree = source.current_degree;
}

//store the whole coef array into the globle coef varible
polynomial::polynomial(const double* coef_array, unsigned int number){
    //allocate the memory here
    coef=new double[number];
    int index=0;
    //loop through and only store no-zero value into coef
    for(unsigned int i=0; i<number; i++){
        
        coef[i]=*coef_array;
        if(*coef_array !=0){
            index++;
        }
        coef_array++;
    }
    // up date the current_degree
    current_degree=index;
}
//free memory for coef
polynomial::~polynomial()
{
    delete [] coef;
    coef=NULL;
}
//set every thing to zero
void polynomial::clear()
{
    for(unsigned int l = 0 ; l < size ; l++){
        coef[l] = 0;
    }
    
    current_degree=0;
    
}
//change the size of array to the input number, however it has to larger than number of stored coefficents
void polynomial::reserve(unsigned int number)
{
    // if the request number is same as the current size it return nothing
    
    if (number == current_degree)
        return;
    //if the request number is less than the current size, it will keep the current size;
    if (number < current_degree)
        number = current_degree;
    
    
    else{
        //else create new array with request size and store zero to the array and update the current_degree
        for (unsigned int i = 0; i < number; i++)
        {
            coef[i] = 0;
        }
    }
    //delete [ ] coef;
    //coef = larger_array;
    size = number;
    current_degree=number-1;
    
}



//this function is to input coefficient store into request exponent place
void polynomial::assign_coef(double new_coefficient, unsigned int exponent)
{
    int index=0;
    double var;
    //check if the request exponent is larger than the size of the array
    if(exponent >= size)
    {
        index=current_degree;
        var =coef[current_degree];
        
        reserve(exponent);
        coef[index] +=var;
        
        
        
        
        
    }
    
    
    coef[exponent] = new_coefficient;
    //to check the postcondition
    if(coef[exponent] != 0)
    {
        if(exponent > current_degree)
            current_degree = exponent;
    }
    
    
    
    
    
    
}
//to reduce the current degree which has zero coefficient
void polynomial::reduce()
{
    int count=0;
    
    for(unsigned int i=0; i<=current_degree; i++){
        
        if(coef[i] !=0){
            count++;
        }
        
    }
    current_degree=count;
}
//to add the new amount of number to the coefficient list
void polynomial::add_to_coef(double amount, unsigned int exponent){
    //check if the exponet is larger than what is now having 
    //if yes go reseve to have new coef array with right size
    if(exponent > current_degree){
        reserve(exponent);
        coef[exponent]=amount;
        
    }
    //if no just add the exsisting 
    else{
        coef[exponent] +=amount;
        
    }
    
   
    
}
//the operate to going to let the coefficient sync to the varible
//if they are already euqal then du nothing
polynomial& polynomial::operator =(const polynomial& source)
{
    
    double *new_coef;
    
    if (this == &source)
        return *this;
    //if they are not equal then to copy the coef into
    //varible
    if (size != source.size)
    {
        new_coef = new double[source.size];
        delete[] coef;
        coef = new_coef;
        size = source.size;
    }
    return *this;
}
//to check the coefficient by input the exponent
double polynomial::coefficient(unsigned int exponent) const{
    
    if(exponent <= current_degree)
    {
        
        return coef[exponent];
        
    }
    //if exponent is out of the coefficient list just return 0
    else
    {
        return 0;
    }
    return 0;
}
//to select the next term of where you start to from index of e
unsigned int polynomial::next_term(unsigned int e) const{
    unsigned int n;
    
    if(e<degree())
    {
        for(n=e+1; n<=degree(); n++)
            if(coefficient(n)!=0.0)
                return n;
    }
    
    return 0;
}
//this will return the value of the powers correspoding to the entering coefficient
double polynomial::operator( ) (double x) const{
    int coel = current_degree;
    double total = 0;
    
    //to loop through the coefficient list and take sum the power of the x and  
    while(coel >= 0)
    {
        total += coef[coel] * pow(x, coel);
        coel--;
    }
    
    return total;
    
}
// this operator is going to take two sets of polynomial and adding each coefficent
//to creat one set of polynomial 
polynomial operator +(const polynomial& p1, const polynomial& p2){
    polynomial result;
    unsigned int HighestDegree;
    unsigned int index = 0;
    double coefTotal;
    
    HighestDegree = p1.degree();
    //to check if two polyname have the same current degree 
    if(HighestDegree < p2.degree())
        HighestDegree = p2.degree();
    
    //adding the every coefficient
    while(index <= HighestDegree)
    {coefTotal = p1.coefficient(index) + p2.coefficient(index);
        if(coefTotal != 0)
        {result.assign_coef(coefTotal, index);}
        index++;
    }
    
    return result;
    
}
// this operator is going to take two sets of polynomial and subtract each coefficent
//to creat one set of polynomial 
polynomial operator -(const polynomial& p1, const polynomial& p2){
    polynomial result;
    unsigned int HighestDegree;
    unsigned int index = 0;
    double coefTotal;
    
    HighestDegree = p1.degree();
    //to check if two polyname have the same current degree
    if(HighestDegree < p2.degree())
        HighestDegree = p2.degree();
    //adding the every coefficient
    while(index <= HighestDegree)
    {coefTotal = p1.coefficient(index) - p2.coefficient(index);
        if(coefTotal != 0)
        {result.assign_coef(coefTotal, index);}
        index++;
    }
    
    return result;
    
}
// this operator is going to take two sets of polynomial and multiply each coefficent
//to creat one set of polynomial as well as multiply exponent number
polynomial operator *(const polynomial& p1, const polynomial& p2){
    
    
    polynomial result;
    unsigned int HighestDegree;
    unsigned int index = 0;
    double coefTotal;
  
    
    HighestDegree = p1.degree();
    //to check if two polyname have the same current degree
    if(HighestDegree < p2.degree())
        HighestDegree = p2.degree();
        
    //multiply the every coefficient
    while(index <= HighestDegree)
    //multiply every coefficients
    {coefTotal = p1.coefficient(index) * p2.coefficient(index);
    
        if(coefTotal != 0)
        {result.assign_coef(coefTotal, index);}
        index++;
    }
    
    
    return result;
}
//this opreator is going to print all the coefficient and exponent as polynimail format
std::ostream& operator << (std::ostream& out, const polynomial& p){
    int index;
    bool empty = true;
    bool first = true;
    
    for(index = p.degree() ; index >= 0 ; index--)
    {
        //follow the coefficient and print out the X and its power as well as the
        //coefficients
        if(p.coefficient(index) != 0)
        {empty = false;
            if(first)
            { out << p.coefficient(index);
                first = false;
                
                if(p.coefficient(index) > 0)
                {
                    if(index > 1)
                        out << "x^" << index;
                    if(index == 1)
                        out << "x";
                }
                if(p.coefficient(index) < 0)
                {
                    if(index > 1)
                        out << "x^" << index;
                    if(index == 1)
                        out << "x";
                }
                
                
            }
            else
            {
                
                if(p.coefficient(index) > 0)
                {
                    out << " + ";
                    
                    if(index > 1)
                        out << p.coefficient(index) << "x^" << index;
                    if(index == 1)
                        out << p.coefficient(index) << "x";
                    if(index < 1)
                        out << p.coefficient(index);
                }
                if(p.coefficient(index) < 0)
                {
                    out << " - ";
                    
                    if(index > 1)
                        out << p.coefficient(index) * (-1) << "x^" << index;
                    if(index == 1)
                        out << p.coefficient(index) * (-1) << "x";
                    if(index < 1)
                        out << p.coefficient(index) * (-1);
                }
                
                
            }
            
        }
    }
    
    if(empty)
        out << 0;
    
    out << "\n";
    return out;
}



