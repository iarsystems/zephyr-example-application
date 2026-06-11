# IAR Zephyr Example Application

<a href="https://github.com/zephyrproject-rtos/example-application/actions/workflows/build.yml?query=branch%3Amain">
  <img src="https://github.com/zephyrproject-rtos/example-application/actions/workflows/build.yml/badge.svg?event=push">
</a>
<a href="https://github.com/zephyrproject-rtos/example-application/actions/workflows/docs.yml?query=branch%3Amain">
  <img src="https://github.com/zephyrproject-rtos/example-application/actions/workflows/docs.yml/badge.svg?event=push">
</a>
<a href="https://zephyrproject-rtos.github.io/example-application">
  <img alt="Documentation" src="https://img.shields.io/badge/documentation-3D578C?logo=sphinx&logoColor=white">
</a>
<a href="https://zephyrproject-rtos.github.io/example-application/doxygen">
  <img alt="API Documentation" src="https://img.shields.io/badge/API-documentation-3D578C?logo=c&logoColor=white">
</a>

This repository contains a Zephyr example application ready to use with IAR.
The main purpose of this repository is to serve as a reference on how to 
structure Zephyr-based applications. 
Some of the features demonstrated in this example are:

- Basic multi-threaded [Zephyr application][app_dev] skeleton
- [Zephyr workspace applications][workspace_app]
- [Zephyr modules][modules]
- [West T2 topology][west_t2]
- [Custom boards][board_porting]
- Custom [devicetree bindings][bindings]
- Out-of-tree [drivers][drivers]
- Out-of-tree libraries
- Example CI configuration (using GitHub Actions)
- Custom [west extension][west_ext]
- Custom [Zephyr runner][runner_ext]
- Doxygen and Sphinx documentation boilerplate

This repository uses the development branch of [Zephyr][zephyr] and the [manifest](west.yml) file points to `main`. It is possible to change the manifest file in your own application to point to a corresponding Zephyr tag. Note that Zephyr 4.1 was the first production-grade version providing support for the IAR toolchain for Arm. [^1] 

[^1]: [Zephyr RTOS 4.1 Now Available: Performance Improvements, Support for IAR Toolchain, and More]( https://zephyrproject.org/zephyr-rtos-4-1-is-available/)

[app_dev]: https://docs.zephyrproject.org/latest/develop/application/index.html
[workspace_app]: https://docs.zephyrproject.org/latest/develop/application/index.html#zephyr-workspace-app
[modules]: https://docs.zephyrproject.org/latest/develop/modules.html
[west_t2]: https://docs.zephyrproject.org/latest/develop/west/workspaces.html#west-t2
[board_porting]: https://docs.zephyrproject.org/latest/hardware/porting/board_porting.html
[bindings]: https://docs.zephyrproject.org/latest/build/dts/bindings.html
[drivers]: https://docs.zephyrproject.org/latest/kernel/drivers/index.html
[zephyr]: https://github.com/zephyrproject-rtos/zephyr
[west_ext]: https://docs.zephyrproject.org/latest/develop/west/extensions.html
[runner_ext]: https://docs.zephyrproject.org/latest/develop/modules.html#external-runners

## Getting Started
This guide assumes you already have a compatible IAR toolchain for Arm (v9.70.1+) installed and ready to use.

Before getting started, make sure you have a proper Zephyr development environment.
Follow the official [Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html).

>[!TIP]
>When you reach the **Install the Zephyr SDK** section, you only need:
>```
>west sdk install --gnu-toolchains arm-zephyr-eabi
>```
>Doing this will prevent `west` from downloading gigabytes of unrelated toolchains, which would take time to download and would occupy significant storage space. Once you have reached that point, you can return to this guide.


### Initialization

The first step is to initialize the workspace folder (``my-workspace``) where
the ``zephyr-example-application`` and all Zephyr modules will be cloned. Run the following
command:

```shell
# initialize my-workspace for the zephyr-example-application (main branch) 
west init -m https://github.com/iarsystems/zephyr-example-application --mr main my-workspace
# update Zephyr modules
cd my-workspace
west update
```

### Building and running
For building with IAR, make sure you set `ZEPHYR_TOOLCHAIN_VARIANT` [^2] and `IAR_TOOLCHAIN_PATH` in your system and then run the following commands:

[^2]: [Zephyr Docs/Developing with Zephyr/Toolchains/IAR toolchain for Arm](https://docs.zephyrproject.org/latest/develop/toolchains/iar_arm_toolchain.html)

```shell
cd zephyr-example-application
west build -b $BOARD app
```

where `$BOARD` is the target board.

You can use the `custom_aca` board found in this
repository. Note that Zephyr sample boards may be used if an
appropriate overlay is provided (see [`app/boards`][apps-boards]).
When switching boards, always perform a pristine build:
```shell
# pristine builds are obtained with -p or --pristine
west build -b $BOARD app -p
```

[apps-boards]: app/boards

A sample debug configuration is also provided. To apply it, run the following
command:

```shell
west build -b $BOARD app -- -DEXTRA_CONF_FILE=debug.conf
```

Once you have built the application, run the following command to flash it:

```shell
# with the IAR I-jet (default)
west flash
# or with the SEGGER J-Link
west flash --runner jlink
```

If you have set `IAR_TOOLCHAIN_PATH` to an instance of IAR Embedded Workbench, you can debug your application directly, with the IAR C-SPY Debugger for Arm:

```shell
# with the IAR I-jet (default)
west debug
# or with the SEGGER J-link
west debug --runner jlink
```

### Testing

To execute Twister integration tests, run the following command:

```shell
west twister -T tests --integration
```

### Documentation

A minimal documentation setup is provided for Doxygen and Sphinx. To build the
documentation first change to the ``doc`` folder:

```shell
cd doc
```

Before continuing, check if you have Doxygen installed. It is recommended to
use the same Doxygen version used in [CI](.github/workflows/docs.yml). To
install Sphinx, make sure you have a Python installation in place and run:

```shell
pip install -r requirements.txt
```

API documentation (Doxygen) can be built using the following command:

```shell
doxygen
```

The output will be stored in the ``_build_doxygen`` folder. Similarly, the
Sphinx documentation (HTML) can be built using the following command:

```shell
make html
```

The output will be stored in the ``_build_sphinx`` folder. You may check for
other output formats other than HTML by running ``make help``.
