# Computer Graphics
## Photorealistic Path Tracing Renderer

## Path Tracing
Path tracing is a computational expensive operation that simulates light rays' interaction with physical world.
We trace rays from camera to the geometry in the world and eventually back to
the light sources.

## Code Optimizations
Compiler optimization: `-O3` - about 20 times speed up
parallel rendering with OpenMP: '-fopenmp' - scales to the number of cores.
GPU programming: OpenCL GPU ray tracing with output to OpenGL framebuffer.