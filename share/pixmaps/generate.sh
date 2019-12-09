#!/bin/sh

for size in 256 128 64 32 16; do
    convert dngrcoin.png -resize "${size}x${size}" "dngrcoin${size}.png"
    convert dngrcoin.png -resize "${size}x${size}" "dngrcoin${size}.xpm"
done
