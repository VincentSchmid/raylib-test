# raylib-3d test
Started to work on some basic framework in c++, to be able to create a 3d game using raylib. But ditched the project, when I found that PBR (Physical Based Rendering) was not properly implemented in raylib, or atleast I did not find the example accessible. Raylib is a lot of fun and I might come back to it at a later stage.  
  
What the project currently has is:  
- camera that works using normalized edge-scroll (moving the mouse to the edge moves the camera in that direction)    
- Asset loading class, where 3d assets are loaded  
- A Game Map class that holds an array and can draw the array in the drawing phase of the gameloop  
- GameSettings class that hold all Game Parameters  
- Some kind of input / controlls handling class  
- Main class that brings everything together and draws the map aswell as a 3d model.  
- some free itch.io game assets converted properly to glb so they can be used with ray-lib.  
- Python script to batch convert 3d meshes using blender.
