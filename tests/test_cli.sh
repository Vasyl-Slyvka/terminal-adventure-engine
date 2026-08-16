#!/bin/sh
set -eu

output_file="${TMPDIR:-/tmp}/terminal-adventure-cli-$$.txt"
long_input_file="${TMPDIR:-/tmp}/terminal-adventure-long-input-$$.txt"
trap 'rm -f "$output_file" "$long_input_file"' EXIT HUP INT TERM

./adventure < scenario.txt > "$output_file"

grep -q "The Age of Stars begins" "$output_file"
grep -q "Hra bola uspesne dokoncena" "$output_file"

awk 'BEGIN { for (i = 0; i < 140; i++) printf "x"; print ""; print "quit" }' > "$long_input_file"
./adventure < "$long_input_file" > "$output_file"
grep -q "Prikaz je prilis dlhy" "$output_file"
grep -q "Koniec hry" "$output_file"

printf 'CLI scenario test passed.\n'
