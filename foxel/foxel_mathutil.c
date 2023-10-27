#include <foxel/foxel_mathutil.h>

#include <math.h>
#include <stdlib.h>

void mat4_multiply(mat4_t a, mat4_t b, mat4_t c)
{
	mat4_t nu;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			nu[j + (i * 4)] = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				nu[j + (i * 4)] += a[k + (i * 4)] * b[j + (k * 4)];
			}
		}
	}

	mat4_copy(c, nu);
}

void mat4_translate(mat4_t m, float x, float y, float z)
{
	mat4_t m2;
	mat4_identity(m2);

	m2[3] = x;
	m2[7] = y;
	m2[11] = z;

	mat4_multiply(m, m2, m);
}
static void mat4_rotateX(mat4_t m, float x)
{
	mat4_t m2;
	mat4_identity(m2);

	m2[5] = cosf(x);
	m2[6] = sinf(x);
	m2[9] = -sinf(x);
	m2[10] = cosf(x);

	mat4_multiply(m, m2, m);
}
static void mat4_rotateY(mat4_t m, float y)
{
	mat4_t m2;
	mat4_identity(m2);

	m2[0] = cosf(y);
	m2[2] = sinf(y);
	m2[8] = -sinf(y);
	m2[10] = cosf(y);

	mat4_multiply(m, m2, m);
}
static void mat4_rotateZ(mat4_t m, float z)
{
	mat4_t m2;
	mat4_identity(m2);

	m2[0] = cosf(z);
	m2[1] = sinf(z);
	m2[4] = -sinf(z);
	m2[5] = cosf(z);

	mat4_multiply(m, m2, m);
}
void mat4_rotation(mat4_t m, float x, float y, float z)
{
	mat4_rotateX(m, x);
	mat4_rotateY(m, y);
	mat4_rotateZ(m, z);
}
void mat4_scale(mat4_t m, float x, float y, float z)
{
	mat4_t m2;
	mat4_identity(m2);

	m2[0] = x;
	m2[5] = y;
	m2[10] = z;

	mat4_multiply(m, m2, m);
}

void mat4_copy(mat4_t x, mat4_t y)
{
	for (int i = 0; i < 16; i++)
	{
		x[i] = y[i];
	}
}

void mat4_identity(mat4_t m)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = 0.0f;
	}

	m[0] = 1.0f;
	m[5] = 1.0f;
	m[10] = 1.0f;
	m[15] = 1.0f;
}
void mat4_inverse(mat4_t m)
{
	for (int i = 0; i < 16; i++) {
		m[i] = -m[i];
	}
}

void vec3_copy(vec3_t* x, vec3_t y)
{
	x->x = y.x;
	x->y = y.y;
	x->z = y.z;
}

void vec3_add(vec3_t* x, vec3_t y)
{
	x->x = x->x + y.x;
	x->y = x->y + y.y;
	x->z = x->z + y.z;
}
void vec3_subtract(vec3_t* x, vec3_t y)
{
	x->x = x->x - y.x;
	x->y = x->y - y.y;
	x->z = x->z - y.z;
}
void vec3_multiply(vec3_t* x, vec3_t y)
{
	x->x = x->x * y.x;
	x->y = x->y * y.y;
	x->z = x->z * y.z;
}
void vec3_divide(vec3_t* x, vec3_t y)
{
	x->x = x->x / y.x;
	x->y = x->y / y.y;
	x->z = x->z / y.z;
}

float vec3_dot(vec3_t x, vec3_t y)
{
	return x.x * y.x + x.y * y.y + x.z * y.z;
}

float* vec3_toBuffer(vec3_t* x, int size)
{
	float* v = malloc(sizeof *v * size * 3);

	for (int i = 0; i < size; i++)
	{
		int pos = (i * 3);
		v[pos + 0] = x[i].x;
		v[pos + 1] = x[i].y;
		v[pos + 2] = x[i].z;
	}

	return v;
}

float vec3_normalize(vec3_t* x)
{
	float length = sqrtf(x->x*x->x + x->y*x->y + x->z*x->z);

	if (length)
	{
		x->x /= length;
		x->y /= length;
		x->z /= length;
	}

	return length;
}
float vec3_length(vec3_t x)
{
	return sqrtf(x.x*x.x + x.y*x.y + x.z*x.z);
}
