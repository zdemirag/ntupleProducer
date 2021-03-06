The Ntuple Producer code
========================
This is a CMSSW code for creating small ROOT ntuples from CMS data/MC samples.
Check out this twiki for more details: [CMS/UserCodeNWUntupleProducer][1]

Instructions for Users
---------------------
 * Set up the environment
```
  setenv SCRAM_ARCH slc5_amd64_gcc462
  cmsrel CMSSW_5_3_11_patch6
  cd CMSSW_5_3_11_patch6/src
  cmsenv
```
(note: _patch6 is recommended in met recepie)

 * New Met recipes (including MVA MET), according to [met-recipe][9]:
```
  cp /uscms/home/chayanit/work/forZeynep/Type1MET.tgz .
  cp /uscms/home/chayanit/work/forZeynep/PatUtils.tgz .
  cp /uscms/home/chayanit/work/forZeynep/METPUSubtraction.tgz .

  tar -xvf Type1MET.tgz
  tar -xvf PatUtils.tgz
  tar -xvf METPUSubtraction.tgz

  cvs co -r V00-03-23 CommonTools/RecoAlgos 
  cvs co -r b5_3_X_cvMEtCorr_2013Feb26 CommonTools/ParticleFlow
  cvs co -r V05-00-18 DataFormats/JetReco
  cvs co -r b5_3_X_cvMEtCorr_2013Feb22 DataFormats/METReco 
  cvs co -r V06-05-06-10 DataFormats/PatCandidates
  cvs co -r V00-02-15 DataFormats/StdDictionaries
  #cvs co -r MM_53X_2013Jun17 JetMETCorrections/METPUSubtraction #not tagged yet
  #cvs co -r V04-06-15 JetMETCorrections/Type1MET #not tagged yet
  cvs co -r V08-09-57 PhysicsTools/PatAlgos
  #cvs co -r b5_3_X_cvMEtCorr_2013Feb25 PhysicsTools/PatUtils #not tagged yet
  cvs co -r V00-03-34 PhysicsTools/SelectorUtils
  cvs co -r b5_3_X_cvMEtCorr_2013Feb25 RecoMET/METAlgorithms
  cvs co -r b5_3_X_cvMEtCorr_2013Feb25 RecoJets/JetProducers 
  cvs co -r V00-00-08 RecoMET/METAnalyzers 
  cvs co -r V00-00-13-01 RecoMET/METFilters 
  cvs co -r V03-03-12-02 RecoMET/METProducers
  cvs co -r V01-04-25 RecoTauTag/RecoTau 
  cvs co -r V01-04-13 RecoTauTag/Configuration
```
 * Met filters according to [MissingETOptionalFilters][4]:
```
  cvs co -r V01-00-11-01 DPGAnalysis/Skims
  cvs co -r V00-11-17 DPGAnalysis/SiStripTools
  cvs co -r V00-00-08 DataFormats/TrackerCommon
  cvs co -r V01-09-05 RecoLocalTracker/SubCollectionProducers
```

 * Egamma tools from [5]:
```
  cvs co -r V00-00-09 EgammaAnalysis/ElectronTools
  cvs co -r V09-00-01 RecoEgamma/EgammaTools
  cd EgammaAnalysis/ElectronTools/data
  cat download.url | xargs wget
  cd ../../../
```

 * Extra code (for boosted Z->ee isolation), following [6] and [7]:
```
  cvs co -r V00-02-03 -d TSWilliams/BstdZeeTools  UserCode/TSWilliams/BstdZee/BstdZeeTools
  cvs co -r V00-09-03 -d SHarper/HEEPAnalyzer UserCode/SHarper/HEEPAnalyzer 
```

 * PF footprint removal [Supercluster footprint removal twiki][8]:
```
  git clone https://github.com/peruzzim/SCFootprintRemoval.git
  cd SCFootprintRemoval
  git checkout V01-06
  cd ..
  mkdir PFIsolation
  mv SCFootprintRemoval PFIsolation/SuperClusterFootprintRemoval
```

 * Now check out the ntuple producer code and then the specific tag/branch of the code that is known to work
