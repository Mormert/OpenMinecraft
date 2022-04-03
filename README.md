# Open Minecraft

Open Minecraft was initially written in OpenGL 3.3, but was ported to OpenGL ES 3.0 to ease the porting to WebGL 2. Now, it runs on OpenGL ES 3.0 on desktop, and WebGL 2 on the web.

## Cross-Play Networking Support
Using Node.js + Socket.IO on the server and an abstraction layer over the client-side Socket.IO (C++ and JavaScript) allows for cross-play between the browser and native platforms such as Mac, Linux and Windows.

## Web Demo
Using Emscripten, Open Minecraft has a WebAssembly port. [Click here](https://open-mc.mormert.com).

### Terrain Generation using the FastNoise C++ Library.
![Terrain Generation](https://raw.githubusercontent.com/Mormert/OpenMinecraft/master/SCREENSHOT2.PNG)

### Building and Digging
![Building](https://raw.githubusercontent.com/Mormert/OpenMinecraft/master/SCREENSHOT3.PNG)

### Instanced block rendering
Rendering millions of individual blocks at an acceptable framerate using instanced rendering.
![Block Rendering](https://raw.githubusercontent.com/Mormert/OpenMinecraft/master/SCREENSHOT.PNG)

### Dependencies & Building

Open Minecraft is very easy to build, using CMake with no external dependencies.

#### Building to WebAssembly using Emscripten
Requires the Emscripten SDK, and a shell with the Emscripten environment set-up.
```shell
mkdir build
cd build
emcmake cmake .. -DBUILD_EMSCRIPTEN=ON
emmake make
```
