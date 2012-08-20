#ifndef API_GRAPHIC_H
#define API_GRAPHIC_H

typedef void (*key_listener)(int);

void gfx_init(int width, int height, const char *title);
void gfx_quit();

bool gfx_event_loop();
/*
int gfx_event_set_key_listener(key_listener key_down, key_listener key_up)
*/

#endif
