#!/usr/bin/env python
import libnum

with open('ciphertext', 'rb') as f:
    data = f.readlines()
    c1 = int(data[4])
    c2 = int(data[5])

flag1 = libnum.n2s(c1)
flag2 = libnum.n2s(c2)
flag = flag1 + flag2
print flag

