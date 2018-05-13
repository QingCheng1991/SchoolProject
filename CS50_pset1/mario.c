#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height=-1;
   
    
    
    while(height <0 || height >23){
        printf("enter your height here:");
        height=get_int();

    }

 
    for(int i=0;i<height;i++){
        printf("%.*s", height-i,"                            ");
        printf("%.*s", i+1,"##############################");
        printf("  ");
        printf("%.*s\n", i+1,"##############################");
    }

  
}