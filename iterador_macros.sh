#!/bin/bash

a='data_E'
b='.root'

echo "Creando macros..."
cp macro.mac macro/neutron_G$1_E0.mac
for i in `seq 0 10`;
do
	n0=$(($i - 13))
	n1=$(($i - 12))
	n2=$(($i - 11))
	grep -lr -e "point	1e$n1	1" macro.mac | xargs sed -i "s/point	1e$n1	1/point	1e$n2	1/g"
	if	(($i == 0))
	then
			grep -lr -e "point	0	0" macro.mac | xargs sed -i "s/point	0	0/point	1e$n1	0/g"
	fi
	grep -lr -e "point	1e$n0	0" macro.mac | xargs sed -i "s/point	1e$n0	0/point	1e$n1	0/g"
	it=$(($i + 1))
	cp macro.mac macro/neutron_G$1_E$it.mac

done

it=12
grep -lr -e "point	1e-1	1" macro.mac | xargs sed -i "s/point	1e-1	1/point	.2	1/g"
grep -lr -e "point	1e-2	0" macro.mac | xargs sed -i "s/point	1e-2	0/point	.1	0/g"
cp macro.mac macro/neutron_G$1_E$it.mac
it=0

for j in `seq 2 199`;
do
	ant=$(echo "scale=2; .1 * $j - .1" | bc)
	act=$(echo "scale=2; .1 * $j" | bc)
	sig=$(echo "scale=2; .1 * $j + .1" | bc)
	grep -lr -e "point	$act	1" macro.mac | xargs sed -i "s/point	$act	1/point	$sig	1/g"
	grep -lr -e "point	$ant	0" macro.mac | xargs sed -i "s/point	$ant	0/point	$act	0/g"
	it=$(echo "scale=2; $j + 11" | bc)
	cp macro.mac macro/neutron_G$1_E$it.mac

done

echo "Macros creados"

grep -lr -e "point	$sig	1" macro.mac | xargs sed -i "s/point	$sig	1/point	1e-12	1/g"
grep -lr -e "point	$act	0" macro.mac | xargs sed -i "s/point	$act	0/point	0	0/g"
