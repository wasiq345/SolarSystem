# 🌌 Solar System Simulation

A **realistic, data-driven Solar System simulation** built using **C++ and Python**.

---

## ✨ Project Overview

This project is an interactive simulation of our Solar System, built from scratch with:

- 🧠 **C++** for graphics rendering and simulation logic (using [raylib](https://www.raylib.com/))
- 🐍 **Python** for fetching live NASA ephemeris data and generating data visualizations

It combines real-time astronomy data, intuitive controls, and immersive design to bring space closer to us.

---

## 🚀 Features

✅ Realistic orbital motions of planets  
✅ Zoom in/out and move the camera view smoothly  
✅ Click planets to display their names dynamically  
✅ Integrated live NASA ephemeris data (RA, DEC, Delta) for Earth  
✅ Graphs of Earth’s Right Ascension (RA) plotted over past 7 days using `matplotlib`  
✅ Interstellar OST running in background for cinematic experience  
✅ Modular C++ classes for Sun and Planets with scalable design  

---

## 📷 Preview

_Coming soon..._

---

## 🔧 Installation & Setup

### 1. Clone the Repository
```bash
git clone https://github.com/wasiq345/SolarSystem.git
cd solar-system-simulation
```

### 2. C++ Setup

Install **raylib** on your system. Then compile the C++ files:

```bash
g++ main.cpp -o SolarSystem -lraylib -lopengl32 -lgdi32 -lwinmm
```
> ⚠️ Modify the compile command based on your OS (Windows/Mac/Linux) and IDE setup.

### 3. Python Dependencies

Install required Python packages:

```bash
pip install astroquery matplotlib astropy
```

### 4. Fetch Live NASA Data

Run the following Python scripts:

```bash
python generate_minimal_data.py
python earth_graph.py
```

These will generate:
- `earth_data_minimal.txt` — Live ephemeris data
- `earth_ra.png` — Graph of Earth's RA

### 5. Run the Simulation

Execute the C++ compiled executable:

```bash
./SolarSystem
```

> Ensure the data files and graph image are in the **same directory** as the executable.

---

## 🎮 Controls

| Action            | Key(s)             |
|-------------------|--------------------|
| Zoom In/Out       | ↑ / ↓ Arrows       |
| Move Camera       | W A S D            |
| Click on Planet   | Display Name       |
| Mute Music        | M                  |
| Exit Simulation   | ESC                |

---

## 🧠 Learning Goals

Through this project, I explored:

- Fetching and interpreting **live astronomy data** using NASA APIs
- Graphics rendering and event handling with **raylib in C++**
- Designing **OOP classes** for scalable simulations
- Integrating **Python data pipelines** with C++ applications
- Plotting data visualizations using **matplotlib**
- Combining **science, art, and technology** for immersive learning

---

## 💡 Future Improvements

- Add planet facts database (JSON/SQLite)
- Implement more detailed textures and lighting effects
- Integrate LLMs as an astronomy tutor bot within the simulation
- Deploy as a cross-platform standalone educational tool

---

## 🤝 Credits & References

- [NASA JPL Horizons API](https://ssd.jpl.nasa.gov/horizons/) — Ephemeris data
- [Astroquery](https://astroquery.readthedocs.io/) & [Astropy](https://www.astropy.org/) — Python libraries
- [raylib](https://www.raylib.com/) — C++ graphics library
- 🎵 Interstellar OST by Hans Zimmer (for educational demo only)

---

## 📜 License

This project is open source under the **MIT License**.  
Feel free to fork and build upon it for educational purposes.

---

## 🙌 Connect

If you found this useful or have suggestions for improvement, feel free to:

- Open an issue on GitHub
- Connect with me on [LinkedIn](https://www.linkedin.com/in/wasiq-azeem-730215367/)

---

> 🚀 “The important thing is not to stop questioning. Curiosity has its own reason for existing.” – Einstein
