import string

s = """\
    0b00000000, // ({})[{}]
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
    0b00000000, //
                //
"""


r = ""

for n in range(256):
    if chr(n) in string.printable and not (chr(n) in string.whitespace):
        r += s.format(chr(n), n)
    else:
        r += s.format(" ", n)

print(r)
