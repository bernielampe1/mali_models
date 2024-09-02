#!/bin/sh 

if [ -f "$1" ]; then rm "$1"; fi
wget http://10.0.2.2:8080/$1
chmod 755 "$1"

