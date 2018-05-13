# IMPORT MODULES - BEGIN
import socket
import picamera
import os
import time
# IMPORT MODULES - END

# PI IDENTIFICATION - BEGIN
# Station 1 = Prior to Trim 1 / After Paint Shop
# Station 2 = TBD
# Station 3 = TBD
# Station 4 = TBD
# Station 5 = TBD
# Station 6 = TBD
# Angle 0 = Barcode Pi
# Angle 1 = Driver Front
# Angle 2 = Driver Mid
# Angle 3 = Driver Rear
# Angle 4 = Passenger Front
# Angle 5 = Passenger Mid
# Angle 6 = Passenger Rear
# Station number
stn_num = 1
# Angle number
ang_num = 1
# PI IDENTIFICATION - END

# GLOBAL VARIABLES - BEGIN
# Previous barcode is initially 0 
prevbarcode = 0
# barcode is initially 1 
barcode = 1
# Barcode Port
barcode_port = (60000 + 10*stn_num)
# Central Server image port
central_port_img = (60000 + 10*stn_num + ang_num)
# Central Server name port
central_port_name = (50000 + 10*stn_num + ang_num)
# Central Station IP address
central_host_ip = '149.164.37.245'#'192.168.50.52' # CENTRAL PC IP ADDRESS GOES HERE
# Local machine IP address
host = ''
# Was img sent successfully
central_response = 'no'
# GLOBAL VARIABLES - EN


# FUNCTION DEFINITIONS - BEGIN
# Define send image function
def sendimg(host_ip,cent_port):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((host_ip, cent_port))
        filename = '/home/pi/Desktop/gm/1/' + str(barcode) + '_' + str(stn_num) + '_' + str(ang_num) + '.png'
        f = open(filename, 'rb')
        l = f.read(1024)

        while(l):
            
            s.send(l)
               
            l = f.read(1024)
        prevbarcode= barcode
        print('image sent successfully, connection closing')
        
        f.close()
        s.close()
        return barcode
    except:
        a=1
        return 0
    
        
            
            

    
# Define receivebarcode function
def receivebarcode(HOST,BCODE_PORT):
    try:
    # create socket object
        s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # bind the socket to an ip and port combination
        s1.bind((HOST, BCODE_PORT))
    # listen for a client to connect
        s1.listen(1)
    # accept client connection
        conn1, addr1 = s1.accept()
        global barcode
    # receive barcode from barcode pi
        barcode = conn1.recv(4096)
    # close the connection
        
        conn1.close()
      
    except:
        a=1
        

    
# Define send image name function
def sendimgname(HOST,PORT):
    
    try:
        print('1')
            # Create socket object
        s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            # connect to host
        print('attempting to connect to host')
        s2.connect((HOST, PORT))
        print('attempting to send image name to host')
            # send barcode through socket
            
        s2.sendall(str(barcode) + '_' + str(stn_num) + '_' + str(ang_num) + '.png')
       
        print('image name sent successfully, connection closing')
        # close connection
            
        s2.close()
        
        
    except:
        a=1

        
            
            

    
# FUNCTION DEFINITIONS - END

camera = picamera.PiCamera()
camera.resolution = (2592, 1944)

while(1):
    
    receivebarcode(host,barcode_port)
    if (barcode != prevbarcode):
        camera.capture('/home/pi/Desktop/gm/1/' + str(barcode) + '_' + str(stn_num) + '_' + str(ang_num) + '.png')
        sendimgname(central_host_ip,central_port_name)
        prevbarcode=sendimg(central_host_ip,central_port_img)
        print('4')
        print(barcode)
        print('pre',prevbarcode)
        
    else:
        
        try:
            os.remove('/home/pi/Desktop/gm/1/' + str(barcode) + '_' + str(stn_num) + '_' + str(ang_num) + '.png')
        except:
            a=1
      
  


    

    
    
    



    
