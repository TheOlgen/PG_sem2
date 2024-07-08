#!/bin/bash

grep "OK DOWNLOAD" cdlinux.txt | cut -d "\"" -f 2,4 | sort -u | cut -d '"' -f 2 | sed " s#.*/##" | grep "iso$" > tmp.txt
cut -d" " -f 1,7,9 cdlinux2.txt |grep '200$'|sort |uniq |cut -d " " -f 2|grep '\.iso'|grep -o "cdlinux-.*" |sed "s#?.*##" >> tmp.txt

cat < tmp.txt | sort | uniq -c 
