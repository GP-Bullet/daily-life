#ifndef __LIBKERNEL_LIST_H
#define __LIBKERNEL_LIST_H

struct list_elem{
    struct list_elem* prev;
    struct list_elem* next;
};

struct list {
    struct list_elem head;
    struct list_elem tail;
};







#endif