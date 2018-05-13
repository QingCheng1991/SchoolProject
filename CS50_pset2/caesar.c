#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[]){
    
    //check if the argc is invalid 
    if(argc !=2){
        printf("error");
        return 1;
    }
    //printing the test to ask for string
    printf("plaintest:");
    string s;
    s=get_string();
    int k;
    k=atoi(argv[1]);
    int n=strlen(s);
     printf("ciphertext:");
    //loop every char in the string and transfrom the letter and kepp other thing the same
    for(int i=0;i<n;i++){
        if(s[i]>='a'&&s[i]<='z'){
            
            
            printf("%c",((int)s[i]+k)%97%26+97);
        }
        else if(s[i]>='A'&&s[i]<='Z'){
            printf("%c",((int)s[i]+k)%65%26+65);
            
        }
        else{
            printf("%c",s[i]);
        }
        
   
        
    }
printf("\n");
return 0;
}