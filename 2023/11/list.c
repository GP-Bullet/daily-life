#include "list.h"

void list_init(struct list* list){
    list -> head.prev = NULL;
    list -> head.next = &list->tail;
    list ->tail.prev = &list->head;
    list -> tail.next = NULL;
}

//elem 插入到 before之前
void list_insert_before(struct list_elem* before,struct list_elem * elem){
    enum
}