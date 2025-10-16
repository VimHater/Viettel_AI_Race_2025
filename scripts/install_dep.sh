#!/usr/bin/env bash

DEPENDENCIES=("pipx")

for dep in "${DEPENDENCIES[@]}"; do
    if ! command -v "$dep" &> /dev/null; then
        echo "Require '$dep'"
        exit 1;
    fi
done

if ! "$HOME/.local/bin/marker_single"; then
    pipx install markder-pdf
fi
