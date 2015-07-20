#!/usr/bin/env bash

ZYPPER_CMD=`command -v zypper`
APT_GET_CMD=`command -v apt-get`

# Requirements
if [ -n "$ZYPPER_CMD" ]; then
    sudo zypper install python-pygame
 elif [ -n "$APT_GET_CMD" ]; then
    sudo apt-get install python-pygame
 else
    echo "error can't install package python-pygame"
    exit 1;
 fi