```
 git clone https://github.com/zdemirag/ntupleProducer.git  NWU/ntupleProducer
 cd NWU/ntupleProducer
 git checkout master 
 cd ../..
```

 * Patched to checked folders
```
 cp NWU/ntupleProducer/patches/PATMHTProducer.h PhysicsTools/PatAlgos/plugins/PATMHTProducer.h 
 cvs co -r V00-02-14 DataFormats/StdDictionaries
 cp NWU/ntupleProducer/patches/classes.h DataFormats/StdDictionaries/src/classes.h
 cp NWU/ntupleProducer/patches/classes_def.xml DataFormats/StdDictionaries/src/classes_def.xml
 cp NWU/ntupleProducer/patches/PileupJet* RecoJets/JetProducers/python/
 cp NWU/ntupleProducer/patches/PFMETAlgorithmMVA.cc JetMETCorrections/METPUSubtraction/src/. 
 scram b -j 12
```

Once compiled, we are ready to run it
### Runnning the code
```
  cd NWU/ntupleProducer/test
  cmsRun ntupleProducer_cfg.py
```
it assumes you are running over an MC sample. If you want to run on data, do:
```
  cmsRun ntupleProducer_cfg.py isRealData=1
``` 
that will set up an appropriate global tag etc.

*NB* 
By defualt, the ntuples require that there be at least one muon(electron) with pT > 3(5) GeV in order for an event to be saved. 
In the case that this is not desired (for instance, in jet or photon based studies), 
you should switch off the ```skimLeptons``` option in ntupleProducer_cfg.py

In addition to this, there are various flags the configuration file, ntupleProducer_cfg.py, that allow to save/not save certain objects (muons, jets, etc). All are saved by default.  

#### Running with CRAB
Look into ```crabNtuples_MC.cfg``` and ```crabNtuples_Data.cfg``` scripts.

Will incorporate multicrab soon.

Instructions for Developers
--------------------------

 * First, make sure you are on master branch and have the latest code:
```
  git checkout master
  git pull
```

 * Then create a new branch and swich to it:
```
  git branch dev-username
  git checkout dev-username
```

 * Now you can make any changes you want. Once you are done, commit it and push your branch.
```
  git commit -a
  git push origin dev-username
```

 * When you are satisfied with you new code, merge it with master branch. For that:
```
  git checkout master
  git merge dev-username
  git push
```

If the changes do not conflict, you are done. 
If there are conflicts, markers will be left in the problematic files showing the conflict; `git diff` will show this. 
Once you have edited the files to resolve the conflicts, `git commit -a`.
 
### Tagging policy
At any time you can tag your code, and push your tags to remote:
```
  git tag -a test1 -m "my tag"
  git push origin --tags
```
You can use any tags you want, later those can be deleted.

For the global production though, we should stick with a tagging convention.
Tags should be **vX.Y** and I am starting them with **v6.1**. Such that the tag corresponds to the **nutuple_v6** name 
of ntuple production. 
If the new code significantly changes the format of the ntuples (substantial changes to class definitions etc.) then the first number of a tag should be incremented 
(to v7.1 etc.) and the ntuple production path-name should be changed correspondingly.  Otherwise, incremental changes should be reflected in changes to the second digit.


[1]: https://twiki.cern.ch/twiki/bin/view/CMS/UserCodeNWUntupleProducer
[2]: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMetAnalysis
[3]: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMETRecipe53X
[4]: https://twiki.cern.ch/twiki/bin/view/CMS/MissingETOptionalFilters
[5]: https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentification
[6]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BoostedZToEEModIso
[7]: https://twiki.cern.ch/twiki/bin/view/CMS/HEEPSelector
[8]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SuperClusterFootprintRemoval
[9]: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SamplesForMETJINST