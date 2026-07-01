#!/usr/bin/env python3
"""Regenerate FusionPixel12.c with Chinese punctuation glyphs added."""

from PIL import Image, ImageDraw, ImageFont
import os

FONT_TTF = os.path.join(os.path.dirname(__file__), "fonts", "fusion-pixel-12px-monospaced-zh_hans.ttf")
FONT_C = os.path.join(os.path.dirname(__file__), "..", "fonts", "FusionPixel12.c")
FONT_SIZE = 12
MAP_START = 19968

CHAR_RANGES = "32-126, 160-255, 0x3000-0x3029, 0x3030-0x303F, 0xFF00-0xFFEF, 0xFE10-0xFE1F, 0xFE30-0xFE4F, 0x2010-0x2027, 19968-40959"

def to_int(s):
    if s.startswith("0x") or s.startswith("0X"):
        return int(s, 16)
    try:
        return int(s, 10)
    except ValueError:
        return int(s, 16)

def get_char_list(ranges):
    if isinstance(ranges, str):
        ranges = ranges.replace(" ", "").split(',')
    chars = []
    for intervals in ranges:
        parts = intervals.split('-')
        first = to_int(parts[0])
        second = to_int(parts[1]) if len(parts) > 1 else first
        for c in range(first, second + 1):
            chars.append(c)
    return sorted(set(chars))


def find_bounding_box(image):
    pixels = image.load()
    w, h = image.size
    x_min, y_min = w, h
    x_max, y_max = 0, 0
    for y in range(h):
        for x in range(w):
            if pixels[x, y] >= 1:
                x_min = min(x_min, x)
                y_min = min(y_min, y)
                x_max = max(x_max, x)
                y_max = max(y_max, y)
    if x_min > x_max or y_min > y_max:
        return None
    return (x_min, y_min, x_max + 1, y_max + 1)


def load_font(font_path, font_size):
    pil_font = ImageFont.truetype(font_path, font_size)
    font_name = ' '.join(pil_font.getname())
    codes = get_char_list(CHAR_RANGES)
    font_data = []
    for char_code in codes:
        char = chr(char_code)
        image = Image.new("1", (font_size * 2, font_size * 2), 0)
        draw = ImageDraw.Draw(image)
        draw.text((1, 0), char, font=pil_font, fill=255)
        bbox = find_bounding_box(image)
        if bbox is None:
            width, height = 0, 0
            offset_x, offset_y = 0, 0
        else:
            x0, y0, x1, y1 = bbox
            width, height = x1 - x0, y1 - y0
            offset_x, offset_y = x0, y0
            if offset_x:
                offset_x -= 1
        try:
            adv_w = int(draw.textlength(char, font=pil_font))
            adv_w = max(adv_w, width + offset_x)
        except:
            adv_w = width + offset_x
        cropped = image.crop(bbox) if bbox else image
        bitmap = []
        row = 0
        i = 0
        for y in range(height):
            for x in range(width):
                if i == 8:
                    bitmap.append(row)
                    row = 0
                    i = 0
                pixel = 1 if cropped.getpixel((x, y)) else 0
                row = (row << 1) | pixel
                i += 1
        bitmap.append(row << (8 - i)) if i else None
        bitmap = bitmap[:int((width * height + 7) / 8)]
        font_data.append({
            "char_code": char_code,
            "ofs_y": offset_y,
            "box_w": width,
            "box_h": height,
            "ofs_x": offset_x,
            "adv_w": adv_w,
            "bitmap": bitmap,
        })
    # Adjust offsets for consistent height
    max_height = max(g["ofs_y"] + g["box_h"] for g in font_data)
    if max_height > font_size:
        min_ofs_y = min((g["ofs_y"] if g["box_h"] > 0 else 1000) for g in font_data)
        for g in font_data:
            if min_ofs_y > 0 and g["ofs_y"] >= min_ofs_y:
                g["ofs_y"] -= min_ofs_y
        max_height = max(g["ofs_y"] + g["box_h"] for g in font_data)
    print(f"Glyphs: {len(font_data)}, max_height: {max_height}")
    return font_name, font_size, font_data


def generate_c_font(font_name, font_size, font_data):
    normalized_name = font_name.replace('-', '_').replace(' ', '') + str(font_size)
    # Generate map
    codes = [g["char_code"] for g in font_data]
    max_char = max(codes)
    map_size = max_char - MAP_START + 1
    map_data = [0] * map_size
    data_index = 0
    for g in font_data:
        mi = g["char_code"] - MAP_START
        if 0 <= mi < map_size:
            map_data[mi] = data_index
        data_index += 7 + len(g["bitmap"])
    mem_usage = sum(len(g["bitmap"]) + 7 for g in font_data) + map_size * 4
    # Build file
    lines = []
    lines.append('#include "../rg_gui.h"')
    lines.append('')
    lines.append('// File generated with font_converter.py (https://github.com/ducalex/retro-go/tree/dev/tools)')
    lines.append('')
    lines.append(f'// Font           : {font_name}')
    lines.append(f'// Point Size     : {font_size}')
    lines.append(f'// Memory usage   : {mem_usage} bytes')
    lines.append(f'// # characters   : {len(font_data)}')
    lines.append(f'// Map start code : {MAP_START}')
    lines.append(f'// Map size       : {len(map_data)} entries')
    lines.append('')
    lines.append(f'static const uint32_t font_{normalized_name}_map[] = {{')
    for i in range(0, len(map_data), 8):
        chunk = map_data[i:i+8]
        lines.append("    " + ", ".join(f"0x{v:04X}" for v in chunk) + ",")
    lines.append('};')
    lines.append('')
    lines.append(f'const rg_font_t font_{normalized_name} = {{')
    lines.append(f'    .name = "{font_name}",')
    lines.append(f'    .type = 2,')
    lines.append(f'    .width = 0,')
    lines.append(f'    .height = {font_size},')
    lines.append(f'    .chars = {len(font_data)},')
    lines.append(f'    .map_start_code = {MAP_START},')
    lines.append(f'    .map = font_{normalized_name}_map,')
    lines.append(f'    .map_len = sizeof(font_{normalized_name}_map) / 4,')
    lines.append(f'    .data = {{')
    for g in font_data:
        cc = g["char_code"]
        hdr = [cc & 0xFF, cc >> 8, g["ofs_y"], g["box_w"], g["box_h"], g["ofs_x"], g["adv_w"]]
        label = chr(cc) if 0x20 <= cc <= 0x7E else '?'
        lines.append(f'        /* U+{cc:04X} \'{label}\' */')
        lines.append('        ' + ', '.join(f"0x{b:02X}" for b in hdr) + ',')
        if g["bitmap"]:
            lines.append('        ' + ', '.join(f"0x{b:02X}" for b in g["bitmap"]) + ',')
        lines.append('')
    lines.append('')
    lines.append('        // Terminator')
    lines.append('        0x00, 0x00,')
    lines.append('    },')
    lines.append('};')
    lines.append('')
    return '\n'.join(lines)


def main():
    print(f"Loading font: {FONT_TTF}")
    name, size, data = load_font(FONT_TTF, FONT_SIZE)
    print(f"Generating C font: {name}")
    c_code = generate_c_font(name, size, data)
    print(f"Writing to: {FONT_C}")
    with open(FONT_C, 'w', encoding='UTF-8') as f:
        f.write(c_code)
    print("Done!")


if __name__ == '__main__':
    main()
