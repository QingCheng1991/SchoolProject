// <Put your name and date here>
// bookstore.cc: A user interactive program
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cassert>
#include "book.h"
#include "booklist.h"

using namespace std;

// Function Prototypes
// Note: Please add your implementation after the main() function

void print_menu();
// This function prints the menu options

char get_choice( );
// This function gets the command choice of the user and returns the command character

void fill_catalog(booklist& books, string bookfilename);
// This function creates the default book catalog

void checkout(const booklist& books);
// This function calculates and displays the total cost and savings of the books in cart
// and ends the program

int main( )
{
	booklist catalog; // a book catalog for the book store
	booklist cart; // a list of books in the cart
	char choice;

	// Fill the list of books with the default catalog of books
	fill_catalog(catalog, "booklist.txt");

    // Print the menu
    print_menu();

    // Read in choice until the user inputs 'Q' or 'q'
    do
    {
        fill_catalog(catalog, "booklist.txt");
        choice = toupper(get_choice( ));
        switch (choice)
        {
		    // Perform the command entered by the user
            case 'L':
                // List the books in the catalog
                cout<<"Book Tittle"<<string(32,' ')<<"Price"<<"   "<<"Copies"<<" "<<"On Sale?"<<endl;
                cout<<"-----------"<<string(32,' ')<<"-----"<<"   "<<"------"<<" "<<"--------"<<endl;
                catalog.list_books();
                break;

            case 'A':   // TODO: add your code below ...
                int tempid, copies;
                // Get the book ID of the book to be added
                cout<<"Book Id?";
                cin>>tempid;
                cout<<"copies?";
                cin>>copies;
                cart.addcart(catalog.search(tempid,copies),copies);
                cout<<"Item in cart:"<<endl;
                cout<<"Book Tittle"<<string(32,' ')<<"Price"<<"   "<<"Copies"<<" "<<"On Sale?"<<endl;
                cout<<"-----------"<<string(32,' ')<<"-----"<<"   "<<"------"<<" "<<"--------"<<endl;
                cart.list_books();
                //cart.addcart(b);
                // Get the number of copies

                // Search the book in the catalog and add to the cart
                // Note: The number of copies of the same book in the catalog
                //       should be adjusted after the add operation.

                // Print the cart content

                break;

            case 'R':   // TODO: add your code below ...
                // Get the book ID of the book to be removed
                int removeid, removecopies;
                cout<<"Book Id?";
                cin>>removeid;
                cout<<"copies?";
                cin>>removecopies;
                cart.removelist(cart.search(removeid,removecopies), removecopies);
                cout<<"Item in cart:"<<endl;
                cout<<"Book Tittle"<<string(32,' ')<<"Price"<<"   "<<"Copies"<<" "<<"On Sale?"<<endl;
                cout<<"-----------"<<string(32,' ')<<"-----"<<"   "<<"------"<<" "<<"--------"<<endl;
                cart.list_books();
                // Get the number of copies

                // Search the book in the cart and return to the catalog
                // Note: The number of copies of the same book in
                //       both the cart and the catalog should be adjusted
                //       after the remove operation.

                // Print the cart content

                break;

            case 'S':
                // TODO: add your code below ...
                // Get the keyword from the user
                catalog.searchstring();
                //cout<<"Keyword?";
                //cin>>key;
                
                // Search the book titles for the keyword

                // Print the search result
                break;
			case 'C':
                // Check out and show the total price and savings
                checkout(cart);
			    break;

            case 'M':
                print_menu();
                break;

            case 'Q':
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << choice << " is not a valid input." << endl;
        }
    } while (choice != 'Q');

    return 0;
}



void fill_catalog(booklist& books, string bookfilename){
		
	// Open the booklist file for reading
	ifstream bookfile;
	bookfile.open(bookfilename.c_str(), ifstream::in);

	assert(bookfile);

	do 
    {
        unsigned int id, copies;
		string title;
		double price;
		char sale;
		bool onsale;

		// read in features of a book
		bookfile >> id;
		if(bookfile.eof()) break;

		bookfile.ignore(1,'\t');
		getline(bookfile, title, '\t');
		bookfile >> price >> copies >> sale;
        
		assert (sale == 'N' || sale == 'Y');

		if (sale == 'N') 
			onsale = false;
		else 
			onsale = true;
		
   	    // Create a new book b
		book* b = new book(id, title, price, copies, onsale);

		// Push book b into the back of booklist (reference to bookList)
		books.add_book(b);
	} while (true);
	
	// close the booklist file
	bookfile.close();
}

void print_menu() {
	// Display the menu of commands 
	
	cout << "=========================" << endl;
	cout << "Menu:" << endl;
	cout << "[L]ist all books" << endl;
    cout << "[A]dd a book to cart" << endl;
    cout << "[R]emove a book from cart" << endl;
	cout << "[S]earch" << endl;
    cout << "[C]heckout" << endl;
    cout << "[M]enu" << endl;
    cout << "[Q]uit" << endl;
	cout << "=========================" << endl;
}

char get_choice( ) {

	// Get input command and return the input character
	char command;
	cout << "Command: ";
	cin >> command;
	return command;

}

void checkout(const booklist& books){
    //books.list_books();
    books.domath();
    
    
    
    
    
    
}

