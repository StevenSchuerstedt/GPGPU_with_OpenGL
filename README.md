# GPGPU_with_OpenGL

# building
use cmake to build

# Details
This application adds two vectors together by using the powers of the GPU, accessed through OpenGL. 

Data transfer is done with textures, there is one texture for each of the input vectors and one output texture.
The output texture is attached to a framebuffer object. 
The textures use 4 color channel RGBA, with a 32 bit floating point value per color. The OpenGL texture target is a rectangle texture, so the texture coordinate dont need to be normalized to [0,1]. Other formats would work as well. 

The actual computation is performed in the fragment shader. There is a one to one mapping from texels to pixels. 
orthogonale projection matrix mappt koordinaten von 0.0, texSize auf -1.0, 1.0
so die OpenGL konvention für screen filling quad

glviewport??

welchen texture type benutzen? GL_RECTANGLE, GL_TEXTURE_2D, GL_LUMINANDE
bei GL_RECTANGLE werden texturkoordinaten nicht normalisiert, können also gleich vertex koordinaten sein
float rgba etc
