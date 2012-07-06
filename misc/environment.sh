#!/bin/sh

if [ "$WINDIR" ]; then
    if [ -d "../ode-0.11.1/include/ode" ];then
        export ODE_INCLUDE=$PWD/../ode-0.11.1/include
    fi
    if [ -d "../ode-0.11.1/lib/ReleaseDoubleLib" ];then
        export ODE_LIB=$PWD/../ode-0.11.1/lib/ReleaseDoubleLib
    fi
    if [ -d "../ode-0.11.1/drawstuff/src" ];then
        export DRAWSTUFF_RC_DIR=$PWD/../ode-0.11.1/drawstuff/src
    fi
    if [ -d ../ode-0.11.1/drawstuff/textures ]; then
        export DRAWSTUFF_TEXTURE_PATH=$PWD/../ode-0.11.1/drawstuff/textures
    fi
fi
    