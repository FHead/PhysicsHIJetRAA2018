OutputBase = '/store/group/phys_heavyions/chenyi/pp2017/MIX'
# OutputBase = '/store/user/chenyi/pp2017/MIX'
DatasetName = '/QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8/chenyi-20211121PrivateDijetGSRetry-89a6ef68b87e0721d67a027534bffde4/USER'
Tag = '2021121PrivateDijetMIXRetry3'

from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName = Tag

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
# config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'HIN-RunIISummer20UL17pp5TeVDR-00002_1_cfg.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.maxMemoryMB = 2500
#config.JobType.maxJobRuntimeMin = 1440
#config.JobType.inputFiles = ['']

config.section_("Data")
config.Data.inputDataset = DatasetName
# config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSReader/'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.publication = True
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
# config.Data.outputPrimaryDataset = 'QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8'
config.Data.outputDatasetTag = Tag
config.Data.outLFNDirBase = OutputBase + DatasetName
config.Data.ignoreLocality = True
config.Data.allowNonValidInputDataset = True
# config.Data.lumiMask = 'Cert_306546-306826_5TeV_EOY2017ReReco_Collisions17_JSON.txt'

config.section_("Site")
config.Site.blacklist = ['T3_US_TAMU']
config.Site.blacklist = ['T3_US_UCR']
config.Site.whitelist = ['T2_IT_Bari', 'T2_US_MIT', 'T2_CH_CERN', 'T2_US_Vanderbilt']
config.Site.storageSite = 'T2_CH_CERN'