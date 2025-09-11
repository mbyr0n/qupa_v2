#
# Qupa headers
#
# argos3/plugins/robots/qupa/control_interface
set(ARGOS3_HEADERS_PLUGINS_ROBOTS_QUPA_CONTROLINTERFACE
  control_interface/ci_qupa_base_ground_sensor.h
  control_interface/ci_qupa_distance_scanner_actuator.h
  control_interface/ci_qupa_distance_scanner_sensor.h
  control_interface/ci_qupa_encoder_sensor.h
  control_interface/ci_qupa_gripper_actuator.h
  control_interface/ci_qupa_light_sensor.h
  control_interface/ci_qupa_motor_ground_sensor.h
  control_interface/ci_qupa_proximity_sensor.h
  control_interface/ci_qupa_turret_actuator.h
  control_interface/ci_qupa_turret_encoder_sensor.h)
# argos3/plugins/robots/qupa/simulator
if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_HEADERS_PLUGINS_ROBOTS_QUPA_SIMULATOR
    simulator/dynamics2d_qupa_model.h
    simulator/pointmass3d_qupa_model.h
    simulator/qupa_base_ground_rotzonly_sensor.h
    simulator/qupa_distance_scanner_default_actuator.h
    simulator/qupa_distance_scanner_equipped_entity.h
    simulator/qupa_distance_scanner_rotzonly_sensor.h
    simulator/qupa_entity.h
    simulator/qupa_gripper_default_actuator.h
    simulator/qupa_light_rotzonly_sensor.h
    simulator/qupa_motor_ground_rotzonly_sensor.h
    simulator/qupa_proximity_default_sensor.h
    simulator/qupa_turret_default_actuator.h
    simulator/qupa_turret_encoder_default_sensor.h
    simulator/qupa_turret_entity.h)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Qupa sources
#
set(ARGOS3_SOURCES_PLUGINS_ROBOTS_QUPA
  ${ARGOS3_HEADERS_PLUGINS_ROBOTS_QUPA_CONTROLINTERFACE}
  control_interface/ci_qupa_base_ground_sensor.cpp
  control_interface/ci_qupa_distance_scanner_actuator.cpp
  control_interface/ci_qupa_distance_scanner_sensor.cpp
  control_interface/ci_qupa_encoder_sensor.cpp
  control_interface/ci_qupa_gripper_actuator.cpp
  control_interface/ci_qupa_light_sensor.cpp
  control_interface/ci_qupa_motor_ground_sensor.cpp
  control_interface/ci_qupa_proximity_sensor.cpp
  control_interface/ci_qupa_turret_actuator.cpp
  control_interface/ci_qupa_turret_encoder_sensor.cpp)

if(ARGOS_BUILD_FOR_SIMULATOR)
  set(ARGOS3_SOURCES_PLUGINS_ROBOTS_QUPA
    ${ARGOS3_SOURCES_PLUGINS_ROBOTS_QUPA}
    ${ARGOS3_HEADERS_PLUGINS_ROBOTS_QUPA_SIMULATOR}
    simulator/dynamics2d_qupa_model.cpp
    simulator/pointmass3d_qupa_model.cpp
    simulator/qupa_base_ground_rotzonly_sensor.cpp
    simulator/qupa_distance_scanner_default_actuator.cpp
    simulator/qupa_distance_scanner_equipped_entity.cpp
    simulator/qupa_distance_scanner_rotzonly_sensor.cpp
    simulator/qupa_entity.cpp
    simulator/qupa_gripper_default_actuator.cpp
    simulator/qupa_light_rotzonly_sensor.cpp
    simulator/qupa_motor_ground_rotzonly_sensor.cpp
    simulator/qupa_proximity_default_sensor.cpp
    simulator/qupa_turret_default_actuator.cpp
    simulator/qupa_turret_encoder_default_sensor.cpp
    simulator/qupa_turret_entity.cpp)
  # Compile the graphical visualization only if the necessary libraries have been found
  if(ARGOS_QTOPENGL_FOUND)
    include_directories(${ARGOS_QTOPENGL_INCLUDE_DIRS})
    set(ARGOS3_HEADERS_PLUGINS_ROBOTS_QUPA_SIMULATOR
      ${ARGOS3_HEADERS_PLUGINS_ROBOTS_QUPA_SIMULATOR}
      simulator/qtopengl_qupa.h)
    set(ARGOS3_SOURCES_PLUGINS_ROBOTS_QUPA
      ${ARGOS3_SOURCES_PLUGINS_ROBOTS_QUPA}
      simulator/qtopengl_qupa.h
      simulator/qtopengl_qupa.cpp)
  endif(ARGOS_QTOPENGL_FOUND)
endif(ARGOS_BUILD_FOR_SIMULATOR)

#
# Create qupa plugin
#
add_library(argos3plugin_${ARGOS_BUILD_FOR}_qupa SHARED ${ARGOS3_SOURCES_PLUGINS_ROBOTS_QUPA})
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_qupa
  argos3plugin_${ARGOS_BUILD_FOR}_genericrobot
  argos3plugin_${ARGOS_BUILD_FOR}_dynamics2d
  argos3plugin_${ARGOS_BUILD_FOR}_pointmass3d)
if(ARGOS_QTOPENGL_FOUND)
  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_qupa argos3plugin_${ARGOS_BUILD_FOR}_qtopengl)
endif(ARGOS_QTOPENGL_FOUND)

#
# Add plugin to ARGOS_PLUGIN_PATH
#
set(ARGOS_PLUGIN_PATH "${ARGOS_PLUGIN_PATH}:${CMAKE_CURRENT_BINARY_DIR}" CACHE INTERNAL "ARGoS plugin path")

install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_QUPA_CONTROLINTERFACE} DESTINATION include/argos3/plugins/robots/qupa/control_interface)

if(ARGOS_BUILD_FOR_SIMULATOR)
  install(FILES ${ARGOS3_HEADERS_PLUGINS_ROBOTS_QUPA_SIMULATOR}      DESTINATION include/argos3/plugins/robots/qupa/simulator)
endif(ARGOS_BUILD_FOR_SIMULATOR)

install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_qupa
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3)
