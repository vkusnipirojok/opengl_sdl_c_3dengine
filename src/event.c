#include "../header/event.h"

struct event
{
    SDL_Event event;

    struct camera *item_camera;

    bool running;

    int32_t dir;

    double new_x;
    double new_y;

    double old_x;
    double old_y;

    double x_off_set;
    double y_off_set;

    bool space;
    bool cull_face;
    bool flag;
};

struct event *event_malloc() 
{ 
    return (struct event *)malloc(sizeof(struct event)); 
};

void event_init(struct event *item_event,
                struct camera *item_camera,
                bool item_running,
                int32_t item_dir,
                double item_new_x,
                double item_new_y,
                double item_old_x,
                double item_old_y,
                double item_x_off_set,
                double item_y_off_set,
                bool item_space,
                bool item_cull_face)
{
    item_event->item_camera = item_camera;

    item_event->running = item_running;

    item_event->dir = item_dir;

    item_event->new_x = item_new_x;
    item_event->new_y = item_new_y;

    item_event->old_x = item_old_x;
    item_event->old_y = item_old_y;

    item_event->x_off_set = item_x_off_set;
    item_event->y_off_set = item_y_off_set;

    item_event->space = item_space;
    item_event->cull_face = item_cull_face;
    item_event->flag = item_cull_face;
};

bool event_get_running(struct event *item_event) { return item_event->running; };

void event_destroy(struct event *item_event) { free(item_event); };

void event_handle(struct event *item_event)
{
    item_event->dir = 0;

    item_event->new_x = item_event->new_y = 0;

    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    while(SDL_PollEvent(&item_event->event))
    {
        if(item_event->event.type == SDL_KEYDOWN)
        {
            if(item_event->event.key.keysym.sym == SDLK_SPACE)
            {
                item_event->space = !item_event->space;
            }
            if(item_event->event.key.keysym.sym == SDLK_i)
            {
                item_event->cull_face = !item_event->cull_face;
            }
            if(item_event->event.key.keysym.sym == SDLK_p)
            {
                item_event->flag = !item_event->flag;
            }
        }
        if(item_event->flag)
        {
            if(item_event->event.type == SDL_MOUSEMOTION)
            {
                item_event->new_x = item_event->event.motion.xrel;
                item_event->new_y = item_event->event.motion.yrel;
            }
            if(item_event->event.type == SDL_MOUSEWHEEL)
            {
                camera_change_fov(item_event->item_camera, 
                                  item_event->event.wheel.y);
            }
        }
    }

    if(key_state[SDL_SCANCODE_W])
        item_event->dir |= CAMERA_FORWARD;

    if(key_state[SDL_SCANCODE_A])
        item_event->dir |= CAMERA_LEFT;

    if(key_state[SDL_SCANCODE_S])
        item_event->dir |= CAMERA_BACKWARD;

    if(key_state[SDL_SCANCODE_D])
        item_event->dir |= CAMERA_RIGHT;

    if(key_state[SDL_SCANCODE_ESCAPE])
        item_event->running = false;

    item_event->old_x = item_event->old_y = 0;

    item_event->x_off_set = item_event->new_x - item_event->old_x;
    item_event->y_off_set = item_event->new_y - item_event->old_y;
    
    item_event->old_x = item_event->new_x;
    item_event->old_y = item_event->new_y;
};

int32_t event_get_dir(struct event *item_event) { return item_event->dir; };

double event_get_x_off_set(struct event *item_event)
{
    return item_event->x_off_set;
};

double event_get_y_off_set(struct event *item_event)
{
    return item_event->y_off_set;
};

bool event_get_space(struct event *item_event) { return item_event->space; };

bool event_get_cull_face(struct event *item_event) 
{ 
    return item_event->cull_face;
};

bool event_get_flag(struct event *item_event)
{
    return item_event->flag;
};
