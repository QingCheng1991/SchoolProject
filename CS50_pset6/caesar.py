import cs50
import sys


def main():
    if len(sys.argv) != 2:
        print("error")
        return 1
      
    print("plaintext: ",end='')
    s=cs50.get_string()
    convert(s)

def convert(s):
    # to check if the input the alphabet
    print("ciphertext: ",end='')
    number =int(sys.argv[1])
    for i in s:
        if(i>='a' and i<='z'):
            
            print(chr( (ord(i) + number)%97%26+97),end='')
        elif(i>='A' and i<='Z'):
            
            print(chr( (ord(i) + number)%65%26+65),end='')
        else:
            print(i,end='')
            
            
    
    print('\n', end='')
            
            
            
if __name__ == "__main__":
    main()
 
            
      
            
    
        
        

    