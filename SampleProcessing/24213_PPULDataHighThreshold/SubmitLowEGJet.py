OutputBase = '/store/group/phys_heavyions/chenyi/pp2017/Forest/'
# DatasetName = '/HighEGJet/Run2017G-17Nov2017-v2/AOD'
# OutputBase = '/store/user/chenyi/crab/pp2017'
DatasetName = '/LowEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD'
Tag = '20211201FullRunULLowEGJetHighTreshold'

from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName = Tag

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'forest_MiniAOD_106X_DATA.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.maxMemoryMB = 3500
config.JobType.maxJobRuntimeMin = 1440
#config.JobType.inputFiles = ['']

config.section_("Data")
config.Data.inputDataset = DatasetName
config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
# config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSReader/'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.publication = False
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.outputDatasetTag = Tag
config.Data.outLFNDirBase = OutputBase + DatasetName + '/'
config.Data.ignoreLocality = True
config.Data.allowNonValidInputDataset = True
config.Data.lumiMask = 'Cert_306546-306826_5TeV_EOY2017ReReco_Collisions17_JSON.txt'

config.section_("Site")
config.Site.blacklist = ['T3_US_TAMU']
config.Site.blacklist = ['T3_US_UCR']
config.Site.whitelist = ['T2_IT_Bari', 'T2_US_MIT', 'T2_CH_CERN', 'T2_US_Vanderbilt']
config.Site.storageSite = 'T2_CH_CERN'
