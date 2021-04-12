# GPGPU_with_OpenGL

# building
use cmake to build

# Details
This application adds two vectors of size N together by using the powers of the GPU, accessed through OpenGL. 

Data transfer is done with textures, there is one texture for each of the input vectors and one output texture.
The output texture is attached to a framebuffer object for offscreen rendering. 
The textures use 4 color channel RGBA, with a 8 bit floating point value per color. I only used OpenGL commands available in OpenGL ES 2.0.

The actual computation is performed in the fragment shader. There is a one to one mapping from texels to pixels. 

