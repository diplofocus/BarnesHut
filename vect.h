#ifndef __VECT_H__
#define __VECT_H__

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;
class Vect
{
 public:
  double x,y,z;

  Vect()
    {
     this->x = 0;
     this->y = 0;
     this->z = 0;
    }

  Vect(double _x, double _y, double _z)
    {
      this->x = _x;
      this->y = _y;
      this->z = _z;
    }

 
  Vect operator-(const Vect& v)
  {
    Vect r;
    r.x = this->x - v.x;
    r.y = this->y - v.y;
    r.z = this->z - v.z;
    return r;
  }
 
  Vect operator+(const Vect& v)
  {
    Vect r;
    r.x = this->x + v.x;
    r.y = this->y + v.y;
    r.z = this->z + v.z;
    return r;
  }

  Vect operator+=(const Vect& v)
  {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
  }
  
  Vect operator*=(const double& scalar)
  {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
  }

  Vect operator/=(const double& scalar)
  {
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
  }

  Vect operator*(const double& scalar)
    {
      Vect re;
      re.x = this->x * scalar;
      re.y = this->y * scalar;
      re.z = this->z * scalar;
      return re;
    }

  Vect operator/(const double& scalar)
  {
    Vect re;
    re.x = this->x / scalar;
    re.y = this->y / scalar;
    re.z = this->z / scalar;
    return re;
  }

  double Int()
  {
    return sqrt(this->x * this->x + this->y * this->y + this->z + this->z);
  }
};
#endif
