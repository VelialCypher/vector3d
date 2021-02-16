#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector3d.h"

#define SMOOTH 0.00001

vector3d_t* vector3d_new(double x, double y, double z) {
	vector3d_t* vector = (vector3d_t*)malloc(sizeof(vector3d_t));

	if(NULL == vector) exit(1);
	
	vector3d_set(vector, x, y, z);

	return vector;
}

vector3d_t* vector3d_normalize(vector3d_t* vector) {
	double m = vector3d_length(vector);

	if(m > SMOOTH) {
		m = 1.0f / m;
		vector -> x *= m;
		vector -> y *= m;
		vector -> z *= m;
	} else {
		vector -> x = vector -> y = vector -> z = 0;
	}
	return vector;
}

vector3d_t* vector3d_clone(const vector3d_t* vec) {
	vector3d_t* vector = vector3d_new(0, 0, 0);
	memcpy(vector, vec, sizeof(vector3d_t));
	return vector;
}

double vector3d_length(vector3d_t* vector) {
	return sqrt(
		pow(vector -> x, 2) +
		pow(vector -> y, 2) +
		pow(vector -> z, 2)
	);
}

void vector3d_set(vector3d_t* vector, double x, double y, double z) {
	vector -> x = x;
	vector -> y = y;
	vector -> z = z;
}

void vector3d_set_vec(vector3d_t* vector_l, vector3d_t* vector_r) {
	vector3d_set(vector_l, vector_r -> x, vector_r -> y, vector_r -> z);
}

char* vector3d_toString(vector3d_t* vector) {
	char* fstring = (char*)malloc(256);
	sprintf(fstring, "y = %.2f; x = %.2f; z = %.2f;", vector -> x, vector -> y, vector -> z);
	return fstring;
}

void vector3d_free(vector3d_t* vector) {
	free(vector);
}

void vector3d_add(vector3d_t* vector, double x, double y, double z) {
	vector -> x += x;
	vector -> y += y;
	vector -> z += z;
}

void vector3d_add_vec(vector3d_t* vector_l, vector3d_t* vector_r) {
	vector3d_add(vector_l, vector_r -> z, vector_r -> y, vector_r -> z);
}

void vector3d_interpolate(vector3d_t* vector, double x, double y, double z, double a) {
	vector -> x += (x - vector -> x) * a;
	vector -> y += (y - vector -> y) * a;
	vector -> z += (z - vector -> z) * a;
}

void vector3d_interpolate_vec(vector3d_t* vector_l, vector3d_t* vector_r, double a) {
	vector3d_interpolate(vector_l, vector_r -> x, vector_r -> y, vector_r -> z, a);
}

void vector3d_sub(vector3d_t* vector, double x, double y, double z) {
	vector -> x -= x;
	vector -> y -= y;
	vector -> z -= z;
}

void vector3d_sub_vec(vector3d_t* vector_l, vector3d_t* vector_r) {
	vector3d_sub(vector_l, vector_r -> x, vector_r -> y, vector_r -> z);
}

void vector3d_mul(vector3d_t* vector, double a) {
	vector -> x *= a;
	vector -> y *= a;
	vector -> z *= a;
}

double vector3d_dot(vector3d_t* vector, double x, double y, double z) {
	return vector -> x * x + vector -> y * y + vector -> z * z;
}

double vector3d_dot_vec(vector3d_t* vector_l, vector3d_t* vector_r) {
	return vector3d_dot(vector_l, vector_r -> x, vector_r -> y, vector_r -> z);
}

double vector3d_dist(vector3d_t* vector, double x, double y, double z) {
	return vector3d_dist3d(vector -> x, vector -> y, vector -> z, x, y, z);
}

double vector3d_dist_vec(vector3d_t* vector_l, vector3d_t* vector_r) {
	return vector3d_dist(vector_l, vector_r -> x, vector_r -> y, vector_r -> z);
}

double vector3d_dist2d(vector3d_t* vector, double x, double y, double z) {
	return vector3d_dist3d(vector -> x, 0, vector -> z, x, 0, z);
}

double vector3d_dist2d_vec(vector3d_t* vector_l, vector3d_t* vector_r) {
	return vector3d_dist2d(vector_l, vector_r -> x, vector_r -> y, vector_r -> z);
}

int vector3d_compare(const vector3d_t* vector_l, const vector3d_t* vector_r) {
	if (
		vector_l -> x != vector_r -> x ||
		vector_l -> y != vector_r -> y ||
		vector_l -> z != vector_r -> z
	) {
		return 0;
	}
	return 1;
}

void vector3d_roateZYX(vector3d_t* vector, double az, double ay, double ax) {
	// Z
	double x = vector -> x * cos(az) - vector -> y * sin(az);
	double y = vector -> x * sin(az) + vector -> y * cos(az);

	vector -> x = x;
	vector -> y = y;

	// Y
	double z = vector -> z * cos(ay) - vector -> x * sin(ay);
	x = vector -> z * sin(az) + vector -> x * cos(az);

	vector -> z = z;
	vector -> x = x;

	// X
	y = vector -> y * cos(ax) - vector -> z * sin(ax);
	z = vector -> y * sin(ax) + vector -> z * cos(ax);

	vector -> z = z;
	vector -> x = x;
}

void vector3d_roate(vector3d_t* vector, double ax, double ay, double az) {
	// X
	double y = vector -> y * cos(ax) - vector -> z * sin(ax);
	double z = vector -> y * sin(ax) + vector -> z * cos(ax);

	vector -> y = y;
	vector -> z = z;

	// Y
	y = vector -> z * cos(ay) - vector -> x * sin(ay);
	double x = vector -> z * sin(ay) + vector -> x * cos(ay);

	vector -> z = z;
	vector -> x = x;

	// Z
	x = vector -> x * cos(ay) - vector -> y * sin(ay);
	y = vector -> x * sin(ay) + vector -> y * cos(ay);

	vector -> x = x;
	vector -> y = y;
}

void vector3d_multAdd(vector3d_t* vector, double dx, double dy, double dz, double dist) {
	vector -> x += dx * dist;
	vector -> y += dy * dist;
	vector -> z += dz * dist;
}

void vector3d_multAdd_vec(vector3d_t* vector_l, vector3d_t* vector_r, double dist) {
	vector3d_multAdd(vector_l, vector_r -> x, vector_r -> y, vector_r -> z, dist);
}

double vector3d_dist3d(double x, double y, double z, double x1, double y1, double z1) {
	return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1) + (z - z1) * (z - z1));
}