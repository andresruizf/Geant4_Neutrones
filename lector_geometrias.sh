#!/bin/bash


if	[ "$1" == "read" ]
then
	echo "Leyendo Dummy..."
	para=$(awk '{print $2}' dummy.txt)
	grep -lr -e "setSampleDetMat	--" macro.mac | xargs sed -i "s/setSampleDetMat	--/setSampleDetMat $para/g"

	para=$(awk '{print $3}' dummy.txt)
	grep -lr -e "Diametro_Det	--" macro.mac | xargs sed -i "s/Diametro_Det	--/Diametro_Det $para mm/g"

	para=$(awk '{print $4}' dummy.txt)
	grep -lr -e "sampleThickness	--" macro.mac | xargs sed -i "s/sampleThickness	--/sampleThickness $para mm/g"

	grep -lr -e "sampleThicknessZ_Core	--" macro.mac | xargs sed -i "s/sampleThicknessZ_Core	--/sampleThicknessZ_Core $para mm/g"

	grep -lr -e "sampleThicknessZ	--" macro.mac | xargs sed -i "s/sampleThicknessZ	--/sampleThicknessZ $para mm/g"

	grep -lr -e "sampleThicknessZ_2	--" macro.mac | xargs sed -i "s/sampleThicknessZ_2	--/sampleThicknessZ_2 $para mm/g"

	grep -lr -e "sampleThicknessZ_3	--" macro.mac | xargs sed -i "s/sampleThicknessZ_3	--/sampleThicknessZ_3 $para mm/g"

	para=$(awk '{print $5}' dummy.txt)
	grep -lr -e "setSampleMatAl	--" macro.mac | xargs sed -i "s/setSampleMatAl	--/setSampleMatAl $para/g"

	para=$(awk '{print $6}' dummy.txt)
	grep -lr -e "Diametro_Al	--" macro.mac | xargs sed -i "s/Diametro_Al	--/Diametro_Al $para mm/g"

	para=$(awk '{print $7}' dummy.txt)
	grep -lr -e "setSampleMatCad	--" macro.mac | xargs sed -i "s/setSampleMatCad	--/setSampleMatCad $para/g"

	para=$(awk '{print $8}' dummy.txt)
	grep -lr -e "Diametro_Cad	--" macro.mac | xargs sed -i "s/Diametro_Cad	--/Diametro_Cad $para mm/g"


	para=$(awk '{print $9}' dummy.txt)
	grep -lr -e "setSampleMatCore	--" macro.mac | xargs sed -i "s/setSampleMatCore	--/setSampleMatCore $para/g"

	para=$(awk '{print $10}' dummy.txt)
	grep -lr -e "sampleThicknessX_Core	--" macro.mac | xargs sed -i "s/sampleThicknessX_Core	--/sampleThicknessX_Core $para mm/g"

	grep -lr -e "sampleThicknessY_Core	--" macro.mac | xargs sed -i "s/sampleThicknessY_Core	--/sampleThicknessY_Core $para mm/g"


	para=$(awk '{print $11}' dummy.txt)
	grep -lr -e "setSampleMatC1	--" macro.mac | xargs sed -i "s/setSampleMatC1	--/setSampleMatC1 $para/g"

	para=$(awk '{print $12}' dummy.txt)
	grep -lr -e "sampleThicknessX	--" macro.mac | xargs sed -i "s/sampleThicknessX	--/sampleThicknessX $para mm/g"

	grep -lr -e "sampleThicknessY	--" macro.mac | xargs sed -i "s/sampleThicknessY	--/sampleThicknessY $para mm/g"


	para=$(awk '{print $13}' dummy.txt)
	grep -lr -e "setSampleMatC2	--" macro.mac | xargs sed -i "s/setSampleMatC2	--/setSampleMatC2 $para/g"

	para=$(awk '{print $14}' dummy.txt)
	grep -lr -e "sampleThicknessX_2	--" macro.mac | xargs sed -i "s/sampleThicknessX_2	--/sampleThicknessX_2 $para mm/g"

	grep -lr -e "sampleThicknessY_2	--" macro.mac | xargs sed -i "s/sampleThicknessY_2	--/sampleThicknessY_2 $para mm/g"


	para=$(awk '{print $15}' dummy.txt)
	grep -lr -e "setSampleMatC3	--" macro.mac | xargs sed -i "s/setSampleMatC3	--/setSampleMatC3 $para/g"

	para=$(awk '{print $16}' dummy.txt)
	grep -lr -e "sampleThicknessX_3	--" macro.mac | xargs sed -i "s/sampleThicknessX_3	--/sampleThicknessX_3 $para mm/g"

	grep -lr -e "sampleThicknessY_3	--" macro.mac | xargs sed -i "s/sampleThicknessY_3	--/sampleThicknessY_3 $para mm/g"

	echo "Preparando geometría para las macros... Listo"
