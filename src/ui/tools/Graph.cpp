#include "ui/tools/Graph.h"
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
        double totalLength = 0;
        for (const auto& spline: trajectory->splines) {
            totalLength += spline.length;
        }
        ImGui::SliderFloat("Path Following", &currentLength, 0, totalLength);
    }
    ImPlot::BeginPlot("Splines", ImGui::GetContentRegionAvail());
    if (trajectory) {
        for (int i = 0; i < trajectory->splines.size(); i++) {
            const auto& spline = trajectory->splines[i];
            double xStart = spline.start.position.x();
            double xEnd = spline.end.position.x();
            if (xStart > xEnd) {
                std::swap(xStart, xEnd);
            }
            int count = (xEnd - xStart) / H_STEP;
            double x_values[count];
            double y_values[count];

            for (int ii = 0; ii < count; ii++) {
                double x = xStart + ii * H_STEP;
                x_values[ii] = x;
                y_values[ii] = getY(spline.coefficients, x);
            }

            ImPlot::PlotLine(std::format("Spline {}", i).c_str(), x_values, y_values, count);
        }

        Pose2d followingPoint = poseByArcLength(*trajectory, currentLength);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Cross, IMPLOT_AUTO);
        ImPlot::PlotLine("Following", &followingPoint.position.x(), &followingPoint.position.y(), 1);
    }
    ImPlot::EndPlot();
    ImGui::End();
}