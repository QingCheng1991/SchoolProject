//file nume: stat.cc
//ECE368 Data Structure Programing Assigment 1
//programer number: Qing Cheng
//Data: Septermber 8,2017
//_________________________________________________________________________________
//Program Description:
//This programing will allow you to generate multiple numbers of sequence number
//and keep track its sum, length, maximum, minimum value and as well as adding and
//multiplying two sequence number. It also featureing compare two seuqnce number if
//they have same value
//_________________________________________________________________________________

#include <assert.h>  // Provides assert
#include "stats.h"

//when class create all the private variablue have to initialzed to zero
statistician::statistician()
{
    count =0;
    total =0;
    tiniest =0;
    largest =0;
    
}

//this function is going to take the next sequance of value from the
//given variable r
void statistician::next(double r)
{
    if (count == 0)
    {
        // if the number is the first one total, max, and min are all
        //frist element
        total = r;
        tiniest = r;
        largest = r;
        
    }
    else
    {
        //if it is not first one it well added to total and check if
        //the temperate value is largest or smallest
        total += r;
        if (r < tiniest)
        {
            tiniest = r;
        }
        if (r > largest)
        {
            largest = r;
        }
    }
    //keep tracking the number of the sequances
    count++;
}

//This is reset trigger to initialzed every private value to zero
void statistician::reset( )
{
    count =0;
    total =0;
    tiniest =0;
    largest =0;
}

//This function is return the count value which is length of the sequence number

int statistician::length( ) const
{
    return count;
}

//This function is just return the total which already generate in the next function
double statistician::sum( ) const
{
    return total;
}

//This function is going to have the sum and divide by the count to get the mean
//value from seuqance
double statistician::mean( ) const
{
    if(length()>0)
        return sum()/count;
    return 0;
}
//This function is going to load the tiniest value which is the minimum number from sequence
double statistician::minimum( ) const
{
    //check if the sequence
    if(length()>0)
        return tiniest;
    return 0;
}
//This function is going to load the largest value which is the maximum number from sequence
double statistician::maximum( ) const
{
    if(length()>0)
        return largest;
    return 0;
}

//Postcondition: the two sequence are adding and return as one seuqence
statistician operator +(const statistician& s1, const statistician& s2)
{
    statistician result;
    //Sum of the two sequence number
    result.total = s1.sum() + s2.sum();
    //Check the total length of two sequence number
    result.count = s1.length() + s2.length();
    //Compare which sequence has largest number and return it
    if(s1.maximum() > s2.maximum())
        result.largest = s1.maximum();
    else
        result.largest = s2.maximum();
    //Compare which sequence has smallest number and return it
    if(s1.minimum() > s2.minimum())
        result.tiniest=s2.minimum();
    else
        result.tiniest=s1.minimum();
    
    return result;
        
}


//Postcondition: one sequence number and multipy by a scale
statistician operator *(double scale, const statistician& s)
{
    
    statistician result;
    //Check if the scale is zero then zero multiply anything will
    //return zero
    if (scale == 0)
    {
        result.count =s.length();
        result.total =s.sum()*scale;
        result.tiniest=s.minimum()*scale;
        result.largest=s.maximum()*scale;
        
        
    }
    //Check if the scale is bigger then zero and then multipy by scale and
    //return the value
    else if(scale >0)
    {
        
        
    
        result.largest=s.maximum() *scale;
        result.tiniest=s.minimum() *scale;
        result.total=s.sum() *scale;
        result.count=s.length();
        return result;
    }
    //Check if the scale is negative number and the largest number multiply by
    //negative number will become smallest number. The smalled number multiply by
    //negative number will become larger if there is no zero in sequence
    else if(scale <0)
    {
        
        result.tiniest=s.maximum() *scale;
        if(s.minimum() ==0)
        result.largest=0;
        else
        result.largest=s.minimum() *scale;
        result.total=s.total*scale;
        result.count =s.length();
        return result;
        
    }
    return result;
    
}

//Postcondition to compare two sequence if they are same seuqence
bool operator ==(const statistician& s1, const statistician& s2)
{
    //Check if their largest, length, sum are same, if they all same
    //they have to be the same sequence
    if(s1.maximum() == s2.maximum())
    {
        if(s1.minimum() == s1.minimum())
        {
            if(s1.length() == s2.length())
            {
                if(s1.sum() == s1.sum())
                    return true;
            }
        }
    }
    return false;
}



