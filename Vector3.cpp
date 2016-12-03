#include "stdafx.h"
#include "Vector3.h"

Vector3 Vector3::operator=(const Vector3 vec){
    x_ = vec.x_;
    y_ = vec.y_;
    z_ = vec.z_;
    return *this;
}

Vector3 Vector3::operator-(const Vector3 vec){
    return Vector3(x_ - vec.x_, y_ - vec.y_, z_ - vec.z_);
}
Vector3 Vector3::operator+(const Vector3 vec){
    return Vector3(x_ + vec.x_, y_ + vec.y_, z_ + vec.z_);
}
Vector3 Vector3::operator*(const Vector3 vec){
    return Vector3(x_ * vec.x_, y_ * vec.y_, z_ * vec.z_);
}

bool Vector3::operator<(const Vector3 vec){
    return (x_ < vec.x_ && y_ < vec.y_ && z_ < vec.z_);
}
bool Vector3::operator<=(const Vector3 vec){
    return (x_ <= vec.x_ && y_ <= vec.y_ && z_ <= vec.z_);
}
bool Vector3::operator>(const Vector3 vec){
    return (x_ > vec.x_ && y_ > vec.y_ && z_ > vec.z_);
}
bool Vector3::operator>=(const Vector3 vec){
    return (x_ >= vec.x_ && y_ >= vec.y_ && z_ >= vec.z_);
}
bool Vector3::operator==(const Vector3 vec){
    return (x_ == vec.x_ && y_ == vec.y_ && z_ == vec.z_);
}

void Vector3::cross(Vector3 vec0, Vector3 vec1){
    x_ = vec0.y_ * vec1.z_ - vec0.z_ * vec1.y_;
    y_ = vec0.z_ * vec1.x_ - vec0.x_ * vec1.z_;
    z_ = vec0.x_ * vec1.y_ - vec0.y_ * vec1.x_;
}

float Vector3::length(){
    return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}
void Vector3::normalize(){
    float len = this->length();
    x_ /= len;
    y_ /= len;
    z_ /= len;
}
void Vector3::rotate(Vector3 r){
    r = r * (PI / 180);

    float newX = x_ * cos(r.y_) * cos(r.z_) + y_ * (-cos(r.x_) * sin(r.z_) + sin(r.x_) * sin(r.y_) * cos(r.z_)) + z_ * (sin(r.x_) * sin(r.z_) + cos(r.x_) * sin(r.y_) * cos(r.z_));
    float newY = x_ * cos(r.y_) * sin(r.z_) + y_ * (cos(r.x_) * cos(r.z_) + sin(r.x_) * sin(r.y_) * sin(r.z_)) + z_ * (-sin(r.x_) * cos(r.z_) + cos(r.x_) * sin(r.y_) * sin(r.z_));
    float newZ = -x_ * sin(r.y_) + y_ * sin(r.x_) * cos(r.y_) + z_ * cos(r.x_) * cos(r.y_);
}
