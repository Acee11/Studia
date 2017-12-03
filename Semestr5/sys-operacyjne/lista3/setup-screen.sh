#!/bin/bash
if [ "$1" == "setup" ]; then
    xrandr --output eDP-1 --mode 1024x768 --same-as DP-1
elif [ "$1" == "reset" ]; then
    xrandr --output eDP-1 --auto --left-of DP-1
fi