# 🚢 Titanic-II (OpenGL C++ Project)

## 📌 Overview  
**Titanic-II** is a **C++ OpenGL simulation** that visually represents a ship scene using **GLUT (OpenGL Utility Toolkit)**. It includes animated elements like the **ship movement, moonlight effects, water waves, and particle-based smoke simulation**.  

## 🎯 Features  
✅ **Real-time animation** of a ship using OpenGL  
✅ **User interaction** via keyboard and mouse (move ship, toggle lights, full-screen mode)  
✅ **Particle effects** for smoke simulation  
✅ **Dynamic lighting and color rendering** for a realistic effect  
✅ **GLUT-based window handling and user input support**  

## 🛠 Technologies Used  
- **C++** (Core programming language)  
- **OpenGL** (Graphics rendering)  
- **GLUT (OpenGL Utility Toolkit)** (User input, window management)  
- **GLU (OpenGL Utility Library)** (Higher-level OpenGL functions)  
- **Windows API** (For system-level operations)  

## 🚀 Installation & Setup  
### 1️⃣ Clone this repository  
```bash
git clone https://github.com/yourusername/Titanic-OpenGL-Simulation.git  
cd Titanic-OpenGL-Simulation  
```
### 2️⃣ Install OpenGL and GLUT
Windows: Install freeglut and add it to your compiler’s library
Linux: Install using:
```bash
sudo apt-get install freeglut3 freeglut3-dev  
sudo apt-get install binutils-gold
```
Mac: Install via Homebrew:
```bash
brew install freeglut
```
### 3️⃣ Compile & Run
Use g++ or Code::Blocks:
```bash
g++ main.cpp -o titanic -lGL -lGLU -lglut  
./titanic
```
Or open titanicII.cbp in Code::Blocks and run the project.

## 📂 Project Structure
- main.cpp – Core OpenGL simulation code
- titanicII.cbp – Code::Blocks project file
- README.md – Documentation
- .gitignore – Excludes compiled binaries

## 📜 License
This project is licensed under the MIT License.
