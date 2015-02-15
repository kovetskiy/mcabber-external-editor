#!/bin/bash

LDFLAGS=$(pkg-config --cflags glib-2.0)
echo $LDFLAGS
$(go env CC) $(go env GOGCCFLAGS) $LDFLAGS -shared editor.c -o libeditor.so 
