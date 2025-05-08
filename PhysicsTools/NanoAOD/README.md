# Customize NanoAODv9 to add GloParT and PFCand

## Set up Environment

```bash
cmssw-el7
cmsrel CMSSW_10_6_31
cd CMSSW_10_6_31/src
cmsenv

# To have PFCand, checkout this branch
git cms-checkout-topic phym73:my_nanov9_pfcand

# To include GloParT score, follow the guid here: https://github.com/PhyM73/NanoTuples/tree/dev-part-UL
git clone https://github.com/PhyM73/NanoTuples.git PhysicsTools/NanoTuples -b dev-part-UL
./PhysicsTools/NanoTuples/scripts/install_onnxruntime.sh

scram b -j15
```

## Test command to customize Nano

```bash
cmsDriver.py --python_filename test_nanoTuples_mc2018.py --eventcontent NANOAODSIM --customise PhysicsTools/NanoTuples/nanoTuples_cff.nanoTuples_customizeMC --datatier NANOAODSIM --fileout file:nano_mc2018.root --conditions 106X_upgrade2018_realistic_v16_L1v1 --step NANO --filein /store/mc/RunIISummer20UL18MiniAODv2/NMSSM_XToYH_HTo2T_YTo2WTo4Q_MX_300_MY_60_TuneCP5_13TeV-madgraph-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/130000/2F6CA128-F495-A546-A927-A6FEFFC49C2F.root --era Run2_2018,run2_nanoAOD_106Xv2 --mc -n 50 --customise_commands "process.options.wantSummary = cms.untracked.bool(True)" >& test_mc2018.log
```

<!-- 
```bash
cmsDriver.py --python_filename test_nanoTuples_mc2018.py --eventcontent NANOAODSIM --customise PhysicsTools/NanoTuples/nanoTuples_cff.nanoTuples_customizeMC --datatier NANOAODSIM --fileout file:nano_mc2018.root --conditions 106X_upgrade2018_realistic_v16_L1v1 --step NANO --filein file:/eos/home-f/fameng/analysis/BosonRes/tmp_test_miniaod/2F6CA128-F495-A546-A927-A6FEFFC49C2F.root --era Run2_2018,run2_nanoAOD_106Xv2 --mc -n 50 --customise_commands "process.options.wantSummary = cms.untracked.bool(True)" >& test_mc2018.log
``` 
-->

<!-- 
## Production

### Step 0: switch to the crab production directory and set up grid proxy, CRAB environment, etc.
```bash
cd $CMSSW_BASE/src/PhysicsTools/NanoTuples/crab
# set up grid proxy
voms-proxy-init -rfc -voms cms --valid 168:00
# set up CRAB env (must be done after cmsenv)
source /cvmfs/cms.cern.ch/common/crab-setup.sh
```

### Step 1: generate the python config file with cmsDriver.py:

MC (2018, 102X):
```bash
cmsDriver.py mc2018 -n -1 --mc --eventcontent NANOAODSIM --datatier NANOAODSIM --conditions 106X_upgrade2018_realistic_v16_L1v1 --step NANO --nThreads 1 --era Run2_2018,run2_nanoAOD_106Xv2 --customise PhysicsTools/NanoTuples/nanoTuples_cff.nanoTuples_customizeMC --filein file:step-1.root --fileout file:nano.root --no_exec
```

### Step 2: use the crab.py script to submit the CRAB jobs

Writable sites: T2_TR_METU, T2_US_Nebraska

For MC:
```bash
python crab.py -p mc_NANO.py --site T2_CH_CERN -o /store/user/$USER/outputdir -t NanoTuples-GloParT -i mc.txt --num-cores 1 --send-external -s FileBased -n 2 --work-area crab_projects_mc --dryrun
```

For data:
```bash
python crab.py -p data_NANO.py --site T2_CH_CERN -o /store/user/$USER/outputdir -t NanoTuples-[version] -i data.txt --num-cores 1 --send-external -s EventAwareLumiBased -n 100000 -j [json_file] --work-area crab_projects_data --dryrun
```

A JSON file can be applied for data samples with the -j options.

Golden JSON, 2016:
```
https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt
```

Golden JSON, 2017:
```
https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt
```

Golden JSON, 2018:
```
https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt
```

These command will perform a "dryrun" to print out the CRAB configuration files. Please check everything is correct (e.g., the output path, version number, requested number of cores, etc.) before submitting the actual jobs. To actually submit the jobs to CRAB, just remove the --dryrun option at the end.

### Step 3: check job status

The status of the CRAB jobs can be checked with:

```bash
./crab.py --status --work-area crab_projects_*  --options "maxjobruntime=2500 maxmemory=2500" && ./crab.py --summary
```

Note that this will also resubmit failed jobs automatically.

The crab dashboard can also be used to get a quick overview of the job status:

https://monit-grafana.cern.ch/d/cmsTMGlobal/cms-tasks-monitoring-globalview?orgId=11

------

# Edit CMSSW_10_6_X to include PFCand in NanoAODv9 
```bash
cmsrel CMSSW_10_6_31
cd CMSSW_10_6_31/src
cmsenv

git cms-addpkg PhysicsTools/NanoAOD
git cms-addpkg PhysicsTools/PatAlgos
git cms-addpkg DataFormats/NanoAOD

# edit the `PhysicsTools/NanoAOD/python/jets_cff.py` according to 
# 1. https://github.com/cms-sw/cmssw/pull/46012
# 2. https://github.com/cms-sw/cmssw/pull/47206

# It is pushed to https://github.com/PhyM73/cmssw/pull/1 now and can be directly downloaded with `git cms-checkout-topic`
```

P.S. divide the x->qq score by 3 might have a better performance -->