fi

if	[ "$1" == "close" ]
then
	echo "Closing macro..."
	
	para=$(awk '{print $2}' dummy.txt)
	grep -lr -e "setSampleDetMat $para" macro.mac | xargs sed -i "s/setSampleDetMat $para/setSampleDetMat	--/g"

	para=$(awk '{print $3}' dummy.txt)
	grep -lr -e "Diametro_Det $para mm" macro.mac | xargs sed -i "s/Diametro_Det $para mm/Diametro_Det	--/g"

	para=$(awk '{print $4}' dummy.txt)
	grep -lr -e "sampleThickness $para mm" macro.mac | xargs sed -i "s/sampleThickness $para mm/sampleThickness	--/g"

	grep -lr -e "sampleThicknessZ_Core $para mm" macro.mac | xargs sed -i "s/sampleThicknessZ_Core $para mm/sampleThicknessZ_Core	--/g"
	
	grep -lr -e "sampleThicknessZ $para mm" macro.mac | xargs sed -i "s/sampleThicknessZ $para mm/sampleThicknessZ	--/g"
	
	grep -lr -e "sampleThicknessZ_2 $para mm" macro.mac | xargs sed -i "s/sampleThicknessZ_2 $para mm/sampleThicknessZ_2	--/g"
	
	grep -lr -e "sampleThicknessZ_3 $para mm" macro.mac | xargs sed -i "s/sampleThicknessZ_3 $para mm/sampleThicknessZ_3	--/g"

	para=$(awk '{print $5}' dummy.txt)
	grep -lr -e "setSampleMatAl $para" macro.mac | xargs sed -i "s/setSampleMatAl $para/setSampleMatAl	--/g"

	para=$(awk '{print $6}' dummy.txt)
	grep -lr -e "Diametro_Al $para mm" macro.mac | xargs sed -i "s/Diametro_Al $para mm/Diametro_Al	--/g"

	para=$(awk '{print $7}' dummy.txt)
	grep -lr -e "setSampleMatCad $para" macro.mac | xargs sed -i "s/setSampleMatCad $para/setSampleMatCad	--/g"

	para=$(awk '{print $8}' dummy.txt)
	grep -lr -e "Diametro_Cad $para mm" macro.mac | xargs sed -i "s/Diametro_Cad $para mm/Diametro_Cad	--/g"


	para=$(awk '{print $9}' dummy.txt)
	grep -lr -e "setSampleMatCore $para" macro.mac | xargs sed -i "s/setSampleMatCore $para/setSampleMatCore	--/g"

	para=$(awk '{print $10}' dummy.txt)
	grep -lr -e "sampleThicknessX_Core $para mm" macro.mac | xargs sed -i "s/sampleThicknessX_Core $para mm/sampleThicknessX_Core	--/g"

	grep -lr -e "sampleThicknessY_Core $para mm" macro.mac | xargs sed -i "s/sampleThicknessY_Core $para mm/sampleThicknessY_Core	--/g"


	para=$(awk '{print $11}' dummy.txt)
	grep -lr -e "setSampleMatC1 $para" macro.mac | xargs sed -i "s/setSampleMatC1 $para/setSampleMatC1	--/g"

	para=$(awk '{print $12}' dummy.txt)
	grep -lr -e "sampleThicknessX $para mm" macro.mac | xargs sed -i "s/sampleThicknessX $para mm/sampleThicknessX	--/g"

	grep -lr -e "sampleThicknessY $para mm" macro.mac | xargs sed -i "s/sampleThicknessY $para mm/sampleThicknessY	--/g"


	para=$(awk '{print $13}' dummy.txt)
	grep -lr -e "setSampleMatC2 $para" macro.mac | xargs sed -i "s/setSampleMatC2 $para/setSampleMatC2	--/g"

	para=$(awk '{print $14}' dummy.txt)
	grep -lr -e "sampleThicknessX_2 $para mm" macro.mac | xargs sed -i "s/sampleThicknessX_2 $para mm/sampleThicknessX_2	--/g"

	grep -lr -e "sampleThicknessY_2 $para mm" macro.mac | xargs sed -i "s/sampleThicknessY_2 $para mm/sampleThicknessY_2	--/g"


	para=$(awk '{print $15}' dummy.txt)
	grep -lr -e "setSampleMatC3 $para" macro.mac | xargs sed -i "s/setSampleMatC3 $para/setSampleMatC3	--/g"

	para=$(awk '{print $16}' dummy.txt)
	grep -lr -e "sampleThicknessX_3 $para mm" macro.mac | xargs sed -i "s/sampleThicknessX_3 $para mm/sampleThicknessX_3	--/g"

	grep -lr -e "sampleThicknessY_3 $para mm" macro.mac | xargs sed -i "s/sampleThicknessY_3 $para mm/sampleThicknessY_3	--/g"


	
	echo "Macro closed."
fi

























