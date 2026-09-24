#!/bin/sh

INPUT="src/logo/ascii"
OUTPUT="build/logos.h"

mkdir -p build

echo "/* Generated file. Do not edit. */" >"$OUTPUT"

RED=$(printf '\033[31m')
GREEN=$(printf '\033[32m')
BGREEN=$(printf '\033[1;32m')
YELLOW=$(printf '\033[33m')
BLUE=$(printf '\033[34m')
MAGENTA=$(printf '\033[35m')
CYAN=$(printf '\033[1;36m')
WHITE=$(printf '\033[37m')
BWHITE=$(printf '\033[1;37m')
BLACK=$(printf '\033[30m')
RESET=$(printf '\033[0m')

find "$INPUT" -type f -name "*.txt" | while read -r file; do

  tmp=$(mktemp)
sed \
  -e 's/@BLACK@/'"$BLACK"'/g' \
  -e 's/@RED@/'"$RED"'/g' \
  -e 's/@GREEN@/'"$GREEN"'/g' \
  -e 's/@BGREEN@/'"$BGREEN"'/g' \
  -e 's/@YELLOW@/'"$YELLOW"'/g' \
  -e 's/@BLUE@/'"$BLUE"'/g' \
  -e 's/@MAGENTA@/'"$MAGENTA"'/g' \
  -e 's/@CYAN@/'"$CYAN"'/g' \
  -e 's/@WHITE@/'"$WHITE"'/g' \
  -e 's/@BWHITE@/'"$BWHITE"'/g' \
  -e 's/@RESET@/'"$RESET"'/g' \
  "$file" >"$tmp"

  name=$(printf '%s' "$file" | sed 's|/|_|g; s|\.|_|g')

  xxd -i "$tmp" |
    sed \
      "s/^unsigned char .*\\[\] = {/unsigned char ${name}[] = {/; \
             s/^unsigned int .*_len =/unsigned int ${name}_len =/;" \
      >>"$OUTPUT"

  rm -f "$tmp"

done

echo "Logos generated: $OUTPUT"
