typedef int elem_t;
typedef long unsigned int size_t;

struct node {
    elem_t data;
    struct node* next;
    struct node* prev;
};

struct list {
    size_t size;
    struct node* head;
    struct node* tail;
};

struct list* list_constructor();
int list_destructor(struct list* lst);
int push_front(struct list* lst, const elem_t data);
int push_back(struct list* lst, const elem_t data);
int pop_front(struct list* lst);
int pop_back(struct list* lst);
int insert_node(struct list* lst, const size_t index, const elem_t data);
int delete_node(struct list* lst, const size_t index);
int find_and_get_pos(const struct list* lst, const elem_t data); 
struct node* find_and_get_ptr(const struct list* lst, const elem_t data);