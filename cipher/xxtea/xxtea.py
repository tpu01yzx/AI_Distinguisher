#!/usr/bin/python
#  -*- coding: utf-8 -*-
import struct
import sys
import random
import getopt
_DELTA = 0x9E3779B9


def _long2str(v, w):
    n = (len(v) - 1) << 2
    if w:
        m = v[-1]
        if (m < n - 3) or (m > n):
            return ''
        n = m
    s = struct.pack('<%iL' % len(v), *v)
    return s[0:n] if w else s


def _str2long(s, w):
    n = len(s)
    m = (4 - (n & 3) & 3) + n
    s = s.ljust(m, "\0")
    v = list(struct.unpack('<%iL' % (m >> 2), s))
    if w:
        v.append(n)
    return v


def encrypt(str, key):
    if str == '':
        return str
    v = _str2long(str, True)
    k = _str2long(key.ljust(16, "\0"), False)
    n = len(v) - 1
    z = v[n]
    y = v[0]
    sum = 0
    q = 6 + 52 // (n + 1)
    while q > 0:
        sum = (sum + _DELTA) & 0xffffffff
        e = sum >> 2 & 3
        for p in xrange(n):
            y = v[p + 1]
            v[p] = (v[p] + ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)
                            ^ (sum ^ y) + (k[p & 3 ^ e] ^ z))) & 0xffffffff
            z = v[p]
        y = v[0]
        v[n] = (v[n] + ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)
                        ^ (sum ^ y) + (k[n & 3 ^ e] ^ z))) & 0xffffffff
        z = v[n]
        q -= 1
    return _long2str(v, False)


if __name__ == "__main__":
    msg = '''\nUsage: python xxtea.py 
    -l lenght(byte)
    -k key
    -o output cipher stream to file
    '''

    if len(sys.argv) < 2:
        print msg
    try:
        options, args = getopt.getopt(sys.argv[1:], "l:k:o:")
        for opt, arg in options:
            if opt == '-l':
                lenght = int(arg)
            elif opt == '-k':
                key = arg
            elif opt == '-o':
                file = arg

                data = ''
                for i in range(lenght):
                    data += chr(random.randint(1, 127))
                file_object = open(file, 'w')
                file_object.write(encrypt(data, key))
                file_object.close()
                print '%d bytes (%fMB)' % (lenght, lenght/1024.0/1024)

    except Exception, e:
        print msg
