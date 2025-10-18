#!/usr/bin/env bash

PDF_INPUT_DIR="../pdfs"
OUTPUT_DIR="../outputs"
MARKER_TOOL="$HOME/.local/bin/marker_single"

for pdf_path in "$PDF_INPUT_DIR"/*.pdf; do

    "$MARKER_TOOL" "$pdf_path" --output_dir "$OUTPUT_DIR" --use_llm --ollama_base_url 127.0.0.1:11435 --ollama_model deepseek-r1:1.5b --llm_service=marker.services.ollama.OllamaService

    if [ $? -ne 0 ]; then
        echo "Warning: marker_single failed to process $pdf_path"
    fi

done
