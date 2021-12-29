

Prepare:
	rm -f Input
	ln -sf $(ProjectBase)/MainAnalysis/24236_RebinUnfoldInput//Output Input
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh

RunPP:
	for i in Input/PPData_R*NominalFine_JSON.txt; do bash CheckJSON.sh $$i; done

RunAA:
	for i in Input/PbPbData_R*NominalFine_JSON.txt; do bash CheckJSON.sh $$i; done



