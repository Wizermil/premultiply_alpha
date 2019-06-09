#!/usr/bin/env python3

import os

from PIL import Image
import click


@click.group(invoke_without_command=True)
@click.option('--input', '-i', type=click.Path(exists=True), help='file to export')
@click.option('--output', '-o', type=click.Path(), help='result of the conversion')
def export(input, output):
    try:
        namespace = os.path.splitext(os.path.basename(input))[0]
        with Image.open(input) as im, open(output, 'wb') as f:
            f.write('#pragma once\n'
                    '#include <cstdint>\n'
                    '#include <cstddef>\n'
                    '\n'
                    'namespace {} {{\n'
                    '    static constexpr std::size_t width = {};\n'
                    '    static constexpr std::size_t height = {};\n'
                    '    static constexpr std::uint8_t image[{}] = {{'.format(namespace, im.width, im.height, im.width * im.height * 4).encode('utf-8'))

            for j in range(im.height):
                for i in range(im.width):
                    r, g, b, a = im.getpixel((i, j))
                    f.write('{:#04x},'.format(r).encode('utf-8'))
                    f.write('{:#04x},'.format(g).encode('utf-8'))
                    f.write('{:#04x},'.format(b).encode('utf-8'))
                    f.write('{:#04x},'.format(a).encode('utf-8'))

            f.write('};\n'
                    '}\n'.encode('utf-8'))
    except IOError:
        pass


if __name__ == "__main__":
    export()  # pylint: disable=no-value-for-parameter
