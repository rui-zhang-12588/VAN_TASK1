#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>

using namespace std::chrono_literals;

class TurtleCircle : public rclcpp::Node {
public:
    TurtleCircle() : Node("turtle_circle_node") {
        // 创建发布者，向话题 /turtle1/cmd_vel 发送速度指令
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        
        // 创建定时器，每 100 毫秒触发一次回调函数
        timer_ = this->create_wall_timer(
            100ms, std::bind(&TurtleCircle::timer_callback, this));
    }

private:
    void timer_callback() {
        auto message = geometry_msgs::msg::Twist();
        
        // 线速度（往前走）和角速度（转弯），组合起来就是画圆
        message.linear.x = 1.0;  
        message.angular.z = 1.0; 
        
        // 发布指令
        publisher_->publish(message);
    }
    
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    // 初始化 ROS2
    rclcpp::init(argc, argv);
    // 运行节点
    rclcpp::spin(std::make_shared<TurtleCircle>());
    // 关闭 ROS2
    rclcpp::shutdown();
    return 0;
}