#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_RIPPLES 50
#define CANVAS_WIDTH 80
#define CANVAS_HEIGHT 24

typedef struct {
    int x, y;
    int radius;
    int max_radius;
    char symbol;
    int active;
    int delay;
} Ripple;

Ripple ripples[MAX_RIPPLES];
int ripple_count = 0;

void clear_screen() {
    printf("\033[2J\033[H");
}

void reset_cursor() {
    printf("\033[H");
}

void hide_cursor() {
    printf("\033[?25l");
}

void show_cursor() {
    printf("\033[?25h");
}

void set_color(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void reset_color() {
    printf("\033[0m");
}

void draw_canvas() {
    char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
    memset(canvas, ' ', sizeof(canvas));

    for (int i = 0; i < ripple_count; i++) {
        if (!ripples[i].active) continue;
        
        int center_x = ripples[i].x;
        int center_y = ripples[i].y;
        int radius = ripples[i].radius;
        
        for (int y = 0; y < CANVAS_HEIGHT; y++) {
            for (int x = 0; x < CANVAS_WIDTH; x++) {
                int dx = x - center_x;
                int dy = y - center_y;
                int distance = dx * dx + dy * dy;
                
                if (distance >= (radius - 1) * (radius - 1) && 
                    distance <= (radius + 1) * (radius + 1)) {
                    if (y >= 0 && y < CANVAS_HEIGHT && x >= 0 && x < CANVAS_WIDTH) {
                        canvas[y][x] = ripples[i].symbol;
                    }
                }
            }
        }
    }

    reset_cursor();
    
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
        for (int x = 0; x < CANVAS_WIDTH; x++) {
            set_color(200, 200, 200);
            putchar(canvas[y][x]);
            reset_color();
        }
        putchar('\n');
    }
}

void add_ripple(int x, int y, char symbol) {
    if (ripple_count >= MAX_RIPPLES) {
        for (int i = 0; i < MAX_RIPPLES - 1; i++) {
            ripples[i] = ripples[i + 1];
        }
        ripple_count--;
    }
    
    ripples[ripple_count].x = x;
    ripples[ripple_count].y = y;
    ripples[ripple_count].radius = 0;
    ripples[ripple_count].max_radius = rand() % 10 + 5;
    ripples[ripple_count].symbol = symbol;
    ripples[ripple_count].active = 1;
    ripples[ripple_count].delay = 0;
    ripple_count++;
}

void update_ripples() {
    for (int i = 0; i < ripple_count; i++) {
        if (!ripples[i].active) continue;
        
        if (ripples[i].delay > 0) {
            ripples[i].delay--;
            continue;
        }
        
        ripples[i].radius++;
        
        if (ripples[i].radius > ripples[i].max_radius) {
            ripples[i].active = 0;
        }
    }
    
    int active_count = 0;
    for (int i = 0; i < ripple_count; i++) {
        if (ripples[i].active) {
            ripples[active_count++] = ripples[i];
        }
    }
    ripple_count = active_count;
}

void print_instructions() {
    printf("\033[1;1H");
    set_color(180, 180, 180);
    printf("Terminal Ripple Animation - Click anywhere or press keys to create ripples\n");
    printf("Press 'q' to quit, 'c' to clear, 'r' for random ripples\n");
    reset_color();
}

int kbhit() {
    int ch = getchar();
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

char getch_nonblock() {
    char ch;
    system("stty raw -echo");
    ch = getchar();
    system("stty cooked echo");
    return ch;
}

int main() {
    srand(time(NULL));
    
    clear_screen();
    hide_cursor();
    
    char symbols[] = {'◦', '◯', '○', '◌', '◍', '●', '◉', '◎', '◉', '◯'};
    int symbol_count = sizeof(symbols) / sizeof(symbols[0]);
    
    print_instructions();
    
    while (1) {
        if (kbhit()) {
            char ch = getch_nonblock();
            
            if (ch == 'q' || ch == 'Q') {
                break;
            } else if (ch == 'c' || ch == 'C') {
                for (int i = 0; i < ripple_count; i++) {
                    ripples[i].active = 0;
                }
                ripple_count = 0;
            } else if (ch == 'r' || ch == 'R') {
                for (int i = 0; i < 5; i++) {
                    int x = rand() % CANVAS_WIDTH;
                    int y = rand() % CANVAS_HEIGHT;
                    char symbol = symbols[rand() % symbol_count];
                    add_ripple(x, y, symbol);
                }
            } else {
                int x = rand() % CANVAS_WIDTH;
                int y = rand() % CANVAS_HEIGHT;
                char symbol = symbols[rand() % symbol_count];
                add_ripple(x, y, symbol);
            }
        }
        
        draw_canvas();
        update_ripples();
        
        usleep(100000);
    }
    
    show_cursor();
    clear_screen();
    
    return 0;
}