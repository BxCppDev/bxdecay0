#!/usr/bin/env bash
# Author: F.Mauger
# Date: 2020-12-12
# A Bash script to build and install devel BxDecay0 on Ubuntu Linux (20.04).
# Reserved for quick build by developpers.

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

  --help                     print this help then exit
  --prefix [path]            set the installation directory
  --gsl-prefix [path]        set the GSL installation directory
  --with-dbd-gA-data         build with DBD gA data support
  --without-dbd-gA-data      build without DBD gA data support
  --with-geant4-extension    build the Geant4 extension library
  --without-geant4-extension do not build the Geant4 extension library (default)
  --geant4-prefix [path]     set the Geant4 installation directory
  --install-dir [path]       set the installation directory
EOF
    return 0
}

src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d
clean=false
devel=false
gsl_prefix=
with_dbd_gA_data=false
with_geant4_extension=false
geant4_prefix=

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
    elif [ "${opt}" = "--with-dbd-gA-data" ]; then
	with_dbd_gA_data=true
    elif [ "${opt}" = "--without-dbd-gA-data" ]; then
	with_dbd_gA_data=false
    elif [ "${opt}" = "--with-geant4-extension" -o "${opt}" = "-g4" ]; then
	with_geant4_extension=true
    elif [ "${opt}" = "--without-geant4-extension" ]; then
	with_geant4_extension=false
    elif [ "${opt}" = "--gsl-prefix" ]; then
	shift 1
	gsl_prefix="$1"
    elif [ "${opt}" = "--geant4-prefix" ]; then
	shift 1
	geant4_prefix="$1"
    elif [ "${opt}" = "--install-dir" ]; then
	shift 1
	install_dir="$1"
    fi
    shift 1
done

echo >&2 "[log] install_dir = '${install_dir}'"
echo >&2 "[log] clean       = ${clean}"
echo >&2 "[log] with_dbd_gA_data = ${with_dbd_gA_data}"
echo >&2 "[log] with_geant4_extension = ${with_geant4_extension}"
echo >&2 "[log] gsl_prefix  = '${gsl_prefix}'"
echo >&2 "[log] geant4_prefix  = '${geant4_prefix}'"

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
    which gsl-config >/dev/null 2>&1
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

dbd_gA_data_options="-DBXDECAY0_INSTALL_DBD_GA_DATA=ON"
if [ ${with_dbd_gA_data} = false ]; then
    dbd_gA_data_options="-DBXDECAY0_INSTALL_DBD_GA_DATA=OFF"
fi
echo >&2 "[info] DBD gA options = '${dbd_gA_data_options}'"

geant4_extension_options="-DBXDECAY0_WITH_GEANT4_EXTENSION=OFF"
if [ ${with_geant4_extension} = true ]; then
    if [ "x${geant4_prefix}" = "x" ]; then
	which geant4-config >/dev/null 2>&1
	if [ $? -ne 0 ]; then
	    echo >&2 "[error] Cannot find 'geant4-config' on this system! Abort!"
	    my_exit 1
	fi
	geant4_ver="$(geant4-config --version)"
	geant4_prefix="$(geant4-config --prefix)/lib/Geant4-${geant4_ver}"
    fi
    if [ ! -d ${geant4_prefix} ]; then
	echo >&2 "[error] Geant4 prefix does not exist on this system! Abort!"
	my_exit 1
    fi
    geant4_extension_options="-DBXDECAY0_WITH_GEANT4_EXTENSION=ON -DGeant4_DIR=${geant4_prefix}"
    echo >&2 "[info] Geant4 extension options = '${geant4_extension_options}'"
fi

## exit 0
echo >&2 ""
echo >&2 "[info] Configuring..."
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    ${gsl_options} \
    ${dbd_gA_data_options} \
    ${geant4_extension_options} \
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
