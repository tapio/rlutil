#!/bin/sh
# Script name: publish-docs.sh
# Description: Builds and publishes documentation and webpage

./build-docs.sh || exit 1

git add HTML
git commit -a -m "Sync documentation and webpage." || exit 1
git checkout gh-pages || exit 1
echo "Merging changes from master branch..."
git merge -Xtheirs master || exit 1
echo "Publishing changes..."
git push origin gh-pages || exit 1
git checkout master
git push origin master || exit 1
echo "All done."

