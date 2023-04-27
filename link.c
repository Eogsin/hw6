#include<stdio.h>
#include<stdlib.h>
/*[----- [김승진] [2017038092] -----]*/
typedef struct Node {		//구조체
	int key;
	struct Node* link;
} listNode;

typedef struct Head {		
	struct Node* first;
}headNode;

headNode* initialize(headNode* h);  //아래에 주석 달겠습니다. 
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()							////메인 함수에서는 사용자로부터 명령어를 입력 받아 해당 명령어에 따라 함수들을 호출하고, q를 입력받으면 프로그램 종료 
{
	char command;				
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");		//영상참고//
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {		//z일떄 
		case 'z': case 'Z':
			headnode = initialize(headnode);	
			break;
		case 'p': case 'P':		//p일때
			printList(headnode);
			break;
		case 'i': case 'I':		//I일때 
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':		//D일때
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':		//N일때 
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':		//E일때
			deleteLast(headnode);
			break;
		case 'f': case 'F':			//F일때
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':		//T일때
			deleteFirst(headnode);
			break;
		case 'r': case 'R':		//R일때
			invertList(headnode);
			break;
		case 'q': case 'Q':  	//Q일때
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');	//q종료 

	return 1;
}

headNode* initialize(headNode* h) {		//연결리스트를 초기화한다. 기존에 생성되어 있던 노드 들을 모두 삭제하고 
										//새로운 헤드노드를 생성하여 반환한다.	
	if(h != NULL)						//h가 null이 아니면				
		freeList(h);					//freeList 함수를 호출하여 기존에 생성되어 있던 노드들을 모두 삭제한다.

	headNode* temp = (headNode*)malloc(sizeof(headNode)); 		//temp라는 이름의 headNode 포인터 변수를 선언하고, malloc 함수를 호출하여 메모리 할당
	temp->first = NULL;					//temp가 가리키는 구조체의 first 멤버 변수를 NULL로 초기화
	return temp;						//리턴 temp
}

int freeList(headNode* h){				//연결 리스트에 존재하는 모든 노드들을 삭제하고 헤드노드를 해제
	listNode* p = h->first;				//리스트의 첫번째 노드를 가리키는 포인터 p를 헤드노드의 첫번째 노드를 가리키는 포인터로 초기화
	listNode* prev = NULL;				//포인터 prev를 NULL로 초기화
	while(p != NULL) {					//while 루프를 돌며 포인터 p가 NULL이 아니면 반복
		prev = p;						//루프 안에서, prev에 현재 p가 가리키는 노드를 대입
		p = p->link;					//p를 다음 노드로 이동
		free(prev);						//prev가 가리키는 노드를 메모리에서 해제
	}
	free(h);							//포인터 h를 해제
	return 0;
}


int insertNode(headNode* h, int key) {	//주어진 key값을 가지는 노드를 연결리스트에 삽입한다. key값에 따라 연결리스트가 정렬되도록 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));		//새로운 노드를 동적 할당하여 key값과 link를 초기화
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)										//h의 first 값이 NULL이라면, 연결 리스트가 비어있는 것이므로 										
	{															//새로운 노드를 첫번째 노드로 추가해주고 함수를 종료	
		h->first = node;
		return 0;
	}

	listNode* n = h->first;									//현재 연결 리스트의 노드들을 순차적으로 탐색하면서 새로운 노드의 key값이 현재 노드의 key값보다 작거나 같을 경우
	listNode* trail = h->first;								//새로운 노드를 현재 노드 앞에 삽입해주고 함수를 종료
															//현재 노드가 첫번째 노드인 경우와 그렇지 않은 경우를 나누어 처리
	while(n != NULL) {
		if(n->key >= key) {									//새로운 노드의 key값이 모든 노드들의 key값보다 크다면
			if(n == h->first) {								//새로운 노드를 연결 리스트의 가장 뒤에 추가 
				h->first = node;							//while문에서 n이 NULL이 되어 빠져나온 경우
				node->link = n;								//마지막 노드 뒤에 새로운 노드를 추가
			} else { 
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	trail->link = node;
	return 0;
}

int insertLast(headNode* h, int key) {		//연결리스트의 마지막 주어진 key값을 가지는 노드를 삽입한다.

	listNode* node = (listNode*)malloc(sizeof(listNode));	//새로운 노드를 생성하고, key 값과 link 값 (즉, 다음 노드를 가리키는 포인터)을 설정  
	node->key = key;			
	node->link = NULL;

	if (h->first == NULL)									//만약 연결 리스트가 비어있다면, 헤드 노드의 첫번째 노드로 새로운 노드를 지정해주고,
	{														//함수를 종료
		h->first = node;
		return 0;
	}

	listNode* n = h->first;								//연결 리스트가 비어있지 않다면, 현재 노드를 가리키는 포인터인 n을 헤드 노드의 첫번째 노드로 설정
	while(n->link != NULL) {							// n의 다음 노드가 NULL일 때까지 반복문을 실행
		n = n->link;									//이후 n의 다음 노드가 NULL인 마지막 노드를 찾았으므로, 이 마지막 노드의 link 값을 새로운 노드의 포인터 값으로 지정
	}
	n->link = node;
	return 0;
}

int insertFirst(headNode* h, int key) {								//연결리스트의 첫번째에 주어진 key값을 가지는 노드를 삽입합니다.

	listNode* node = (listNode*)malloc(sizeof(listNode));			//매개변수로는 연결 리스트의 헤드 노드를 가리키는 포인터 h와 추가할 key 값을 받음
	node->key = key;												//새로운 노드를 생성하고, 매개변수로 받은 key 값을 할당합니다.
	node->link = h->first;											//노드의 link 필드를 현재 첫 번째 노드를 가리키도록 합니다.
	h->first = node;												//헤드 노드의 first 필드를 새로 추가한 노드를 가리키도록 변경

	return 0;
}

int deleteNode(headNode* h, int key) {					//연결리스트에서 주어진 key값을 가지고 노드를 삭제합니다.

	if (h->first == NULL)								//만약 연결리스트가 비어있다면 "nothing to delete."를 출력하고 0을 반환합니다.
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;								//삭제할 노드를 찾으면 그 노드를 삭제하고 0을 반환
	listNode* trail = NULL;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) {
				h->first = n->link;
			} else { 
                trail->link = n->link;
			}
			free(n);
			return 0;
		}
														//삭제할 노드를 찾지 못하면 "cannot find the node for key = %d"를 출력하고 0을 반환합니다.
		trail = n;
		n = n->link;
	}

	printf("cannot find the node for key = %d\n", key);
	return 0;

}

