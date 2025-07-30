#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CTX_SIZE 4096
#define MAX_KEY_LEN 256
#define MAX_VAL_LEN 1024

typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VAL_LEN];
} ctx_entry_t;

typedef struct {
    ctx_entry_t entries[MAX_CTX_SIZE];
    size_t count;
    bool initialized;
} ctx_t;

static ctx_t global_ctx = {0};

bool ctx_init(void) {
    if (global_ctx.initialized) {
        return true;
    }
    
    memset(&global_ctx, 0, sizeof(global_ctx));
    global_ctx.initialized = true;
    return true;
}

bool ctx_set(const char* key, const char* value) {
    if (!key || !value || !global_ctx.initialized) {
        return false;
    }
    
    if (strlen(key) >= MAX_KEY_LEN || strlen(value) >= MAX_VAL_LEN) {
        return false;
    }
    
    for (size_t i = 0; i < global_ctx.count; i++) {
        if (strcmp(global_ctx.entries[i].key, key) == 0) {
            strncpy(global_ctx.entries[i].value, value, MAX_VAL_LEN - 1);
            global_ctx.entries[i].value[MAX_VAL_LEN - 1] = '\0';
            return true;
        }
    }
    
    if (global_ctx.count >= MAX_CTX_SIZE) {
        return false;
    }
    
    strncpy(global_ctx.entries[global_ctx.count].key, key, MAX_KEY_LEN - 1);
    strncpy(global_ctx.entries[global_ctx.count].value, value, MAX_VAL_LEN - 1);
    global_ctx.entries[global_ctx.count].key[MAX_KEY_LEN - 1] = '\0';
    global_ctx.entries[global_ctx.count].value[MAX_VAL_LEN - 1] = '\0';
    global_ctx.count++;
    
    return true;
}

const char* ctx_get(const char* key) {
    if (!key || !global_ctx.initialized) {
        return NULL;
    }
    
    for (size_t i = 0; i < global_ctx.count; i++) {
        if (strcmp(global_ctx.entries[i].key, key) == 0) {
            return global_ctx.entries[i].value;
        }
    }
    
    return NULL;
}

bool ctx_delete(const char* key) {
    if (!key || !global_ctx.initialized) {
        return false;
    }
    
    for (size_t i = 0; i < global_ctx.count; i++) {
        if (strcmp(global_ctx.entries[i].key, key) == 0) {
            for (size_t j = i; j < global_ctx.count - 1; j++) {
                global_ctx.entries[j] = global_ctx.entries[j + 1];
            }
            global_ctx.count--;
            return true;
        }
    }
    
    return false;
}

void ctx_clear(void) {
    if (!global_ctx.initialized) {
        return;
    }
    
    global_ctx.count = 0;
}

size_t ctx_count(void) {
    return global_ctx.initialized ? global_ctx.count : 0;
}

bool ctx_exists(const char* key) {
    return ctx_get(key) != NULL;
}

void ctx_foreach(void (*callback)(const char*, const char*)) {
    if (!callback || !global_ctx.initialized) {
        return;
    }
    
    for (size_t i = 0; i < global_ctx.count; i++) {
        callback(global_ctx.entries[i].key, global_ctx.entries[i].value);
    }
}

void ctx_destroy(void) {
    if (!global_ctx.initialized) {
        return;
    }
    
    ctx_clear();
    global_ctx.initialized = false;
}

#ifdef TEST_CTX
#include <assert.h>

static void test_ctx_basic(void) {
    assert(ctx_init());
    assert(ctx_count() == 0);
    
    assert(ctx_set("theme", "neutral"));
    assert(ctx_count() == 1);
    assert(strcmp(ctx_get("theme"), "neutral") == 0);
    
    assert(ctx_set("theme", "minimal"));
    assert(ctx_count() == 1);
    assert(strcmp(ctx_get("theme"), "minimal") == 0);
    
    assert(ctx_set("emoji", "enabled"));
    assert(ctx_count() == 2);
    assert(strcmp(ctx_get("emoji"), "enabled") == 0);
    
    assert(ctx_delete("theme"));
    assert(ctx_count() == 1);
    assert(ctx_get("theme") == NULL);
    
    ctx_clear();
    assert(ctx_count() == 0);
    
    ctx_destroy();
}

static void test_ctx_edge_cases(void) {
    assert(ctx_init());
    
    assert(!ctx_set(NULL, "value"));
    assert(!ctx_set("key", NULL));
    assert(!ctx_set("key", "value"));
    
    char long_key[MAX_KEY_LEN + 10];
    memset(long_key, 'a', sizeof(long_key) - 1);
    long_key[sizeof(long_key) - 1] = '\0';
    assert(!ctx_set(long_key, "value"));
    
    char long_value[MAX_VAL_LEN + 10];
    memset(long_value, 'a', sizeof(long_value) - 1);
    long_value[sizeof(long_value) - 1] = '\0';
    assert(!ctx_set("key", long_value));
    
    assert(!ctx_get(NULL));
    assert(!ctx_delete(NULL));
    assert(!ctx_exists(NULL));
    
    ctx_destroy();
}

int main(void) {
    test_ctx_basic();
    test_ctx_edge_cases();
    printf("All tests passed!\n");
    return 0;
}
#endif