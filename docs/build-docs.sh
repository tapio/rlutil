#!/bin/sh
# Script name: build-docs.sh
# Description: Builds documentation and webpage

ND="naturaldocs"
MD="markdown"
SD="sed"

echo "Building API documentation..."
$ND -h >/dev/null 2>&1 || echo "Cannot find NaturalDocs!"
$ND -i .. -o HTML HTML -p nd || echo "API documentation building failed."

echo "Building Readme..."
$MD -v >/dev/null 2>&1 || echo "Cannot find markdown!"
$MD ../README.markdown > Readme.html || echo "Readme building failed."

echo "Building index page..."
$SD --version >/dev/null 2>&1 || echo "Cannot find sed!"
$SD '/Readme.html/ r Readme.html' < template.html > ../index.html || exit 1

echo "All done."

