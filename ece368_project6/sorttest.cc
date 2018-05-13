
//Programer: Qing Cheng
//Clase: ECE368
//Date: 12/1/2017
//description: the program is going to read the text file and sort every word every time and write into 
//new file as well as print the runing time of sorting
// FILE: sorttest.cc


#include "sort.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <time.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////////

// PROTOTYPES for functions used by this test program:

void print_menu( );
// Postcondition: A menu of choices for this program has been written to cout.

char get_user_command( );
// Postcondition: The user has been prompted to enter a one character command.
// The next character has been read (skipping blanks and newline characters),
// and this character has been returned.

void testsort(void sorter(string data[], size_t n), const char* inname, const char* outname);
// A function that will test one of the sorting functions

void check_results(string data[], size_t n);
// A function that will check that the data array is sorted

int main( )
{
    
    char choice; // A command character entered by the user

    do
    {
        print_menu( );
        choice = toupper(get_user_command( ));
        switch (choice)
        {
            case 'I': testsort(insertionsort, "randomwordlist.txt", "sortedwordlist.txt");
                      break;
            case 'Q': testsort(quicksort, "randomwordlist.txt", "sortedwordlist.txt");
                      break;
            case 'X': cout << "Exit the test program." << endl;
                      break;
            default:  cout << choice << " is invalid. Sorry." << endl;
        }
    }
    while ((choice != 'X'));

    return EXIT_SUCCESS;
}



void print_menu( )
{
    cout << endl; // Print blank line before the menu
    cout << "The following choices are available: " << endl;
    cout << " I   Run insertionsort" << endl;
    cout << " Q   Run quicksort" << endl;
    cout << " X   Exit this test program" << endl;
}

char get_user_command( )
{
    char command;

    cout << "Enter choice: ";
    cin >> command; // Input of characters skips blanks and newline character

    return command;
}

void testsort(void sorter(string words[], size_t n), const char* inputfile_name, const char* outputfile_name)
// Use the specified sorter function to sort the words in the file with the given input file name,
// Sorted words will be written to the file with the given output file name.
//
// TODO: Please complete the implementation
{
    //set time variable for record time
    clock_t nStart, nEnd;
	// Open the random word list text file
    string textfilename = inputfile_name;
    ifstream textfile;
    textfile.open(textfilename.c_str(), ifstream::in);
    
    //Open text file for write sort output
    string writefile = outputfile_name;
    ofstream output;
    output.open(writefile.c_str(), ofstream::out);
    
    assert(output);
    
    assert(textfile);
    int order =0;
    while(true){
    //string to read each word at a time
    //variable to track the Nth word been sorted
    
    order++;
    string x;
    textfile>>x;
    if(textfile.eof()) break;
    //create string array because the function parameter need string array
    string y[x.length()];
    //store string into string array
    for(unsigned int i=0; i<x.length();i++){
    y[i]=x[i];
    }
    
    //sort the array by selected sort method
    nStart = clock(); 
    sorter(y,x.length());
    nEnd = clock();
    
    //printing the sorting time
    cout<<"The "<<order<<"th word has been sorted";
    cout << "time elapsed:";
    cout << (nEnd-nStart)*1.0/CLOCKS_PER_SEC*1000 << "msec.\n";
    check_results(y,x.length());
    for(unsigned int i=0; i<x.length();i++){
    
    output<<y[i];
        
    }
    output<<"\n";
    
    
    }
    

    //close the file
    textfile.close();
    output.close();
}

// Check that the data array is sorted
void check_results(string data[], size_t n)
{
    for (size_t i = 1; i < n; ++i)
    {
		if (data[i-1] > data[i])
		{
			cout << "Incorrect sort at index " << i << endl;
			return;
		}
    }

    cout << "Sorted successfully!" << endl;
}
