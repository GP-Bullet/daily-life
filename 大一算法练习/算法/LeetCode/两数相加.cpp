//虚拟头结点
//链表双指针技巧
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *p1=l1,*p2=l2;
        int jw=0;
        ListNode *xuni=new ListNode(-1);//分配空间
        //新链表
        ListNode *p=xuni;
        while(p1!=nullptr||p2!=nullptr||jw>0){
            int val=jw;
            if(p1!=nullptr){
                val+=p1->val;
                p1=p1->next;
            }
            if(p2!=nullptr){
                val+=p2->val;
                p2=p2->next;
            }
            jw=val/10;
            val=val%10;//??
            //构造新结点
            p->next=new ListNode(val);
            p=p->next;        
        }
            return xuni->next;
    }
};