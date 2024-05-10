# Raytracer

## Primitive

- Sphere
    - position (x, y, z) -> Vector3D
    - rotation (x, y, z) -> Vector3D
    - radius -> double
    - material -> IMaterial

- Plane
    - position (x, y, z) -> Vector3D
    - rotation (x, y, z) -> Vector3D
    - height -> double
    - width -> double
    - material -> IMaterial

- Triangle
    - position (x, y, z) -> Vector3D
    - rotation (x, y, z) -> Vector3D
    - pointA -> (x, y, z) -> Point3D
    - pointB -> (x, y, z) -> Point3D
    - pointC -> (x, y, z) -> Point3D
    - material -> IMaterial

- Cone
    - position (x, y, z) -> Vector3D
    - rotation (x, y, z) -> Vector3D
    - radius -> double
    - length -> double
    - material -> IMaterial

- Cylinder
    - position (x, y, z) -> Vector3D
    - rotation (x, y, z) -> Vector3D
    - radius -> double
    - length -> double
    - material -> IMaterial

## Material

```
In the config file a material is represented like that:

materialName: Name of the material we can use in any primitive to assign at this surface.

color: The color of the material in RGB.
```

### Lambertian
    - color -> Color01
```
{ materialName = "lambertian_name"; color = { r = 0; g = 255; b = 0; }; }
```

### Metal
    - color -> Color01
    - reflection -> double [0, 1]
```
{ materialName = "metal_name"; color = { r = 0; g = 255; b = 0; }; reflection = 0.0 }
```

### Dielectric
    - reflection -> [0, 1]
```
{ materialName = "dielectric_name"; reflection = 0.0 }
```

### Diffuse Light
    - emit -> Color01
```
{ materialName = "diffuseLight"; color = { r = 255; g = 255; b = 255; multiplier = 2.0 }; }
```
The multiplier will multiply the value of r, g and b by this number to increase or decrease the color of the light.

## Texture

- ChessBoar
    - scale -> double
    - color1 -> Color01
    - color2 -> Color01
- Image
    - path -> std::string

## Object

A file who contains a list of triangles who will represent a 3d model.
```
{ filepath = "assets/panter.obj"; scale = 1.0; material = "lambertian_RANDOM"; }
```

It is composed by three parameters:

- filepath: path to the file where the model is placed.
- scale: the multiplier who represent the size of the 3d model.
- material: the material who is assigned to this model.
