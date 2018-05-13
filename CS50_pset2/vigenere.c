#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc,string argv[]){
    
//check if the argc is invalid
    if(argc != 2){
        printf("error\n");
        return 1;
    }
    
    
    
    else{
// check the argv[]only has leter if not exsit the code
    string num=argv[1];
    
    
    int m=strlen(num);
    int j=0;
    for (int i = 0; i < m; i++)
    {   
        if (isalpha( argv[1][i]) == false)
        {
            printf("error\n");
            return 1;
        }
    }
    // ask for the input text and transfrom the world and print out the output
    printf("plaintext:  ");
    string s=get_string();
    int n=strlen(s);
    printf("ciphertext: ");
    
    for(int i=0;i<n;i++){
   //printf("%c\n",num[j]);
   
   if(s[i]>='a'&&s[i]<='z'){
    printf("%c",((int)s[i]+(int)toupper(num[j])-65)%97%26+97);
    j++;
   }
   else if(s[i]>='A'&&s[i]<='Z'){
       printf("%c",((int)s[i]+(int)toupper(num[j])-65)%65%26+65);
      j++;
        
    }
   else{
       printf("%c",s[i]);
   }
    
    if(j==m){
        j=0;
    }
    
            
       
   
 
        
    }
    printf("\n");
    return 0;
    }
    
}