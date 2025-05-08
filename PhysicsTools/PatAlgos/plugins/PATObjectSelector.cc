#include "FWCore/Framework/interface/MakerMacros.h"
#include "PhysicsTools/PatAlgos/plugins/PATObjectSelector.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

namespace pat {
  typedef SingleObjectSelector<
      std::vector<PackedCandidate>,
      StringCutObjectSelector<PackedCandidate, true>  // true => lazy parsing => get all methods of daughters
      >
      PATPackedCandidateSelector;

  typedef SingleObjectSelector<std::vector<edm::Ptr<PackedCandidate>>,
                               StringCutObjectSelector<edm::Ptr<PackedCandidate>, true>,
                               std::vector<edm::Ptr<PackedCandidate>>>
      PATPackedCandidatePtrSelector;

}  // namespace pat

using namespace pat;

DEFINE_FWK_MODULE(PATElectronSelector);
DEFINE_FWK_MODULE(PATMuonSelector);
DEFINE_FWK_MODULE(PATTauSelector);
DEFINE_FWK_MODULE(PATPhotonSelector);
DEFINE_FWK_MODULE(PATJetSelector);
DEFINE_FWK_MODULE(PATMETSelector);
DEFINE_FWK_MODULE(PATPFParticleSelector);
DEFINE_FWK_MODULE(PATCompositeCandidateSelector);
DEFINE_FWK_MODULE(PATTriggerObjectStandAloneSelector);
DEFINE_FWK_MODULE(PATGenericParticleSelector);
DEFINE_FWK_MODULE(PATPackedCandidateSelector);
DEFINE_FWK_MODULE(PATPackedCandidatePtrSelector);

DEFINE_FWK_MODULE(PATElectronRefSelector);
DEFINE_FWK_MODULE(PATMuonRefSelector);
DEFINE_FWK_MODULE(PATTauRefSelector);
DEFINE_FWK_MODULE(PATPhotonRefSelector);
DEFINE_FWK_MODULE(PATJetRefSelector);
DEFINE_FWK_MODULE(PATMETRefSelector);
DEFINE_FWK_MODULE(PATPFParticleRefSelector);
DEFINE_FWK_MODULE(PATGenericParticleRefSelector);
DEFINE_FWK_MODULE(PATCompositeCandidateRefSelector);


DEFINE_FWK_MODULE(IsoTrackSelector);
DEFINE_FWK_MODULE(MuonRefPatCount);

