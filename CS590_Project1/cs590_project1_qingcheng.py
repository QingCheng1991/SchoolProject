import csv
import math

#define all the varibale with reasonable name
count =1
fname =0
lname =0
test1 =0
test2 =0
test3 =0
test =0
maxscore= 0
last_name =''
first_name =''
gender =''
serial =''
color =''
tempcolor=''
#create dictionary for the differeng type of color
colorlist ={
            'Aquamarine':0,
            'Blue':0,
            'Crimson':0,
            'Fuscia':0,
            'Goldenrod':0,
            'Green':0,
            'Indigo':0,
            'Khaki':0,
            'Maroon':0,
            'Mauv':0,
            'Orange':0,
            'Pink':0,
            'Puce':0,
            'Purple':0,
            'Red':0,
            'Teal':0,
            'Turquoise':0,
            'Violet':0,
            'Yellow':0
}
#create the file for write into the infomation
file = open('report.txt','w') 

#loop into the file and store the data into relate variable
with open('Pilots1.csv') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        #calculate the length of the name and divide by the number to get the average 
        fname = fname + len(row['first_name'])
        lname = lname + len(row['last_name'])
        test1 = test1 + int(row['field_test_1'])
        test2 = test2 + int(row['field_test_2'])
        test3 = test3 + int(row['field_test_3'])
        #adding the three test score and get the average by dividing 3
        test = (int(row['field_test_1']) + int(row['field_test_2']) + int(row['field_test_3']))/3
        #use the temp color to check the existing key word in dictionary
        tempcolor = row['robot_color']
        # to update the highest average test score
        if test > maxscore:
            #update infomation who has the highest average score(name, serial, color)
             maxscore = test
             last_name = row['last_name']
             first_name = row['first_name']
             serial = row['robot_serial']
             gender = count
             color = row['robot_color']
        #finding the color in dictionary by using tempcolor as keyword and uodate the amount of color
        if tempcolor in colorlist:
            colorlist[tempcolor] += 1
            
        #this variable to count the number of total robot for calculate the average     
        count += 1
         
    
    
    #printing the infomation in command line as well as write the infomation in report file
    print("the average length of first name is:", int(fname/count))
    file.write("the average length of first name is: " +str(int(fname/count))+'\n')
    print("the average length of lirst name is:", int(lname/count))
    file.write("the average length of lirst name is:"+str(int(lname/count))+'\n')
    print("the average length of the test feild 1 is :", math.ceil(test1/count))
    file.write("the average length of the test feild 1 is :"+ str(math.ceil(test1/count))+'\n')
    print("the average length of the test feild 2 is :", math.ceil(test2/count))
    file.write("the average length of the test feild 2 is :"+str(math.ceil(test2/count))+'\n')
    print("the average length of the test feild 3 is :", math.ceil(test3/count))
    file.write("the average length of the test feild 3 is :"+str(math.ceil(test3/count))+'\n')
    print("Best pilot data:")
    file.write("Best pilot data:\n")
    print(first_name,last_name,"serial ", serial,color,"with an average test feild score of ", int(maxscore))
    file.write(first_name+' ')
    file.write(last_name)
    file.write(" serial ")
    file.write(serial)
    file.write(' '+ color)
    file.write(" with an average test feild score of ")
    file.write(str(int(maxscore))+'\n')
    print("Colors Histogram: ")
    file.write("Colors Histogram: \n")
    #loop through the dictionary to diskplay and write file
    for x in colorlist:
        print (x,":",colorlist[x])
        file.write(x+":"+str(colorlist[x])+'\n')
file.close()