/* Copyright (c) 2012-2024 ImFusion GmbH, Munich, Germany. All rights reserved.
 */
#pragma once

#include <ImFusion/Base/ImFusionLibPlugin.h>
#include <string>

namespace ImFusion {

/// Plugin for Robotics Ultrasound Demo functionality
class RoboticsUltrasoundDemoPlugin : public ImFusionLibPlugin {
public:
  RoboticsUltrasoundDemoPlugin();
  ~RoboticsUltrasoundDemoPlugin() override;

  static const char *id() { return "ImFusion.RoboticsUltrasoundDemo"; }

  std::string author() const override;
  std::string description() const override;
  Status init() override;
};
} // namespace ImFusion
