"""Functions to complete set1 of the Cryptopals challenges."""

import base64
import binascii


def hex_to_base64(s:str) -> str:
    """Convert the hex string, 's', to base64."""
    decoded = binascii.unhexlify(s)
    return base64.b64encode(decoded).decode('utf-8')


def fixed_xor(s1:str, s2:str) -> str:
    """XOR strings 's1' and 's2', returning the result as a hex-string."""
    s1_int = int(s1, base=16)
    s2_int = int(s2, base=16)
    return hex(s1_int ^ s2_int)[2:]


def xor_string(s:str, b:str) -> str:
    """
    XOR of hexstring 's' with hexstring 'b'.  If len(b) != len(s), then it is
    expanded and only b[0:len(s)] is XOR'd against 's'.
    Returns result of XOR.
    """
    expanded_b = b * (len(s) // 2)
    return fixed_xor(s, expanded_b[0:len(s)])


def decode_str(s:str) -> str:
    """Decode the hexstring 's' into ASCII."""
    decoded = ''
    for i in range(0, len(s)-1, 2):
        decoded += chr(int(s[i] + s[i+1], base=16))
    return decoded


def freq_count(s:str) -> int:
    """
    Does a basic frequency count of the decoded-string 's' based on the
    preponderance of the letters ETAOIN SHRDLU in the English language.
    Returns an integer of the count.
    """
    count = 0
    for letter in s:
        if letter.upper() in ('ABCDEFGHIJKLMNOPQRSTUVWXYZ'):
            count += 4
        elif letter in ('0123456789., \n\t'):
            count += 2
        elif letter in ('?!/-'):
            count += 1
    return count


