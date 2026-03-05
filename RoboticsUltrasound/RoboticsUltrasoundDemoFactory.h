/* Copyright (c) 2012-2024 ImFusion GmbH, Munich, Germany. All rights reserved.
 */
#pragma once

#include <ImFusion/Base/AlgorithmControllerFactory.h>
#include <ImFusion/Base/AlgorithmFactory.h>

namespace ImFusion {
class Algorithm;

/// AlgorithmFactory for Robotics Ultrasound Demo plugin
class RoboticsUltrasoundDemoAlgorithmFactory : public AlgorithmFactory {
public:
  RoboticsUltrasoundDemoAlgorithmFactory();
};

/// AlgorithmControllerFactory for Robotics Ultrasound Demo plugin
class RoboticsUltrasoundDemoControllerFactory
    : public AlgorithmControllerFactory {
public:
  RoboticsUltrasoundDemoControllerFactory();
  AlgorithmController *create(Algorithm *a) const override;
};
} // namespace ImFusion
