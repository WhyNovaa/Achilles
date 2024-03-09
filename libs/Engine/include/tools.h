#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

extern inline const double PH_CONST_G = 9.81;
extern inline const double PH_CONST_COLLISION_PRES = 0.05;

// ----------------------------------------------------------------------
// vec
// ----------------------------------------------------------------------
// ����� vec ��������� � ���� ������� � �����. ��� �������������� �
// ���������� sfml ������������ ����� cord(int width, int height) � �����
// anticord(int width, int height) - �������.
class vec {
   public:
    double x = 0;
    double y = 0;

    vec() : x(0), y(0) {};

    vec(double _x, double _y) : x(_x), y(_y) {};

    vec operator+(const vec& vect) const {
        return vec(x + vect.x, y + vect.y);
    }

    vec operator-(const vec& vect) const {
        return vec(x - vect.x, y - vect.y);
    }

    double operator*(const vec& vect) const {
        return x * vect.x + y * vect.y;
    }

    vec operator*(double k) const {
        return vec(x * k, y * k);
    }

    vec operator/(double k) const {
        return vec(x / k, y / k);
    }

    bool operator==(const vec& other) const {
        return abs(x - other.x) <= 0.0001 && abs(y - other.y) <= 0.0001;
    }

    double length() const {
        return std::sqrt(x * x + y * y);
    }

    vec cord(int width, int height) const;  // convert cords to sfml

    vec anticord(int width, int height) const;  // convert back
};

// ----------------------------------------------------------------------
// line
// ----------------------------------------------------------------------
// ����� line ��������� � ���� �������. ������ ����� ������. ����� norm()
// ���������� ������ ��������� ������� � �������.
class line {
   public:
    vec p1, p2; // end points of a segment

    line(const vec& point1, const vec& point2) : p1(point1), p2(point2){};

    line move(const vec& vector) const;

    vec norm() const;  // ��������� ������� � �������/������

    bool operator==(const line& other) const {
        return p1 == other.p1 && p2 == other.p2;
    }
};

// ���������� ����� ����� �������
double Distance(const vec& p1, const vec& p2);

// ���������� ����� ������(��������) � ������
double Distance(const vec& point, const line& segment);

// ������ ����������
inline double Distance(const line& segment, const vec& point) {
    return Distance(point, segment);
}

// �������� ���������� �� ����� �� �������(������)
double SignedDistance(const vec& point, const line& segment);

// ���������� �� ������� �� ������� (�.� ����������� ������ �������, ������ ��������
// ����������� ������ �������, ����� �������)
double Distance(const line& l1, const line& l2);  

// ������������ �� �������
bool IsIntersect(const line& l1, const line& l2);  

vec Projection(const vec& v, const line& axis);

vec Projection(const vec& v, vec axis);

// ----------------------------------------------------------------------
// Object
// ----------------------------------------------------------------------
// ����� Object ��������� � ���� ������� ��� ������� (����� ���������).
// ������ ���������� basepoint'a (������ ������, �� ���� �����
// ����������� �������). ����� �������� � ���� ����� ��������� (�����) -
// polygons, ����� ������� ��������.
class Object {
   public:  // TODO (later): change visability for members - bpoint & polygons 
    friend class Engine;

    explicit Object(const vec& _basepoint, const std::vector<line>& _polygons)
        : basepoint(_basepoint), polygons(_polygons) {
    }

    virtual ~Object() = default;

    vec basepoint;
    std::vector<line> polygons;
};

// ----------------------------------------------------------------------
// MoveableObject
// ----------------------------------------------------------------------
// ����� MoveableObject ��������� � ���� ������� ��� �������, ����������
// � ��������. �������� ������ Object. ������ ���� ����������� ���
// ���������� ������: resultantForce, velocity, magicForces, mass,
// frictionCoef. ����� move(vector) �������� basepoint �� ������ vector.
class MoveableObject : public Object {
   public:
    vec resultantForce;
    vec velocity;
    vec magicForces;
    double mass = 0;
    double frictionCoef = 1;

   public:
    void move(const vec& vector);

    void sumNormalForces(Object* obj);

    explicit MoveableObject(const vec& basepoint, const std::vector<line>& polygons)
        : Object(basepoint, polygons) {
    }

    explicit MoveableObject(const vec& basepoint, const std::vector<line>& polygons, double m)
        : Object(basepoint, polygons), mass(m) {
    }
};