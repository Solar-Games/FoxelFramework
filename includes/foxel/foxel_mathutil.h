#ifndef __FOXEL_FRAMEWORK_MATHUTIL_H__
#define __FOXEL_FRAMEWORK_MATHUTIL_H__

#define PI 3.14159

#define DEG_TO_RAD(x) ((x) * 3.14159 / 180.0)
#define RAD_TO_DEG(x) ((x) * 180.0 / 3.14159)

typedef float mat4_t[16];
typedef struct {
	float x;
	float y;
	float z;
} vec3_t;

void mat4_multiply(mat4_t a, mat4_t b, mat4_t c);

void mat4_translate(mat4_t m, float x, float y, float z);
void mat4_rotation(mat4_t m, float x, float y, float z);
void mat4_scale(mat4_t m, float x, float y, float z);

void mat4_copy(mat4_t x, mat4_t y);

void mat4_identity(mat4_t m);
void mat4_inverse(mat4_t m);

void vec3_copy(vec3_t* x, vec3_t y);

void vec3_add(vec3_t* x, vec3_t y);
void vec3_subtract(vec3_t* x, vec3_t y);
void vec3_multiply(vec3_t* x, vec3_t y);
void vec3_divide(vec3_t* x, vec3_t y);

float vec3_dot(vec3_t x, vec3_t y);

float* vec3_toBuffer(vec3_t* x, int size);

float vec3_normalize(vec3_t* x);
float vec3_length(vec3_t x);

#endif // __FOXEL_FRAMEWORK_MATHUTIL_H__
