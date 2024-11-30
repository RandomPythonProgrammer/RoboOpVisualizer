#pragma once
#include "pathing/Trajectory.h"
#include <common/Pose2d.h>
#include <memory>
#include <vector>

/**
 * @brief Represents a control point
 * 
 */
struct ControlPoint {
    Pose2d pose = Pose2d::Zero();
    bool reversed = false;
};

/**
 * @brief A trajectory builder interface for the GUI class
 * 
 */
class TrajectoryManager {
private:
    std::vector<ControlPoint> controlPoints{{}};
    std::shared_ptr<Trajectory> trajectory;
public:
    /**
     * @brief Regenerates the spline
     * 
     */
    void regenerate();
    /**
     * @brief Swaps two of the control points
     * 
     * @param a The first index 
     * @param b The second index 
     */
    void swap(int a, int b);
    /**
     * @brief Adds a new control point
     * 
     * @param index The location to insert
     */
    void add(int index);
    /**
     * @brief Removes a control point
     * 
     * @param index The location to remove 
     */
    void remove(int index);
    std::vector<ControlPoint>& getPoints();
    /**
     * @brief Returns the generated trajectory
     * 
     * @return The generated trajectory 
     */
    std::shared_ptr<Trajectory> generateTrajectory() const; 
};