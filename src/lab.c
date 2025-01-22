#include <lab.h>


list_t *list_add(list_t *list, void *data) {
    if (list == NULL || data == NULL) {
        return NULL;
    }

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = data;

    if (list->head == NULL) {
        // Initialize the sentinel node
        list->head = (node_t *)malloc(sizeof(node_t));
        if (list->head == NULL) {
            free(new_node);
            return NULL;
        }
        list->head->next = list->head;
        list->head->prev = list->head;
    }

    new_node->next = list->head->next;
    new_node->prev = list->head;

    list->head->next->prev = new_node;
    list->head->next = new_node;

    list->size++;
    return list;
}
