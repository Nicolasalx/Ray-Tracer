# Raytracer

## Primitive

- Sphere
    - position (x, y, z) -> Vector3D
    - rotation (x, y, z) -> Vector3D
    - radius -> double
    - material -> IMaterial

- Plane
- Triangle
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
- ChessBoar
    - scale -> double
    - color1 -> Color01
    - color2 -> Color01

### Builder

```cpp
    void createObject(const Math::Vector3D &translation, const Math::Vector3D &rotation, const Param &... param)
    void applyMaterial(const std::shared_ptr<Rt::IMaterial> material)
    std::shared_ptr<Rt::IObject> getResult()
```

- Create a Sphere:
    ```cpp
    void createObject(const Math::Vector3D &translation, const Math::Vector3D &rotation, const double &radius)
    ```

- Create a Plane:
    ```cpp
    void createObject(const Math::Vector3D &translation, const Math::Vector3D &rotation, const Math::Point3D &pos, const Math::Vector3D &u, const Math::Vector3D &v)
    ```

- Create a Triangle:
    ```cpp
    void createObject(const Math::Vector3D &translation, const Math::Vector3D &rotation, const Math::Point3D &origin, const Math::Point3D &pointA, const Math::Point3D &pointB)
    ```

- Create a Cone:
    ```cpp
    void createObject(const Math::Vector3D &translation, const Math::Vector3D &rotation, double radius, double length)
    ```

- Create a Cylinder:
    ```cpp
    void createObject(const Math::Vector3D &translation, const Math::Vector3D &rotation, double radius, double length)
    ```

### Material Factory


