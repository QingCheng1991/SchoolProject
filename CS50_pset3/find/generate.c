/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    /*to check if they are the proper useage you should have includ at least 'n' which repsesent how many number
    you want to generate the [s] is optinal if argc also can be 3 */
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    //convert the usage number 'n' in a new integer variable  n
    int n = atoi(argv[1]);
    

    /*to check if the argc have the optinal[s] input and store into the srand with seedval that make sure every time
    you excute the code it generate the same number as before otherwise it does not care the number you generate*/
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    //use the loop to print out the number that n times which will generate the random number
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() *LIMIT));
    }

    // success
    return 0;
}
