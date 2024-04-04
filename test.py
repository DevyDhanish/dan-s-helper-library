import socket
from time import sleep

soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)

soc.bind(("localhost", 4444))

soc.listen(10)

client, addr = soc.accept()

msg = "hello"

while True:
    print("Sending data")
    client.send(msg.encode())

    sleep(5)