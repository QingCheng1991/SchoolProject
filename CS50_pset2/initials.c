#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void){
    //get the string with you full name
    //printf("please enter you name here:");
    string s=get_string();
   if(s != NULL){
    printf("%c",toupper(s[0]));
    for(int i=0;i<strlen(s);i++){
        if(s[i]==' '){
            printf("%c",toupper(s[i+1]));
        }
        
    }
    printf("\n");
   }
}