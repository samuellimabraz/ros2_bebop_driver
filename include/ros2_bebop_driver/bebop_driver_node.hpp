/**
Software License Agreement (BSD)

\file      bebop_driver_node.hpp
\authors   Jeremy Fix <jeremy.fix@centralesupelec.fr>
\copyright Copyright (c) 2022, CentraleSupélec, All rights reserved. Based on
the work of Mani Monajjemi bebop_autonomy

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.
 * Neither the name of Autonomy Lab nor the names of its contributors may be
used to endorse or promote products derived from this software without specific
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WAR- RANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, IN- DIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <tf2_ros/transform_broadcaster.h>

#include <camera_info_manager/camera_info_manager.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <image_transport/image_transport.hpp>
#include <memory>
#include <nav_msgs/msg/odometry.hpp>
#include <optional>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/empty.hpp>
#include <std_msgs/msg/u_int8.hpp>

#include "ros2_bebop_driver/bebop.hpp"
namespace bebop_driver {
class BebopDriverNode : public rclcpp::Node {
   private:
    std::shared_ptr<Bebop> bebop;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr subscription_takeoff;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr subscription_land;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr
	subscription_emergency;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr subscription_flattrim;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr
	subscription_navigateHome;
    rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr
	subscription_animationFlip;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr
	subscription_cmdVel;
    rclcpp::Subscription<geometry_msgs::msg::Vector3>::SharedPtr subscription_moveCamera;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr
	subscription_photo;

    std::string camera_frame_id;
    std::shared_ptr<camera_info_manager::CameraInfoManager> cinfo_manager;

    image_transport::CameraPublisher publisher_camera;
    rclcpp::TimerBase::SharedPtr camera_timer;

    std::string odom_frame_id;
    std::optional<rclcpp::Time> last_odom_time;
    geometry_msgs::msg::TransformStamped tf_odom_to_base;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisher_odometry;
    rclcpp::TimerBase::SharedPtr odom_timer;

    void publishCamera(void);
    void publishOdometry(void);
    void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg);

   public:
    BebopDriverNode();
};
}  // namespace bebop_driver
