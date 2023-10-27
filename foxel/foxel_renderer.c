#include <foxel/foxel_renderer.h>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <stdio.h>
#include <stdlib.h>

texture_t renderer_createTexture(const char* path, unsigned int wrap)
{
	printf("Creating texture.\n");
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, channels;
	unsigned char* data = stbi_load(path, &width, &height, &channels, 4);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		printf("TEXTURE ERROR: Couldn't find or load image.\n");
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	printf("Finished creating texture.\n");

	return texture;
}
void renderer_bindTexture(texture_t texture, unsigned int id)
{
	glActiveTexture(id);
	glBindTexture(GL_TEXTURE_2D, texture);
}
void renderer_destroyTexture(texture_t texture)
{
	glDeleteTextures(1, &texture);
}

static unsigned int buildSubShader(const char* src, int type) {
	unsigned int sh = glCreateShader(type);
	glShaderSource(sh, 1, &src, NULL);
	glCompileShader(sh);

	int success;
	char log[512];
	glGetShaderiv(sh, GL_COMPILE_STATUS, &success);
	if (!success) {
		printf("Hello\n");
		glGetShaderInfoLog(sh, 512, NULL, log);
		printf("SHADER ERROR: %s\n", log);
	}

	return sh;
}

shader_t renderer_createShader(const char* vsrc, const char* fsrc)
{
	unsigned int vsh = buildSubShader(vsrc, GL_VERTEX_SHADER);
	unsigned int fsh = buildSubShader(fsrc, GL_FRAGMENT_SHADER);

	unsigned int shader = glCreateProgram();

	glAttachShader(shader, vsh);
	glAttachShader(shader, fsh);
	glLinkProgram(shader);

	int success;
	char log[512];
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, log);
		printf("SHADER PROGRAM ERROR: %s\n", log);
	}

	glDeleteShader(vsh);
	glDeleteShader(fsh);

	printf("SHADER SUCCESS: Could successfully create shader.\n");
	return shader;
}
shader_t renderer_loadShader(const char* vpath, const char* fpath)
{
	FILE* vfile = fopen(vpath, "r");
	FILE* ffile = fopen(fpath, "r");

	if (vfile && ffile)
	{
		printf("LOADING SUCCESS: Could find the shader files.\n");

		fseek(vfile, 0, SEEK_END);
		long vsize = ftell(vfile);
		fseek(vfile, 0, SEEK_SET);

		fseek(ffile, 0, SEEK_END);
		long fsize = ftell(ffile);
		fseek(ffile, 0, SEEK_SET);

		char vsrc[vsize + 1];
		fread(vsrc, 1, vsize, vfile);
		vsrc[vsize] = 0;

		char fsrc[fsize + 1];
		fread(fsrc, 1, fsize, ffile);
		fsrc[fsize] = 0;

		fclose(ffile);
		fclose(vfile);

		return renderer_createShader(vsrc, fsrc);
	} else {
		printf("LOADING ERROR: Could not find shader file.\n");
		return 0;
	}
}
void renderer_useShader(shader_t shader)
{
	glUseProgram(shader);
}
void renderer_destroyShader(shader_t shader)
{
	glDeleteProgram(shader);
}

int renderer_getUniform(shader_t shader, const char* name, int* uniform)
{
	int u = glGetUniformLocation(shader, name);

	if (uniform)
		uniform[0] = u;

	return u;
}

void renderer_setUniform1f(unsigned int uniform, float x)
{
	glUniform1f(uniform, x);
}
void renderer_setUniform2f(unsigned int uniform, float x, float y)
{
	glUniform2f(uniform, x, y);
}
void renderer_setUniform3f(unsigned int uniform, float x, float y, float z)
{
	glUniform3f(uniform, x, y, z);
}
void renderer_setUniform4f(unsigned int uniform, float x, float y, float z, float w)
{
	glUniform4f(uniform, x, y, z, w);
}

void renderer_setUniform1i(unsigned int uniform, int x)
{
	glUniform1i(uniform, x);
}
void renderer_setUniform2i(unsigned int uniform, int x, int y)
{
	glUniform2i(uniform, x, y);
}
void renderer_setUniform3i(unsigned int uniform, int x, int y, int z)
{
	glUniform3i(uniform, x, y, z);
}
void renderer_setUniform4i(unsigned int uniform, int x, int y, int z, int w)
{
	glUniform4i(uniform, x, y, z, w);
}

void renderer_setUniform4m(unsigned int uniform, float* matrix)
{
	glUniformMatrix4fv(uniform, 1, 0, matrix);
}

unsigned int renderer_createVAO()
{
	unsigned int vao;
	glGenVertexArrays(1, &vao);

	return vao;
}
unsigned int renderer_createBuffer()
{
	unsigned int buffer;
	glGenBuffers(1, &buffer);

	return buffer;
}

void renderer_bindVAO(unsigned int vao)
{
	glBindVertexArray(vao);
}
void renderer_bindVBO(unsigned int vbo, float* data, unsigned long size)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void renderer_bindEBO(unsigned int ebo, unsigned int* indices, unsigned long size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void renderer_unbindVAO()
{
	glBindVertexArray(0);
}
void renderer_unbindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void renderer_bindAttribute(unsigned int attrib)
{
	glEnableVertexAttribArray(attrib);
}
void renderer_setAttribute(unsigned int attrib, unsigned int attrib_size, unsigned int type, unsigned long buffer_size, unsigned long buffer_offset)
{
	glVertexAttribPointer(attrib, attrib_size, type, GL_FALSE, buffer_size, (void*) buffer_offset);
}
void renderer_unbindAttribute(unsigned int attrib)
{
	glDisableVertexAttribArray(attrib);
}

model_t* renderer_createModel(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int size)
{
	model_t* model = malloc(sizeof *model);

	model->vao = vao;
	model->vbo = vbo;
	model->ebo = ebo;

	model->size = size;

	return model;
}
void renderer_drawModel(model_t* model)
{
	glBindVertexArray(model->vao);
	glDrawElements(GL_TRIANGLES, model->size, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void renderer_destroyModel(model_t* model)
{
	glDeleteVertexArrays(1, &model->vao);
	glDeleteBuffers(1, &model->vbo);
	glDeleteBuffers(1, &model->ebo);
	free(model);
}
