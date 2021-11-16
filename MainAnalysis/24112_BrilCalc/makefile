

Prepare:
	rm -f Input
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../GlobalSetting/GlobalSetting.dh

RunPP:
	for i in Input/PPData_R*Nominal_JSON.txt; do bash CheckJSON.sh $$i; done

RunAA:
	for i in Input/PbPbData_R*Nominal_JSON.txt; do bash CheckJSON.sh $$i; done



