// system include files
#include <memory>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GeometryVector/interface/GlobalVector.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/deltaPhi.h"

// Libraries for objects
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/PFMETFwd.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/METReco/interface/METCollection.h"
#include "DataFormats/METReco/interface/METFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Luminosity/interface/LumiSummary.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/JetMatching/interface/JetFlavour.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourMatching.h"
#include "SimDataFormats/JetMatching/interface/MatchedPartons.h"
#include "SimDataFormats/JetMatching/interface/JetMatchedPartons.h"

//#include "RecoVertex/PrimaryVertexProducer/interface/VertexHigherPtSquared.h"

// JEC
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "JetMETCorrections/Type1MET/interface/Type1MET.h"
#include "JetMETCorrections/Type1MET/interface/Type1METAlgo.h"

#include "DataFormats/AnomalousEcalDataFormats/interface/AnomalousECALVariables.h"
#include "DataFormats/METReco/interface/BeamHaloSummary.h"

// ntuple storage classes
#include "TCPrimaryVtx.h"
#include "TCJet.h"
#include "TCMET.h"
#include "TCMuon.h"
#include "TCElectron.h"
#include "TCTau.h"
#include "TCPhoton.h"
#include "TCGenJet.h"

// Need for HLT trigger info:
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

//Root  stuff
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include "TObject.h"
#include "TObjArray.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace edm;
using namespace std;
using namespace reco;

//
// class declaration
//

class ntupleProducer : public edm::EDAnalyzer {
	public:
		explicit ntupleProducer(const edm::ParameterSet&);
		~ntupleProducer();

	private:
		virtual void beginJob() ;
		virtual void beginRun(const edm::Run&, const edm::EventSetup&) ;
		virtual void analyze(const edm::Event&, const edm::EventSetup&);
		virtual void endLuminosityBlock(const edm::LuminosityBlock&,const edm::EventSetup&);
		virtual void endRun(const edm::Run&, const edm::EventSetup&);
		virtual void endJob() ;

		virtual bool  triggerDecision(edm::Handle<edm::TriggerResults>& hltR, int iTrigger);
		virtual float sumPtSquared(const Vertex& v);
		virtual void  associateJetToVertex(reco::PFJet inJet, Handle<reco::VertexCollection> vtxCollection, TCJet *outJet);   
		virtual bool isFilteredOutScraping(const edm::Event& iEvent, const edm::EventSetup& iSetup, int numtrack=10, double thresh=0.25);
		// ----------member data ---------------------------

		struct JetRefCompare :
			public std::binary_function<edm::RefToBase<reco::Jet>, edm::RefToBase<reco::Jet>, bool> {
				inline bool operator () (const edm::RefToBase<reco::Jet> &j1, const edm::RefToBase<reco::Jet> &j2) const {
					return j1.id() < j2.id() || (j1.id() == j2.id() && j1.key() < j2.key()); 
				}
			};

		typedef std::map<edm::RefToBase<reco::Jet>, unsigned int, JetRefCompare> FlavourMap;

		//Standard event info
		int eventNumber, runNumber, lumiSection, bunchCross;
		float ptHat, qScale, evtWeight;
		float deliveredLumi, recordedLumi, lumiDeadTime;
		float rhoFactor;

		edm::Service<TFileService> fs;
		TTree* eventTree;
		TTree* runTree;
		edm::InputTag jetTag_;
		edm::InputTag metTag_;
		edm::InputTag genJetTag_;
		edm::InputTag muonTag_;
		edm::InputTag electronTag_;
		edm::InputTag photonTag_;
		edm::InputTag tauTag_;
		edm::InputTag primaryVtxTag_;
		edm::InputTag triggerResultsTag_;
		edm::InputTag rhoCorrTag_;
		edm::InputTag ecalFilterTag_;
		edm::InputTag hcalFilterTag_;

		bool saveJets_;
		bool saveElectrons_;
		bool saveMuons_;
		bool savePhotons_;
		bool saveTaus_;
		bool saveMET_;
		bool saveGenJets_;
		bool isRealData;

		//Physics object containers
		TClonesArray* recoJets;
		TClonesArray* recoMuons;
		TClonesArray* recoElectrons;
		TClonesArray* recoTaus;
		TClonesArray* recoPhotons;
		TClonesArray* genJets;
		TCMET*        recoMET;

		//Vertex info
		TClonesArray* primaryVtx;
		TVector3*     beamSpot;
		int           nPUVertices;

		//GenParticles
		TClonesArray* hardPartonP4;
		int           partonPdgId[4];

		//Triggers
		HLTConfigProvider hltConfig_;
		string            hlTriggerResults_, hltProcess_, triggerName_;
		TriggerNames      triggerNames;
		vector<string>    hlNames;
		vector<string>    triggerPaths_;
		long unsigned int triggerStatus;
		unsigned int      hltPrescale[64];

		//Filters 
		Bool_t isNoiseHcal, isDeadEcalCluster;
		Bool_t isCSCTightHalo, isCSCLooseHalo, isHcalTightHalo, isHcalLooseHalo, isEcalTightHalo, isEcalLooseHalo;
		Bool_t isGlobalTightHalo, isGlobalLooseHalo;
		Bool_t isScraping;

		//Histograms
		TH1D * h1_ptHat;
};
