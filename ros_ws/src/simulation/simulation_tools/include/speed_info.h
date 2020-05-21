#pragma once

#include "circle.h"
#include "config.h"
#include "physical_properties.h"
#include "process_track.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float64.h"
#include <cmath>
#include <drive_msgs/drive_param.h>
#include <ros/ros.h>

constexpr const char* TOPIC_CONTROLLED_DRIVE_PARAM = "/commands/controlled_drive_param";
constexpr const char* TOPIC_MAX_SPEED = "/speed_info/max_speed";
constexpr const char* TOPIC_LASER_SCAN = "/scan";

class SpeedInfo
{
    private:
    double m_current_speed = 0;
    double m_last_determined_speed = 0;
    ProcessTrack m_process_track;

    ros::NodeHandle m_node_handle;
    ros::Subscriber m_laserscan_subscriber;
    ros::Subscriber m_controlled_drive_parameters_subscriber;
    ros::Publisher m_max_speed_publisher;

    public:
    SpeedInfo();

    double getCurrentSpeed()
    {
        return m_current_speed;
    }
    double getLastDeterminedSpeed()
    {
        return m_last_determined_speed;
    }
    void publishMaxSpeed(std::vector<Point>& pointcloud);
    double calcMaxCurveSpeed(double radius);
    double calcMaxSpeed(double distance, double target_speed);
    double calcBrakingDistance(double distance, double target_speed);
    double calcSpeed(ProcessedTrack& processed_track);
    void getScanAsCartesian(std::vector<Point>* storage, const sensor_msgs::LaserScan::ConstPtr& laserscan);

    void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& laserscan);
    void controlledDriveParametersCallback(const drive_msgs::drive_param::ConstPtr& parameters);
};