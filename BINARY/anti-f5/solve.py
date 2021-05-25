#!/usr/bin/env python
from Crypto.Cipher import ARC4

data = [0xff, 0x21, 0xc2, 0xe7, 0x1c, 0x44, 0x69, 0x28, 0x26, 0xd6, 0x78, 0xfb, 0xbb, 0x41, 0xd0, 0xe9, 0xd0, 0xd5, 0x2e, 0x5b, 0x5a, 0x19, 0x43, 0x30, 0x39, 0x28, 0xae, 0xf, 0x2a, 0xb6, 0xe0, 0x93, 0x9b, 0x82, 0x12, 0x21, 0xcd, 0xe, 0xe, 0x47, 0xb0]
data = ''.join(chr(c) for c in data)
key = 'zjgsuctf'

rc4 = ARC4.new(key)
plaintext = rc4.decrypt(data)
print plaintext
