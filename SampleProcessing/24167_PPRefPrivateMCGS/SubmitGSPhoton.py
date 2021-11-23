OutputBase = '/store/group/phys_heavyions/chenyi/pp2017/GEN-SIM/'
# DatasetName = '/HighEGJet/Run2017G-17Nov2017-v2/AOD'
DatasetName = 'QCDPhoton_pThat-15_TuneCP5_5p02TeV_pythia8'
Tag = '20211121PrivatePhotonjetGS'

from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName = Tag

config.section_("JobType")
config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'HIN-RunIIpp5Spring18GS-00019-on-RunIISummer20UL17pp5TeVGS-00001_1_cfg.py'
config.JobType.allowUndistributedCMSSW = True

config.section_("Data")
config.Data.outputPrimaryDataset = DatasetName
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 1000000
config.Data.totalUnits = 3000000000
config.Data.publication = True
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.outputDatasetTag = Tag
config.Data.outLFNDirBase = OutputBase + DatasetName + '/'

config.section_("Site")
config.Site.blacklist = ['T3_US_TAMU']
config.Site.blacklist = ['T3_US_UCR']
config.Site.whitelist = ['T2_IT_Bari', 'T2_US_MIT', 'T2_CH_CERN', 'T2_US_Vanderbilt']
config.Site.storageSite = 'T2_CH_CERN'

