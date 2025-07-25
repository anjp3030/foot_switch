# FootSwitch ROS 2 노드

이 패키지는 USB 풋스위치 장치의 상태를 읽어 ROS 토픽으로 발행하는 ROS 2 노드(`fshw_node`)를 제공합니다.

## 주요 기능

- Linux의 `input_event`를 사용하여 USB 풋스위치의 키 이벤트를 읽습니다.
- 풋스위치의 ON/OFF 상태를 `std_msgs/Bool` 메시지로 발행합니다.
- 토픽 이름: `footswitch1`
- 기본 장치 경로:  
  `/dev/input/by-id/usb-DIY_Devices_16F1455_Generic_HID__Keyboard_and_Mouse-if01-event-kbd`

## 요구 사항

- `/dev/input`을 지원하는 Linux 환경
- ROS 2 (Humble, Foxy 등에서 테스트됨)
- 입력 장치(`/dev/input/...`)에 대한 읽기 권한

## 빌드 방법

ROS 2 워크스페이스에 이 저장소를 클론한 후 다음 명령어를 실행하세요:

```bash
cd ~/ros2_ws
colcon build --packages-select <your_package_name>
source install/setup.bash
```
