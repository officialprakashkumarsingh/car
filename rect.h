#ifndef RECT_H
#define RECT_H

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Rect;

static inline Rect rect_make(float x, float y, float w, float h) {
    Rect r = {x, y, w, h};
    return r;
}

static inline int rect_contains_point(Rect r, float px, float py) {
    return px >= r.x && px < r.x + r.width && py >= r.y && py < r.y + r.height;
}

static inline int rect_intersects_rect(Rect a, Rect b) {
    return !(a.x + a.width <= b.x || b.x + b.width <= a.x ||
             a.y + a.height <= b.y || b.y + b.height <= a.y);
}

static inline Rect rect_intersection(Rect a, Rect b) {
    float x = (a.x > b.x) ? a.x : b.x;
    float y = (a.y > b.y) ? a.y : b.y;
    float x2 = (a.x + a.width < b.x + b.width) ? a.x + a.width : b.x + b.width;
    float y2 = (a.y + a.height < b.y + b.height) ? a.y + a.height : b.y + b.height;
    return rect_make(x, y, x2 - x, y2 - y);
}

static inline Rect rect_union(Rect a, Rect b) {
    float x = (a.x < b.x) ? a.x : b.x;
    float y = (a.y < b.y) ? a.y : b.y;
    float x2 = (a.x + a.width > b.x + b.width) ? a.x + a.width : b.x + b.width;
    float y2 = (a.y + a.height > b.y + b.height) ? a.y + a.height : b.y + b.height;
    return rect_make(x, y, x2 - x, y2 - y);
}

static inline Rect rect_inset(Rect r, float dx, float dy) {
    return rect_make(r.x + dx, r.y + dy, r.width - 2*dx, r.height - 2*dy);
}

static inline Rect rect_offset(Rect r, float dx, float dy) {
    return rect_make(r.x + dx, r.y + dy, r.width, r.height);
}

static inline float rect_area(Rect r) {
    return r.width * r.height;
}

#endif