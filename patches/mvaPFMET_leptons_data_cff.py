
import FWCore.ParameterSet.Config as cms

#from RecoMET.METProducers.PFMET_cfi import pfMet
from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff  import *
from JetMETCorrections.Configuration.DefaultJEC_cff                     import *
from JetMETCorrections.METPUSubtraction.mvaPFMET_leptons_cfi            import *
from RecoJets.JetProducers.PileupJetIDParams_cfi                        import JetIdParams

calibratedAK5PFJetsForPFMEtMVA = cms.EDProducer('PFJetCorrectionProducer',
    src = cms.InputTag('ak5PFJets'),
    correctors = cms.vstring("ak5PFL1FastL2L3Residual")
)

pfMEtMVA = cms.EDProducer("PFMETProducerMVA",
    srcCorrJets = cms.InputTag('calibratedAK5PFJetsForPFMEtMVA'),
    srcUncorrJets = cms.InputTag('ak5PFJets'),
    srcPFCandidates = cms.InputTag('particleFlow'),
    srcVertices = cms.InputTag('offlinePrimaryVertices'),
    srcLeptons = cms.VInputTag("isophotons"),
   #    srcLeptons = cms.VInputTag("isomuons","isoelectrons","isotaus"),#"muons","hpsPFTauProducer"), # NOTE: you need to set this to collections of electrons, muons and tau-jets
                          #       passing the lepton reconstruction & identification criteria applied in your analysis
    srcRho = cms.InputTag('kt6PFJets','rho'),
    globalThreshold = cms.double(-1.),#pfMet.globalThreshold,
    minCorrJetPt = cms.double(-1.),
    inputFileNames = cms.PSet(
        U     = cms.FileInPath('JetMETCorrections/METPUSubtraction/data/gbrmet_53_June2013_type1.root'),
        DPhi  = cms.FileInPath('JetMETCorrections/METPUSubtraction/data/gbrmetphi_53_June2013_type1.root'),
        CovU1 = cms.FileInPath('JetMETCorrections/METPUSubtraction/data/gbru1cov_53_Dec2012.root'),
        CovU2 = cms.FileInPath('JetMETCorrections/METPUSubtraction/data/gbru2cov_53_Dec2012.root')
    ),
    loadMVAfromDB = cms.bool(False),
    is42 = cms.bool(False), # CV: set this flag to true if you are running mvaPFMET in CMSSW_4_2_x
    minNumLeptons = cms.int32(0),
    corrector = cms.string("ak5PFL1Fastjet"),
    useType1  = cms.bool(True),
    useOld42  = cms.bool(False),
    dZcut     = cms.double(0.1),
    impactParTkThreshold = cms.double(0.),
    tmvaWeights = cms.string("RecoJets/JetProducers/data/TMVAClassificationCategory_JetID_MET_53X_Dec2012.weights.xml"),
    tmvaMethod = cms.string("JetID"),
    version = cms.int32(-1),
    cutBased = cms.bool(False),
    tmvaVariables = cms.vstring(
        "nvtx",
        "jetPt",
        "jetEta",
        "jetPhi",
        "dZ",
        "beta",
        "betaStar",
        "nCharged",
        "nNeutrals",
        "dR2Mean",
        "ptD",
        "frac01",
        "frac02",
        "frac03",
        "frac04",
        "frac05",
    ),
    tmvaSpectators = cms.vstring(),
    JetIdParams = JetIdParams,
    verbosity = cms.int32(0)
)

pfMEtMVAsequence  = cms.Sequence(
    (isomuonseq+isotauseq+isoelectronseq+isophotonseq)*
    calibratedAK5PFJetsForPFMEtMVA*
    pfMEtMVA
    )

