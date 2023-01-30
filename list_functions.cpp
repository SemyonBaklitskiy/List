#include <stdlib.h>
#include "list_functions.h"
#include "list_errors.h"

#define PRINT_ERROR(error) processor_of_errors(error, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define CHECK_NULLPTR(pointer, error, ...) if (pointer == NULL) { PRINT_ERROR(error); __VA_ARGS__; }

static void free_nodes(struct node* freeNode);
static struct node* get_element_by_index(const struct list* lst, const size_t index);

struct list* list_constructor() {
    struct list* lst = (struct list*)calloc(1, sizeof(list));
    
    CHECK_NULLPTR(lst, CALLOC_RETURNED_NULL, return NULL);

    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;

    return lst;
}

int list_destructor(struct list* lst) {
    CHECK_NULLPTR(lst, NULLPTR_GIVEN, return NULLPTR_GIVEN);

    free_nodes(lst->head);
    free(lst);
    lst = NULL;

    return NO_ERRORS;
}

int push_front(struct list* lst, const elem_t data) {
    CHECK_NULLPTR(lst, NULLPTR_GIVEN, return NULLPTR_GIVEN);

    struct node* newNode = (struct node*)calloc(1, sizeof(node));
    CHECK_NULLPTR(newNode, CALLOC_RETURNED_NULL, return CALLOC_RETURNED_NULL);

    newNode->data = data;
    newNode->next = lst->head;
    newNode->prev = NULL;

    if (lst->head != NULL)
        lst->head->prev = newNode;

    lst->head = newNode;

    if (lst->tail == NULL) 
        lst->tail = newNode;

    ++lst->size;
    return NO_ERRORS;
}

int push_back(struct list* lst, const elem_t data) {
    CHECK_NULLPTR(lst, NULLPTR_GIVEN, return NULLPTR_GIVEN);

    struct node* newNode = (struct node*)calloc(1, sizeof(node));
    CHECK_NULLPTR(newNode, CALLOC_RETURNED_NULL, return CALLOC_RETURNED_NULL);

    newNode->data = data;
    newNode->prev = lst->tail;
    newNode->next = NULL;

    if (lst->tail != NULL)
        lst->tail->next = newNode;

    lst->tail = newNode;

    if (lst->head == NULL)
        lst->head = newNode;

    ++lst->size;
    return NO_ERRORS;
}

int pop_front(struct list* lst) {
    CHECK_NULLPTR(lst, NULLPTR_GIVEN, return NULLPTR_GIVEN);
    CHECK_NULLPTR(lst->head, EMPTY_LIST, return EMPTY_LIST);

    struct node* head = lst->head;

    if (head->next != NULL) {
        head->next->prev = NULL;
        lst->head = head->next;

    } else {
        lst->head = NULL;
        lst->tail = NULL;
    }

    --lst->size;
    free(head);

    return NO_ERRORS;
}

int pop_back(struct list* lst) {
    CHECK_NULLPTR(lst, NULLPTR_GIVEN, return NULLPTR_GIVEN);
    CHECK_NULLPTR(lst->tail, EMPTY_LIST, return EMPTY_LIST);

    struct node* tail = lst->tail;

    if (tail->prev != NULL) {
        tail->prev->next = NULL;
        lst->tail = tail->prev;

    } else {
        lst->head = NULL;
        lst->tail = NULL;
    }

    --lst->size;
    free(tail);

    return NO_ERRORS;
}

int insert_node(struct list* lst, const size_t index, const elem_t data) { //inserting after support element in list
    CHECK_NULLPTR(lst, NULLPTR_GIVEN, return NULLPTR_GIVEN);

    if (lst->size == 0) {
        struct node* newNode = (struct node*)calloc(1, sizeof(node));
        CHECK_NULLPTR(newNode, CALLOC_RETURNED_NULL, return CALLOC_RETURNED_NULL);

        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;

        lst->head = newNode;
        lst->tail = newNode;
        lst->size = 1;

        return NO_ERRORS;
    }

    struct node* supElement = get_element_by_index(lst, index);
    CHECK_NULLPTR(supElement, WRONG_INDEX, return WRONG_INDEX);

    struct node* newNode = (struct node*)calloc(1, sizeof(node));
    CHECK_NULLPTR(newNode, CALLOC_RETURNED_NULL, return CALLOC_RETURNED_NULL);

    if (supElement->next == NULL) 
        return push_back(lst, data);

    newNode->data = data;
    newNode->prev = supElement;
    newNode->next = supElement->next;

    supElement->next->prev = newNode;
    supElement->next = newNode;
    ++lst->size;

    return NO_ERRORS;
}

int delete_node(struct list* lst, const size_t index) {
    CHECK_NULLPTR(lst, NULLPTR_GIVEN, return NULLPTR_GIVEN);

    if (lst->size == 0) {
        PRINT_ERROR(EMPTY_LIST);
        return EMPTY_LIST;
    }

    struct node* deleteNode = get_element_by_index(lst, index);
    CHECK_NULLPTR(deleteNode, WRONG_INDEX, return WRONG_INDEX);

    if (deleteNode->next == NULL) {
        return pop_back(lst);

    } else if (deleteNode->prev == NULL) {
        return pop_front(lst);
    }

    deleteNode->next->prev = deleteNode->prev;
    deleteNode->prev->next = deleteNode->next;

    free(deleteNode);
    --lst->size;

    return NO_ERRORS;
}

int find_and_get_pos(const struct list* lst, const elem_t data) {
    CHECK_NULLPTR(lst, NULLPTR_GIVEN, return -1);

    size_t result = 0;
    struct node* lookingNode = lst->head;

    for (result = 0; result < lst->size; ++result) {
        if (data == lookingNode->data)
            return result;

        lookingNode = lookingNode->next;
    }

    return -1;
}

struct node* find_and_get_ptr(const struct list* lst, const elem_t data) {
    CHECK_NULLPTR(lst, NULLPTR_GIVEN, return NULL);
    
    struct node* result = lst->head;

    for (size_t listIndex = 0; listIndex < lst->size; ++listIndex) {
        if (result->data == data)
            return result;

        result = result->next;
    }

    return NULL;
}

static void free_nodes(struct node* freeNode) {
    freeNode->prev = NULL;

    if (freeNode->next == NULL) {
        free(freeNode);
        return;
    }

    free_nodes(freeNode->next);
    freeNode->next = NULL;
    free(freeNode);
}

static struct node* get_element_by_index(const struct list* lst, const size_t index) {
    if (index > lst->size - 1) 
        return NULL;

    struct node* result = NULL;

    if (index >= lst->size / 2) {
        result = lst->tail;

        for (size_t i = 0; i < lst->size - 1 - index; ++i) 
            result = result->prev;

    } else {
        result = lst->head;

        for (size_t i = 0; i < index; ++i) 
            result = result->next;
    }

    return result;
}