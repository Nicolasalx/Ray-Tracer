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

- Lambertian
    - albedo -> Color01
- Metal
    - diffusion -> Color01
    - reflection -> double [0, 1]
- Dielectric
    - refraction -> [0, 1]
- Diffuse Light
    - emit -> Color01

## Texture

- ChessBoar
    - scale -> double
    - color1 -> Color01
    - color2 -> Color01
- Image
    - path -> std::string
