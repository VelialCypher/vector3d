#ifndef VECTOR3D_H
#define VECTOR3D_H
#pragma once

typedef struct vector3d {
	double x, y, z;
} vector3d_t;

vector3d_t* vector3d_new(double x, double y, double z);
vector3d_t* vector3d_normalize(vector3d_t* vector);

vector3d_t* vector3d_clone(const vector3d_t* vector);
double vector3d_length(vector3d_t* vector);

void vector3d_set(vector3d_t* vector, double x, double y, double z);
void vector3d_set_vec(vector3d_t* vector_l, vector3d_t* vector_r);

char* vector3d_toString(vector3d_t* vector);
void vector3d_free(vector3d_t* vector);

void vector3d_add(vector3d_t* vector, double x, double y, double z);
void vector3d_add_vec(vector3d_t* vector_l, vector3d_t* vector_r);

void vector3d_interpolate(vector3d_t* vector, double x, double y, double z, double a);
void vector3d_interpolate_vec(vector3d_t* vector_l, vector3d_t* vector_r, double a);

void vector3d_sub(vector3d_t* vector, double x, double y, double z);
void vector3d_sub_vec(vector3d_t* vector_l, vector3d_t* vector_r);

void vector3d_mul(vector3d_t* vector, double a);

double vector3d_dot(vector3d_t* vector, double x, double y, double z);
double vector3d_dot_vec(vector3d_t* vector_l, vector3d_t* vector_r);

double vector3d_dist(vector3d_t* vector, double x, double y, double z);
double vector3d_dist_vec(vector3d_t* vector_l, vector3d_t* vector_r);

double vector3d_dist2d(vector3d_t* vector, double x, double y, double z);
double vector3d_dist2d_vec(vector3d_t* vector_l, vector3d_t* vector_r);

int vector3d_compare(const vector3d_t* vector_l, const vector3d_t* vector_r);
void vector3d_roateZYX(vector3d_t* vector, double az, double ay, double ax);
void vector3d_roate(vector3d_t* vector, double ax, double ay, double az);

void vector3d_multAdd(vector3d_t* vector, double dx, double dy, double dz, double dist);
void vector3d_multAdd_vec(vector3d_t* vector_l, vector3d_t* vector_r, double dist);

// util

double vector3d_dist3d(double x, double y, double z, double x1, double y1, double z1);

#endif