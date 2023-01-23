#!/bin/sh

echo "Building BS.Snake ..."
gcc snake.c -lncurses -lpthread -o snake
if [ -f snake ]
    then
    chmod +x snake
fi
