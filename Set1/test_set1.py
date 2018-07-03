"""Test all the challenges completed so far using pytest."""

from _set1 import hex_to_base64
from _set1 import fixed_xor
from _set1 import xor_string
from _set1 import decode_str
from _set1 import freq_count


def test_s1ch1_hex_to_base64():
    """Test to verify set1.challenge1."""
    given = '49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d'
    expected = 'SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t'
    assert hex_to_base64(given) == expected


def test_s1ch2_fixed_xor():
    """Test to verify set1.challenge2."""
    s1_given = '1c0111001f010100061a024b53535009181c'
    s2_given = '686974207468652062756c6c277320657965'
    expected = '746865206b696420646f6e277420706c6179'
    assert fixed_xor(s1_given, s2_given) == expected


def test_s1ch3_single_byte_xor():
    """Test to verify set1.challenge3."""
    c = '1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736'
    expected = "Cooking MC's like a pound of bacon"
    results = {}
    for i in range(0, 256):
        xord = xor_string(c, hex(i)[2:])
        decoded = decode_str(xord)
        fcount = freq_count(decoded)
        results[i] = (fcount, decoded)
    assert results[max(results, key=results.get)][1] == expected




