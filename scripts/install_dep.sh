#!/usr/bin/env bash

DEPENDENCIES=("pipx")

for dep in "${DEPENDENCIES[@]}"; do
    if ! command -v "$dep" &> /dev/null; then
        echo "Require '$dep'"
        exit 1;
    fi
done

if ! command -v "$HOME/.local/bin/marker" &> /dev/null; then
    pipx install markder-pdf
fi
