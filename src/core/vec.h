#pragma once

#include <cmath>
#include <iostream>

class vec2 {
	public:
		vec2() : e{ 0, 0 } {}
		vec2(double x, double y) : e{ x, y } {}

		double x() const { return e[0]; }
		double y() const { return e[1]; }

		vec2 operator-() const { return vec2(-e[0], -e[1]); }
		vec2 operator+=(const vec2& v) { 
			e[0] += v.e[0];
			e[1] += v.e[1];
			return *this;
		}
		vec2 operator*=(const double t) { 
			e[0] *= t;
			e[1] *= t;
			return *this;
		}
		vec2 operator/=(const double t) { 
			e[0] /= t;
			e[1] /= t;
			return *this;
		}
		double length_squared() const {
			return e[0] * e[0] + e[1] * e[1];
		}
		double length() const {
			return sqrt(length_squared());
		}
	public:
		double e[2];
};

inline std::ostream& operator<<(std::ostream& out, const vec2& v) {
	return out << "(" << v.e[0] << "," << v.e[1] << ")\n";
}

inline vec2 operator+(const vec2& u, const vec2& v) {
	return vec2(u.e[0] + v.e[0], u.e[1] + v.e[1]);
}

inline vec2 operator+(const vec2& u, const double c) {
	return vec2(u.e[0] + c, u.e[1] + c);
}

inline vec2 operator-(const vec2& u, const vec2& v) {
	return vec2(u.e[0] - v.e[0], u.e[1] - v.e[1]);
}

inline vec2 operator-(const vec2& u, const double c) {
	return vec2(u.e[0] - c, u.e[1] - c);
}

inline vec2 operator*(const double c, const vec2& u) {
	return vec2(u.e[0] * c, u.e[1] * c);
}

inline vec2 operator*(const vec2& u, const double c) {
	return c * u;
}

inline vec2 operator/(const vec2& u, const double c) {
	return (1 / c) * u;
}

inline double dot(const vec2& u, const vec2& v) {
	return u.e[0] * v.e[0] + u.e[1] * v.e[1]; 
}

inline double cross(const vec2& u, const vec2& v) {
	return u.e[0] * v.e[1] - u.e[1] * v.e[0]; 
}

inline vec2 unit_vector(vec2 v) {
	return v / v.length();
}

using point2 = vec2;

class vec3 {
	public:
		vec3() : e{ 0, 0, 0 } {}
		vec3(double x, double y, double z) : e { x, y, z } {}

		double x() const { return e[0]; }
		double y() const { return e[1]; }
		double z() const { return e[2]; }

		vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
		double operator[](int i) const { return e[i]; }
		double& operator[](int i) { return e[i]; }

		vec3& operator+=(const vec3& v) {
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}
		vec3& operator*=(const double t) {
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}
		vec3& operator/=(const double t) {
			return *this *= 1 / t;
		}

		double length_squared() const {
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}

		double length() const {
			return sqrt(length_squared());
		}
    public:
        double e[3];
};

using point3 = vec3;
using color3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << "(" << v.e[0] << "," << v.e[1] << "," << v.e[2] << ")\n";
}

inline vec3 operator+(const vec3& v, const vec3& u) {
	return vec3(v.e[0] + u.e[0], v.e[1] + u.e[1], v.e[2] + u.e[2]);
}

inline vec3 operator+(const vec3& v, double c) {
	return vec3(v.e[0] + c, v.e[1] + c, v.e[2] + c);
}

inline vec3 operator-(const vec3& v, const vec3& u) {
	return vec3(v.e[0] - u.e[0], v.e[1] - u.e[1], v.e[2] - u.e[2]);
}

inline vec3 operator-(const vec3& v, double c) {
	return vec3(v.e[0] - c, v.e[1] - c, v.e[2] - c);
}

inline vec3 operator*(const vec3& v, const vec3& u) {
	return vec3(v.e[0] * u.e[0], v.e[1] * u.e[1], v.e[2] * u.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
	return (1 / t) * v;
}

inline double dot(const vec3& v, const vec3& u) {
	return v.e[0] * u.e[0]
		+ v.e[1] * u.e[1]
		+ v.e[2] * u.e[2];
}

inline vec3 cross(const vec3& v, const vec3& u) {
	return vec3(v.e[1] * u[2] - v.e[2] * u[1],
		v.e[2] * u[0] - v.e[0] * u[2],
		v.e[0] * u[1] - v.e[1] * u[0]);
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}


