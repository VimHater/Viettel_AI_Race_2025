#!/bin/bash

if [ -z "$1" ]; then
    exit 1
fi

cd ../nougat_raw/ || exit;

OUTPUT_FILE="$1.md"

curl -X 'POST' \
  'http://192.168.101.28:8503/predict/' \
  -H 'accept: application/json' \
  -H 'Content-Type: multipart/form-data' \
  -F "file=@$1;type=application/pdf" \
  > "$OUTPUT_FILE"

