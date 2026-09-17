# PodiaGuard — Smart Foot Health Monitor for Diabetic Patients

PodiaGuard is a smart shoe system designed to catch diabetic foot ulcers **before they happen**. Instead of reacting to visible wounds, it continuously fuses plantar pressure, bilateral temperature, and humidity readings into a single risk score — and pushes that score to both the patient and their doctor in real time.

## The Problem

Diabetic foot ulcers are typically caught only after visible skin damage has already occurred. Existing commercial solutions (temperature-only insoles, pressure-only mats) monitor a single variable and raise simple threshold alarms. There is currently no widely available system that **fuses multiple early-warning signals into one predictive score**, and none that stay useful once a patient's condition progresses to amputation.

## System Overview

| Layer | What it does |
|---|---|
| **Sensors** | 3x plantar pressure (heel / midfoot / forefoot), 2x bilateral temperature, 1x humidity |
| **Firmware (MCU)** | STM32F103C8 (Blue Pill) — samples all sensors, computes a weighted risk score, drives a local buzzer alert, streams data over UART |
| **Mobile App — PodiaGuard** | Patient View (simple risk indicator + guidance) and Doctor Mode (live telemetry, thresholds, trend tracking) |

## Hardware Simulation (Proteus)

Phase-1 circuit simulated in Proteus ISIS — 3x FSR-proxy potentiometers for pressure, 2x LM35 for temperature, 1x DHT11 for humidity, buzzer for local alerting, and a virtual terminal streaming live CSV sensor data over UART.

![Proteus simulation schematic](images/proteus_simulation.png)

## Mobile App

The PodiaGuard app has two modes, chosen at launch:

![App home screen — mode selection](images/app_home_screen.png)

- **Patient View** — a simple daily safety score, a color-coded foot map (green / amber / red per zone), and plain-language guidance when something needs attention.
- **Doctor Mode** — live telemetry sparklines, raw sensor readings, and configurable risk thresholds for clinical review.

![Patient View — daily risk score and foot map](images/app_patient_view.png)

In the screenshot above, the app has flagged a **2.8°C temperature spike in the right heel** — a bilateral asymmetry that, left unaddressed, is a known early predictor of tissue inflammation before a visible sore forms.

## Risk Fusion Logic

The firmware combines three signals into a single 0–100 risk score:

- **+40** if any pressure zone exceeds its threshold
- **+40** if the left/right temperature difference exceeds 2.2°C (clinical bilateral-asymmetry threshold)
- **+20** if humidity exceeds 70% (maceration risk)

A score ≥ 60 triggers the local buzzer and is flagged as "Attention Needed" in the app.

## Status / Roadmap

- [x] Phase 1: pressure + temperature + humidity sensing, local risk fusion, Proteus simulation
- [x] Mobile app UI (Patient View, Doctor Mode)
- [ ] Phase 2: shear-force sensing, gait (IMU), and gas/VOC sensing for early infection detection
- [ ] Cloud sync between shoe firmware and app (BLE/WiFi bridge)
- [ ] Post-amputation continuity mode: residual-limb measurement assistance and socket-liner sensor reuse

## Author

Developed by Ganna Ahmed ,Nada Ahmed ,Hend Aboelouon ,Hoor Tamer ,Mahmoud Ahmed  —  Faculty of Engineering.
