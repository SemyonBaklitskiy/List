#include "list_functions.h"
#include <stdio.h>

int main() {
    struct list* lst = list_constructor();
    push_back(lst, 0);
    push_back(lst, 1);
    push_front(lst, -1);
    insert_node(lst, 1, 228);

    printf("%d\n", find_and_get_pos(lst, 228));
    printf("%d\n", find_and_get_pos(lst, -1));
    printf("%d\n", find_and_get_pos(lst, 1));

    list_destructor(lst);

    return 0;
}
