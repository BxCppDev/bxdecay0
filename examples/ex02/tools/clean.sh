#!/usr/bin/env bash

# A Bash script to clean BxDecay0 example ex02 tutorials on Ubuntu (16.04).

opwd=$(pwd)

install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d

rm -fr ${install_dir}
rm -fr ${build_dir}

if [ -f gendecay0.data ]; then
    rm -f gendecay0.data
fi

find . -name "*~" -exec rm -f \{\} \;

exit 0

# end
