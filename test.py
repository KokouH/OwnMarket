import socket
import time
import random
import requests
import threading
from multiprocessing import Pool

s = []

proc_count = 20
threads_count = 2
req_count = 25

print("Start", proc_count * threads_count * req_count)

# HTTP test
def th_func():

    st = time.time()
    c = 0
    for _ in range(req_count):
        try:
            r = requests.get(f'http://localhost:8484/api/get_inventory?id=0')
            # print(r.text)
            c += 1
        except:
            pass
        # print(r.text)
    print(time.time() - st, "sec time")

def po(i):
    ts = []
    for _ in range(threads_count):
        t = threading.Thread(target=th_func, daemon=True)
        t.start()
        ts.append(t)
    
    for t in ts:
        t.join()

with Pool(proc_count) as pool:
    pool.map( po, [0 for _ in range(proc_count)] )


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


