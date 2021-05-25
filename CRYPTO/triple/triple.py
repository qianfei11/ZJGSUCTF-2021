#!/usr/bin/env python
import os
import pyDes
from secret import FLAG, KEY

d1 = pyDes.des(KEY)
ciphertext1 = d1.encrypt(os.urandom(8)).encode('base64')
d2 = pyDes.triple_des(KEY * 3)
ciphertext2 = d2.encrypt(FLAG.encode()).encode('base64')

with open('ciphertext', 'wb') as f:
    f.write('ciphertext1 = ' + ciphertext1)
    f.write('ciphertext2 = ' + ciphertext2)

print d1.Kn[6]
# [1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0]

