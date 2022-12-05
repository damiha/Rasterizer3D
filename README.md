### Version 0.0.3

- added new scenes
- extended Mesh-Loader for obj.format
- added Gouraud shading
- implemented perspective correct implementation

![flat shading fix](/dev%20documentation/Flat%20shading%20Bug%20fix.png)
<figcaption>Phong Modell after bug fix</figcation>

![gouraud shading](/dev%20documentation/Gouraud%20Shading.png)
<figcaption>Gouraud Shading</figcation>

### Version 0.0.2

- added ImGui to project
- select different render modes (Phong, ZBuffer, WireFrame) and shading types (flat, gouroud, phong)

![zbuffer shading](/dev%20documentation/ZBuffer%20and%20GUI.png)

<figcaption> ZBuffer Render Mode selected</figcaption>

<br>

### Version 0.0.1

- added flat shading support
- currently runs at approx. 30 FPS

![flat shading diffuse](/dev%20documentation/Flat%20Shading%20Diffuse.png)

<figcaption>Flat shading with ambient and diffuse term</figcaption>

![flat shading specular](/dev%20documentation/Flat%20Shading%20Specular.png)

<figcaption>Flat shading with ambient, diffuse and specular term</figcaption>
<br>
Note: Shadows are not yet implemented. The handle of the Utah teapot is illuminated even though it should not be.