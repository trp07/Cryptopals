"""Test all the challenges completed so far using pytest."""

from _set1 import hex_to_base64
from _set1 import fixed_xor


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
