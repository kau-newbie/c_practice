https://www.geeksforgeeks.org/scanf-and-fscanf-in-c/

geeksforgeeks사이트의 내용을 참고하여
filestream에 관해 공부를 하던 중, 의문점이 생겼다.
우선, 해당 사이트의 글은

name age city
abc  25  hyberabad
bef  25  delhi
cce  65  bangalore

라는 내용의 text1.txt를 만들고,
```
// C Program to demonstrate fscanf
#include <stdio.h>

// Driver Code
int main()
{
	FILE* ptr = fopen("abc.txt", "r");
	if (ptr == NULL) {
		printf("no such file.");
		return 0;
	}

	/* Assuming that abc.txt has content in below
	format
	NAME AGE CITY
	abc	 12 hyderabad
	bef	 25 delhi
	cce	 65 bangalore */
	char buf[100];
	while (fscanf(ptr, "%*s %*s %s ", buf) == 1)
		printf("%s\n", buf);

	return 0;
}
```
에서 실행하면, city열들만 출력된다는 내용이였다.

처음에 든 생각은, %s %s %s에서 앞에 두 개의 스트링포맷은 *을 추가했으므로, 
어떤 작용으로 세번째 스트링만 읽는구나, 싶었다. 그런데, %s는 \0까지 읽는 게 아닌가?
어디까지가 str인지 알고 읽는 거지? 단순히 space로도 알 수가 있나? 혹은 그냥 space가 아니라
tab키로 해놨나? 이런저런 생각이 들어 우선, 코드를 조금 바꿔 *를 전부 없애보았다.

```char buf[100];
	while (fscanf(ptr, "%s %s %s ", buf) == 1)
		printf("%s\n", buf);
```
결과는, 잠시 응답이 없다가 이내 강제종료됐다.
정상적인 종료는 아닌 것이, 아무래도 %s인데 \0이 없어서
한 줄을 끝까지 읽다보니 무한loop에 빠진 게 아닌가 싶었다. 그런데 \n은?
\n은 못읽나..? 아니면 혹시 한 줄을 읽는데 %s로 \n까지 읽고, 나머지 두개의 str을 찾아
loop에 빠져버린건가?

scanf부터 알아봤다.
https://www.tutorialspoint.com/c_standard_library/c_function_scanf.htm
 int scanf(const char *format, ...)

Whitespace character, Non-whitespace character and Format specifiers. 
A format specifier will be like [=%[*][width][modifiers]type=] as explained below −

- *

> This is an optional starting asterisk indicates that the data is to be read from the stream 
but ignored, i.e. it is not stored in the corresponding argument.


- width

> This specifies the maximum number of characters to be read in the current reading operation.


- modifiers

> Specifies a size different from int (in the case of d, i and n), unsigned int (in the case of o, u and x) or 
float (in the case of e, f and g) for the data pointed by the corresponding additional argument:
h : short int (for d, i and n), or unsigned short int (for o, u and x) l : long int (for d, i and n), or unsigned long int (for o, u and x), or double (for e, f and g) L : long double (for e, f and g)



- type

> A character specifying the type of data to be read and how it is expected to be read. 

여기서 type을 s로 쓴 것이다.
String of characters. This will read subsequent characters until a whitespace is found 
(whitespace characters are considered to be blank, newline and tab).

s의 설명은 위와 같았다. 여기서 다시한번 whitespace character가 궁금해졌다.
> Space, tab, line feed (newline), carriage return, form feed, 
and vertical tab characters are called "white-space characters" 
because they serve the same purpose as the spaces between words and lines on a printed page 
라고 한다.

white space가 space도 포함하면..., 왜 loop에 빠지는 거지...?

생각해보니 scanf를 왜 봤더라
다시 fscanf로 가본다.

> int fscanf(FILE *stream, const char *format, ...)

다른 설명은 다 똑같았는데, 예제를 보니 뭔가 알것도 같았다.
https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm

```
#include <stdio.h>
#include <stdlib.h>


int main () {
   char str1[10], str2[10], str3[10];
   int year;
   FILE * fp;

   fp = fopen ("file.txt", "w+");
   fputs("We are in 2012", fp);
   
   rewind(fp);
   fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);
   
   printf("Read String1 |%s|\n", str1 );
   printf("Read String2 |%s|\n", str2 );
   printf("Read String3 |%s|\n", str3 );
   printf("Read Integer |%d|\n", year );

   fclose(fp);
   
   return(0);
}
```

~~space (whitesapce character)마다 한 문장으로 인식했다.~~
그런데 whitespace 중 space로 읽어들였을 때는,~~
buff안에서 \n이나 \0이 아니기 때문에,~~

~~아마 처음 예제에서~~
~~%s %s %s는 처음 생각처럼~~
~~%s로 한 줄을 끝까지 읽고 나머지 두 개의 str을 찾아 루프를 돌지 않았을까...?~~

