#include "tools/TrajectoryManager.h"
#include "common/Pose2d.h"
#include <memory>
#include <pathing/TrajectoryBuilder.h>
#include <vector>

void TrajectoryManager::regenerate() {
    trajectory = nullptr;
    if (controlPoints.size() > 1) {
        TrajectoryBuilder builder = TrajectoryBuilderFactory::create(controlPoints[0].pose);
        bool reversed = false;
        for (int i = 1; i < controlPoints.size(); i++) {
            if (controlPoints[i].reversed != reversed) {
                reversed = not reversed;
                builder.setReversed(reversed);
            }
            builder.to(controlPoints[i].pose);
        }
        trajectory = builder.build();
    }
}

void TrajectoryManager::swap(int a, int b) {
    std::swap(controlPoints[a], controlPoints[b]);
    regenerate();
}

void TrajectoryManager::add(int index) {
    ControlPoint point;
    if (index > 0)
        point = controlPoints[index];
    controlPoints.insert(controlPoints.begin() + index, point);
    regenerate();
}

void TrajectoryManager::remove(int index) {
    controlPoints.erase(controlPoints.begin() + index);
    regenerate();
}

std::shared_ptr<Trajectory> TrajectoryManager::generateTrajectory() const {
    return trajectory;
}

std::vector<ControlPoint>& TrajectoryManager::getPoints() {
    return controlPoints;
}