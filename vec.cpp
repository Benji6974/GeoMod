
#include <cmath>

#include "vec.h"

float distance( const Point& a, const Point& b )
{
    return length(a - b);
}

float distance2( const Point& a, const Point& b )
{
    return length2(a - b);
}

Point center( const Point& a, const Point& b )
{
    return Point((a.x + b.x) * 0.5f, (a.y + b.y) * 0.5f, (a.z + b.z) * 0.5f);
}

Vector operator- ( const Point& a, const Point& b )
{
    //~ return make_vector(a.x - b.x, a.y - b.y, a.z - b.z);
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector operator- ( const Vector& v )
{
    return Vector(-v.x, -v.y, -v.z);
}

Point operator+ ( const Point& a, const Vector& v )
{
    return Point(a.x + v.x, a.y + v.y, a.z + v.z);
}

Point operator+ ( const Vector& v, const Point& a )
{
    return a + v;
}

Point operator- ( const Vector& v, const Point& a )
{
    return a + (-v);
}

Point operator- ( const Point& a, const Vector& v )
{
    return a + (-v);
}

Vector operator+ ( const Vector& u, const Vector& v )
{
    return Vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector operator- ( const Vector& u, const Vector& v )
{
    return Vector(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vector operator* ( const float k, const Vector& v )
{
    return Vector(k * v.x, k * v.y, k * v.z);
}

Vector operator* ( const Vector& v, const float k )
{
    return k * v;
}

Vector operator/ ( const Vector& v, const float k )
{
    float kk= 1 / k;
    return kk * v;
}

Vector normalize( const Vector& v )
{
    float kk= 1 / length(v);
    return kk * v;
}

Vector cross( const Vector& u, const Vector& v )
{
    return Vector(
        (u.y * v.z) - (u.z * v.y),
        (u.z * v.x) - (u.x * v.z),
        (u.x * v.y) - (u.y * v.x));
}

bool vec2i::operator ==(const vec2i &b) const
{
    return this->x == b.x && this->y == b.y;
}

float length( const vec2& v )
{
    return sqrt(length2(v));
}

float length2( const vec2& v )
{
    return v.x * v.x + v.y * v.y;
}


vec2 normalize( const vec2& v )
{
    float kk= 1 / length(v);
    return v * kk;
}

vec2 operator+ ( const vec2& u, const vec2& v )
{
    return vec2(u.x + v.x,u.y + v.y);
}

vec2 operator- ( const vec2& u, const vec2& v )
{
    return vec2(u.x - v.x,u.y - v.y);
}

vec2 operator/ ( const vec2& u, const vec2& v )
{
    return vec2(u.x / v.x, u.y / v.y);
}

vec2 operator* ( const vec2& u, const float f )
{
    return vec2(u.x * f, u.y * f);
}

vec3 operator+ ( const vec3& u, const vec3& v )
{
    return vec3(u.x + v.x,u.y + v.y,u.z + v.z);
}

vec3 operator* ( const vec3& u, const float f )
{
    return vec3(u.x * f, u.y * f,u.z * f);
}

vec3 operator- ( const vec3& u, const vec3& v )
{
    return vec3(u.x - v.x,u.y - v.y,u.z - v.z);
}

float dot( const Vector& u, const Vector& v )
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float length( const Vector& v )
{
    return std::sqrt(length2(v));
}

float length2( const Vector& v )
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
