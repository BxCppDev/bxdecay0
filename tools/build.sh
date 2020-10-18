#!/usr/bin/env bash

# A Bash script to build and install devel BxDecay0 on Ubuntu (YY.04).

opwd=$(pwd)
function my_exit()
{
    local error_code=$1
    shift 1
    cd ${opwd}
    exit ${error_code}
}

function do_usage()
{
    cat<<EOF

build.sh [options]

Options:

  --help              print this help then exit
  --prefix [path]     set the installation directory
  --gsl-prefix [path] set the GSL installation directory
  --with-dbd-gA       build with DBD gA support
  --without-dbd-gA    build without DBD gA support

EOF
    return 0
}

src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d
clean=false
devel=false
gsl_prefix=
with_dbd_gA=false

while [ -n "$1" ]; do
    opt="$1"
    if [ "${opt}" = "--help" ]; then
	do_usage
    	my_exit 0
    elif [ "${opt}" = "--prefix" ]; then
	shift 1
	install_dir="$1"
    elif [ "${opt}" = "--clean" ]; then
	clean=true
    elif [ "${opt}" = "--with-dbd-gA" ]; then
	with_dbd_gA=true
    elif [ "${opt}" = "--without-dbd-gA" ]; then
	with_dbd_gA=false
    elif [ "${opt}" = "--gsl-prefix" ]; then
	shift 1
	gsl_prefix="$1"
    fi
    shift 1
done

echo >&2 "[log] install_dir = '${install_dir}'"
echo >&2 "[log] clean       = ${clean}"
echo >&2 "[log] with_dbd_gA = ${with_dbd_gA}"
echo >&2 "[log] gsl_prefix  = '${gsl_prefix}'"

if [ ${clean} = true ]; then
    if [ -d ${install_dir} ]; then
	rm -fr ${install_dir}
    fi

    if [ -d ${build_dir} ]; then
	rm -fr ${build_dir}
    fi
fi

mkdir -p ${build_dir}

cd ${build_dir}

gsl_options=
if [ "x${gsl_prefix}" = "x" ]; then
    which gsl-config > /dev/null 2>&1
    if [ $? -ne 0 ]; then
	echo >&2 "[error] Cannot find 'gsl-config' on this system! Abort!"
	my_exit 1
    fi
    gsl_prefix=$(gsl-config --prefix)
fi

if [ "x${gsl_prefix}" != "x" ]; then
    if [ ! -d ${gsl_prefix} ]; then
	echo >&2 "[error] GSL prefix directory '${gsl_prefix}' does not exist! Abort!"
	
	my_exit 1
    fi
    gsl_options="-DGSL_ROOT_DIR=${gsl_prefix}"
fi

dbd_gA_options="-DBxDecay0_WITH_DBD_GA=ON"
if [ ${with_dbd_gA} = false ]; then
    dbd_gA_options="-DBxDecay0_WITH_DBD_GA=OFF"
fi
    
echo >&2 ""
echo >&2 "[info] Configuring..."
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    ${gsl_options} \
    ${dbd_gA_options} \
    ${src_dir}
if [ $? -ne 0 ]; then
    echo >&2 "[error] CMake failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Building..."
make -j
if [ $? -ne 0 ]; then
    echo >&2 "[error] Build failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Testing..."
make test
if [ $? -ne 0 ]; then
    echo >&2 "[error] Testing failed! Abort!"
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
