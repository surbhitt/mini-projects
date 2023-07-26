# for compiling all the files
# ./build.sh
# for compiling a single file 
# ./build.sh file_name

#!/usr/bin/env sh

build_file() {
    echo "-building $1"
    file_name = $(echo $1 | awk -F "." '{print $1}')
    file_ext = $(echo $1 | awk -F "." '{print $2}')
    command = "$1 -o $file_name.out"
    if [[ $file_ext -eq c ]]; then
        gcc $command
    elif [[ $file_ext -eq cpp ]]; then
        gpp $command 
    fi
}

build_all () {
    for file in *; do
        build_file file      
    done
}

if [[ $# < 1 ]]; then
    build_all 
else
    build_file $1
fi


