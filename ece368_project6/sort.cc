// Qing Cheng
// FILE: sort.cc
// Implementation of the quicksort and insertionsort functions.

#include "sort.h"
using namespace std;


void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

//////////////// Insertion Sort ////////////////////////////
void insertionsort(string data[], size_t n)
// Precondition: data is an array with at least n components.
// Postcondition: The elements of data have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].
{
    string key;
    int j;
    for (unsigned int i = 1; i < n; i++)
    {
        key = data[i];
        j = i-1;
        
        /* Move elements of arr[0..i-1], that are
         greater than key, to one position ahead
         of their current position */
        while (j >= 0 && data[j] > key)
        {
            data[j+1] = data[j];
            j = j-1;
        }
        data[j+1] = key;
    }
}


////////////////// Quick Sort ///////////////////////////////
static
void partition(string data[], size_t n, size_t& pivot_index);

void quicksort(string data[], size_t n)
// Precondition: data is an array with at least n components.
// Postcondition: The elements of data have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].
{
    size_t pivot_index; // Array index for the pivot element
    size_t n1;          // Number of elements before the pivot element
    size_t n2;          // Number of elements after the pivot element
    
    if (n > 1)
    {
        // Partition the array, and set the pivot index
        partition(data, n, pivot_index);

        // Compute the sizes of the subarrays
        n1 = pivot_index;
        n2 = n - n1 - 1;

        // Recursive calls to sort the subarrays
        
        quicksort(data, n1);
        quicksort((data + pivot_index+ 1), n2);
    }
}


static
void partition(string data[], size_t n, size_t& pivot_index)
// Precondition: n > 1, and data is an array (or subarray)
// with at least n elements.
// Postcondition: The function has selected some "pivot" value that
// occurs in data[0]..data[n-1] (e.g., you can set pivot = data[0]).
// after the partition function, the elements of data will be
// rearranged, and the pivot_index is set so that:
//   -- data[pivot_index] is equal to the pivot;
//   -- Each item before data[pivot_index] is <= the pivot;
//   -- Each item after data[pivot_index] is >= the pivot.
//
{
 
    string pivot=data[0];
    size_t too_big_index=1;
    size_t too_small_index=n-1;
    //start2=clock();
    while( too_big_index<=too_small_index )
    {
        while(too_big_index<n && data[too_big_index]<=pivot	)
            too_big_index++;
        while(data[too_small_index]> pivot)
            too_small_index--;
        if(too_big_index < too_small_index)
        {
            // swap the values
            // of data[too_big_index]
            // and data[too_small_index]
            string temp=data[too_big_index];
            data[too_big_index]=data[too_small_index];
            data[too_small_index]=temp;
        }
    }
    //end2=clock();
    // move pivot element
    // to its correct position
    pivot_index=too_small_index;
    
    data[0]=data[pivot_index];
    
    data[pivot_index]=pivot;
    
}




