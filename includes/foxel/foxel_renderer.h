#ifndef __FOXEL_FRAMEWORK_RENDERER_H__
#define __FOXEL_FRAMEWORK_RENDERER_H__

typedef unsigned int shader_t;
typedef unsigned int texture_t;
typedef struct
{
	unsigned int vao;

	unsigned int ebo;
	unsigned int vbo;

	unsigned int size;
} model_t;

texture_t renderer_createTexture(const char* path, unsigned int wrap);
void renderer_bindTexture(texture_t texture, unsigned int id);
void renderer_destroyTexture(texture_t texture);

shader_t renderer_createShader(const char* vsrc, const char* fsrc);
shader_t renderer_loadShader(const char* vpath, const char* fpath);
void renderer_useShader(shader_t shader);
void renderer_destroyShader(shader_t shader);

int renderer_getUniform(shader_t shader, const char* name, int* uniform);

void renderer_setUniform1f(unsigned int uniform, float x);
void renderer_setUniform2f(unsigned int uniform, float x, float y);
void renderer_setUniform3f(unsigned int uniform, float x, float y, float z);
void renderer_setUniform4f(unsigned int uniform, float x, float y, float z, float w);

void renderer_setUniform1i(unsigned int uniform, int x);
void renderer_setUniform2i(unsigned int uniform, int x, int y);
void renderer_setUniform3i(unsigned int uniform, int x, int y, int z);
void renderer_setUniform4i(unsigned int uniform, int x, int y, int z, int w);

void renderer_setUniform4m(unsigned int uniform, float* matrix);

unsigned int renderer_createVAO();
unsigned int renderer_createBuffer();

void renderer_bindVAO(unsigned int vao);
void renderer_bindVBO(unsigned int vbo, float* data, unsigned long size);
void renderer_bindEBO(unsigned int ebo, unsigned int* indices, unsigned long size);

void renderer_unbindVAO();
void renderer_unbindVBO();

void renderer_bindAttribute(unsigned int attrib);
void renderer_setAttribute(unsigned int attrib, unsigned int attrib_size, unsigned int type, unsigned long buffer_size, unsigned long buffer_offset);
void renderer_unbindAttribute(unsigned int attrib);

model_t* renderer_createModel(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int size);
void renderer_drawModel(model_t* model);
void renderer_destroyModel(model_t* model);

#endif // __FOXEL_FRAMEWORK_RENDERER_H__
