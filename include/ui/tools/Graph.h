#pragma once
#include "tools/TrajectoryManager.h"
#include "ui/ITool.h"
#include <memory>

struct Graph: public ITool {
    std::shared_ptr<TrajectoryManager> manager;
    float currentLength;
    Graph(const std::shared_ptr<TrajectoryManager>& manager): manager{manager}, currentLength{0} {}
    void render() override;
};