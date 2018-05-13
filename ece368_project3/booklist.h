// Programer:Qing Cheng
// Date: October 4 2017
// FILE: booklist.h 
// CLASS PROVIDED: booklist
//
// CONSTRUCTOR and DESCTRUCTOR for the booklist class:
//   booklist( )
//     Postcondition: The booklist has been initialized as an empty list.
//   ~booklist()
//     Postcondition: The booklist has been emptied and its memory released.
//
// MODIFICATION MEMBER FUNCTIONS for the booklist class:
//   void add_book(const book* b)
//     Postcondition: A new book is added to the booklist. 

// CONSTANT MEMBER FUNCTIONS for the booklist class:
//   void list_books() const
//     Postcondition: The information of the books in the list is printed.
//
#ifndef BOOKLIST_H
#define BOOKLIST_H

#include "book.h"
using namespace std;

class node 
{
public:
    book* book_ptr;
    node* next_ptr;
    node(book* b) 
    { 
	      book_ptr = b; 
	      next_ptr = NULL; 
    }

};

class booklist
{
public:
    booklist()
    {
        head=NULL;
       
        
    } // Constructor
    ~booklist(){
        for ( node *b=head;b != NULL; )
        {
            node *next =b->next_ptr;
            delete b;
            b=next;
        }
    } // Desctructor
    
    
    //add the book into the catalog class
    void add_book(book* b);
    
    //show the book list from the linked list
    void list_books() const;
    
    //add book into the cart class as linked list
    void addcart(book *b, unsigned int i);
    
    //remove the book relate to the copies
    void removelist(book *b, unsigned int copy);
    
    //search the book by keywords
    void searchstring();
    
    //searching the book by enter id
    book* search(unsigned int i, unsigned int copy);
    
    //function calculate total price including discount
    void domath() const;
    

private:
    node* head;
    unsigned int count;
};

#endif