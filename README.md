> [!IMPORTANT]
> **This project has moved.** Active development of DEJA.js and the Track & Trestle model
> railroad platform now happens in private repositories under
> [**Track and Trestle Technology, LLC**](https://github.com/trackandtrestle).
> This repository stays public as a historical snapshot and is no longer maintained.
>
> **Current product, docs, and downloads → [dejajs.com](https://dejajs.com)**

# 🔧 Layout Conductor — Arduino Firmware

**Per-area Arduino sketches for turnouts, signals, sounds, and lighting on a model railroad.**

<p align="center">
  <img src="https://img.shields.io/badge/Arduino-00878F?style=for-the-badge&logo=arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" />
  <img src="https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white" />
</p>

The embedded layer of the **Layout Conductor** system. Each sketch is scoped to one
physical area of the railroad — its own servos, relays, LEDs, and sensors — and listens on
USB serial for commands from
[`layout-conductor-api`](https://github.com/jmcdannel/layout-conductor-api).

## 📂 Sketches

| Sketch | Scope |
|--------|-------|
| `tam-station/`, `tam-station-north/` | Tamarack station yard — turnouts and platform lighting |
| `tamcity/` | Town module — building lights and street effects |
| `tammtn/` | Mountain module — signals and grade accessories |
| `coffee-canyon/` | Canyon scene accessories |
| `weldarc/` | Animated welding-arc lighting effect |
| `signalLightDemo/` | Standalone signal aspect demonstration |
| `traincontrol/` | General throttle and track power control |
| `CommandStation-EX/` | Pinned build of the [DCC-EX](https://dcc-ex.com/) command station firmware |

`serial.py` is a small host-side utility for exercising a board's command set directly from
a laptop without bringing the whole stack up.

## 🔌 Command protocol

Boards accept short bracketed serial commands (`<t 1 90>`, `<e 3 on>`) so a sketch stays
readable and a dropped byte cannot leave a servo mid-throw. Pin maps and servo angles are
defined per sketch rather than shared, which kept each module independently flashable.

## 🧑‍💻 Flashing

Open the target sketch folder in the Arduino IDE, select the board for that module, and
upload. Boards are addressed by USB port on the Pi — see `ports.py` in
[`layout-conductor-api`](https://github.com/jmcdannel/layout-conductor-api) for the
discovery logic that keeps assignments stable across reboots.

## 📌 Status

Retired alongside the rest of Layout Conductor. Its successor, the `io/` package in
[DEJA.js](https://github.com/jmcdannel/DEJA.js), replaced per-area sketches with one
firmware image configured by JSON — and added MQTT so Pico W and ESP32 nodes could join
without a USB cable.

## 🧭 Where this fits

This repo is one step in a long-running line of model railroad control software:

| Era | Project | What changed |
|-----|---------|--------------|
| 2020 | [`train-control`](https://github.com/jmcdannel/train-control) | First React throttle, JMRI + Arduino over HTTP |
| 2021 | [`dctc`](https://github.com/jmcdannel/dctc) | Standalone Arduino DC controller (no computer required) |
| 2022–23 | [`layout-conductor-*`](https://github.com/jmcdannel?tab=repositories&q=layout-conductor) | Split into app + API; Python, Node, and Deno backends explored |
| 2024 | [`Track-and-Trestle-Technology-Suite`](https://github.com/jmcdannel/Track-and-Trestle-Technology-Suite) | MQTT-based monorepo: dispatcher, throttle, dashboard, action API |
| 2024–25 | [`DEJA.js`](https://github.com/jmcdannel/DEJA.js) | TypeScript/Turborepo rewrite, Firebase realtime backbone |
| 2025– | **[dejajs.com](https://dejajs.com)** (private) | Commercial cloud platform for DCC-EX |

---

<sub>Built by [Josh McDannel](https://github.com/jmcdannel) · [dejajs.com](https://dejajs.com) · [LinkedIn](https://www.linkedin.com/in/jmcdannel)</sub>
