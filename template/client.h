#ifndef __YOUR_CLIENT_H__
#define __YOUR_CLIENT_H__

void client_resize(int width, int height);
void client_mousemove(float x, float y);
void client_mousepress(int button, int action, int mods);
void client_key(int button, int action, int mods);

void client_update(float delta);
void client_draw();

void client_close();

void client_main();

#endif // __YOUR_CLIENT_H__
