void fun(FILE *fin,FILE*fout){
    for(ST t;fscanf(fin,"%s%s%d%d%lf",t.name,t.id,&t.gender,&t.age,&t.scored)!=EOF;output(&t,fout));
}


struct ListNode *createlist(){
    struct ListNode*head=(struct ListNode*)malloc(sizeof(struct ListNode));
    int data;
    scanf("%d",&data);
    if(data==-1)return NULL;
    head->data=data;
    head->next=NULL;

    while(1){
        scanf("%d",&data);
        if(data==-1)break;
        struct ListNode*temp=(struct ListNode*)malloc(sizeof(struct ListNode));
        temp->data=data;
        temp->next=head;
        head=temp;       
    }   

    return head;
}