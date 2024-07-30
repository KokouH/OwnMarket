import socket
import time
import random
import requests

s = []

n = 1000
# n = random.randint(10, 30)
print(n)

# HTTP test
# for _ in range(n):
#     r = requests.get('http://localhost:8484')
#     print(r.text)

# Socket test

for _ in range(n):
    s.append( socket.socket(socket.AF_INET, socket.SOCK_STREAM) )

for soc in s:
    soc.connect(('localhost', 8484))

for soc in s:
    soc.send(b"TEST data")

for soc in s:
    soc.recv(1024)

s = list()


