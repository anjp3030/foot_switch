# FootSwitch ROS 2 Node

This package provides a ROS 2 node (`fshw_node`) for reading a USB footswitch device and publishing its state as a ROS topic.

## Features

- Reads key events from a USB footswitch using Linux `input_event`.
- Publishes footswitch ON/OFF state as a `std_msgs/Bool` message.
- Topic name: `footswitch1`
- Device path (default):  
  `/dev/input/by-id/usb-DIY_Devices_16F1455_Generic_HID__Keyboard_and_Mouse-if01-event-kbd`

## Requirements

- Linux (with `/dev/input` support)
- ROS 2 (tested on Humble, Foxy, etc.)
- Permissions to read input device (`/dev/input/...`)

## How to Build

Clone this repository in your ROS 2 workspace, then:

```bash
cd ~/ros2_ws
colcon build --packages-select <your_package_name>
source install/setup.bash
