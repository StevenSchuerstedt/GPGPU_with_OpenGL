# GPGPU_with_OpenGL

# building
use cmake to build

# Details
This application adds two vectors of size N together by using the powers of the GPU, accessed through OpenGL. 

Data transfer is done with textures, there is one texture for each of the input vectors and one output texture.
The output texture is attached to a framebuffer object for offscreen rendering. 
The textures use 4 color channel RGBA, with a 32 bit floating point value per color. The OpenGL texture target is a rectangle texture, so the texture coordinates dont need to be normalized to [0,1]. Other formats would work as well. 

The actual computation is performed in the fragment shader. There is a one to one mapping from texels to pixels. 

