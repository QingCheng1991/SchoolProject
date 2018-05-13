# IMPORT MODULES - BEGIN
import socket

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
# PI IDENTIFICATION - END

# GLOBAL VARIABLES - BEGIN
# Local machine IP address
host = ''
# Initialize barcode to zero
imgname = 'test.png'
# initialize angle loop variable
i = 1
# initialize station loop variable
j = 1
# GLOBAL VARIABLES - END

# FUNCTION DEFINITIONS BEGIN
# Define receive image Function
def receiveimg(HOST,PORT):
    # Create Socket Object
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # bind the socket to an ip and port combination
    s.bind((HOST,PORT))
    # listen for a client to connect
    s.listen(1)
    print('server listening for image file')
    # accept client connection
    conn, addr = s.accept()
    print('Connected by', addr)
    # Declare this image name to be the global image name
    global imgname
    # UPDATE THIS LINE TO DESIRED DIRECTORY
    
    with open('GMproject1\Debug\\'+imgname, 'wb') as f:
        print 'file opened'
        while True:
            
            data = conn.recv(1024)
            
            if not data:
                break
            # write data to a file
            f.write(data)

    f.close()
    print('Successfully get the file')
    conn.close()
    print('connection closed')
    
# Define receive image name function
def receiveimgname(HOST,BCODE_PORT):
    # create socket object
    s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # bind the socket to an ip and port combination
    s1.bind((HOST, BCODE_PORT))
    # listen for a client to connect
    s1.listen(1)
    print('server listening for image name')
    # accept client connection
    conn1, addr1 = s1.accept()
    print('Connected by', addr1)
    # Declare this image name to be the global image name
    global imgname
    # receive barcode from barcode pi
    imgname = conn1.recv(4096)
    print('image name received successfully, closing img name connection')
    # close the connection
    conn1.close()
# FUNCTION DEFINITIONS END

while 1:
    
    receiveimgname(host,(50000 + 10*j + 1))
    receiveimg(host,(60000 + 10*j + 1))
    receiveimgname(host,(50000 + 10*j + 2))
    receiveimg(host,(60000 + 10*j + 2))
    receiveimgname(host,(50000 + 10*j + 3))
    receiveimg(host,(60000 + 10*j + 3))
    receiveimgname(host,(50000 + 10*j + 4))
    receiveimg(host,(60000 + 10*j + 4))
    receiveimgname(host,(50000 + 10*j + 5))
    receiveimg(host,(60000 + 10*j + 5))

