#!/usr/bin/env bash

# A Bash script to build and install devel BxDecay0 example ex01 tutorials on Ubuntu (16.04).

opwd=$(pwd)
function my_exit()
{
    local error_code=$1
    shift 1
    cd ${opwd}
    exit ${error_code}
}

src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d

devel=false
bxdecay0_prefix=""

while [ -n "$1" ]; do
    opt="$1"
    if [ "${opt}" = "--bxdecay0-prefix" ]; then
	shift 1
	bxdecay0_prefix="$1"
    elif [ "${opt}" = "--devel" ]; then
	devel=true
    fi
    shift 1
done

if [ -z "${bxdecay0_prefix}" ]; then
    if [ ${devel} = true ]; then
	bxdecay0_prefix="../../_install.d"
    else
	which bxdecay0-query > /dev/null 2>&1
	if [ $? -eq 0 ]; then
	    bxdecay0_prefix=$(bxdecay0-query --cmakedir)
	fi
    fi
fi

if [ -z "${bxdecay0_prefix}" ]; then
    echo >&2 "[error] Missing BxDecay0 installation path! Abort!"
    my_exit 1
fi

if [ ! -d ${bxdecay0_prefix} ]; then
    echo >&2 "[error] No BxDecay0 installation! Abort!"
    my_exit 1
fi
cd ${bxdecay0_prefix}
bxdecay0_prefix=$(pwd)
echo >&2 "[info] BxDecay0 install dir = '${bxdecay0_prefix}'"
cd ${opwd}
export PATH="${bxdecay0_prefix}/bin:${PATH}"

which bxdecay0-query > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo >&2 "[error] BxDecay0 is not installed! Abort!"
    my_exit 1
else
    echo >&2 "[info] Found BxDecay0 config script."
fi

if [ -d ${install_dir} ]; then
    rm -fr ${install_dir}
fi

if [ -d ${build_dir} ]; then
    rm -fr ${build_dir}
fi

mkdir -p ${build_dir}

cd ${build_dir}
echo >&2 ""
echo >&2 "[info] Configuring..."
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    -DBxDecay0_DIR="$(bxdecay0-query --cmakedir)" \
    ${src_dir}
if [ $? -ne 0 ]; then
    echo >&2 "[error] CMake failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Building..."
make -j4
if [ $? -ne 0 ]; then
    echo >&2 "[error] Build failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Installing..."
make install
if [ $? -ne 0 ]; then
    echo >&2 "[error] Installation failed! Abort!"
    my_exit 1
fi

my_exit 0

# end
