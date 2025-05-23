import FWCore.ParameterSet.Config as cms

# HLT dimuon trigger
import HLTrigger.HLTfilters.hltHighLevel_cfi
hltZMMPbPb = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltZMMPbPb.HLTPaths = ["HLT_HIL2SingleMu*_v*","HLT_HIL3SingleMu*_v*"]
hltZMMPbPb.throw = False
hltZMMPbPb.andOr = True

# selection of valid vertex
primaryVertexFilterForZMM = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2"), 
    filter = cms.bool(True),   # otherwise it won't filter the events
    )

# selection of dimuons with mass in Z range
muonSelectorForZMM = cms.EDFilter("MuonSelector",
    src = cms.InputTag("muons"),
    cut = cms.string("(isPFMuon && isGlobalMuon) && pt > 15. && abs(eta) < 2.4"),
    filter = cms.bool(True)
    )

muonFilterForZMM = cms.EDFilter("MuonCountFilter",
    src = cms.InputTag("muonSelectorForZMM"),
    minNumber = cms.uint32(2)
    )

dimuonMassCutForZMM = cms.EDProducer("CandViewShallowCloneCombiner",
    checkCharge = cms.bool(True),
    cut = cms.string('mass > 60'),
    decay = cms.string("muonSelectorForZMM@+ muonSelectorForZMM@-")
    )

dimuonMassCutFilterForZMM = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("dimuonMassCutForZMM"),
    minNumber = cms.uint32(1)
    )

# Z->mumu skim sequence
zMMSkimSequence = cms.Sequence(
    hltZMMPbPb *
    primaryVertexFilterForZMM *
    muonSelectorForZMM *
    muonFilterForZMM *
    dimuonMassCutForZMM *
    dimuonMassCutFilterForZMM
    )
