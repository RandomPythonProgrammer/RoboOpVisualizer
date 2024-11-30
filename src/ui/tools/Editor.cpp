#include "ui/tools/Editor.h"
#include "imgui.h"
#include <format>
#include "IconsFontAwesome6.h"
#include "tools/TrajectoryManager.h"

void Editor::render() {
    if (ImGui::Begin("Editor")) {
        if (ImGui::BeginChild("Splines")) {
            for (int i = 0; i < manager->getPoints().size(); i++) {
                ImGui::PushID(i);
                ControlPoint& point = manager->getPoints()[i];

                ImGui::SeparatorText(std::format("Spline {}", i).c_str());

                ImGui::SetNextItemWidth(80);
                if (ImGui::InputDouble("X", &point.pose.position.x(), 0, 0, "%g")) {
                    manager->regenerate();
                }

                ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                if (ImGui::InputDouble("Y", &point.pose.position.y(), 0, 0, "%g")) {
                    manager->regenerate();
                }

                ImGui::SameLine();
                ImGui::SetNextItemWidth(80);
                if (ImGui::InputDouble("RAD", &point.pose.rotation, 0, 0, "%g")) {
                    manager->regenerate();
                }

                ImGui::SameLine();

                bool disabled = i <= 0;
                
                if (disabled)
                    ImGui::BeginDisabled();
                if (ImGui::Checkbox("Reversed", &point.reversed)) {
                    manager->regenerate();
                }
                if (disabled)
                    ImGui::EndDisabled();

                ImGui::SameLine();

                if (disabled)
                    ImGui::BeginDisabled();
                if (ImGui::Button(ICON_FA_CHEVRON_UP, {20, 0})) {
                    manager->swap(i, i-1);
                }
                if (disabled)
                    ImGui::EndDisabled();

                ImGui::SameLine();

                disabled = i >= manager->getPoints().size() -1;
                if (disabled)
                    ImGui::BeginDisabled();
                if (ImGui::Button(ICON_FA_CHEVRON_DOWN, {20, 0})) {
                    manager->swap(i, i+1);
                }
                if (disabled)
                    ImGui::EndDisabled();
                ImGui::SameLine();

                disabled = manager->getPoints().size() <= 1;
                if (disabled)
                    ImGui::BeginDisabled();
                ImGui::SetNextItemWidth(25);
                ImGui::PushStyleColor(ImGuiCol_Button, 0xFF0000DD);
                if (ImGui::Button(ICON_FA_XMARK, {20, 0})) {
                    manager->remove(i);
                }
                ImGui::PopStyleColor();
                if (disabled)
                    ImGui::EndDisabled();
                ImGui::SameLine();

                ImGui::PushStyleColor(ImGuiCol_Button, 0xFF00DD00);
                if (ImGui::Button(ICON_FA_PLUS, {20, 0})) {
                    manager->add(i+1);
                }
                ImGui::PopStyleColor();

                ImGui::PopID();
            }
            ImGui::EndChild();
        }
        ImGui::End();
    }
}