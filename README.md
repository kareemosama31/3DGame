# 3D Game – OpenGL Amusement Park

This project is a simple 3D scene built with C++ and [OpenGL](https://www.opengl.org/). It creates a small
amusement park environment where a player character can move around using the
keyboard.

## Features

- Uses GLUT to open a window titled **"Amusement Park"** and render a 3D scene.
- Keyboard controls allow moving the player along the X, Y and Z axes.
- Arrow keys rotate the camera to view the scene from different angles.
- Demonstrates basic lighting and shading with `glEnable` and `glShadeModel`.

## Building

This project was originally created in Visual Studio. On systems with GCC and
OpenGL/GLUT installed you can attempt to build it with:

```bash
g++ OpenGL3DTemplate.cpp -o game -lglut -lGLU -lGL
```

Make sure the appropriate development packages for OpenGL and GLUT are
available on your system.

## Running

If compilation succeeds, run the program with:

```bash
./game
```

Use the defined keyboard controls to move the player and adjust the camera.

## License

This project does not specify a license.

