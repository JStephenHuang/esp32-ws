# ESP32 Workspace

A reusable ESP-IDF development workspace with a pinned, containerized toolchain. The repository root is mounted at `/ws` inside the container.

Heavily inspired by: https://github.com/ShawnHymel/course-iot-with-esp-idf.

## Prerequisites

- Git
- Docker Engine
- Visual Studio Code
- The VS Code Dev Containers extension

A native ESP-IDF installation is not required. The Docker image provides ESP-IDF, `idf.py`, the cross-compilers, CMake, Ninja, Python packages, and flashing/debugging tools.

I have only tested this workspace on a Linux host. Mac and Windows might be different.

## Create a workspace

Clone this template under any desired directory name:

```bash
git clone <template-url> my-esp-project
cd my-esp-project
code .
```

In VS Code, run **Dev Containers: Reopen in Container**. Docker automatically downloads the pinned ESP-IDF image if it is not cached locally.

Host and container paths map as follows:

```text
<clone>/apps        -> /ws/apps
<clone>/components  -> /ws/components
```

## Select an ESP-IDF version

Change `ESP_IDF_VERSION` at the top of `Dockerfile`, using an existing `espressif/idf` image tag:

```dockerfile
ARG ESP_IDF_VERSION=v6.0.2
```

Then run **Dev Containers: Rebuild Container**. Pin a release tag rather than `latest` to keep builds reproducible.

Verify the active toolchain inside the container:

```bash
echo "$IDF_PATH"
idf.py --version
```

## Workspace layout

```text
.
├── .devcontainer/
├── Dockerfile
├── apps/
└── components/
```

Each directory under `apps/` should be an independent ESP-IDF project with its own top-level `CMakeLists.txt`, `sdkconfig.defaults`, `main/`, and build directory.

Shared components live directly under `components/`. An app exposes them to ESP-IDF by setting `EXTRA_COMPONENT_DIRS` before loading `project.cmake`:

```cmake
cmake_minimum_required(VERSION 3.22)

set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../components")
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(my_app)
```

## Building and Flashing

Activate the ESP-IDF:

```
source "$IDF_PATH/export.sh"
```

Build from the selected application directory:

```bash
cd /ws/apps/my_app
idf.py set-target esp32
idf.py build
idf.py -p {port} flash monitor
```

Replace `esp32` with the target used by your board, such as `esp32c3` or `esp32s3`.
Specify the port when flashing.


Typical serial devices include `/dev/ttyUSB0` and `/dev/ttyACM0`. If the board is not visible, check the host device and permissions before reopening the container:

Exit the console with `Ctrl + ]`

```bash
ls -l /dev/ttyUSB* /dev/ttyACM* 2>/dev/null
```

If nothing returns you might need to rebuild the container.

## Common pitfall

Without extra config under the /main/CMakeLists.txt the parent needs to be called main. I first named it /src and it had a build error. ESP-IDF by default looks for {PROJECT_PATH}/main.

The board must be connected before creating the container. If you connected the board while the container was already running, you have to rebuild the container.