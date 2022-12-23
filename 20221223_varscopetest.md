#### 어제 동생 도와주다 재밌는 걸 발견했다.

```
  #include<stdio.h>

int main(){
    int c=0;
    printf("\n%d",c);
    while(c<1){
        printf("\n%d",c);
        int c=0;
        printf("\n%d",c);
        c++;
    }
    return 0;
}
```

`루프를 돌까?`

>돈다.

vs code 기능을 이용해봤다.   
`int c=0;`으로 제일 처음 루프 밖에서 선언한 부분을 한번 클릭,

결과는 루프 안에서 새 c를 선언하기 전까지만 같은 c로 읽었다.  
아니 조건문은 그래도 루프 돌 때 안의 c로 해야하는 거 아닌가...?


코드를 조금 바꿔서 {} block안에서 변수를 선언할 때 scope를 확인해봤다.

```
  #include<stdio.h>

int main(){
    int c=0;
    printf("\n%d",c);
    while(c<1){
        printf("\n%d",c);
        int d=0;
        printf("\n%d",c);
        c++;
    }
    printf("\nd는 %d.",d);
    return 0;
}
```
compiler가 {}밖에서 d는 undefined랜다.
이건 몰랐네 나 왜 몰랐지? 그럼 마지막으로 while조건문에서 쓰는 변수는 {}(block) 밖에서 쓰나?

```
  #include<stdio.h>

int main(){
    while(c<1){
        printf("\n%d",c);
        int c=0;
        printf("\n%d",c);
        c++;
    }
    return 0;
}
```
아 근데 생각해보니까, 이러면 c<1에서 c를 컴파일러가 모른다 ㅋㅋ 
얘네 위에서부터 읽지 참.... 
```
  #include<stdio.h>

int main(){
    do{
        int c=0;
        printf("\n%d",c);
        c++;
    }while(c<1);
    return 0;
}
```
do while문도 마찬가지다. 위에서 읽는 거랑 별개로 {}(block)바깥에서 없던걸 못읽나 보다.

와 생각해보니까 `for(int i=0; i<n; i++)` 도 i를 {}(block)밖에서 선언한 건가...?
>그건 아니다.
```
  #include<stdio.h>

int main(){
    int sum=0;
    for(int i=0;i<10;i++){
        sum += i;
    }
    printf("\n%d", i);
    return 0;
}
```
i가 제일 아래 printf에서 없댄다.  
약간 hierarchy가 있는 것 같다.
```
main(
    조건문(
      {}블락(
      
      )
    )
)
```
끄읕 배고프다 점심 뭐먹지
