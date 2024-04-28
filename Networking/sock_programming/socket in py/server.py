"""
socket() create the socket
bind() the socket with the address(host and ipv4)
listen() waiting for the client
accept() performs the task
"""

import socket
import threading

# first message, tells us how long the message is going to be
HEADER = 64 
FORMAT = 'utf-8'
DISCONNECT_MESSAGE = "DISCONNECTED!"
PORT = 5050
# gethostbyname returns ip by name of the host
SERVER = socket.gethostbyname(socket.gethostname())

ADDR = (SERVER, PORT)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create socket
server.bind(ADDR) # bind


def handle_client(conn, addr):
    print(f"[NEW CONNECTION] {addr} connected...")

    connected = True
    while connected:
        # this is a blocking code, blocks connection to other clients
        msg_length = conn.recv(HEADER).decode(FORMAT) 
        if msg_length:
            msg_length = int(msg_length)
            msg = conn.recv(msg_length).decode(FORMAT)
            if msg == DISCONNECT_MESSAGE:
                connected = False
                print(f"[DISCONNECTED] {addr}...[ACTIVE CONNECTIONS] {threading.active_count() - 2} ")
            else:
                print(f"{addr} says {msg}")
                # conn.send("msg received") for server to client communication

    conn.close()

def start():
    server.listen() # listen
    print(f"[LISTENING] server is listening on {SERVER}:{PORT}")
    while True:     # keep on accepting the requests until
        conn, addr = server.accept() # conn = object to send back info
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 1}")


print("[STARTING] server is starting")
start()