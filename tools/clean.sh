#!/usr/bin/env bash

# A Bash script to clean devel BxDecay0 installation on Ubuntu Linux (20.04).
#
#
opwd=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d
if [ -d ${install_dir} ]; then
    rm -fr ${install_dir}
fi

if [ -d ${build_dir} ]; then
    rm -fr ${build_dir}
fi

cd ${opwd}
exit 0
