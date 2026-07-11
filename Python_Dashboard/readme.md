#  Python Dashboard

A **real-time monitoring dashboard** developed in **Python** for the **EV ADAS System**. The dashboard communicates with the STM32 over UART and provides live visualization of vehicle parameters, ADAS alerts, and system status.

---

#  Overview

The Python Dashboard serves as the Human Machine Interface (HMI) of the EV ADAS project. It receives real-time data from the STM32 microcontroller and displays important vehicle parameters in an easy-to-understand graphical interface.

The dashboard enables users to monitor the vehicle's health, battery status, collision risks, and blind spot detection while the simulation is running in **PICSimLab**.

---

# Features

##  Vehicle Monitoring

- Real-Time Vehicle Speed Display
- Battery State of Charge (SOC)
- Motor Temperature Monitoring
- Torque Visualization
- Power Monitoring
- Estimated Driving Range

---

##  ADAS Monitoring

### Forward Collision Warning (FCW)

- Obstacle Distance Display
- Collision Risk Status
- Time-To-Collision (TTC)
- Warning Indicators

---

### Blind Spot Detection (BSD)

- Left Blind Spot Alert
- Right Blind Spot Alert
- Real-Time LED Status

---

##  Fault Monitoring

Displays critical system faults including:

- Motor Overheating
- Low Battery Warning
- Collision Detection
- Safe-State Activation

---

##  Live Visualization

The dashboard updates continuously to display:

- Vehicle Speed
- Battery SOC
- Motor Temperature
- Torque
- Vehicle Power
- Estimated Range
- Drive Mode
- System Status

---

#  Technologies Used

- Python 3.x
- Tkinter
- PySerial
- Matplotlib

---

#  Project Structure

```
Python_Dashboard/
│
├── ev_dashboard.py
├── requirements.txt
├── README.md
├── assets/
│   ├── dashboard.png
│   ├── speed_gauge.png
│   └── alerts.png
│
└── screenshots/
    ├── dashboard_running.png
    ├── collision_warning.png
    └── blind_spot_alert.png
```

---

#  Installation

Navigate to the dashboard directory.

```bash
cd Python_Dashboard
```

Install the required Python packages.

```bash
pip install -r requirements.txt
```

---

#  Running the Dashboard

Start the dashboard using:

```bash
python ev_dashboard.py
```

The application will automatically connect to the configured serial port and begin displaying real-time data from the STM32.

---

#  Dashboard Displays

The dashboard provides live monitoring of:

-  Vehicle Speed
-  Battery State of Charge (SOC)
-  Motor Temperature
-  Motor Torque
-  Motor Power
-  Estimated Driving Range
-  Collision Warning Status
-  Blind Spot Detection Status
-  Current Drive Mode
-  Fault Notifications

---

#  Screenshots

Store the screenshots in the following structure:

```
screenshots/
│
├── dashboard_running.png
├── collision_warning.png
├── blind_spot_alert.png
└── system_status.png
```

Then display them in the README like this:

```markdown
## Dashboard

![Dashboard](screenshots/dashboard_running.png)

---

## Collision Warning

![Collision Warning](screenshots/collision_warning.png)

---

## Blind Spot Detection

![Blind Spot Detection](screenshots/blind_spot_alert.png)

---

## System Status

![System Status](screenshots/system_status.png)
```

---

#  Data Flow

```
STM32 Firmware
      │
      │ UART
      ▼
PySerial Communication
      │
      ▼
Python Dashboard
      │
      ├────────► Vehicle Monitoring
      ├────────► ADAS Alerts
      ├────────► Fault Monitoring
      └────────► Live Visualization
```

---

#  Requirements

Install all required dependencies using:

```bash
pip install -r requirements.txt
```

The required libraries include:

- Python 3.x
- PySerial
- Tkinter
- Matplotlib

---

#  Future Improvements

Potential enhancements include:

- Modern Dark Theme UI
- Circular Speedometer Gauge
- Battery Percentage Gauge
- Live Graph Plotting
- CAN Bus Support
- Data Logging to CSV
- Cloud Connectivity
- AI-Based Driving Analytics
- GPS Integration
- Mobile Dashboard Support

---

#  Author

**Malavika**

Department of Electronics and Communication Engineering

TKM College of Engineering

---

#  License

This dashboard is intended for **educational and research purposes** and is part of the **EV ADAS System using STM32** project.
