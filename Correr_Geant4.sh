#!/bin/bash


echo "Iniciando simulaciones de Geant4... Tenga paciencia..."

for G in `seq 1 2`;
do
	echo "Preparandose para geometria	$G..."
	text=$(grep "key$G " matrix.txt) 
	echo $text > dummy.txt
	mkdir $G
	mkdir $G/data
	mkdir $G/out
	./iterar_energias.sh $G
	hadd data_G$G.root data_E{0..210}.root
	mv data_E{0..210}.root $G/data/.
	mv out* $G/out/.
	mv data_G$G.root $G/.
	echo "Simulaciones para Geometria:	$G...	finalizadas"
done
echo "Simulaciones ejecutadas :3"

