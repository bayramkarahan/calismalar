#!/bin/bash

directory=$1

for i in $(find $directory -type f -name \*.rst)
do
    RST_FILE="$i"
    HTML_FILE="./html/${i}.html"
    HTML_DIR=$(dirname ${HTML_FILE})
    mkdir -p ${HTML_DIR}
    rst2html "$i" "$HTML_FILE"
   #echo "$i" 
   # echo "$HTML_FILE"
done

