#!/usr/bin/env python3
"""Simple Markdown to HTML translator (partial) using re.

Recognizes headings (#), emphasis (* and **) with constraints, and
unordered (- ) and ordered (N. ) lists. Writes output to .html file.
"""
import re
import sys
from pathlib import Path


def translate_text(text: str) -> str:
    # Bold first: **text** where not adjacent to alnum and not starting/ending with space
    bold_re = re.compile(r"(?<![A-Za-z0-9])\*\*([^\s][^*]*?[^\s])\*\*(?![A-Za-z0-9])")
    text = bold_re.sub(r"<strong>\1</strong>", text)

    # Italic: *text* with same constraints
    em_re = re.compile(r"(?<![A-Za-z0-9])\*([^\s][^*]*?[^\s])\*(?![A-Za-z0-9])")
    text = em_re.sub(r"<em>\1</em>", text)

    return text


def convert_lines(lines):
    out_lines = []
    in_ul = False
    in_ol = False

    for raw in lines:
        line = raw.rstrip('\n')

        # Headings: only when # appear at start followed by space
        m = re.match(r'^(#{1,6})\s+(.*)$', line)
        if m:
            # close any open lists
            if in_ul:
                out_lines.append('</ul>')
                in_ul = False
            if in_ol:
                out_lines.append('</ol>')
                in_ol = False

            level = len(m.group(1))
            content = translate_text(m.group(2))
            out_lines.append(f"<h{level}>{content}</h{level}>")
            continue

        # Unordered list item
        m = re.match(r'^-\s+(.*)$', line)
        if m:
            if in_ol:
                out_lines.append('</ol>')
                in_ol = False
            if not in_ul:
                out_lines.append('<ul>')
                in_ul = True
            content = translate_text(m.group(1))
            out_lines.append(f" <li>{content}</li>")
            continue

        # Ordered list item like '1. item'
        m = re.match(r'^(\d+)\.\s+(.*)$', line)
        if m:
            if in_ul:
                out_lines.append('</ul>')
                in_ul = False
            if not in_ol:
                out_lines.append('<ol>')
                in_ol = True
            content = translate_text(m.group(2))
            out_lines.append(f" <li>{content}</li>")
            continue

        # Any other line: close lists if open, then translate inline
        if in_ul:
            out_lines.append('</ul>')
            in_ul = False
        if in_ol:
            out_lines.append('</ol>')
            in_ol = False

        if line.strip() == '':
            out_lines.append('')
        else:
            out_lines.append(translate_text(line))

    # Close lists at EOF
    if in_ul:
        out_lines.append('</ul>')
    if in_ol:
        out_lines.append('</ol>')

    return out_lines


def convert_file(path: Path) -> Path:
    src = path
    dst = path.with_suffix('.html')

    with src.open('r', encoding='utf-8') as f:
        lines = f.readlines()

    out_lines = convert_lines(lines)

    with dst.open('w', encoding='utf-8') as f:
        for ln in out_lines:
            f.write(ln + '\n')

    return dst


def main():
    if len(sys.argv) < 2:
        print('Usage: md2html.py <file.md> [more.md ...]')
        sys.exit(1)

    for p in sys.argv[1:]:
        dst = convert_file(Path(p))
        print(f'Wrote {dst}')


if __name__ == '__main__':
    main()
