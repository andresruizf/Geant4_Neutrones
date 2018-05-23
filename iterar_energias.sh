#!/bin/bash

for E in `seq 0 210`
do
	echo "Corriendo intervalo de energia:	$E/210	en geometria:	$1"
	./detector_He3 ../macro/neutron_G$1_E$E.mac > out_G$1_E$E.txt

	# En caso de multi-nucleos
	# hadd data_E$E.root data_t{0..39}.root

	mv data.root data_E$E.root
done
