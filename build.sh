#!/bin/bash

BUILD_DIR=configs

if [ ! -d $BUILD_DIR ]; then
    mkdir -p $BUILD_DIR
fi

cd $BUILD_DIR
cmake ../
make
