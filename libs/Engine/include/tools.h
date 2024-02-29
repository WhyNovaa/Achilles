#pragma once

#include <cmath>
#include <string>
#include <utility>
#include <vector>

/// ������� �������� � ���. ������������

class vec {
   public:
    double x = 0, y = 0;
    // ��� � ������, � �����, �� ����. ������ ���������� ������ ���������� ���� ��� ��������

    vec(double _x, double _y) : x(_x), y(_y){};

    vec operator+(vec vect) {
        return vec(x + vect.x, y + vect.y);
    }

    vec operator-(vec vect) {
        return vec(x - vect.x, y - vect.y);
    }

    double operator*(vec vect) {
        return x * vect.x + y * vect.y;
    }

    vec operator*(double k) {
        return vec(x * k, y * k);
    }

    vec operator/(double k) {
        return vec(x / k, y / k);
    }

    double length() {
        return std::sqrt(x * x + y * y);
    }

    vec cord(int width, int height) const;  // �������������� �� ���� ��������� � ����

    vec anticord(int width, int height) const;  // ��������
};

class line {
   public:
    vec d1, d2;  // ��� ��������� ���� �������� (�� � ���, � ��� � � ��� �������� - ����� ���������,
                 // ������ ��� ����� ����� ������ - �������.

    line(vec p1, vec p2) : d1(p1), d2(p2){};

    line move(vec vector);
    vec norm();  // ��������� ������� � �����������
};

// ����������� ���� ������� ��� ������������ ����������

double Distance(vec p1, vec p2);

double Distance(vec dot, line line);  // ���������� �� ����� �� �������

double SignedDistance(vec dot, line line);  // �������� ���������� �� ����� �� �������(������)

inline double Distance(line line, vec dot) {
    return Distance(dot, line);
}

double Distance(
    line l1, line l2);  // ���������� �� ������� �� ������� (�.� ����������� ����� �������, ������
                        // �������� ����������� ������� �������, � ����� - �������

bool IsIntersect(line l1, line l2);  // ������������ �� �������

/// ����� ��������� - ������. ����� ������� ��� ��� �������� ����� (�� ��� ����� ����� �����������
/// ��� ��������������� ���������); �������� � ���� ����� ��������� (�����), ����� ������� ��������

class Object {
   private:
    friend class Engine;
    vec basepoint_;
    std::vector<line> polygons_;

   public:
    void move(vec vector);

    explicit Object(std::vector<line> polygons) : basepoint_(0, 0), polygons_(std::move(polygons)) {
    }

    explicit Object(vec basepoint, std::vector<line> polygons);
};

// ����: ������� �������� ��������, ���� �������� ������� � ��� �������� (������������ basepoint). �
// � ������ ������� ������ ��������� �������� � basepoint. Load ���� ����� ��� ��������...