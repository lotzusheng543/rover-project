# 🤖 **Versatile Rover – Group5**

This repository contains the detailed technical design, circuitry, coding, and hardware information for the **Versatile Rover**, developed as part of the **FEEG2001 Systems Design and Computing** project.

---

## 📑 Table of Contents
- [📌 Project Overview](#-project-overview)
- [👥 Team and Supervisors](#-team-and-supervisors)
- [📊 Technical Specifications](#-technical-specifications)
- [🛠 Hardware Design and Manufacturing](#-hardware-design-and-manufacturing)
- [🔌 Electronic and System Design](#-electronic-and-system-design)
- [💻 Software & Control](#-software--control)
- [🧪 Testing and Performance](#-testing-and-performance)
- [🔮 Future Developments](#-future-developments)
- [📁 Repository Structure](#-repository-structure)
- [🚀 Getting Started](#-getting-started)
- [🙏 Acknowledgements](#-acknowledgements)
- [📄 License](#-license)

---

## 📌 Project Overview

The **Versatile Rover** project aimed to design and build a fully functional terrain-roaming rover within a **RM550** budget over an **11-week period**. Inspired by NASA’s Mars rovers, the design prioritized **reliability**, **stability**, and **modular adaptability**.

> ⚙️ Key Goals:
> - Navigate varied terrains with obstacle handling
> - Carry a 3kg payload with gyroscopic stabilization
> - Remain cost-effective and robust for real-world scenarios

The final rover included:
- A **2+3 wheel configuration**
- **Four-bar steering mechanism**
- A **gyroscopic payload system**
- Torque-optimized **gearbox drive system**
- Rugged mechanical design suitable for **disaster relief**

---

## 👥 Team and Supervisors

**Group 5 Members:**
- Niranjanaa A/P Manivannan (34403604)
- Lee Ming Jun (34403523)
- Lo Tzu Sheng (34396101)
- Mihir Lilo Naraindas (35420146)
- Tang Zhi Xi (35444665)
- Tan Ying Jie (35514892)

**Project Supervisors:**
- Dr. Wong Kok Hoe
- Dr. Shiau Ch’ng
- Dr. Gooi Wen Pin
- Dr. Adrian Tan

📅 **Project Date:** 7 May 2025

---

## 📊 Technical Specifications

**Mobility & Terrain Handling**
- Tri-wheel config climbs slopes up to 30°
- Passive adjustment ensures maximum traction

**Drive System**
- Dual 12V DC motors (front/rear)
- 5Nm torque via gearbox
- 10kg supported payload
- Max speed: **0.3 m/s**

**Steering**
- Four-bar linkage
- Controlled by MG995 180° servo motor
- Turning radius: ~20°

**Gyroscopic Payload**
- Keeps payload horizontal within ±5° on inclines
- Modular, hot-swappable system

**Power**
- 11.1V 1500mAh LiPo battery
- Up to **3–4 hours runtime**
- Buck converter supplies clean 5V–6V power

---

## 🛠 Hardware Design and Manufacturing

- Main chassis: **6mm MDF board**
- Precision parts: **3D printed**
- Designed using **SolidWorks** with **FEA** for strength validation
- Manufacturing included:
  - **Laser cutting**
  - **Doughnut board soldering**
  - **Manual assembly** prioritizing accessibility

---

## 🔌 Electronic and System Design

**Core Control:**
- **ESP32 (Doit Devkit V1)** microcontroller  
- Manages:
  - DC motors via **L298N drivers**
  - Servo with **PWM (50Hz)**
  - Real-time user input via Wi-Fi AP

**Circuit Overview:**
- **11.1V LiPo** battery input
- **Buck converter** stabilizes voltage
- Circuit protection via **fuses**
- All components integrated on custom doughnut board

---

## 💻 Software & Control

- ESP32 operates in **Access Point (AP)** mode  
- Creates a Wi-Fi hotspot accessible via smartphones/laptops
- Web interface hosted at:

### 🔧 Web Interface Features:
- Forward / Backward / Left / Right / Stop
- Motor speed control slider
- Real-time response with **JavaScript + CSS**

🔗 **Code available in**: [`/src`](./src)

---

## 🧪 Testing and Performance

### ✅ Achievements:
- Tri-wheels handled slopes and gravel well
- Gearbox increased torque for ramp climbing
- Four-bar steering worked for basic navigation
- Web control was fast and reliable

### ⚠️ Challenges:
- Front steering linkage hit slope edges
- Rear gearbox mounted too low
- Gear-shaft fit was loose (caused failure during final demo)
- Late testing delayed bug discovery

---

## 🔮 Future Developments

1. **Wider Tri-Wheel Sleeves** – for better flotation in sand  
2. **Larger Front Wheel** – improves weight distribution  
3. **Redesigned Steering** – bearings + bushings for tighter turning  

---

## 📁 Repository Structure









The circuit testing:
![circuit video](https://github.com/user-attachments/assets/9cab709e-d7d5-48cd-8e3c-f326b0bb3e80)





The final assembly of the rover:
https://github.com/user-attachments/assets/96c99748-0c48-4abf-b9e3-6a479564f352


















REAL Performance:
![rover performance](https://github.com/user-attachments/assets/a8a1dca2-ef85-4b2c-afae-4d63a94c9c3b)

