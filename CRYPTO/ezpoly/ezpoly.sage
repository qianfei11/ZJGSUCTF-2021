#!/usr/bin/env sage
import os

load("secret.sage")

key = [123456789, 987654321]

def encrypt(msg, base, master_key):
    key_1, key_2 = master_key
    m = bin(int(msg.encode('hex'), 16))[2:]
    assert len(m) <= 256
    f = 0
    idx = 0
    for c in m[::-1]:
        f += int(c) * (x**idx)
        idx += 1
    assert(key_1 < base)
    assert(f < base)
    assert(key_2 < base)
    h = (((key_1 * f) + key_2) % base).exponents()
    ciphertext = ''
    for i in range(256):
        if i in h:
            ciphertext += '1'
        else:
            ciphertext += '0'
    return int(ciphertext[::-1], 2)

F.<x> = GF(2)[]
polynomial = x**255+ x**166+ x**88 + x**6 + 1  

random1 = os.urandom(30)
random2 = os.urandom(30)
FF = GF(2**256)

def s2n(s):
    return int(s.encode('hex').strip('L'), 16)

with open('ciphertext', 'wb') as f:
    ciphertext1 = encrypt(random1, polynomial, key)
    ciphertext2 = encrypt(random2, polynomial, key)
    f.write(str(s2n(random1)) + '\n')
    f.write(str(s2n(random2)) + '\n')
    f.write(str(ciphertext1) + '\n')
    f.write(str(ciphertext2) + '\n')
    assert(len(flag) == 60)
    f.write(str(encrypt(flag[:30], polynomial, key)) + '\n')
    f.write(str(encrypt(flag[30:], polynomial, key)) + '\n')

