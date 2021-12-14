
default: TestRun

Prepare:
	rm -f Input
	ln -fs $(ProjectBase)/MainAnalysis/23762_UnfoldPreparation/Output Input

Execute: EvaluateConditionNumber.cpp
	CompileRootMacro EvaluateConditionNumber.cpp Execute

TestRun: Execute
	./Execute --Input Input/PbPbData_R4_Centrality50to90_Nominal.root --Response HResponse --DHFile Condition.dh

RunAll: Execute
	bash RunAll.sh



