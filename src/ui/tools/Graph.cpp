#include "ui/tools/Graph.h"
#include "Eigen/src/Core/Matrix.h"
#include "common/Pose2d.h"
#include "common/calc.h"
#include "imgui.h"
#include "implot.h"
#include "pathing/Spline.h"
#include <GL/gl.h>
#include <format>
#include <SOIL2.h>

void Graph::render() {
    auto trajectory = manager->generateTrajectory();
    ImGui::Begin("Graph");
    if (trajectory) {
        ImGui::SliderFloat("Path Following", &currentLength, 0, trajectory->getLength());
    }
    
    if (ImGui::InputText("Overlay Image", overlay.filename, sizeof(overlay)/sizeof(char))) {
        overlay.texture = SOIL_load_OGL_texture(overlay.filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    }
    ImGui::SetNextItemWidth(80);
    ImGui::InputDouble("MinX", &overlay.minX, 0, 0, "%g");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80);
    ImGui::InputDouble("MinY", &overlay.minY, 0, 0, "%g");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80);
    ImGui::InputDouble("MaxX", &overlay.maxX, 0, 0, "%g");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80);
    ImGui::InputDouble("MaxY", &overlay.maxY, 0, 0, "%g");


    if (ImPlot::BeginPlot("Splines", ImGui::GetContentRegionAvail())) {
        if (overlay.filename[0]!='\0') {
            if (overlay.texture) {
                ImPlot::PlotImage("Overlay", overlay.texture, {overlay.minX, overlay.minY}, {overlay.maxX, overlay.maxY});
            }
        }
        
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
    }
    ImGui::End();
}