#include "ui/tools/Graph.h"
#include "Eigen/src/Core/Matrix.h"
#include "common/Pose2d.h"
#include "common/calc.h"
#include "imgui.h"
#include "implot.h"
#include "pathing/Spline.h"
#include <format>

void Graph::render() {
    auto trajectory = manager->generateTrajectory();
    ImGui::Begin("Graph");
    if (trajectory) {
        ImGui::SliderFloat("Path Following", &currentLength, 0, trajectory->getLength());
    }
    ImPlot::BeginPlot("Splines", ImGui::GetContentRegionAvail());
    if (trajectory) {
        for (int i = 0; i < trajectory->splines.size(); i++) {
            const auto& spline = trajectory->splines[i];
            double start = 0;
            int count = 1/H_STEP;
            double x_values[count];
            double y_values[count];
    
            for (int ii = 0; ii < count; ii++) {
                Eigen::Vector2d position = spline.get(ii * H_STEP);
                x_values[ii] = position.x();
                y_values[ii] = position.y();
            }

            ImPlot::PlotLine(std::format("Spline {}", i).c_str(), x_values, y_values, count);
        }

        Pose2d followingPoint = trajectory->poseByArcLength(currentLength);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Cross, IMPLOT_AUTO);
        ImPlot::PlotLine("Following", &followingPoint.position.x(), &followingPoint.position.y(), 1);
    }
    ImPlot::EndPlot();
    ImGui::End();
}