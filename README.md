# FootSwitch ROS 2 노드

이 패키지는 USB 풋스위치 장치의 상태를 읽어 ROS 토픽으로 발행하는 ROS 2 노드(`fshw_node`)를 제공합니다.

## 주요 기능

- Linux의 `input_event`를 사용하여 USB 풋스위치의 키 이벤트를 읽기
- 풋스위치의 ON/OFF 상태를 `std_msgs/Bool` 메시지로 발행
- 토픽 이름: `footswitch1`
- 기본 장치 경로:  
  `/dev/input/by-id/usb-DIY_Devices_16F1455_Generic_HID__Keyboard_and_Mouse-if01-event-kbd`
- if (ev.type == EV_KEY && ev.code == 60) // 풋스위치 키 코드 확인 ev.code는 설정한 키에 따라 달라짐 ex) F2 -> 60, F1 -> 59

## udev rule 적용

```bash
sudo cp 19-footswitch.rules /etc/udev/rules.d
sudo udevadm control --reload-rules
sudo udevadm trigger
```

## 빌드 및 실행

ROS 2 워크스페이스에 이 저장소를 클론한 후 다음 명령어를 실행하세요:

```bash
cd ~/<your workspace>
colcon build --packages-select foot_switch
source install/setup.bash
ros2 run foot_switch foot_switch
```
