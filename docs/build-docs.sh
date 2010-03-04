#!/bin/sh
# Script name: build-docs.sh
# Description: Builds documentation using Natural Docs

ND="NaturalDocs"
MD="markdown"

echo "Building API documentation..."
$ND -h >/dev/null 2>&1 || echo "Cannot find NaturalDocs!"
$ND -i .. -o HTML HTML -p nd || echo "API documentation building failed."

echo "Building Readme..."
$MD -v >/dev/null 2>&1 || echo "Cannot find markdown!"
$MD ../README.markdown > Readme.html || echo "Readme building failed."

echo "All done."

