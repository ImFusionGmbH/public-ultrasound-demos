#include "RoboticsUltrasoundDemoFactory.h"
#include "RoboticsUltrasoundDemoPlugin.h"

#include "CTToMediumAlgorithm.h"

#include <ImFusion/GUI/DefaultAlgorithmController.h>

namespace ImFusion {
RoboticsUltrasoundDemoAlgorithmFactory::RoboticsUltrasoundDemoAlgorithmFactory()
    : AlgorithmFactory{"RoboticsUltrasoundDemo"} {
  // register the US::CTToMediumAlgorithm
  registerAlgorithm<US::CTToMediumAlgorithm>("US::CTToMediumAlgorithm",
                                             "Demo Plugin; CT to US Medium");
}

RoboticsUltrasoundDemoControllerFactory::
    RoboticsUltrasoundDemoControllerFactory()
    : AlgorithmControllerFactory{"RoboticsUltrasoundDemo"} {}

AlgorithmController *
RoboticsUltrasoundDemoControllerFactory::create(Algorithm *a) const {
  // register the DemoController for the DemoAlgorithm
  if (US::CTToMediumAlgorithm *alg =
          dynamic_cast<US::CTToMediumAlgorithm *>(a)) {
    return new US::CTToMediumController(alg);
  }
  return 0;
}
} // namespace ImFusion
