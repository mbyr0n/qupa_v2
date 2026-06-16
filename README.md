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

Follow these steps to compile the QUPA robot plugin for the ARGoS3 simulator.

### 1. Clone the Repository

```bash
git clone https://github.com/coral-espol/qupa_v2.git
```

### 2. Prerequisites — Install ARGoS3

The QUPA plugin requires ARGoS3 to be installed system-wide.

#### 2.1 Install dependencies (Ubuntu 24)

```bash
sudo apt update
sudo apt install build-essential cmake git \
  libfreeimage-dev libfreeimageplus-dev \
  qtbase5-dev libqt5opengl5-dev freeglut3-dev libxi-dev libxmu-dev \
  liblua5.3-dev lua5.3 doxygen graphviz
```

> ⚠ Ubuntu 24 no incluye el paquete `qt5-default`. Qt6 es el default,
> pero ARGoS necesita Qt5, por eso se instala `qtbase5-dev` y
> `libqt5opengl5-dev` explícitamente.
> Si usás Wayland, instalá también `qtwayland5`.

#### 2.2 Clone and build ARGoS

```bash
git clone https://github.com/ilpincy/argos3.git
cd argos3
mkdir build_simulator && cd build_simulator
cmake ../src \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=/usr/local \
  -DARGOS_BUILD_FOR=simulator
make -j"$(nproc)"
make doc
sudo make install
sudo ldconfig
```

#### 2.3 Verify

```bash
argos3 -q all
```

Deberías ver una lista de plugins cargados sin errores.

### 3. Compile the QUPA plugin

```bash
cd ~/qupa_v2
rm -rf build && mkdir build && cd build
cmake ../src \
  -DCMAKE_BUILD_TYPE=Release \
  -DARGOS_BUILD_FOR=simulator \
  -DCMAKE_INSTALL_PREFIX=/usr/local
make -j"$(nproc)"
sudo make install
```

Para desarrollo local sin instalar globalmente, usar `ARGOS_PLUGIN_PATH`:

```bash
export ARGOS_PLUGIN_PATH="$HOME/qupa_v2/build${ARGOS_PLUGIN_PATH:+:$ARGOS_PLUGIN_PATH}"
```

### 4. Test the QUPA robot

```bash
argos3 -c examples/experiments/test_qupa.argos
```

Lua example controllers live in `examples/controllers/lua`.

The robot 3D model is rendered from `qupa.obj` at runtime (not baked into the
code). The OBJ file lives in the plugin directory and is transformed to match
the physical body dimensions (scale 1.13×, Y-up to Z-up rotation).

### 5. Native tags for drone detection

QUPA can expose a native ARGoS tag that drones detect through `tag_medium`.
When enabled, the tag is also rendered visually as a checkerboard square on top
of the robot in the 3D visualization.
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

### 6. Media material

Here you can find a some examples (click on the image to show the video).

1. Simple simulation with the QUPA robot
[![Example 1](examples/experiments/images/frame_0202.png)](https://drive.google.com/file/d/1NISa6QuCtN9FcV-uvQB4OstGJXl4G2BH/view?usp=sharing) 

2. Making experiments example 1
[![Example 1](examples/experiments/images/frame_04608.png)](https://drive.google.com/file/d/1CMT9WoHcIdt_1VtyqQ2vo7GJ7JlBuMgB/view?usp=sharing) 

3. Making experiments example 2
[![Example 1](examples/experiments/images/example1.png)](https://drive.google.com/file/d/18gKZoMNuN__hlouXpRjukzwSWbfgSCyx/view?usp=drive_link)

