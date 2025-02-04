#include "lab.h"

/**
 * Initializes a new doubly linked list.
 *
 * @param destroy_data A function pointer to a function that will be used to
 *                     free the data stored in the list nodes. This function
 *                     will be called when a node is removed from the list.
 * @param compare_to   A function pointer to a function that will be used to
 *                     compare the data stored in the list nodes. This function
 *                     will be used for operations that require data comparison.
 *
 * @return A pointer to the newly created list, or NULL if memory allocation
 *         fails or if either of the function pointers is NULL.
 */
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


/**
 * @brief Adds a new node with the given data to the list.
 *
 * This function creates a new node with the provided data and inserts it
 * immediately after the head of the list. If the list or data is NULL, the
 * function returns the original list without modification.
 *
 * @param list A pointer to the list to which the new node will be added.
 * @param data A pointer to the data to be stored in the new node.
 * @return A pointer to the updated list.
 */
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



/**
 * @brief Destroys a linked list and frees all associated memory.
 *
 * This function deallocates all nodes in the linked list, including the head node,
 * and frees any data associated with each node using the provided destroy_data function.
 * The list pointer is then set to NULL to prevent dangling references.
 *
 * @param list A double pointer to the list to be destroyed. If the list or the list pointer
 *             is NULL, the function does nothing.
 */
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


/**
 * @brief Removes and returns the data at the specified index from the list.
 *
 * This function removes the node at the given index from the list and returns
 * the data stored in that node. If the list is NULL or the index is out of
 * bounds, the function returns NULL.
 *
 * @param list A pointer to the list from which to remove the node.
 * @param index The index of the node to remove.
 * @return A pointer to the data stored in the removed node, or NULL if the
 *         list is NULL or the index is out of bounds.
 */
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

/**
 * @brief Finds the index of the first occurrence of the specified data in the list.
 *
 * This function searches through the list to find the first node that contains
 * the specified data. If the data is found, the index of the node is returned.
 * If the data is not found, or if the list or data is NULL, the function returns -1.
 *
 * @param list A pointer to the list to be searched.
 * @param data A pointer to the data to be found in the list.
 * @return The index of the first occurrence of the specified data in the list,
 *         or -1 if the data is not found or if the list or data is NULL.
 */
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