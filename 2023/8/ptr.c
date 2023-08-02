struct list_elem {
   struct list_elem* prev; // 前躯结点
   struct list_elem* next; // 后继结点
};

/* 链表结构,用来实现队列 */
struct list {
/* head是队首,是固定不变的，不是第1个元素,第1个元素为head.next */
   struct list_elem head;
/* tail是队尾,同样是固定不变的 */
   struct list_elem tail;
};



int main(){
    struct list *li;
    li->head.next=li->tail;
    return 0;
}