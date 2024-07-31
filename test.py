import socket
import time
import random
import requests
import threading

s = []

k = 2
n = 10
# n = random.randint(10, 30)
results = [0 for i in range(k)]
print(k, n)

# HTTP test
def t(results, i):

    st = time.time()
    c = 0
    for _ in range(n):
        try:
            r = requests.get('http://localhost:8484')
            print(r.text)
            c += 1
        except:
            pass
        # print(r.text)
    print(time.time() - st, "sec time")
    results[i] = c

ts = []
for i in range(k):
    ts.append( threading.Thread(target=t, args=(results, i)) )
    ts[-1].start()

for thre in ts:
    thre.join()
    
print(results)
print(sum(results))

# Socket test

# for _ in range(n):
#     s.append( socket.socket(socket.AF_INET, socket.SOCK_STREAM) )

# for soc in s:
#     soc.connect(('localhost', 8484))

# for soc in s:
#     soc.send(b"TEST data")

# for soc in s:
#     soc.recv(1024)

s = list()


