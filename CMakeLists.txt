cmake_minimum_required(VERSION 3.8)
project(foot_switch)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# find_package(franka_msgs REQUIRED)

add_executable(fshw src/fshw.cpp)
ament_target_dependencies(fshw rclcpp std_msgs)


# 설치할 실행 파일 정의
install(TARGETS fshw
  DESTINATION lib/${PROJECT_NAME})

ament_package()
