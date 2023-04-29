
import sys
import os
import pathlib
from socket import *

'''
Solution Explained:
    The sever.py file when executed, take as argument for the command line, the name of a text file which must be located 
    in the input_file folder. When the sever.py file is run, it retreives the host name and checks the following conditions are met:
        1. Were the correct number of command line arguments provided
        2. Is the type of the file a .txt
        3. Is the file located in input_file folder
        4. Reads the file, and checks if it contains 80 or fewer characters

    If any of the above conditions are not met, the server.py process throws an error, prints a message to the terminal 
    explaining the error, and then exits.   

    Otherwise, the server.py process creates a socket, binds it, and waits for a client to connect. If a client connect, the data
    of the file is transmitted, and the sever.py process will close the socket, and wait for a connection from the next client (either in
    queue or not)

server.py assumptions:
    - the file to be transfered must be a text file (i.e of type .txt or .TXT)
    - the file can only contain 80 characters total including the new line character (\n) thus at most, 
      80 lines can exist in a file if no other characters are present as 80 lines would contain 80 new line characters
    - the file to be transfered will be located in the input_file folder, and the name of the file will be provided
      as a command line argument, not the full path of the file

Errors Handled:
    1. Error thrown if: incorrect number of command line arguments
    2. Error thrown if: Name of file provided is not of type .txt or .TXT
    3. Error thrown if: File is not found in input_file folder
    4. Error thrown if: File size is too large - if more than 80 characters are in the file 

Note: To close server.py when running in terminal, The terminal must be closed Ctrl+C does not terminate process (unless it is used and then connected to by client)
'''

INPUT_FOLDER = "input_file/"
HOSTNAME = gethostname()
print("hostname: " + HOSTNAME)
PORT = 12023


inputArguments = sys.argv[1:]


try:
    if (len(inputArguments) != 1):
        #throw error if incorrect number of arguments provided at the command line
        raise ValueError("invalid number of arguments provided via the command line. " + str(len(inputArguments)) + " arguments provided")
    

    filename = inputArguments[0]

    if not(filename.lower().endswith(".txt")):
        #throws error if file is not a text file; does not have .txt or .TXT file extention
        raise ValueError("incorrect file type (.txt required)")

    filepath = INPUT_FOLDER + filename
    filePathExists = pathlib.WindowsPath(filepath).exists()
    
    if not(filePathExists):
        #throw error if file path does not exists - if the given file is not in folder, input_file
        raise FileNotFoundError("The file, " + filepath + " was not found")

    #opens file specified and reads data
    with open(filepath, "r") as file:
        data = file.read()

        if (len(data) > 80):
            #throw error if the file contains more than 80 characters including new line characters
            raise Exception("file is too large: Size = " + str(len(data)) + " characters - limit is 80 characters in file")
        

        #SOCKET CREATION
        serverSocket = socket(AF_INET, SOCK_STREAM)

        #SOCKET BINDING
        serverSocket.bind((HOSTNAME, PORT))

        #SOCKET LISTEN
        serverSocket.listen(1)
        print("socket listening for connection...")

        print("file data to be sent: \n" + data)


        while True:
            #wait for an incoming connection. Return a new socket representing the connection, 
            #and the address of the client. For IP sockets, the address info is a pair (hostaddr, port).
            connectionSocket, address = serverSocket.accept()
            print("Connected to client! \n\n")
            print(connectionSocket, address)
            print("\n\n")
            connectionSocket.sendall(data.encode('utf-8'))

            print("Data sent to client. \nListening for connection from a client...")

            connectionSocket.close()
        
        #unreachable
        serverSocket.close()

        

    
except ValueError as errorMessage:
    print("Error: ", errorMessage)
    exit(1)
except FileNotFoundError as errorMessage:
    print("Error: ", errorMessage)
    exit(1)
except Exception as errorMessage:
    print("Error: ", errorMessage)
    exit(1)








