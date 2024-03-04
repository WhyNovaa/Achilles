#pragma once

#include <cmath>
#include <string>
#include <utility>
#include <vector>

extern inline const double PH_CONST_G = 9.81;
extern inline const double PH_CONST_COLLISION_PRES = 0.3;

/// ������� �������� � ���. ������������

class vec {
   public:
    double x = 0, y = 0;

    // ��� � ������, � �����, �� ����. ������ ���������� ������ ���������� ���� ��� ��������

    vec() : x(0), y(0) {
    }

    vec(double _x, double _y) : x(_x), y(_y) {
    }

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

    vec cord(int width, int height) const;  // �������������� �� ���� ��������� � ����

    vec anticord(int width, int height) const;  // ��������
};

class line {
   public:
    vec d1, d2;  // ��� ��������� ���� �������� (�� � ���, � ��� � � ��� �������� - ����� ���������,
                 // ������ ��� ����� ����� ������ - �������.

    line(const vec& p1, const vec& p2) : d1(p1), d2(p2){};

    line move(const vec& vector) const;
    vec norm() const;  // ��������� ������� � �����������

    bool operator==(const line& other) const {
        return d1 == other.d1 && d2 == other.d2;
    }
};

// ����������� ���� ������� ��� ������������ ����������

double Distance(const vec& p1, const vec& p2);

double Distance(const vec& dot, const line& line);  // ���������� �� ����� �� �������

double SignedDistance(
    const vec& dot, const line& line);  // �������� ���������� �� ����� �� �������(������)

inline double Distance(const line& line, const vec& dot) {
    return Distance(dot, line);
}

double Distance(const line& l1, const line& l2);  // ���������� �� ������� �� ������� (�.�
                                                  // ����������� ����� �������,
// ������
// �������� ����������� ������� �������, � ����� - �������

bool IsIntersect(const line& l1, const line& l2);  // ������������ �� �������

vec Proection(const vec& what, const line& axis);

vec Proection(const vec& what, vec vaxis);

/// ����� ��������� - ������. ����� ������� ��� ��� �������� ����� (�� ��� ����� ����� �����������
/// ��� ��������������� ���������); �������� � ���� ����� ��������� (�����), ����� ������� ��������

class Object {
   protected:
    friend class Engine;
    vec basepoint_;
    std::vector<line> polygons_;

   public:
    explicit Object(const vec& basepoint, const std::vector<line>& polygons)
        : basepoint_(basepoint), polygons_(polygons) {
    }

    virtual ~Object() = default;
};

// ����: ������� �������� ��������, ���� �������� ������� � ��� �������� (������������ basepoint). �
// � ������ ������� ������ ��������� �������� � basepoint. Load ���� ����� ��� ��������...

class MoveableObject : public Object {
   public:
    vec resultantForce;
    vec velocity;
    double mass = 0;
    vec magicForces;
    double frictionCoef = 0;

   public:
    void move(const vec& vector);

    void SumNormalForces(const vec& basepoint, const std::vector<line>& polygons);

    explicit MoveableObject(const vec& basepoint, const std::vector<line>& polygons)
        : Object(basepoint, polygons) {
    }

    explicit MoveableObject(const vec& basepoint, const std::vector<line>& polygons, double m)
        : Object(basepoint, polygons), mass(m) {
    }
};