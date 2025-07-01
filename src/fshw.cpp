#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>

#include <memory>

static int fd = -1;

void SigintHandler(int sig)
{
  if (fd >= 0)
    close(fd);
  rclcpp::shutdown();
}

class FootSwitchNode : public rclcpp::Node
{
public:
  FootSwitchNode() : Node("fshw_node")
  {
    footswitch_pub_ = create_publisher<std_msgs::msg::Bool>("footswitch1", rclcpp::SensorDataQoS());

    fd = open("/dev/input/by-id/usb-DIY_Devices_16F1455_Generic_HID__Keyboard_and_Mouse-if01-event-kbd",
              O_RDONLY | O_NONBLOCK);                  

    if (fd < 0)
    {
      RCLCPP_ERROR(get_logger(), "Failed to open device: %s", strerror(errno));
      rclcpp::shutdown();
      return;
    }

    timer_ = create_wall_timer(
        std::chrono::milliseconds(10),
        std::bind(&FootSwitchNode::timerCallback, this));
  }

  ~FootSwitchNode()
  {
    if (fd >= 0)
      close(fd);
  }

private:
  void timerCallback()
  {
    struct input_event ev;
    ssize_t bytes = read(fd, &ev, sizeof(ev));

    // RCLCPP_INFO(get_logger(), "Footswitch state: %d", ev.code);

    if (bytes == sizeof(ev))
    {
    //   std::cout<<ev.code<<std::endl;
    //   RCLCPP_INFO(get_logger(), "Footswitch state: %d", ev.code);

      if (ev.type == EV_KEY && ev.code == 60) // 풋스위치 키 코드 확인
      {
        std_msgs::msg::Bool msg;
        msg.data = ev.value > 0;
        std::cout<<ev.value<<std::endl;

        footswitch_pub_->publish(msg);
        
        RCLCPP_INFO(get_logger(), "Footswitch state: %s", msg.data ? "ON" : "OFF");
      }
    }
    else if (bytes < 0 && errno != EAGAIN)
    {
      RCLCPP_ERROR(get_logger(), "Error reading input device: %s", strerror(errno));
    }
  }

  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr footswitch_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  signal(SIGINT, SigintHandler);

  auto node = std::make_shared<FootSwitchNode>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
