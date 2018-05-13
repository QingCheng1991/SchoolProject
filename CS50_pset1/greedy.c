#include <stdio.h>
#include <cs50.h>

int main(void){
    float change=-1;
    int coin=0;
    while(change<0){
    printf("O hai! How much change is owed?");
    change=get_float();
    }
    
    while(change >= 0.25){
        coin=coin+1;
        change=change-0.25;
   
    }
        while(change >=0.09 && change <0.24){
        coin=coin+1;
        change=change-0.1;
  
            
    }
        while(change >=0.04 && change <0.09){
        coin=coin+1;
        change=change-0.05;

    }


       while(change >=0.009 && change <0.04){
        coin=coin+1;
        change=change-0.01;
    }
    
    printf("%i\n",coin);
    
}