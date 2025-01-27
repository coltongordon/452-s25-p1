#include "lab.h"


/*list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *));
typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct list {
    node_t *head;
    size_t size;
    void (*destroy_data)(void *);
    int (*compare_to)(const void *, const void *);
} list_t;*/

list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)) {
    if (destroy_data == NULL || compare_to == NULL) {
        return NULL;
    }
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (list == NULL) {
        return NULL;
    }

    // list->head = NULL;
    list->size = 0;
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;

    node_t *sentinel = (node_t *)malloc(sizeof(node_t));
    if (sentinel == NULL) {
        free(list);
        return NULL;
    }
    sentinel->data = NULL;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;

    list->head = sentinel;

    return list;
}


list_t *list_add(list_t *list, void *data) {
    if (list == NULL || data == NULL) {
        return list;
    }

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        return list;
    }

    new_node->data = data;
    new_node->next = list->head->next;
    new_node->prev = list->head;

    list->head->next->prev = new_node;
    list->head->next = new_node;

    list->size++;
    return list;
}



void list_destroy(list_t **list) {
    if (list == NULL || *list == NULL) {
        return;
    }

    node_t *current = (*list)->head->next;
    node_t *next_node;

    while (current != (*list)->head) {
        next_node = current->next;
        (*list)->destroy_data(current->data);
        free(current);
        current = next_node;
    }

    free((*list)->head);
    free(*list);
    *list = NULL;
}


void *list_remove_index(list_t *list, size_t index) {
    if (list == NULL || index >= list->size) {
        return NULL;
    }

    node_t *current = list->head->next;
    size_t current_index = 0;

    while (current_index < index) {
        current = current->next;
        current_index++;
    }

    void *data = current->data;
    current->prev->next = current->next;
    current->next->prev = current->prev;

    free(current);
    list->size--;

    return data;
}

int list_indexof(list_t *list, void *data) {
    if (list == NULL || data == NULL) {
        return -1;
    }

    node_t *current = list->head->next;
    int index = 0;

    while (current != list->head) {
        if (list->compare_to(current->data, data) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}