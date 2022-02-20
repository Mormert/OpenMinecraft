# Open Minecraft

Open Minecraft was initially written in OpenGL 3.3, but was ported to OpenGL ES 3.0 to ease the porting to WebGL 2. Now, it runs on OpenGL ES 3.0 on desktop, and WebGL 2 on the web.

## Web Demo
Using Emscripten, Open Minecraft has a WebAssembly port. [Click here](https://open-mc.mormert.com).

### Terrain generation using the FastNoise C++ library.
![Terrain Generation](https://raw.githubusercontent.com/Mormert/OpenMinecraft/master/SCREENSHOT2.PNG)

### Building and digging
![Building](https://raw.githubusercontent.com/Mormert/OpenMinecraft/master/SCREENSHOT3.PNG)

### Insane amount of blocks rendering
Rendering millions of individual blocks at an acceptable framerate using instanced rendering.
![Block Rendering](https://raw.githubusercontent.com/Mormert/OpenMinecraft/master/SCREENSHOT.PNG)

### Dependencies & building

Open Minecraft is very easy to build, using CMake with no external dependencies.

#### Building to WebAssembly using Emscripten
Requires the Emscripten SDK, and a shell with the Emscripten environment set-up.
```shell
mkdir build
cd build
emcmake cmake .. -DBUILD_EMSCRIPTEN=ON
emmake make
```