//Qing Cheng
//Date: 11/8/2017
//ECE368 Data Structure
// FILE: huffman.cc
// This file contains the implementation of Huffman coding and decoding program.

#include <fstream>
#include <list>
#include <string>
#include <cassert>
#include "node.h"
#include <ctype.h>





int main()
{
    //////////////////////   Read Probability Data   /////////////////////
    
    // Open the probability file for reading
    string probfilename = "probability.txt";
    ifstream probfile;
    probfile.open(probfilename.c_str(), ifstream::in);
    
    assert(probfile);
    list<node*> node_list;
    char letter;
    double frequency;
    while(true){
        
        
        probfile >> letter;
        if(probfile.eof()) break;
        
        probfile.ignore(1,'\t');
        
      
        probfile >> frequency;
        node *b = new node(letter,frequency);
        node_list.push_back(b);
    }
    node_list.sort(comp_prob);
   
    for(int i=0; i<13; i++){
        node *b = new node(node_list.front()->letter,node_list.front()->probability);
     
        node_list.pop_front();
        node_list.push_back( combine(b, node_list.front()));
      
        node_list.pop_front();
    }
    
    
    
    printf("\n");
    
    node *a =new node(' ',node_list.front()->probability);
    a->left=node_list.front();
    node_list.pop_front();
    a->right=node_list.front();
    a->probability +=node_list.front()->probability;
    node_list.push_back(a);
    node_list.pop_front();
    
   
    probfile.close();
    while(node_list.size() !=1)
    {
        node *c = new node(' ',node_list.front()->probability);
        c->right=node_list.front();
        c->left=node_list.back();
        c->probability += node_list.back()->probability;
        node_list.pop_front();
        node_list.back()=c;
        
    }
    
    
    
    
    
    
    
    
    
    
    ///////////////////   Construct Huffman Coding Tree ////////////////////
    
    // TODO: Repeat the following until there is only one node left in the node list,
    //       this node is also the root of the huffman coding tree:
    //       - Sort the node list in order of ascending probability, which can be done by:
    //					node_list.sort(comp_prob);
    //	     - Extract the two nodes with the lowest probabilities, remove them from the
    //		    node list, merge (add up their probabilities) them to create a new node,
    //			and insert the new node back into the list.
    
    
    ///////////////////   Generate Huffman Codes ////////////////////////
    
   
    int code[]={0};
    int top=0;
    
    
    printf("huffman code table:\n");
    
    printcode(node_list.front(), code, top);
    
    
    
    
    
    
    
    
    
    
    /////////////////////////   Encode Input File   ////////////////////////////////
    
    // Open the text file for reading
    string textfilename = "input.txt";
    ifstream textfile;
    textfile.open(textfilename.c_str(), ifstream::in);
    
    assert(textfile);
    
    // Open the file for writing encoded text
    string encodedfilename = "encoded.txt";
    fstream encodedfile;
    encodedfile.open(encodedfilename.c_str(), fstream::out | fstream::in | fstream::trunc);
    
    assert(encodedfile);
    
    // TODO: Read and encode each character from the input file one by one
    // and print the codes to the output file
    
    // Close the text file
    char txt;
    
    while(true){
        if(textfile.eof()) break;
        
        
        
        textfile>>txt;
        
        if( isalpha(txt)){
            node *d =new node(' ',0);
            encode(node_list.front(),d,txt);
            
            encodedfile<<d->code;
            
            
            
        }
        else{
            encodedfile<<txt;
        }
        
    }
    textfile.close();
    
    //////////////////////// Decode the Encoded File ///////////////////////////
    
    // Reset the encoded text file for reading
    encodedfile.clear();
    encodedfile.seekg(0, ios::beg);
    
    // Open the file for writing decoded text
    string decodedfilename = "decoded.txt";
    ofstream decodedfile;
    decodedfile.open(decodedfilename.c_str(), ofstream::out);
    
    assert(decodedfile);
    
  
    char decode;
    string decodeall;
    string printfile;
    
    while(true){
        if(encodedfile.eof()) break;
        encodedfile>>decode;
        
        if(decode != '1' && decode != '0'){
            decodedfile<<decode;
        }
        
        else{
            
            decodeall +=decode;
            printfile=decode_file(node_list.front(), decodeall);
            if(printfile.size() != 0 ){
                decodedfile<<printfile;
                printfile="";
                decodeall="";
            }
            
            
            
            
        }
        
        
        
        
        
    }
    
    // Close the input and output files for decoding
    encodedfile.close();
    decodedfile.close();
    
    // TODO: Delete all the node objects
    // Note: use the clean function in node.h
    clean(node_list.front());
    node_list.front()=NULL;
    exit(0);
}



