#!/usr/bin/env bash

PDF_INPUT_DIR="../pdfs"
OUTPUT_DIR="../outputs"
MARKER_TOOL="$HOME/.local/bin/marker_single"

for pdf_path in "$PDF_INPUT_DIR"/*.pdf; do

    "$MARKER_TOOL" "$pdf_path" --output_dir "$OUTPUT_DIR"

    if [ $? -ne 0 ]; then
        echo "Warning: marker_single failed to process $pdf_path"
    fi

done
