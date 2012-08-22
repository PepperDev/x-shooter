#ifndef API_GRAPHIC_H
#define API_GRAPHIC_H

#define KEY_UP      1
#define KEY_DOWN    2
#define KEY_RIGHT   3
#define KEY_LEFT    4
#define KEY_SPACE   5
#define KEY_CONTROL 6
#define KEY_SHIFT   7
#define KEY_ESCAPE  8

typedef void (*key_listener)(int, void*);

int gui_init(int width, int height, const char *title);
void gui_quit();

void gui_clear(int id);
void gui_update(int id);

bool gui_event_loop();
void gui_event_set_key_listener(key_listener key_down, key_listener key_up, void *data);
void gui_event_set_active_listener(void (*activate)(bool, void*), void *data);

unsigned long gui_time();
void gui_wait(unsigned long time);

int gui_image_load(const char *filename);
int gui_image_width(int image_id);
int gui_image_height(int image_id);
void gui_image_destroy(int image_id);
void gui_image_paint(int source, int x, int y, int target, int left, int top, int width, int height);

#endif
