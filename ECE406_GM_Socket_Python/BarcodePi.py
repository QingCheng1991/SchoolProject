# IMPORT MODULES - BEGIN
import socket
import os
import time
from SimpleCV import Color,Camera,Display
cam = Camera()  #starts the camera
display = Display()
result='1'
temp ='1'

# IMPORT MODULES - END

# GLOBAL VARIABLES - BEGIN
# Previous barcode is initially 0
prevbarcode = 0
# Station Number
stn_num = 1
# Barcode Port
barcode_port = (60000 + 10*stn_num)
# Station 1 IP Address
HOST1 ='149.164.36.187'    #'192.168.50.242' # Replace 0's with actual camera 1 IP address
# Station 2 IP Address
HOST2 = '149.164.37.237'#'192.168.50.237' # Replace 0's with actual camera 2 IP address
# Station 3 IP Address
HOST3 = '0.0.0.0' # Replace 0's with actual camera 3 IP address
# Station 4 IP Address
HOST4 = '0.0.0.0' # Replace 0's with actual camera 4 IP address
# Station 5 IP Address
HOST5 = '0.0.0.0' # Replace 0's with actual camera 5 IP address
# Station 6 IP Address
HOST6 = '0.0.0.0' # Replace 0's with actual camera 6 IP address
# GLOBAL VARIABLES - END

# FUNCTION DEFINITIONS - BEGIN
# Define sendfile function
def sendbarcode(HOST,PORT):
    try:
        print('try to send')
        # Create socket object
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # connect to host
        s.connect((HOST, PORT))
        # send barcode through socket
        s.sendall(result)
        print('sendcomplete')
        # close connection
        s.close()
    except:
        a=1
    
    
       
# FUNCTION DEFINITIONS - END



while(display.isNotDone()):
 
 img = cam.getImage() #gets image from the camera

 barcode = img.findBarcode() #finds barcode data from image
 if(barcode is not None): #if there is some data processed
   barcode = barcode[0]
   tempo =str(barcode.data)
   if(tempo != result):
       result = str(barcode.data)
       print result 
       sendbarcode(HOST1,barcode_port)
       sendbarcode(HOST2,barcode_port)
       print('check')
    
   

