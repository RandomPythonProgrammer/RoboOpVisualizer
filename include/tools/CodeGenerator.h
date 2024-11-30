#pragma once
#include "tools/TrajectoryManager.h"
#include <common/Pose2d.h>

struct CodeGenerator {
    std::string generateCode(const std::vector<ControlPoint>& poses);
};