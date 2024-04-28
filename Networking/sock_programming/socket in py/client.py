
from email import message 
import socket

HEADER = 64 
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "DISCONNECTED!"

SERVER = socket.gethostbyname(socket.gethostname())
PORT = 5050
ADDR = (SERVER, PORT)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create socket
client.connect(ADDR) # connect


def send(msg):
    message = msg.encode(FORMAT)
    msg_len = len(message)
    send_length = str(msg_len).encode(FORMAT)
    # first time a 64 bytes padded string is sent to indicate the length of message
    send_length += b" " * (HEADER - len(send_length)) 
    client.send(send_length)
    # the server is aware of the length to accept the message
    client.send(message) 

message = ""
while  message != DISCONNECT_MESSAGE:
    message = input("> ")
    send(message)
