// <Put your name and date here>
// bookstore.cc: A user interactive program
#include <iostream>

#include <cctype>
#include <string>
#include <iomanip>
#include "book.h"
using namespace std;
//input every info about book into the private varible 
book::book(unsigned int n, string t, double p, unsigned int c, bool s){
   
    set_info(n, t, p, c, s);
    
    
}
//seting all the balue into the private variable by calling the set function
void book::set_info(unsigned int n, string t, double p, unsigned int c, bool s){
    id=0;
    price=0;
    copies=0;
    title="";
    onsale=false;
    
    set_id(n);
    set_title(t);
    set_price(p);
    set_copies(c);
    set_onsale(s);
}

//printing the out with required format
void book::print_info()const{
    
    string sale ="yes";
    unsigned long len =0;
    int extraP=0;
    int extraC=0;
    int space=2;
    //reading if they are on sale if yes print "yes" otherwise print "no"
    if(is_onsale() == 0){
        sale="no";
    }
    if(get_price()<10){
        space=3;
    }
    //calculate how many spaces needed to aligning every lane
    if(get_id()>9){
        extraP=1;
    }
    if(get_copies()<10){
        extraC=1;
    }
    len=title.length();
    //printing every book's info witch calculated spaces
    cout<<get_id()<<". "<<get_title()<<string(40-len-extraP,' ')<<'$'<<setiosflags(ios::fixed) << setprecision(2)<<get_price()<<string(space,' ')<<get_copies()<<string(5+extraC,' ')<<sale<<endl;
    
}
