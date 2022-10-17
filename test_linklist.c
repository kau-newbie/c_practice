#include<stdio.h>
#include<stdlib.h>

typedef struct _node* nodeptr;

typedef struct _node{
    int key;
    nodeptr next;
}node;

//������
void mk_node(int key, node* head);
//���Ҹ�
node* init_node(node* head);
//���Ž��
int fd_node(int key, node* head);
//������
void rm_node(int count, node* head);
//����Ʈ ���
void print_list(node* head);

int main(){

    //���� �ʱ��� ���&����.
    node* head = (node*)malloc(sizeof(node));
    node* tail = (node*)malloc(sizeof(node));
    head->next = tail;
    tail->next = tail;

    while(1){
        int choice_num=0;
        printf("\n�ɼ� ����\n1.������/�Ҹ�\n2.������\n3.������\n4.������\n5.����\n=> ");
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
                printf("\n���� ������ ����� Ű��: ");
                scanf("%d",&k);
                mk_node(k, head);
            }
            else if(choice_num==3){
                int k=0;
                printf("\n� Ű ���� ���� ��带 ����ðڽ��ϱ�?");
                scanf("%d",&k);
                rm_node(fd_node(k,head), head);
            }
            else if(choice_num==4){
                print_list(head);
            }
            else if(choice_num==5){
                break;
            }

        }
        else{
            printf("\n�߸��� �Է��Դϴ�.");
            continue;
        }
    }
    return 0;
}

void mk_node(int key, node* head){
    node *p; //���� ������� ��� �ּ�.
    p=(node*)malloc(sizeof(node));
    p->key = key;
    p->next=head->next;
    head->next = p;
    printf("\nmaking a node complete.");
}

node* init_node(node* head){
    
    node* h; //ó���� ������, �� ���� ���ο� �ص��.
    node* t; //ó���� ���� ��带 ����, �� �� ���ο� ����.
    if(head){
    //����� �ܰ� ����
        h = head;
        while(h->next->next != h->next){
            t = h->next;
            h->next = t->next;
            free(t);
        }
        t = h->next;
        free(t); //tail free.
        free(h); //���������� ��嵵 free.
    }
    //���� malloc���� ���ο� ���� ����
    h= (node*)malloc(sizeof(node));
    t = (node*)malloc(sizeof(node));
    h->next= t;
    t->next = t;
    printf("\ninit complete.");
    return h;
}

int fd_node(int key, node* head){
    node* p;
    p=head;
    int count=0;
    while(p->key != key){
        p=p->next;
        count ++;
    }
    printf("\ncount complete.");
    //ã�����ϱ� ��ȯ
    return count;
}

void rm_node(int count, node* head){
    node* p; //���� �ּ� ���� ��.
    node* targt; //���⿡�� ��� free��ų ��.
    p=head;
    while(count>1){
        p=p->next;
    }
    targt = p->next;
    p->next = targt->next;
    free(targt);
    printf("\ndelete complete.");
}

void print_list(node* head){
    node* p;
    p=head->next;
    while(p->next!=p){
        printf("%d ",p->key);
        p=p->next;
    }
    printf("��.");
}