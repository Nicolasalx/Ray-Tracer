# Raytracer

## Primitive

- Sphere
- Plane
- Triangle
- Cone
- Cylinder

## Material

- Lambertian
- Metal
- Dielectric
- Chess Board
- Diffuse Light

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


