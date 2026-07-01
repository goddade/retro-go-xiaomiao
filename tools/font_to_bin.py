#!/usr/bin/env python3
"""Convert a font .c file (FusionPixel12.c) to a raw binary for flash partition."""

import re
import sys
import struct
import os

def parse_hex_array(text, start_marker, end_marker='};'):
    start = text.find(start_marker)
    if start < 0:
        return None
    start = text.find('{', start)
    if start < 0:
        return None
    end = text.find(end_marker, start)
    if end < 0:
        return None
    body = text[start+1:end]
    values = []
    for v in re.findall(r'0x[0-9A-Fa-f]+', body):
        values.append(int(v, 16))
    return values

def parse_meta(text, field):
    m = re.search(rf'\.{field}\s*=\s*(\d+),', text)
    return int(m.group(1)) if m else None

def parse_str(text, field):
    m = re.search(rf'\.{field}\s*=\s*"(.+?)",', text)
    if m:
        s = m.group(1)
        b = s.encode('utf-8')
        return b.ljust(16, b'\0')[:16]
    return None

def main():
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <input.c> <output.bin>")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = sys.argv[2]

    with open(input_path, 'r', encoding='utf-8') as f:
        text = f.read()

    name = parse_str(text, 'name')
    font_type = parse_meta(text, 'type')
    width = parse_meta(text, 'width') or 0
    height = parse_meta(text, 'height')
    chars = parse_meta(text, 'chars')
    map_start_code = parse_meta(text, 'map_start_code') or 0

    # Find map array: try different naming conventions
    map_name = None
    for m in re.finditer(r'static\s+const\s+uint32_t\s+(\w+)\s*\[\]\s*=\s*\{', text):
        mn = m.group(1)
        if 'map' in mn.lower():
            map_name = mn
            break

    map_array = parse_hex_array(text, map_name) if map_name else None
    if map_array is None:
        print("ERROR: Could not find map array")
        sys.exit(1)

    data_array = parse_hex_array(text, '.data =')
    if data_array is None:
        print("ERROR: Could not find data array")
        sys.exit(1)

    map_len = len(map_array)
    data_size = len(data_array)

    encoded_name = (name or b'Unknown\0\0\0\0\0\0\0\0\0')
    if isinstance(encoded_name, str):
        encoded_name = encoded_name.encode('utf-8')
    encoded_name = encoded_name.ljust(16, b'\0')[:16]

    metadata = (
        encoded_name  # name[16]
        + struct.pack('<BBB', font_type or 2, width, height)  # type, width, height
        + b'\0'  # padding
        + struct.pack('<I', chars or 0)  # chars
        + struct.pack('<I', 0xFFFFFFFF)  # map (placeholder)
        + struct.pack('<I', map_len)  # map_len
        + struct.pack('<I', map_start_code)  # map_start_code
    )
    assert len(metadata) == 36, f"Header should be 36 bytes, got {len(metadata)}"

    glyph_data = bytes(data_array)
    map_bytes = struct.pack(f'<{map_len}I', *map_array)

    map_offset = len(glyph_data)  # offset from font->data to map array
    # Patch the map pointer slot (bytes 24-27) with offset from font->data to map
    metadata = bytearray(metadata)
    struct.pack_into('<I', metadata, 24, map_offset)
    metadata = bytes(metadata)

    with open(output_path, 'wb') as f:
        f.write(metadata)
        f.write(glyph_data)
        f.write(map_bytes)

    print(f"Wrote {len(metadata) + len(glyph_data) + len(map_bytes)} bytes ({len(metadata)} header + {len(glyph_data)} glyphs + {len(map_bytes)} map)")
    print(f"  Map entries: {map_len}")
    print(f"  Glyph bytes: {data_size}")

if __name__ == '__main__':
    main()
