
🌌 Solar System Simulation
A Realistic, Data-Driven Solar System Simulation built using C++ and Python
✨ Project Overview
This project is an interactive simulation of our Solar System, built from scratch with:

C++ for graphics rendering and simulation logic (using raylib)

Python for fetching live NASA ephemeris data and generating data visualisations

It combines real-time astronomy data, intuitive controls, and immersive design to bring space closer to us.

🚀 Features
✅ Realistic orbital motions of planets
✅ Zoom in/out and move the camera view smoothly
✅ Click planets to display their names dynamically
✅ Integrated live NASA ephemeris data (RA, DEC, Delta) for Earth
✅ Graphs of Earth’s Right Ascension (RA) plotted over past 7 days using matplotlib
✅ Interstellar OST running in background for cinematic experience
✅ Modular C++ classes for Sun and Planets with scalable design

📷 Preview
<!-- replace with your actual preview image path -->

🔧 Installation & Setup
1. Clone the repository
bash
Copy
Edit
git clone https://github.com/wasiq345/SolarSystem.git
cd solar-system-simulation
2. C++ Setup
Install raylib on your system.

Compile the C++ files:

bash
Copy
Edit
g++ main.cpp -o SolarSystem -lraylib -lopengl32 -lgdi32 -lwinmm
(Modify according to your OS and IDE setup)

3. Python Dependencies
bash
Copy
Edit
pip install astroquery matplotlib astropy
4. Fetch Live Data
Run the provided Python script to fetch Earth’s live RA, DEC, and delta data:

bash
Copy
Edit
python generate_minimal_data.py
Run the plotting script to generate the RA graph:

bash
Copy
Edit
python earth_graph.py
This will save:

earth_data_minimal.txt (live data)

earth_ra.png (graph image)

5. Running the Simulation
Execute the compiled C++ executable:

bash
Copy
Edit
./SolarSystem
Ensure the data files and graph image are in the same directory as the executable for full functionality.

🎮 Controls
Action	Key(s)
Zoom In/Out	Up / Down Arrows
Move Camera	W A S D
Click on Planet	Display name
Mute Music	M
Exit Simulation	ESC

🧠 Learning Goals
Through this project I learned:

Fetching and interpreting live astronomy data using NASA APIs

Graphics rendering and event handling with raylib in C++

Designing OOP classes for scalable simulations

Integrating Python data pipelines with C++ applications

Plotting data visualisations using matplotlib

Combining science, art, and technology for immersive learning tools

💡 Future Improvements
Add planet facts database (JSON/SQLite) for each planet

Implement more detailed textures and lighting effects

Integrate LLMs as an astronomy tutor bot within the simulation

Deploy as a cross-platform standalone educational tool

🤝 Credits & References
NASA JPL Horizons API (ephemeris data)

Astroquery & Astropy (Python astronomy libraries)

raylib for C++ rendering

Interstellar OST by Hans Zimmer (for educational demo only)

📜 License
This project is open source under the MIT License. Feel free to fork and build upon it for educational purposes.

🙌 Connect
If you found this useful or have suggestions for improvement, feel free to open an issue or connect with me on Linkedin.

🚀 “The important thing is not to stop questioning. Curiosity has its own reason for existing.” – Einstein
