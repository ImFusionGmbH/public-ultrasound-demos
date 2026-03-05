#include "RoboticsUltrasoundDemoPlugin.h"

#include "RoboticsUltrasoundDemoFactory.h"

// Use the standard plugin registration macro
#ifndef IMFUSIONLIB_STATIC
IMFUSION_REGISTER_PLUGIN(ImFusion::RoboticsUltrasoundDemoPlugin)
#endif

namespace ImFusion {

RoboticsUltrasoundDemoPlugin::RoboticsUltrasoundDemoPlugin() = default;

RoboticsUltrasoundDemoPlugin::~RoboticsUltrasoundDemoPlugin() = default;

std::string RoboticsUltrasoundDemoPlugin::author() const {
  return "ImFusion GmbH";
}

std::string RoboticsUltrasoundDemoPlugin::description() const {
  return "Demo Plugin for Robotics Ultrasound capabilities";
}

ImFusionLibPlugin::Status RoboticsUltrasoundDemoPlugin::init() {
  // Register algorithm and controller factories
  registerFactories(std::make_unique<RoboticsUltrasoundDemoAlgorithmFactory>(),
                    std::make_unique<RoboticsUltrasoundDemoControllerFactory>(),
                    nullptr);

  return ImFusionLibPlugin::Status::Success;
}

} // namespace ImFusion
