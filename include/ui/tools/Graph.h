#pragma once
#include "tools/TrajectoryManager.h"
#include "ui/ITool.h"
#include <GL/gl.h>
#include <common/calc.h>
#include <memory>

struct Overlay {
    char filename[64];
    GLuint texture = 0;
    double minX = 0;
    double minY = 0;
    double maxX = 0;
    double maxY = 0;
};

struct Graph: public ITool {
    std::shared_ptr<TrajectoryManager> manager;
    float currentLength;
    double _H_STEP;
    Overlay overlay;
    Graph(const std::shared_ptr<TrajectoryManager>& manager): manager{manager}, currentLength{0}, _H_STEP(H_STEP * 10) {}
    void render() override;
};