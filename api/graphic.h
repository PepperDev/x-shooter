#ifndef API_GRAPHIC_H
#define API_GRAPHIC_H

typedef void (*key_listener)(int);

int gui_init(int width, int height, const char *title);
void gui_quit();

bool gui_event_loop();
/*
int gui_event_set_key_listener(key_listener key_down, key_listener key_up)
*/

unsigned long gui_time();
void gui_wait(unsigned long time);

int gui_image_load(const char *filename);
int gui_image_width(int image_id);
int gui_image_height(int image_id);
void gui_image_destroy(int image_id);
void gui_image_paint(int source, int x, int y, int target, int left, int top, int width, int height);

#endif
