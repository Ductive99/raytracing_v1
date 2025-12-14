# Raytracing_v1

This project is part of the 42 curriculum. **MiniRT** is a simple ray tracer written in C.
<br>
The goal is to render simple 3D scenes using basic ray-tracing techniques, producing realistic lighting and shadows from scratch.

## 🎯 Objectives

* Parse a scene description file (`.rt`)
* Render images using a minimal ray-tracing pipeline
* Implement:

  * Rays, intersections, normals
  * Ambient, diffuse, and specular lighting
  * Shadows
  * Reflection (optional bonus)
* Display the rendered image in a window (MiniLibX)

## 🧩 Supported Scene Elements

* **Cameras**
* **Lights**
* **Objects:**
* **Sphere**
* **Plane**
* **Cylinder**
* (Additional objects in bonus)

## 🛠️ Technologies

* **C**
* **MiniLibX** for windowing and pixel rendering
* No external libraries for math or rendering: everything is implemented manually

## 📦 Installation

```bash
# Clone the repository
git clone <repository_url> raytracing_v1
cd raytracing_v1

# Compile
make

# Run with a scene file
./miniRT test/test_complete.rt
```

## 🎮 Controls

- **ESC** : Quit the program
- **Red X** : Close the window and quit

## 📁 Example Scene

```
A 0.2 255,255,255
C 0,0,0 0,0,1 70
L 10,10,10 0.8 255,255,255
sp 0,0,20 5 255,0,0
```

## 📂 Project Structure

```
raytracing_v1/
├── src/
│   ├── main.c              # Entry point
│   ├── mlx/                # MLX window management
│   │   ├── init_mlx.c      # MLX initialization
│   │   ├── hooks.c         # Event handlers
│   │   ├── cleanup.c       # Memory cleanup
│   │   ├── put_pixel.c     # Pixel manipulation
│   │   └── render.c        # Rendering (test pattern)
│   ├── parser/             # Scene file parsing
│   └── utils/              # Utility functions
├── inc/
│   ├── minirt.h            # Main header
│   └── structs.h           # Data structures
├── test/                   # Test scene files
├── Makefile
└── MLX_INTEGRATION.md      # MLX integration guide
```

## 👥 Team Division

- **Parsing**: Complete ✅
- **MLX Integration**: Complete ✅
- **Raytracing Math**: In progress ⏳

See `MLX_INTEGRATION.md` for detailed integration guide.

## 🚀 Current Status

- ✅ Scene file parsing (.rt files)
- ✅ MLX window and image buffer setup
- ✅ Event handling (ESC, close button)
- ✅ Pixel manipulation functions ready
- ✅ Test pattern rendering
- ⏳ Raytracing calculations (to be implemented)

## 📝 Next Steps

1. Implement ray generation from camera
2. Calculate ray-object intersections
3. Implement lighting calculations
4. Replace `render_test_pattern()` with actual raytracing

## 🔧 Development

```bash
# Recompile everything
make re

# Clean object files
make clean

# Remove all generated files
make fclean

# Test with different scenes
./miniRT test/test.rt
./miniRT test/test_complete.rt
```

## 📚 Resources

- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Ray Tracing in One Weekend](https://raytracing.github.io/)
- MLX_INTEGRATION.md for implementation details
