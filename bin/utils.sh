#!/bin/bash

funcs=(
"assert"
"set_build_type"
"get_args"
)

function assert () {
    if [ ${?} -ne 0 ]; then exit; fi;
}

function set_build_type () {
    BUILD_T="$4"
    if [ "$1" = "-R" ] || [ "$1" = "--Release" ] ; then
        BUILD_T="$2"
    elif [ "$1" = "-D" ] || [ "$1" = "--Debug" ] ; then
        BUILD_T="$3"
    fi
    echo "${BUILD_T}"
}

function get_args () {
    args=""
    for ARG in $( echo "${@}" | sed 's/ / /g' ) ; do
        args="${args} ${ARG}"
    done
    echo "${args}"
}

# SOURCE FUNCS

for((i=0;i<${#funcs[@]};i++)) ; do
    declare -f "${funcs[$i]}" >/dev/null
    [ $? -eq 0 ]
done

if [ "$1" == "--source-specific" ] ; then
    for((i=0;i<${#funcs[@]};i++)) ; do
        for((j=2;j<=$#;j++)); do
            test "${funcs[$i]}" == "$(eval 'echo ${'$j'}')" && continue 2
            done
        unset ${funcs[$i]}
    done
fi
unset i j funcs
