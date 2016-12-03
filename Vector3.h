#pragma once

class Vector3{
    friend class Wall;
public:
    Vector3() : x_(0.0), y_(0.0), z_(0.0) {}
    Vector3(float xyz) : x_(xyz), y_(xyz), z_(xyz) {}
    Vector3(float x, float y, float z) : x_(x), y_(y), z_(z) {}
    ~Vector3() {}

    void set(float xyz) { x_ = y_ = z_ = xyz; }
    void set(float x, float y, float z) { x_ = x; y_ = y; z_ = z; }

    void setX(float x) { x_ = x; }
    void setY(float y) { y_ = y; }
    void setZ(float z) { z_ = z; }

    float getX() { return x_; }
    float getY() { return y_; }
    float getZ() { return z_; }

    Vector3 operator=(const Vector3 vec);
    Vector3 operator-(const Vector3 vec);
    Vector3 operator+(const Vector3 vec);
    Vector3 operator*(const Vector3 vec);
    bool operator<(const Vector3 vec);
    bool operator<=(const Vector3 vec);
    bool operator>(const Vector3 vec);
    bool operator>=(const Vector3 vec);
    bool operator==(const Vector3 vec);

    void cross(Vector3 vec0, Vector3 vec1);

    float length();
    void normalize();
    void rotate(Vector3 r);

private:
    float x_, y_, z_;
};
