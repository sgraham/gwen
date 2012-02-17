#!/bin/bash

UNAME=`uname`

if [ "$UNAME" == "Darwin" ]; then
 
    chmod 777 ./premake4-osx
    ./premake4-osx clean
    ./premake4-osx --platform=universal32 gmake
    ./premake4-osx --platform=universal32 xcode3
    ./premake4-osx --platform=universal32 xcode4
    
    cd macosx/gmake/
    make config=releaseuniv32
    make config=debuguniv32
    
fi
	
if [ "$UNAME" == "Linux" ]; then

    ./premake4 clean
    ./premake4 gmake
    
    cd linux/gmake/
    make config=release
    make config=debug
    
fi

