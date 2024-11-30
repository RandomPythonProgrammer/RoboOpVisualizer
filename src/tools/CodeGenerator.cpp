#include "tools/CodeGenerator.h"
#include "common/Pose2d.h"
#include <format>

std::string formatPose(const Pose2d& pose) {
return std::format("{{{{{}, {}}}, {}}}", pose.position.x(), pose.position.y(), pose.rotation);
}

std::string CodeGenerator::generateCode(const std::vector<ControlPoint>& points) {
    std::string output;
    if (not points.empty()) {
        output += std::format("std::shared_ptr<Trajectory> trajectory = TrajectoryBuilderFactory::create({})\n", formatPose(points[0].pose));
        bool reversed = false;
        for (int i = 1; i < points.size(); i++) {
            if (points[i].reversed != reversed) {
                reversed = not reversed;
                output += std::format("\t.setReversed({})\n", reversed);
            }
            output+=std::format("\t.to({})\n", formatPose(points[i].pose));
        }
        output+="\t.build();\n";
    }
    return output;
}