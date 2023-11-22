!/bin/bash

for i in $(find $directory -type f -name \*.rst)
do

rst2html "$i" "./html${i%}.html"
#echo  "./html${i%}.html"
done
