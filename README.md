# Visual People Counting

Demonstration of a visual based people counting system using the SENSEI platform.

## Prerequisites

- Follow the SDK install instructions in the [SENSEI SDK](https://github.com/pulp-bio/sensei-sdk) `Install.md` to set up toolchains and required environment (Zephyr / nRF Connect SDK, GAP9 toolchain, conda/mamba environment, etc.).

- Export the SDK root environment variable so examples can locate headers/configs (see [SENSEI SDK](https://github.com/pulp-bio/sensei-sdk) `Readme.md`):

   ```sh
   export SENSEI_SDK_ROOT=/path/to/sensei-sdk
   # For zsh permanently:
   echo "export SENSEI_SDK_ROOT=$SENSEI_SDK_ROOT" >> ~/.zshrc
   ```

## Hardware

- Attach the SENSEI Sensor Shield to the SENSEI Base Board before powering the system. The sensor shield repo and base board repo (example, public references):
   - SENSEI Sensor Shield: https://github.com/pulp-bio/sensei-sensor-shield
   - SENSEI Base Board: https://github.com/pulp-bio/sensei-base-board
   -
## Build & Flash

This project contains two parts:

- `src_NRF` — nRF5340 application (Zephyr / nRF Connect SDK).
- `src_GAP9` — GAP9 application (GAP SDK).

Make sure `SENSEI_SDK_ROOT` is set and you have the required toolchains active (see `sensei-sdk/Install.md`).

### nRF (nrf5340) — Build & Flash

You can use either Visual Studio Code with the nRF Connect SDK extension or the terminal.

Using VS Code (recommended for ease):

1. Open the workspace (`sensei-sdk.code-workspace`) in VS Code.
2. Add this repository to the workspace if not already present by using "Add Folder to Workspace".
3. In the explorer, right-click `src_NRF` and use "nRF Connect: Add Folder as Application".
4. In the nRF Connect SDK extension, create or select a CMake preset for the board `nrf5340_senseiv1_cpuapp` and SDK v2.6.1 (or the SDK you have installed).
5. Generate & build, then flash from the extension's Actions tab.

Using terminal (west):

```sh
cd src_NRF
# build for the SENSEI nRF5340 board
west build -b nrf5340_senseiv1_cpuapp
# flash (requires the device connected)
west flash
```

If your environment requires a specific `ZEPHYR_BASE` or activated conda/mamba environment, make sure they are set as described in `sensei-sdk/Install.md`.

### GAP9 — Build & Run

The GAP9 application is built and run using the GAP tools in the `src_GAP9` folder.

From a terminal in `src_GAP9`:

```sh
gap init
gap run
```

To flash the GAP9 application, run the following command:

```sh
gap flash
```

## Streaming & Visualizing Bounding Boxes
Make sure to flash the nRF and GAP9 applications as described above. Additionally, you need to make sure to install the required Python packages by running the following command:
```sh
# Create a virtual environment
python3 -m venv venv

# Activate the virtual environment
source venv/bin/activate

# Install the required packages
pip install -r requirements-streaming.txt
```

To start the streaming server, run the following command:
```sh
# Using the UART over USB connection
python3 scripts/show_bboxes_uart.py -v

# Using BLE connection
python3 scripts/show_bboxes_ble.py -v
```

## Maintainers
- **Philip Wiese** ([wiesep@iis.ee.ethz.ch](mailto:wiesep@iis.ee.ethz.ch))

## Formatting and Linting

We provide the [pre-commit](https://pre-commit.com) configuration file which you can use to install github hooks that execute the formatting commands on your changes.

You will need to manually install pre-commit since it's not added as a dependency to the `pyproject.toml`:
```bash
pip install pre-commit
```

The configuration sets the default stage for all the hooks to `pre-push` so to install the git hooks run:
```bash
pre-commit install --hook-type pre-push
```
The hooks will run before each push, making sure the pushed code can pass linting checks and not fail the CI on linting.

If you change your mind and don't want the git hooks:
```bash
pre-commit uninstall
```

## License
All licenses used in this repository are listed under the `LICENSES` folder. Unless specified otherwise in the respective file headers, all code checked into this repository is made available under a permissive license.
- Most software sources and tool scripts are licensed under the [Apache 2.0 license](https://opensource.org/licenses/Apache-2.0).
- Markdown, JSON, text files, pictures, PDFs, are licensed under the [Creative Commons Attribution 4.0 International](https://creativecommons.org/licenses/by/4.0) license (CC BY 4.0).

To extract license information for all files, you can use the [reuse tool](https://reuse.software/) and by running `reuse spdx` in the root directory of this repository.
