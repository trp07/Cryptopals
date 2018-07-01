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
