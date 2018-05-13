/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    for(int i=0;i<n;i++){
        if(value == values[i]){
            return true;
        }
    }
   
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a searching algorithm using bubble sorting method
   for(int j=n-1;j>=0;j--){
        for(int k=1;k<=j;k++){
            if(values[k-1]>values[k]){
              int temp = values[k-1];
              values[k-1] = values[k];
              values[k] = temp;
                
            }
        }
        
   
        
    }
    
    return;
}
