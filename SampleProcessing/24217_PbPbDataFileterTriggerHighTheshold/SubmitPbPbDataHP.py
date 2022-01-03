OutputBase = '/store/group/phys_heavyions/chenyi/PbPb2018/Forest/'
DatasetName = '/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD'
Tag = 'DefaultPbPbDataHPForJetRAAHighThresholdJet80And100'

from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName = Tag

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'forest_miniAOD_112X_DATA.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.maxMemoryMB = 3500
config.JobType.maxJobRuntimeMin = 2750
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
config.Data.lumiMask = 'Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt'

config.section_("Site")
config.Site.blacklist = ['T3_US_UCR', 'T2_IT_Pisa', 'T3_US_TAMU']
# config.Site.whitelist = ['T2_IT_Bari', 'T2_US_MIT', 'T2_US_Vanderbilt']
# config.Site.whitelist = ['T2_IT_Bari', 'T2_US_MIT', 'T2_CH_CERN', 'T2_US_Vanderbilt', 'T2_US_Caltech', 'T2_US_UCSD']
config.Site.whitelist = ['T2_US_*', 'T2_CH_CERN']
config.Site.storageSite = 'T2_CH_CERN'
