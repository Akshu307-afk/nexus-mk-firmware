# NEXUS Hackpad — QMK firmware starter

This repository contains QMK source for the NEXUS 12-key, two-mode Hackpad concept. It targets a Seeed XIAO RP2040, a rotary encoder and a 128×32 SSD1306 I²C OLED.

> **Hardware status:** this is an untested starter design. The controller and PCB do not need to be physically present to run the online compile, but the UF2 should not be flashed to hardware until the final PCB pin mapping and components match this configuration. The build may reveal QMK version or configuration issues that need fixing.

## Get a UF2 without owning the controller yet

1. Create a repository on GitHub (for example, `nexus-qmk-firmware`).
2. Upload the contents of this folder to the repository, including the hidden `.github/workflows/build.yml` file.
3. Open the repository's **Actions** tab. The workflow named **Build NEXUS UF2** runs after the first push. You can also select **Run workflow**.
4. Open the completed workflow run. Under **Artifacts**, download `NEXUS-UF2` and extract it. If the build passes, the archive contains the generated `.uf2` firmware.
5. If the workflow fails, open the failed run and read the build log; a failed build does not produce a valid UF2.

The workflow compiles the custom keyboard folder against the current QMK firmware repository and uploads the generated UF2 as a GitHub Actions artifact. GitHub's QMK Userspace/build-workflow documentation explains this general approach: https://docs.qmk.fm/newbs_building_firmware_workflow

## Key layout

### Coding Mode

| Row | Left | Middle | Right |
|---|---|---|---|
| 1 | MODE | VS CODE | ARDUINO IDE |
| 2 | VERIFY | UPLOAD | RUN (F5) |
| 3 | SAVE | UNDO | COPY |
| 4 | PASTE | REDO | CUT |

### Music + Tools Mode

| Row | Left | Middle | Right |
|---|---|---|---|
| 1 | MODE | SPOTIFY | PLAY/PAUSE |
| 2 | PREVIOUS | NEXT | SCREENSHOT |
| 3 | LOCK PC | SHOW DESKTOP | CHATGPT |
| 4 | BROWSER | NEW TAB | CLOSE TAB |

Press MODE to switch modes. In Coding Mode, turning the encoder scrolls by page; in Music + Tools Mode, it changes system volume.

## Assumed pin map — must match the PCB

| Function | XIAO RP2040 pad | RP2040 GPIO |
|---|---:|---:|
| Matrix rows 1–4 | D0, D1, D2, D3 | GP26, GP27, GP28, GP29 |
| Matrix columns 1–3 | D6, D7, D8 | GP0, GP1, GP2 |
| Encoder A/B | D9, D10 | GP4, GP3 |
| OLED SDA/SCL | D4, D5 | GP6, GP7 |

Matrix diodes are configured COL2ROW. If the final PCB uses different pins or diode direction, update `info.json` / `config.h` before compiling. The current pin map does not enable RGB LEDs or the encoder push switch.

## Host-specific behaviour

The keymap sends keyboard reports and uses Windows+R for launch shortcuts; the application-launch keys are Windows-oriented. The Arduino command alias may need changing for your installed version. Actual Spotify song title/artist display would need a PC companion program; QMK alone cannot read browser metadata.

## Important

A `.uf2` is the compiled firmware binary, not source code. The file can be built online before you own the microcontroller, but you cannot test or flash it onto a device until you have the supported controller. The current source has not been validated on physical hardware.
