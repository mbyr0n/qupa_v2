# Install script for directory: /home/gmadro/qupa_v2/qupa

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/gmadro/swarm_robotics/argos3-dist")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos3/plugins/robots/qupa/control_interface" TYPE FILE FILES
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_base_ground_sensor.h"
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_distance_scanner_actuator.h"
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_distance_scanner_sensor.h"
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_encoder_sensor.h"
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_gripper_actuator.h"
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_light_sensor.h"
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_motor_ground_sensor.h"
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_proximity_sensor.h"
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_turret_actuator.h"
    "/home/gmadro/qupa_v2/qupa/control_interface/ci_qupa_turret_encoder_sensor.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/argos3/plugins/robots/qupa/simulator" TYPE FILE FILES
    "/home/gmadro/qupa_v2/qupa/simulator/dynamics2d_qupa_model.h"
    "/home/gmadro/qupa_v2/qupa/simulator/pointmass3d_qupa_model.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_base_ground_rotzonly_sensor.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_distance_scanner_default_actuator.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_distance_scanner_equipped_entity.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_distance_scanner_rotzonly_sensor.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_entity.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_gripper_default_actuator.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_light_rotzonly_sensor.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_motor_ground_rotzonly_sensor.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_proximity_default_sensor.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_turret_default_actuator.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_turret_encoder_default_sensor.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qupa_turret_entity.h"
    "/home/gmadro/qupa_v2/qupa/simulator/qtopengl_qupa.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_qupa.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_qupa.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_qupa.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/argos3" TYPE SHARED_LIBRARY FILES "/home/gmadro/qupa_v2/build/libargos3plugin_simulator_qupa.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_qupa.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_qupa.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_qupa.so"
         OLD_RPATH "/home/gmadro/swarm_robotics/argos3-dist/lib/argos3:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/argos3/libargos3plugin_simulator_qupa.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/gmadro/qupa_v2/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
