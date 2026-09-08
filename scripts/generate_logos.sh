#!/bin/sh

INPUT="src/logo/ascii"
OUTPUT="build/logos.h"

mkdir -p build

echo "/* Generated file. Do not edit. */" >"$OUTPUT"

find "$INPUT" -type f -name "*.txt" | while read -r file; do
  xxd -i "$file" >>"$OUTPUT"
done

echo "Logos generated: $OUTPUT"
