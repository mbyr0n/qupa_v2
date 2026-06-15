# Argos QUPA robot

The QUPA robot is a modular, low-cost platform developed in Ecuador by the CoRAL laboratory at the Escuela Superior Politécnica del Litoral (ESPOL). Designed and focuses on swarm robotics applications. The platform is built to be easy to assemble and operate.

### Key Features
- **Omnidirectional camera**
- **6 proximity sensors**
- **1 ground color sensor**
- **5 LEDs**
- **UV-LEDs**

![QUPA ARENA](examples/experiments/images/qupas_argops3.png)

*Current Development:* A gripper mechanism is currently being implemented for the robot.

## How to Compile the Argos3 QUPA Robot

Follow these steps to compile the QUPA robot binaries for the Argos3 simulator.

### 1. Clone the Repository
Download the source code from the GitHub repository:

```bash
git clone https://github.com/coral-espol/qupa_v2.git
```

### 2. Compile the binaries 

Navigate to the project directory and run the build process.

```
cd ~/qupa_v2
rm -rf build && mkdir build && cd build
```
Configure the build with CMake. 

```
cmake ../src \
  -DCMAKE_BUILD_TYPE=Release \
  -DARGOS_BUILD_FOR=simulator \
  -DCMAKE_INSTALL_PREFIX="$HOME/swarm_robotics/argos3-dist"

make -j"$(nproc)"
make install
```
> Note: You must to edit your **DCMAKE_INSTALL_PREFIX** with your diretory where argos3 was installed. 

For local development without installing globally, point ARGoS to the build folder:

```bash
export ARGOS_PLUGIN_PATH="$HOME/qupa_v2/build${ARGOS_PLUGIN_PATH:+:$ARGOS_PLUGIN_PATH}"
```

To know where argos3 was installed and your own rute put in your terminal the next command.

```
which argos3 
```
the next command line is an example for other location.
```
cmake -DCMAKE_BUILD_TYPE=Release \
      -DARGOS_BUILD_FOR=simulator \
      -DCMAKE_INSTALL_PREFIX="/usr/local" \
      -DCMAKE_PREFIX_PATH="/usr/local" \
      ../src
make -j"$(nproc)"
make install
```

### 3. Test the argos QUPA robot 

```
argos3 -c examples/experiments/test_qupa.argos
```

Lua example controllers live in `examples/controllers/lua`.

### 4. Native tags for drone detection

QUPA can expose a native ARGoS tag that drones detect through `tag_medium`.
Define a tag medium and opt in per robot:

```xml
<media>
  <tag id="tags" index="grid" grid_size="5,5,5" />
</media>

<arena ...>
  <qupa id="q0" marker_id="0" tag_medium="tags">
    <body position="0,0,0" orientation="0,0,0" />
    <controller config="my_controller" />
  </qupa>
</arena>
```

`marker_id` becomes the tag payload. If `tag_medium` is omitted, the robot is
created without a tag.

### 5. Media material

Here you can find a some examples (click on the image to show the video).

1. Simple simulation with the QUPA robot
[![Example 1](examples/experiments/images/frame_0202.png)](https://drive.google.com/file/d/1NISa6QuCtN9FcV-uvQB4OstGJXl4G2BH/view?usp=sharing) 

2. Making experiments example 1
[![Example 1](examples/experiments/images/frame_04608.png)](https://drive.google.com/file/d/1CMT9WoHcIdt_1VtyqQ2vo7GJ7JlBuMgB/view?usp=sharing) 

3. Making experiments example 2
[![Example 1](examples/experiments/images/example1.png)](https://drive.google.com/file/d/18gKZoMNuN__hlouXpRjukzwSWbfgSCyx/view?usp=drive_link)

