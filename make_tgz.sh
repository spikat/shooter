#!/bin/sh

if [ ! -e ./src/spishooter ]; then
    echo "First, try to compile spishooter!"
    exit 1;
fi

cp ./src/spishooter . || exit 1;
cp ./src/spishooter_static . || exit 1;
tar cvzf spishooter.tgz spishooter spishooter_static assets || exit 1

