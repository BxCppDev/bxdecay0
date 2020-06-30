#!/usr/bin/env bash

dataset_origdir="/opt/sw/mauger/ga"
dataset_basedir="."
ga_modes="g0 g2 g22 g4"

do_se=true
do_mo=true
do_cd=true
do_nd=true

function input_tab_pdf()
{
    isotope="$1"
    shift 1
    ga_mode="$1"
    shift 1
    if [ "${isotope}" = "Se82" ]; then
	iso2="082Se"
    elif [ "${isotope}" = "Mo100" ]; then
	iso2="100Mo" 
    elif [ "${isotope}" = "Cd116" ]; then
	iso2="116Cd" 
    elif [ "${isotope}" = "Nd150" ]; then
	iso2="150Nd"
    else
	echo >&2 "[error] Unsupported isotope '${isotope}'!"
	exit 1
    fi
    if [ "${ga_mode}" = "g0" ]; then
	ga2="0-N0"
	file2="nEqNull"
    elif [ "${ga_mode}" = "g2" ]; then
	ga2="1-N2"
	file2="nEqTwo"
    elif [ "${ga_mode}" = "g22" ]; then
	ga2="2-N22"
	file2="nEqTwoTwo"
    elif [ "${ga_mode}" = "g4" ]; then
	ga2="3-N4"
	file2="nEqFour"
    else
	echo >&2 "[error] Unsupported gA mode '${ga_mode}'!"
	exit 1
    fi
    echo "${dataset_origdir}/${iso2}/${ga2}/${file2}.dat"
    return 0
}

function test_input_tab_pdf()
{
    echo >&2 "[test] Print original dataset files:"
    input_tab_pdf Se82  g0
    input_tab_pdf Se82  g2
    input_tab_pdf Se82  g22
    input_tab_pdf Se82  g4
    input_tab_pdf Mo100 g0
    input_tab_pdf Mo100 g2
    input_tab_pdf Mo100 g22
    input_tab_pdf Mo100 g4
    input_tab_pdf Cd116 g0
    input_tab_pdf Cd116 g2
    input_tab_pdf Cd116 g22
    input_tab_pdf Cd116 g4
    input_tab_pdf Nd150 g0
    input_tab_pdf Nd150 g2
    input_tab_pdf Nd150 g22
    input_tab_pdf Nd150 g4
    return 0
}

function _process()
{
    local isotope="$1"
    shift 1
    local ga_mode="$1"
    shift 1
    local Qbb="$1"
    shift 1
    local infile=`input_tab_pdf ${isotope} ${ga_mode}`
    if [ ! -f ${infile} ]; then
	echo >&2 "[error] Input file '${infile}' does not exist!"
	return 1
    fi
    echo >&2 "[debug] isotope = ${isotope}"
    echo >&2 "[debug] ga_mode = ${ga_mode}"
    echo >&2 "[debug] Qbb     = ${Qbb}"
    echo >&2 "[debug] infile  = ${infile}"
    python3 mkocdfdata.py "${infile}" "${isotope}" "${ga_mode}" ${Qbb}
    dataset_dir="${dataset_basedir}/${isotope}/${ga_mode}"
    if [ ! -d ${dataset_dir} ]; then
	mkdir -p ${dataset_dir}
    fi
    mv tab_ocdf.data ${dataset_dir}/
    mv tab_pdf.data ${dataset_dir}/
 
    return 0
}

function process_se()
{
    isotope="Se82"
    Qbb=2.99512
    for ga_mode in ${ga_modes} ; do
	_process ${isotope} ${ga_mode}  ${Qbb}
    done
    return 0
}

function process_mo()
{
    isotope="Mo100"
    Qbb=3.0344
    for ga_mode in ${ga_modes} ; do
	_process ${isotope} ${ga_mode}  ${Qbb}
    done
    return 0
}

function process_cd()
{
    isotope="Cd116"
    Qbb=2.8135
    for ga_mode in ${ga_modes} ; do
	_process ${isotope} ${ga_mode}  ${Qbb}
    done
    return 0
}


function process_nd()
{
    isotope="Nd150"
    Qbb=3.37138
    for ga_mode in ${ga_modes} ; do
	_process ${isotope} ${ga_mode}  ${Qbb}
    done
    return 0
}


while [ -n "$1" ]; do
    arg="$1"
    # echo >&2 "[debug] arg='${arg}'"

    if [ "${arg}" = "--input-orig-dir" -o  "${arg}" = "-i" ]; then
	shift 1
	dataset_origdir="$1"
    elif [ "${arg}" = "--output-base-dir" -o  "${arg}" = "-o" ]; then
	shift 1
	dataset_basedir="$1"
     elif [ "${arg}" = "--no-se" ]; then
	do_se=false
    elif [ "${arg}" = "--no-mo" ]; then
	do_mo=false
    elif [ "${arg}" = "--no-cd" ]; then
	do_cd=false
    elif [ "${arg}" = "--no-nd" ]; then
	do_nd=false
    fi
    
    shift 1
done

echo >&2 "[info] dataset_origdir='${dataset_origdir}'"
if [ ! -d ${dataset_origdir} ]; then
    echo >&2 "[error] Original dataset directory '${dataset_origdir}' does not exist!"
    exit 1
fi
echo >&2 "[info] dataset_basedir='${dataset_basedir}'"
if [ ! -d ${dataset_basedir} ]; then
    mkdir -p ${dataset_basedir}
    if [ $? -ne 0 ]; then
	echo >&2 "[error] Cannot create output base directory '${dataset_basedir}'!"
	exit 1
    fi
fi

test_input_tab_pdf

if [ ${do_se} = true ]; then
    process_se
fi
if [ ${do_mo} = true ]; then
    process_mo
fi
if [ ${do_cd} = true ]; then
    process_cd
fi
if [ ${do_nd} = true ]; then
    process_nd
fi

echo >&2 "[info] Output base dir '${dataset_basedir}' has been populated:"
tree ${dataset_basedir}/ 

exit 0

# end

