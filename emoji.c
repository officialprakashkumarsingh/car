#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EMOJIS 100
#define EMOJI_LEN 8  // max bytes for a UTF-8 emoji

typedef struct {
    char emoji[EMOJI_LEN];
    char description[50];
    int usage_count;
} Emoji;

static Emoji emoji_db[MAX_EMOJIS];
static int emoji_count = 0;

static const char *default_emojis[] = {
    "😊", "🌿", "🕊️", "☕", "🌙", "✨", "🏡", "🎯", "⚡", "🎨",
    "📐", "🎭", "🎬", "💚", "🌸", "🎵", "📚", "🔮", "🧘", "🌱"
};

static const char *descriptions[] = {
    "smile", "herb", "dove", "coffee", "moon", "sparkles", "home", "target",
    "lightning", "palette", "triangular ruler", "masks", "clapper board", "green heart",
    "cherry blossom", "musical note", "books", "crystal ball", "lotus", "seedling"
};

void emoji_init(void) {
    emoji_count = 0;
    srand((unsigned)time(NULL));
    
    for (int i = 0; i < (int)(sizeof(default_emojis)/sizeof(default_emojis[0])); ++i) {
        if (i >= MAX_EMOJIS) break;
        strncpy(emoji_db[i].emoji, default_emojis[i], EMOJI_LEN - 1);
        emoji_db[i].emoji[EMOJI_LEN - 1] = '\0';
        strncpy(emoji_db[i].description, descriptions[i], sizeof(emoji_db[i].description) - 1);
        emoji_db[i].description[sizeof(emoji_db[i].description) - 1] = '\0';
        emoji_db[i].usage_count = 0;
        emoji_count++;
    }
}

int emoji_add(const char *emoji, const char *desc) {
    if (emoji_count >= MAX_EMOJIS) return -1;
    if (!emoji || !desc) return -1;
    
    strncpy(emoji_db[emoji_count].emoji, emoji, EMOJI_LEN - 1);
    emoji_db[emoji_count].emoji[EMOJI_LEN - 1] = '\0';
    strncpy(emoji_db[emoji_count].description, desc, sizeof(emoji_db[emoji_count].description) - 1);
    emoji_db[emoji_count].description[sizeof(emoji_db[emoji_count].description) - 1] = '\0';
    emoji_db[emoji_count].usage_count = 0;
    
    return emoji_count++;
}

const char *emoji_get(int index) {
    if (index < 0 || index >= emoji_count) return NULL;
    emoji_db[index].usage_count++;
    return emoji_db[index].emoji;
}

const char *emoji_desc(int index) {
    if (index < 0 || index >= emoji_count) return NULL;
    return emoji_db[index].description;
}

int emoji_count_total(void) {
    return emoji_count;
}

const char *emoji_random(void) {
    if (emoji_count == 0) return NULL;
    int idx = rand() % emoji_count;
    emoji_db[idx].usage_count++;
    return emoji_db[idx].emoji;
}

void emoji_print_all(void) {
    printf("Available emojis:\n");
    for (int i = 0; i < emoji_count; ++i) {
        printf("%2d: %s  %s\n", i, emoji_db[i].emoji, emoji_db[i].description);
    }
}

void emoji_stats(void) {
    printf("\nEmoji usage statistics:\n");
    for (int i = 0; i < emoji_count; ++i) {
        printf("%s  %-15s used %d times\n",
               emoji_db[i].emoji,
               emoji_db[i].description,
               emoji_db[i].usage_count);
    }
}

#ifdef DEMO
int main(void) {
    emoji_init();
    emoji_print_all();
    
    printf("\nRandom emoji: %s\n", emoji_random());
    printf("Random emoji: %s\n", emoji_random());
    
    emoji_stats();
    return 0;
}
#endif