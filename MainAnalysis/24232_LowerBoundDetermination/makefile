

default: TestRun

Prepare:
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .

TestRun: Execute
	./Execute --DHFile GlobalSetting.dh --Base R1_Centrality0to10 \
		--MinPT 150 \
		--DoTrigger true --TriggerPercentage 0.99

RunAll: Execute
	bash RunAll.sh

Execute: GetLowerBound.cpp
	CompileRootMacro GetLowerBound.cpp Execute \
		-I$(ProjectBase)/CommonCode/include/
