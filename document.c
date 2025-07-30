#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 256
#define MAX_DOCUMENTS 100

typedef struct {
    char filename[MAX_WORD_LENGTH];
    char content[MAX_LINE_LENGTH * 10];
    size_t word_count;
    size_t char_count;
} Document;

static Document documents[MAX_DOCUMENTS];
static int document_count = 0;

void create_document(const char* filename, const char* content) {
    if (document_count >= MAX_DOCUMENTS) {
        printf("Error: Maximum number of documents reached.\n");
        return;
    }
    
    Document* doc = &documents[document_count++];
    strncpy(doc->filename, filename, MAX_WORD_LENGTH - 1);
    strncpy(doc->content, content, sizeof(doc->content) - 1);
    
    // Calculate word and character count
    doc->char_count = strlen(content);
    doc->word_count = 0;
    
    char* copy = strdup(content);
    char* token = strtok(copy, " \t\n");
    while (token != NULL) {
        doc->word_count++;
        token = strtok(NULL, " \t\n");
    }
    free(copy);
    
    printf("Document '%s' created successfully.\n", filename);
}

void read_document(const char* filename) {
    for (int i = 0; i < document_count; i++) {
        if (strcmp(documents[i].filename, filename) == 0) {
            printf("Content of '%s':\n%s\n", filename, documents[i].content);
            return;
        }
    }
    printf("Document '%s' not found.\n", filename);
}

void update_document(const char* filename, const char* new_content) {
    for (int i = 0; i < document_count; i++) {
        if (strcmp(documents[i].filename, filename) == 0) {
            strncpy(documents[i].content, new_content, sizeof(documents[i].content) - 1);
            
            // Recalculate counts
            documents[i].char_count = strlen(new_content);
            documents[i].word_count = 0;
            
            char* copy = strdup(new_content);
            char* token = strtok(copy, " \t\n");
            while (token != NULL) {
                documents[i].word_count++;
                token = strtok(NULL, " \t\n");
            }
            free(copy);
            
            printf("Document '%s' updated successfully.\n", filename);
            return;
        }
    }
    printf("Document '%s' not found.\n", filename);
}

void delete_document(const char* filename) {
    for (int i = 0; i < document_count; i++) {
        if (strcmp(documents[i].filename, filename) == 0) {
            // Shift remaining documents
            for (int j = i; j < document_count - 1; j++) {
                documents[j] = documents[j + 1];
            }
            document_count--;
            printf("Document '%s' deleted successfully.\n", filename);
            return;
        }
    }
    printf("Document '%s' not found.\n", filename);
}

void list_documents() {
    if (document_count == 0) {
        printf("No documents available.\n");
        return;
    }
    
    printf("\nAvailable Documents:\n");
    printf("-------------------\n");
    for (int i = 0; i < document_count; i++) {
        printf("%d. %s (%zu words, %zu chars)\n", 
               i + 1, 
               documents[i].filename,
               documents[i].word_count,
               documents[i].char_count);
    }
    printf("\n");
}

void search_documents(const char* keyword) {
    int found = 0;
    printf("\nSearch results for '%s':\n", keyword);
    printf("------------------------\n");
    
    for (int i = 0; i < document_count; i++) {
        if (strstr(documents[i].filename, keyword) != NULL || 
            strstr(documents[i].content, keyword) != NULL) {
            printf("%s\n", documents[i].filename);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No documents found containing '%s'.\n", keyword);
    }
    printf("\n");
}

void word_count(const char* filename) {
    for (int i = 0; i < document_count; i++) {
        if (strcmp(documents[i].filename, filename) == 0) {
            printf("Document '%s' statistics:\n", filename);
            printf("Words: %zu\n", documents[i].word_count);
            printf("Characters: %zu\n", documents[i].char_count);
            return;
        }
    }
    printf("Document '%s' not found.\n", filename);
}

void display_help() {
    printf("\nDocument Management System - Available Commands:\n");
    printf("------------------------------------------------\n");
    printf("create <filename> <content>  - Create a new document\n");
    printf("read <filename>              - Read a document's content\n");
    printf("update <filename> <content>  - Update an existing document\n");
    printf("delete <filename>            - Delete a document\n");
    printf("list                         - List all documents\n");
    printf("search <keyword>             - Search documents by keyword\n");
    printf("count <filename>             - Show word and character count\n");
    printf("help                         - Show this help message\n");
    printf("exit                         - Exit the program\n\n");
}

int main() {
    char input[MAX_LINE_LENGTH];
    char command[MAX_WORD_LENGTH];
    char filename[MAX_WORD_LENGTH];
    char content[MAX_LINE_LENGTH * 10];
    
    printf("Document Management System\n");
    printf("Type 'help' for available commands.\n\n");
    
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Parse command
        if (sscanf(input, "%s", command) != 1) {
            continue;
        }
        
        if (strcmp(command, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }
        else if (strcmp(command, "help") == 0) {
            display_help();
        }
        else if (strcmp(command, "list") == 0) {
            list_documents();
        }
        else if (strcmp(command, "create") == 0) {
            char* rest = input + strlen("create");
            while (*rest == ' ') rest++;
            
            char* space = strchr(rest, ' ');
            if (space == NULL) {
                printf("Usage: create <filename> <content>\n");
                continue;
            }
            
            *space = '\0';
            strncpy(filename, rest, MAX_WORD_LENGTH - 1);
            strncpy(content, space + 1, sizeof(content) - 1);
            
            create_document(filename, content);
        }
        else if (strcmp(command, "read") == 0) {
            if (sscanf(input, "read %s", filename) == 1) {
                read_document(filename);
            } else {
                printf("Usage: read <filename>\n");
            }
        }
        else if (strcmp(command, "update") == 0) {
            char* rest = input + strlen("update");
            while (*rest == ' ') rest++;
            
            char* space = strchr(rest, ' ');
            if (space == NULL) {
                printf("Usage: update <filename> <content>\n");
                continue;
            }
            
            *space = '\0';
            strncpy(filename, rest, MAX_WORD_LENGTH - 1);
            strncpy(content, space + 1, sizeof(content) - 1);
            
            update_document(filename, content);
        }
        else if (strcmp(command, "delete") == 0) {
            if (sscanf(input, "delete %s", filename) == 1) {
                delete_document(filename);
            } else {
                printf("Usage: delete <filename>\n");
            }
        }
        else if (strcmp(command, "search") == 0) {
            char keyword[MAX_WORD_LENGTH];
            if (sscanf(input, "search %s", keyword) == 1) {
                search_documents(keyword);
            } else {
                printf("Usage: search <keyword>\n");
            }
        }
        else if (strcmp(command, "count") == 0) {
            if (sscanf(input, "count %s", filename) == 1) {
                word_count(filename);
            } else {
                printf("Usage: count <filename>\n");
            }
        }
        else {
            printf("Unknown command: %s\n", command);
            printf("Type 'help' for available commands.\n");
        }
    }
    
    return 0;
}