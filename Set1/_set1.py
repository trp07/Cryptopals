"""Functions to complete set1 of the Cryptopals challenges."""

import base64
import binascii


def hex_to_base64(s:str) -> str:
    """Convert the hex string, 's', to base64."""
    decoded = binascii.unhexlify(s)
    return base64.b64encode(decoded).decode('utf-8')


