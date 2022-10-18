#include<stdio.h>
#include<stdlib.h>

//structure node
typedef struct _dnode* dptr;

typedef struct _dnode{
    dptr prev;
    dptr next;
    int value;
}dnode;

//init_node
dnode* init_node(dnode* head);
//in processing 'init_node', making head&tail
dnode* mk_hnt();
//insert_node
int in_node(int val, dnode*head); /*insert a node right next to head?
                                    no.before tail.*/
//delete_node
int del_node(int count, dnode*head);
//find_target_node
int fd_node(dnode*head, int val);
//print_node
void print_node(dnode *head);

int main(){
    dnode* head=mk_hnt();
    while(1){
        int choice_num=0;
        printf("\nchoose options below.\n1.initialize the list.\n2.make a node.\n3.delete a node.\n4.print all nodes.\n5.exit.\n=> ");
        fflush(stdin);
        int securty = scanf("%d",&choice_num);
        if (securty >1){
            break;
        }
        if(choice_num>=1 && choice_num<=5){
            if(choice_num==1){
                head = init_node(head);
            }
            else if(choice_num==2){
                int k=0;
                printf("\nwhich value do you want to input to newnod?: ");
                scanf("%d",&k);
                in_node(k, head);
            }
            else if(choice_num==3){
                int k=0;
                printf("\nwhat node do you want to delete?\nspecify with the value: ");
                scanf("%d",&k);
                del_node(fd_node(head,k), head);
            }
            else if(choice_num==4){
                print_node(head);
            }
            else if(choice_num==5){
                break;
            }

        }
        else{
            printf("\nnot available input.");
            continue;
        }
    }
    return 0;
}


//init_node
dnode* init_node(dnode* head){
    //if head already exit, delete it.
    if(head){
        dnode* p; //temp pointer for prev_targt.
        dnode* t; //temp pointer for target.
        p=head; //start from head.
        while(p->next->next!=p->next){
            t=p->next;
            t->next->prev = p;
            p->next = t->next;
            free(t);
        }
        t=p->next;
        free(t);
        free(p); //end of free()
    }
    printf("\ninit list complete!");
    printf("\nnow making new h&t...");
    return mk_hnt(); //return head pointer.
}

//in processing 'init_node', making head&tail
dnode* mk_hnt(){
    dnode* head = (dnode*)malloc(sizeof(dnode));
    dnode* tail = (dnode*)malloc(sizeof(dnode));
    head->value=-1;
    tail->value=99; //meaningless stillyet.
    head->prev=head;
    head->next=tail;
    tail->prev=head;
    tail->next=tail;
    printf("\nmake head&tail complete!");
    return head;
}

//many times request from my pro. that insert node from backwards.
//insert_node
int in_node(int val, dnode*head){
    dnode* h;
    h=head;
    while(h->next->next!=h->next){
        h=h->next;
    }
    dnode* p; //temp pointer
    p=h; /* in some books, they try to solve this prob. 
          with double pointer. but i dont wanna do that.*/
    h=(dnode*)malloc(sizeof(dnode));
    h->next = p->next;
    p->next = h;
    h->prev = p;
    h->value = val; //finish with inputting the value.
    printf("\ninsert complete!");
    return 1; //maybe meaning of complete?
}

//delete_node
int del_node(int count, dnode*head){
    if(count == -1){
        printf("\nexit the delete option.");
        return -1;
    }
    dnode* h;
    dnode* p;
    h=head->next; //caution:possibly, head's value == val
    p=h->next;
    while(count>1){ //same startpoint, but did counting till h->val==val.
        count --;
        h=h->next;
        p=h->next;
    }
    if(p->next==p){
        p->prev = h->prev;
        h->prev->next=p;
        free(h);
        printf("\ndelete complete!");
        return -1;
    }/*caution when p==tail.*/
    p->next->prev = h;
    h->next = p->next;
    free(p);
    printf("\ndelete complete!");
    return 1; //1 means success.
}

//find_target_node
//���� ó�� ���� value���� �������� ��ȯ�Ѵ�.
int fd_node(dnode*head, int val){
    int countt=0;
    head = head->next; // are they diff? then it'll be fine.
    while(head->value != val){ /*caution! if init head == head,possibly, head's value == val*/
        head=head->next;
        countt++;
        if(head->next==head){
            printf("\nthere's no target node.");
            countt = -1;
            return -1;
        } 
    }
    printf("\nfind out the target!");
    return countt;
}

//print_node
void print_node(dnode *head){
    head=head->next; //caution when to read head.
    while(head->next!=head){
        printf("%d ",head->value);
        head=head->next;
    }
    printf("end.");
}