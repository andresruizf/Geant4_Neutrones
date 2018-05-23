#!/bin/bash


mkdir macro

cp neutron.mac macro.mac

for i in `seq 751 760`;
do
	text=$(grep "key$i " matrix.txt) 
	echo $text > dummy.txt

	./lector_geometrias.sh read
	./iterador_macros.sh $i
	./lector_geometrias.sh close
	
done

rm macro.mac

