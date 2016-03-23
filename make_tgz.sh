#!/bin/sh

if [ ! -e ./src/spishooter ]; then
    echo "First, try to compile spishooter!"
    exit 1;
fi

cp ./src/spishooter . || exit 1;
tar cvf spishooter.tar spishooter assets || exit 1
tar cvzf spishooter.tar.gz spishooter.tar || exit 1

