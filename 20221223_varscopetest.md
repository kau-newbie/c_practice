# 어제 동생 도와주다 재밌는 걸 발견했다.

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

결과는 루프 안에서 c를 선언하기까지만 같은 c로 읽었다.  
아니 조건문은 그래도 루프 돌 때 안의 c로 해야하는 거 아닌가...?
