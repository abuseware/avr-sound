#!/usr/bin/env python3

import sys

if len(sys.argv) != 2:
  print("Usage: {} infile.u8 > outfile.h".format(sys.argv[0]))
  exit(1)

try:
  with open(sys.argv[1], "rb") as data:
    # Determine file size
    data.seek(0, 2)
    data_len = data.tell()
    data.seek(0, 0)

    # Prepare byte array
    data_arr = bytearray(data_len)

    # Fill array and fix length
    data_len = data.readinto(data_arr)

    # Generate C description
    print("const uint32_t pcm_length = {};".format(data_len))
    print("const uint8_t pcm_samples[] PROGMEM = {", end="")
    print(", ".join("0x{:02x}".format(data_byte) for data_byte in data_arr), end="")
    print("};")

except Exception as ex:
  print(ex)