~~해서 txt파일 안에 \0을 넣어보았다.~~

~~name\0 age\0 city~~
abc\0  25\0  hyberabad~~
bef  25  delhi~~
cce  65  bangalore~~

~~실패..인데 아 정신이 없다.~~

일단 printf가 한 줄도 실행 안되는 걸 보면. %s가 못 찾고 끝까지 헤맨다는 게 분명한디....
format과 함께 " " 안에 있는 space때문인가, 싶기도 해서 없애고 돌려봤다.
"%s%s%s"로 바꿨다는 얘기다.
아 어림도 없다.

txt파일 하도 열어서 파일포인터가 eof로 가있나? (몰라서 하는 얘기다, 진짜....)
싶어서 
> int fseek(FILE *stream, long int offset, int whence)
도 써서 파일포인터를 처음으로 옮겨도 봤다.

``` name ```
까진 읽었다. 감동이긴 하다. 그리고 멈췄다.

```
char buf[100];
    fseek(ptr,0,SEEK_SET);
	while (fscanf(ptr, "%s %s %s ", buf) == 1)
		printf("%s\n", buf);
```
니까 space만나기 전까지 name을 읽고, 다음 두 단어도 마찬가지고, 
출력은 %s 하나니까 name출력 후 newline. 인데 왜 멈추지.

```
char buf[100];
    fseek(ptr,0,SEEK_SET);
	while (fscanf(ptr, "%s %s %s ", buf) == 1)
		printf("%s %s %s\n", buf);
```
로 바꿔보았다.

```name (null) (null)```
나한테 왜그래?
혹시 몰라 본 txt파일에는 name(space)age(space)city였다.
아니면 이거 혹시, 
fscanf(ptr, "%s %s %s ", buf)에서 space까지 합쳐져서 ㅜ
버퍼 안에 현재 

<--
-----------------------------------
n a m e (space) (sapce) 
-----------------------------------

로 차있는 게 아닐까...? \n이 없으니까 라고 하기엔
printf를 했그든요

```
char buf[100];
    fseek(ptr,0,SEEK_SET);
	while (fscanf(ptr, "%s", buf) == 1)
		printf("%s\n", buf);
```
로 바꾸어보았다.

```
name
age
city
abc
25
hyberabad
bef
25
delhi
cce
65
bangalore
```
로 나왔다.

(참고로 텍스트 파일은 아래와 같다.
NAME AGE CITY
	abc	 12 hyderabad
	bef	 25 delhi
	cce	 65 bangalore */ )

```
	char buf[100];
    fseek(ptr,0,SEEK_SET);
	while (fscanf(ptr, "%s ", buf) == 1)
		printf("%s\n", buf);
```
로 fscanf() 에서 %s(space)를 넣어도 마찬가지이다.



___

뜬금없긴 한데
재밌는 걸 발견했다.
```
#include<stdio.h>

int main(){
    printf(' ');
    return 0;
}
```
의 실행결과는?
> 오류로 강제종료된다.
gcc compiler에서는 

```
test1-1.c:4:12: warning: passing argument 1 of 'printf' makes pointer from integer without a cast [-Wint-conversion]
    4 |     printf(' ');
      |            ^~~
      |            |
      |            int
In file included from test1-1.c:1:
c:\mingww64\mingw64\x86_64-w64-mingw32\include\stdio.h:498:48: note: expected 'const char * restrict' but argument is of type 'int'
  498 |   int __cdecl printf(const char * __restrict__ _Format,...);
  ```
로 나온다. (int)32랜다.

space는 왜 숫자로 읽어..?
ascii그대로 읽는다.
printf사용법 자체를 몰랐나보다. 'a'도 마찬가지이다. 파이썬 한동안 썼더니 어지럽네;;
'\0'넣었을 때는 아무것도 출력하지 않는다.


```
int main(){
    printf(" ");
    return 0;
}
```

- 이건 된다. " "로 큰 따옴표를 사용해야 하나보다. ' ' 는 안되나보네;;

___

"%s %s %s"는 (char [9]), "%s %s %s\n"는 (char[10])이다. ""안에서는 자동 \n이 추가 되나..?

printf를 알아봤다.

> int printf(const char *format, ...)

format 설명이다.
>> format − This is the string that contains the text to be written to stdout. It can optionally contain embedded format tags that are replaced by the values specified in subsequent additional arguments and formatted as requested. Format tags prototype is %[flags][width][.precision][length]specifier, which is explained below −

<span style:color="red">"replaced by the values"</span>


___
헛짓하고 있었는데, 석사횽이 알려줬다.

https://aeunhi99.tistory.com/39
사이트에 나와있듯이, scanf , fscnaf는 포매팅당 변수 하나였다.

```
scanf("%s %s", x1, x2); 
```
이런 식이다.
아 삽질이 드디어 끝!
