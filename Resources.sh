#! /usr/bin/env bash

BASEDIR=~/.magicseteditor
RESOURCEDIR=$BASEDIR/resource

rm -rf $BASEDIR
mkdir $BASEDIR

cp -R data $BASEDIR

for DIR in $RESOURCEDIR $RESOURCEDIR/icon $RESOURCEDIR/tool $RESOURCEDIR/cursor
do
if [ -d $DIR ]; then
: ;
elif [ -a $DIR ]; then
echo $DIR "exists and is not a directory!";
exit 1 ;
else
mkdir $DIR;
fi
done

cp src/resource/common/* $RESOURCEDIR;
cp src/resource/msw/tool/* $RESOURCEDIR/tool;
cp src/resource/msw/icon/* $RESOURCEDIR/icon;
cp src/resource/msw/cursor/* $RESOURCEDIR/cursor;
cp src/resource/msw/other/* $RESOURCEDIR;
