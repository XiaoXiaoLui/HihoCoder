#!/bin/sh

if [ x$1 = x ]; then
	echo "format: create.sh dir_name"
	exit 1
fi

DIR=$1
mkdir $DIR
FILES=(A B C D)
EXT=".cpp"

for f in ${FILES[@]};
do
	cp "template.cpp" $DIR/$f$EXT
done