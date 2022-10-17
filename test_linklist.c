#include<stdio.h>
#include<stdlib.h>

typedef struct _node* nodeptr;

typedef struct _node{
    int key;
    nodeptr next;
}node;

//노드삽입
void mk_node(int key, node* head);
//노드소멸
node* init_node(node* head);
//노드탐색
int fd_node(int key, node* head);
//노드삭제
void rm_node(int count, node* head);
//리스트 출력
void print_list(node* head);

int main(){

    //아주 초기의 헤드&테일.
    node* head = (node*)malloc(sizeof(node));
    node* tail = (node*)malloc(sizeof(node));
    head->next = tail;
    tail->next = tail;

    while(1){
        int choice_num=0;
        printf("\n옵션 선택\n1.노드생성/소멸\n2.노드삽입\n3.노드삭제\n4.노드출력\n5.종료\n=> ");
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
                printf("\n새로 생성할 노드의 키값: ");
                scanf("%d",&k);
                mk_node(k, head);
            }
            else if(choice_num==3){
                int k=0;
                printf("\n어떤 키 값을 가진 노드를 지우시겠습니까?");
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
            printf("\n잘못된 입력입니다.");
            continue;
        }
    }
    return 0;
}

void mk_node(int key, node* head){
    node *p; //새로 만들어질 노드 주소.
    p=(node*)malloc(sizeof(node));
    p->key = key;
    p->next=head->next;
    head->next = p;
    printf("\nmaking a node complete.");
}

node* init_node(node* head){
    
    node* h; //처음엔 변수로, 그 다음 새로운 해드로.
    node* t; //처음엔 지울 노드를 저장, 그 후 새로운 테일.
    if(head){
    //지우는 단계 먼저
        h = head;
        while(h->next->next != h->next){
            t = h->next;
            h->next = t->next;
            free(t);
        }
        t = h->next;
        free(t); //tail free.
        free(h); //마지막으로 헤드도 free.
    }
    //이제 malloc으로 새로운 헤드와 테일
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
    //찾았으니까 반환
    return count;
}

void rm_node(int count, node* head){
    node* p; //직전 주소 담을 것.
    node* targt; //여기에다 담고 free시킬 것.
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
    printf("끝.");
}