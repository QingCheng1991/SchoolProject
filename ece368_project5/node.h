// <Put your name and date here>
// FILE: node.h
// CLASS PROVIDED: node
//     Each node on a binarytree has the following features:
//     letter: a character. If an internal node, the NULL character ('\0') is used.
//     probability: a double value showing the probability of occurrence
//     left: a pointer to the left child
//     right: a pointer to the right child


#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class node
{
public:
	char letter;
	double probability;
	string code;
	node* left;
	node* right;

	node(char c, double p)
    {
		letter = c;
		probability = p;
		left = right = NULL;
	}
};

// NON-MEMBER FUNCTIONS
// TODO: Attaches two nodes together to a common root
    node* combine(node* left_child, node* right_child)
{
    node *root = new node(' ', left_child->probability+right_child->probability);
    
    root->right=right_child;
    root->left=left_child;
    
    
    return root;
}

// TODO: Clean all nodes attached to the root
void clean(node* root){
    if (root == NULL) return;
 
    /* first delete both subtrees */
    clean(root->left);
    clean(root->right);
   
   
    free(root);
    
}


void printcode(node* root, int array[], int top)
{
    
    //char *pointer;
    
    if(root->left != NULL){
        array[top] = 0;
        
        printcode(root->left,array,top+1);
    }
    if(root->right !=NULL){
        array[top] = 1;
        
        printcode(root->right,array,top+1);
    }
    if(root->left == NULL  || root->right == NULL){
        
        printf("%c: ", root->letter);
        
        for(int i=0; i<top; i++){
            printf("%d",array[i]);
            root->code += std::to_string(array[i]);
            
        }
        
        printf("\n");
        
    }
    
}

void encode(node* root,node *b,char text){
    
        
    
    if(root->left != NULL){
        encode(root->left,b,text);
    }
    if(root->right !=NULL){
        encode(root->right,b,text);
    }
    if(root->left == NULL  || root->right == NULL){
        
        if(root->letter == text || root->letter==(int)(text-32)){
            *b=*root;
            
            
            
        }
        
    }
    
    
    
    
}

string decode_file(node* root, string s)
{
    string ans = "";
    node* p = root;
    for (unsigned int i=0;i<s.size();i++)
    {
        if (s[i] == '0')
            p = p->left;
        else
            p = p->right;
        
        // reached leaf node
        if (p->left==NULL && p->right==NULL)
        {
            ans += p->letter;
            p = root;
        }
    }
    // cout<<ans<<endl;
    return ans;
}


// Define a function comparing the probability
// purpose: to sort the node list in the order of ascending probability
// Note: you do not need to modify this function
bool comp_prob(node* first, node* second)
{
	if ( first->probability < second->probability )
        return true;

    return false;
}

#endif
