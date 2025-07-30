#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * ctx.c - Context management for the car project
 * 
 * This file provides functionality for managing application context,
 * including configuration, state, and runtime data for the car system.
 */

/**
 * Structure to hold the application context
 */
typedef struct {
    char* mode;           // Operation mode (e.g., "manual", "auto")
    int speed;            // Current speed of the car
    int battery_level;    // Battery level percentage
    char* status;         // Current status message
    void* user_data;      // Pointer to additional user-defined data
} CarContext;

/**
 * Global context instance
 */
static CarContext global_ctx = {
    .mode = "manual",
    .speed = 0,
    .battery_level = 100,
    .status = "Initialized",
    .user_data = NULL
};

/**
 * Initialize the car context with default values or configuration
 * 
 * @return 0 on success, -1 on failure
 */
int ctx_init(void) {
    // Reset or initialize context values
    global_ctx.mode = strdup("manual");
    if (!global_ctx.mode) {
        fprintf(stderr, "Error: Memory allocation failed for mode\n");
        return -1;
    }
    
    global_ctx.speed = 0;
    global_ctx.battery_level = 100;
    global_ctx.status = strdup("Initialized");
    if (!global_ctx.status) {
        fprintf(stderr, "Error: Memory allocation failed for status\n");
        free(global_ctx.mode);
        return -1;
    }
    
    global_ctx.user_data = NULL;
    return 0;
}

/**
 * Get the current operation mode
 * 
 * @return Pointer to the mode string
 */
const char* ctx_get_mode(void) {
    return global_ctx.mode;
}

/**
 * Set the operation mode
 * 
 * @param mode New mode string to set
 * @return 0 on success, -1 on failure
 */
int ctx_set_mode(const char* mode) {
    if (!mode) {
        fprintf(stderr, "Error: NULL mode provided\n");
        return -1;
    }
    
    char* new_mode = strdup(mode);
    if (!new_mode) {
        fprintf(stderr, "Error: Memory allocation failed for new mode\n");
        return -1;
    }
    
    free(global_ctx.mode);
    global_ctx.mode = new_mode;
    return 0;
}

/**
 * Get the current speed
 * 
 * @return Current speed value
 */
int ctx_get_speed(void) {
    return global_ctx.speed;
}

/**
 * Set the speed
 * 
 * @param speed New speed value (must be non-negative)
 * @return 0 on success, -1 on invalid input
 */
int ctx_set_speed(int speed) {
    if (speed < 0) {
        fprintf(stderr, "Error: Speed cannot be negative\n");
        return -1;
    }
    global_ctx.speed = speed;
    return 0;
}

/**
 * Get the current battery level
 * 
 * @return Battery level percentage
 */
int ctx_get_battery_level(void) {
    return global_ctx.battery_level;
}

/**
 * Set the battery level
 * 
 * @param level New battery level (0-100)
 * @return 0 on success, -1 on invalid input
 */
int ctx_set_battery_level(int level) {
    if (level < 0 || level > 100) {
        fprintf(stderr, "Error: Battery level must be between 0 and 100\n");
        return -1;
    }
    global_ctx.battery_level = level;
    return 0;
}

/**
 * Get the current status message
 * 
 * @return Pointer to the status string
 */
const char* ctx_get_status(void) {
    return global_ctx.status;
}

/**
 * Set the status message
 * 
 * @param status New status message
 * @return 0 on success, -1 on failure
 */
int ctx_set_status(const char* status) {
    if (!status) {
        fprintf(stderr, "Error: NULL status provided\n");
        return -1;
    }
    
    char* new_status = strdup(status);
    if (!new_status) {
        fprintf(stderr, "Error: Memory allocation failed for new status\n");
        return -1;
    }
    
    free(global_ctx.status);
    global_ctx.status = new_status;
    return 0;
}

/**
 * Set user-defined data
 * 
 * @param data Pointer to user data
 */
void ctx_set_user_data(void* data) {
    global_ctx.user_data = data;
}

/**
 * Get user-defined data
 * 
 * @return Pointer to user data
 */
void* ctx_get_user_data(void) {
    return global_ctx.user_data;
}

/**
 * Cleanup the context and free allocated resources
 */
void ctx_cleanup(void) {
    free(global_ctx.mode);
    free(global_ctx.status);
    global_ctx.mode = NULL;
    global_ctx.status = NULL;
    global_ctx.user_data = NULL;
    global_ctx.speed = 0;
    global_ctx.battery_level = 0;
}