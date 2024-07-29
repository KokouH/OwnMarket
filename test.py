import socket
import time
import random

s = []

# while (1):
n = 1000
# n = random.randint(10, 30)
print(n)
for _ in range(n):
    s.append( socket.socket(socket.AF_INET, socket.SOCK_STREAM) )

for soc in s:
    soc.connect(('localhost', 8484))

for soc in s:
    soc.send(b"TEST data")

for soc in s:
    soc.recv(1024)

s = list()


