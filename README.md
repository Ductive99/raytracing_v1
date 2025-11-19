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

## 📁 Example Scene

```
A 0.2 255,255,255
C 0,0,0 0,0,1 70
L 10,10,10 0.8 255,255,255
sp 0,0,20 5 255,0,0
```
