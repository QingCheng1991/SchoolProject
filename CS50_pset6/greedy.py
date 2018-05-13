import cs50


def main():

    print("O hai! How much change is owed?")
    s=cs50.get_float()
    while(s<=0):
        print("foo")
        print("retry: ",end="")
        s=cs50.get_float()
    calculate(s)





def calculate(s):
    number=0
    while(s>=0.25):
        number +=1
        s=s-0.25
   

    while(s >=0.09 and s <0.24):
        number +=1
        s=s-0.10
    
 
    

    while(s >=0.04 and s <0.09):
        number +=1
        s=s-0.05
 
   
    while(s>=0.009 and s<0.04):
        number +=1
        s=s-0.05
        print("{:d}".format(int(number)))
        
        
        
        
if __name__ == "__main__":
    main()