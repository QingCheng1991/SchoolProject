#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cassert>
#include "book.h"
#include "booklist.h"
#include <iomanip>


using namespace std;



//add the one book at a time into the linked list format
void booklist::add_book(book *b){
    //create new node to store the info
    struct node *newbook, *p;
    newbook=new node(b);
    if(head ==NULL){
        head = newbook;
        
    }
    else
    {
        
        p=head;
        while(p->next_ptr !=NULL){
            
            p=p->next_ptr;
        }
        newbook->next_ptr=NULL;
        p->next_ptr=newbook;
        
    }
   
    
}
//display the book info with id, name, price, copies and sale status
void booklist::list_books() const
{
    
    struct node *temp;
    if (head == NULL)
    {
        cout<<"The List is Empty"<<endl;
        return;
    }
    temp = head;
   
    while (temp != NULL)
    {
        
       
        temp->book_ptr->print_info();
        
        temp=temp->next_ptr;
    }
    
}
//search the book list by entering the id number
book* booklist::search(unsigned int i, unsigned int copy){
    if(copy>head->book_ptr->get_copies()){
        cout<<"not enough amount of copies";
        return 0;
        
    }
    else if(head ==NULL){
        return 0;
    }
    else
    {
    struct node *temp;
    if(head ==NULL){
        cout<<"there is no book list";
        return 0;
        
    }
    temp=head;
   
    book *b=new book;
    while(temp != NULL)
    {
        //check the id number if it equal to the input id
        if(temp->book_ptr->get_id()==i){
            
            b=temp->book_ptr;
            
            return b;
           
        }
        temp=temp->next_ptr;
    }
    return b;
    }
    return 0;
}
//take the ouput from search function and adding it to the cart as linked list
void booklist::addcart(book *b, unsigned int i){
    if(b == NULL){
        return;
    }
    struct node *newbook, *p;
    newbook=new node(b);
    if(head ==NULL){
        head = newbook;
        newbook->book_ptr->set_copies(i);
        if(newbook->book_ptr->is_onsale() ==1){
            newbook->book_ptr->set_price(newbook->book_ptr->get_price()*0.8);
        }
        
    }
    else
    {
        
        p=head;
        while(p->next_ptr !=NULL){
            
            p=p->next_ptr;
        }
        
        newbook->next_ptr=NULL;
        //adjusting the price base on sale of products
        if(newbook->book_ptr->is_onsale() ==1){
            newbook->book_ptr->set_price(newbook->book_ptr->get_price()*0.8);
        }
        p->next_ptr=newbook;
        //store the copies of book base on how many user wants to buy
        newbook->book_ptr->set_copies(i);
    }
   
}
//reading the ouput from search function and remove the 
//certain book with id number and copy
void booklist::removelist(book *b, unsigned int copy)
{
    if(head == NULL){
        return;
    }
    struct node *p, *s;
    
    
    p=head;
    
    //check if your first linked list if what you want delete if yes delete
    if(b->get_title() ==p->book_ptr->get_title())
    {
        //if you want delete more you have than it is error
        if(copy> p->book_ptr->get_copies())
        {
            cout<<"you dont not have enough books to remove"<<endl;
            return;
        }
        //check if you want delete all the copy then remove book from linked list
        else if(copy == p->book_ptr->get_copies())
        {
            head=p->next_ptr;
            return;
        }
        else
        {   //subtract the total copies by how much you want delete
            p->book_ptr->set_copies(p->book_ptr->get_copies()-copy);
            return;
        }
    }
    //loop through the linked list to remove node
    while(p->next_ptr != NULL)
    {
        s=p;
        
        p=p->next_ptr;
        if(copy> p->book_ptr->get_copies())
        {
            cout<<"you dont not have enough books to remove"<<endl;
            return;
        }
        else if(copy == p->book_ptr->get_copies())
        {
            s->next_ptr=p->next_ptr;
             free(p);
            
            return;
        }
        else
        {
            s=s->next_ptr;
            s->book_ptr->set_copies(s->book_ptr->get_copies()-copy);
            
            return;
        }
       
        
    }
    
    
}

//searching the book from the keyword
void booklist::searchstring()
{
      
    struct node *p;
    string key;
    string s;
    cout<<"Keyword?";
    cin>>key;
    p=head;
    cout<<"Search Results:"<<endl;
    cout<<"Book Tittle"<<string(32,' ')<<"Price"<<"   "<<"Copies"<<" "<<"On Sale?"<<endl;
    cout<<"-----------"<<string(32,' ')<<"-----"<<"   "<<"------"<<" "<<"--------"<<endl;
    while(p->next_ptr != NULL)
    {
    //check if the enter string is substring for the book's title
    s=p->book_ptr->get_title();
    string::size_type pos = s.find (key,0);
        if (pos == string::npos)
        {
           
        }
        else
        {   //same excution for print_info() function with printing search result
            string sale ="yes";
            unsigned long len =0;
            int extraP=0;
            int extraC=0;
            int space=2;
            if(p->book_ptr->is_onsale() == 0){
                sale="no";
            }
            if(p->book_ptr->get_price()<10){
                space=3;
            }
            if(p->book_ptr->get_id()>9){
                extraP=1;
            }
            if(p->book_ptr->get_copies()<10){
                extraC=1;
            }
            string temp;
            temp=p->book_ptr->get_title();
            len=temp.length();
            cout<<p->book_ptr->get_id()<<". "<<p->book_ptr->get_title()<<string(40-len-extraP,' ')
            <<'$'<<setiosflags(ios::fixed)<<setprecision(2)<<p->book_ptr->get_price()<<string(space,' ')<<p->book_ptr->get_copies()<<string(5+extraC,' ')<<sale<<endl;;
        }
        p=p->next_ptr;
    
    }
}
//this function is going to excution at checkout() calculate the total money with tax
//and discount
void booklist::domath() const{
    struct node *temp;
    double money=0;
    //calculate the original price without discount to show how much saved
    double withoutsale=0;
    int copy=0;
    if (head == NULL)
    {
        cout<<"The List is Empty"<<endl;
        return;
    }
    temp = head;
    
    while (temp != NULL)
    {
        //calculate book price base on onsale
        if(temp->book_ptr->is_onsale() == 1){
            money=money+temp->book_ptr->get_price()*temp->book_ptr->get_copies();
            withoutsale=withoutsale+temp->book_ptr->get_price()*temp->book_ptr->get_copies()*1.25;
            copy=copy+temp->book_ptr->get_copies();
        }
        else
        {
            money=money+temp->book_ptr->get_price()*temp->book_ptr->get_copies();
            withoutsale=withoutsale+temp->book_ptr->get_price()*temp->book_ptr->get_copies();
            copy=copy+temp->book_ptr->get_copies();
        
        }
        temp=temp->next_ptr;
    }
    //discount
    if(copy >=5 && copy<10){
        money=money*1.1;
    }
    else if(copy>=10){
        money=money*1.15;
    }
    cout<<"Total price after discounts and taxes: $"<<money*1.05<<endl;
    cout<<"Your saving today -> $"<<withoutsale*1.05-money*1.05<<'!'<<endl;
    cout<<"Thanks for shopping with BookSea!"<<endl;
    cout<<"Goodbye!"<<endl;

    
}
                            
