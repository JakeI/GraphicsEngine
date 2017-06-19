# GraphicsEngine
Scene and Entity based Graphics Engine using opengGL and c++
This is a work in progress but eventually it will be a two and three dimentional graphics engine.

## Current features
* Scenes (fundamental drawing objecs) can be organised in a Tree
* Layouts resize the scenes based on the sreensize.
* User Input (throu the WinApi) taken in seprate thread and and processed by a drawing thread _//TODO: make the eventqueue thread save_
* Stabel frame rate
* A resource management system
* Wrappers/loaders for basic OpenGL data (meshes, models, textures)
* Component based entity system
* Animators allow dynamic blending of values _//TODO: add more blend functions_
* Font rendering 
  * using signed-distance-field texture atlases (of character images)
  * all parameters are read from *.fnt files
  * stylable features: body (color and width), edge (color and width), dropshaddow (offset, width and color), background color
* An example program (containgin text-rendering, general rendering (showcasing the caotic double pendulum), texture rendering, leyouts, scenes) 
