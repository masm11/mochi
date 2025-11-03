#!/bin/bash

if [ -d /System ]; then
    make APPLE=1 all
else
    make all
fi
