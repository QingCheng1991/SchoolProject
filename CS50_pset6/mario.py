import cs50

print('height: ',end='')
s=cs50.get_int()

while(s>0 and s<24):
    for i in range(s):
        print(" "*(s-(i+1))+"#"*(i+2))
    break
    

    
 
 


