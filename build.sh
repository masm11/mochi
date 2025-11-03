#!/bin/bash

if [ -d /System ]; then
    make -DAPPLE all
else
    make all
fi
