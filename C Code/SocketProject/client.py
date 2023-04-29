import sys
import os
import pathlib
from socket import *

'''
client.py assumptions:
    - the data to be recieved from sever.py will be written as a text file (i.e .txt or .TXT) and stored in the output_folder. The name of
      the file provided to the command line must be of extention .txt and will be written to path output_file/<name of file>
    - if a file already exists in output_file folder, an error will be thrown; the file will not be overwritten and the user must provide a different file name
    - the host name of the server must be provided to the client as the first command line argument

Errors Handled:
    1. Error thrown if: incorrect number of command line arguments
    2. Error thrown if: Name of file provided is not of type .txt or .TXT
    3. Error thrown if: server with provided hostname is not found
    4. Error thrown if: File is exists in output_file folder
'''

FOLDER = "output_file/"
PORT = 12023

inputArguments = sys.argv[1:]


try:
    if (len(inputArguments) != 2):
        #throw error if incorrect number of arguments provided at the command line
        raise ValueError("invalid number of arguments provided via the command line. " + str(len(inputArguments)) + " arguments provided")


    filename = inputArguments[1]

    if not(filename.lower().endswith(".txt")):
        #throws error if file is not a text file; does not have .txt or .TXT file extention
        raise ValueError("incorrect file type (.txt required)")


    filepath = FOLDER + inputArguments[1]

    
    hostname = inputArguments[0]
    ipAddress = gethostbyname(hostname)
    print("host IP: " + ipAddress)
    folderExists = pathlib.WindowsPath(FOLDER).exists()
    filepathExists = pathlib.WindowsPath(filepath).exists()
    
    if not(folderExists):
        #throw error if folder does not exists
        raise FileNotFoundError("The folder, " + FOLDER + " was not found")

    if (filepathExists):
        #throws error if file already exists in output_file folder - specification are not clear on how to handle case, thus it was decided that files will not be overwritten
        raise Exception("Output file " + filepath + " already exists - please select a different filename")

    
    #SOCKET CREATION
    clientSocket = socket(AF_INET, SOCK_STREAM)

    #SOCKET CONNECT
    
    clientSocket.connect((ipAddress, PORT))
    print("client connected to server via socket")

    #method will wait until it receives data from the remote host, or until the connection is closed by the remote host
    data = clientSocket.recv(1024)
    
    #create file specified and write data provided by server on recived data
    with open(filepath, "w") as file:
        #data written to file
        file.write(data.decode('utf-8'))
        print("Data recieved and written to file: " + filename)

    #socket closed
    clientSocket.close()
        

    
except ValueError as errorMessage:
    print("Error: ", errorMessage)
    exit(1)
except FileNotFoundError as errorMessage:
    print("Error: ", errorMessage)
    exit(1)
except ConnectionRefusedError as errorMessage:
        print("Error: Unable to connect to server: %s" % errorMessage)
except Exception as errorMessage:
    print("Error: ", errorMessage)
    exit(1)

