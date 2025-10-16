#!/usr/bin/env bash

./install_dep.sh

pipx install marker-pdf

"$HOME"/.local/bin/marker "../pdfs/" --output_dir "../outputs/"