int deleteLast(headNode* h) {		//마지막 노드를 삭제한다.

	if (h->first == NULL)			//연결리스트가 비어있을 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;			//리스트의 첫번째 노드를 가리키는 포인터
	listNode* trail = NULL;			//삭제할 노드의 이전 노드를 가리키는 포인터

	if(n->link == NULL) {			//리스트에 노드가 하나만 존재할 경우
		h->first = NULL;			//리스트를 빈 리스트로 만듬
		free(n);					//노드를 메모리에서 해제
		return 0;
	}

	while(n->link != NULL) {		//리스트의 마지막 노드를 찾을 때까지 반복
		trail = n;					//삭제할 노드의 이전 노드를 가리킴
		n = n->link;				//n을 다음 노드로 이동
	}

	trail->link = NULL;				//삭제할 노드의 이전 노드의 링크를 NULL로 만듬
	free(n);						//해재

	return 0;
}
int deleteFirst(headNode* h) {		//연결 리스트 첫번쨰 노드를 삭제
									//headNode 구조체 포인터 변수 h를 입력으로 받음
	if (h->first == NULL)			//만약 연결 리스트가 비어있다면, "nothing to delete."를 출력하고 0을 반환
	{									
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;			//그렇지 않으면, 첫 번째 노드를 가리키는 포인터 변수 n을 생성

	h->first = n->link;				//헤드 노드를 첫 번째 노드의 다음 노드로 바꾸고, n이 가리키는 첫 번째 노드를 메모리에서 해제
	free(n);						//메모리해제

	return 0;
}


int invertList(headNode* h) {	//연결리스트의 순서를 뒤집는다.


	if(h->first == NULL) {
		printf("nothing to invert...\n");		//연결리스트가 비어있으면 "nothing to invert..." 메시지를 출력하고 0을 반환한다.
		return 0;								//연결리스트를 역순으로 만드는 방법은, 현재 노드를 기준으로
												//현재 노드의 다음 노드를 이전 노드로 바꾸는 방식으로 진행된다
	}
	listNode *n = h->first;						//n은 현재 노드를 가리키는 포인터 
	listNode *trail = NULL;						//trail은 n보다 앞의 노드를 가리키는 포인터
	listNode *middle = NULL;					//middle은 n보다 뒤의 노드를 가리키는 포인터

	while(n != NULL){							//while 루프를 돌면서, 현재 노드(n)의 다음 노드를 middle에 저장하고, n은 다음 노드로 이동
		trail = middle;							//middle의 다음 노드를 trail에 저장
		middle = n;						
		n = n->link;							//middle의 링크를 trail로 바꿈
		middle->link = trail;
	}

	h->first = middle;							//헤드 노드 포인터(h->first)를 middle로 업데이트하여 뒤집은 리스트의 첫 번째 노드를 가리키게 한다

	return 0;
}


void printList(headNode* h) {//연결리스트에 존재하는 노드들의 값을 출력한다.
	int i = 0;
	listNode* p;			

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");		// h가 NULL인 경우 아무것도 출력하지 않음
		return;
	}

	p = h->first;								// 첫 번째 노드부터 출력을 시작함

	while(p != NULL) {							// 노드가 NULL이 될 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key);		// 노드의 인덱스와 key값 출력
		p = p->link;							// 다음 노드로 이동
		i++;									// 인덱스 값 증가
	}

	printf("  items = %d\n", i);				// 총 출력한 노드의 수 출력
}
