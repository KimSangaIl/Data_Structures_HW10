/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	printf("[----- [Kim Sangil] [2019038041] -----]\n");

	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for ( ; ; ) {
		for ( ; node; node = node->left) {
			push(node);			//왼쪽 노드가 NULL이 될때까지 스택에 노드를 삽입
		}
		node = pop();				//가장 왼쪽 노드를 스택에서 삭제
		if (!node) break;			//스택이 공백이 되면 반복문 종료
		printf(" [%d] ", node->key);		//노드의 키값 출력
		node = node->right;			//오른쪽 노드로 이동
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr) return;				//공백 트리인 경우 함수를 종료
	enQueue(ptr);					//큐에 루트 노드를 삽입
	for ( ; ; ) {
		ptr = deQueue();			//큐에서 원소를 하나 삭제
		if (ptr) {				//큐가 공백이 아닌 경우
			printf(" [%d] ", ptr->key);	//노드의 키값 출력
			if (ptr->left) {		//ptr의 왼쪽 노드가 존재하는 경우
				enQueue(ptr->left);	//큐에 왼쪽 노드 삽입
			}
			if (ptr->right) {		//ptr의 오른쪽 노드가 존재하는 경우
				enQueue(ptr->right);	//오른쪽 노드 삽입
			}
		}
		else break;				//큐가 공백인 경우 함수 종료
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL) {			//헤드 노드가 비어있는 경우
		printf("Nothing to delete!\n");	//오류 메시지 출력
		return -1;			//비정상 함수 종료
	}

	if (head->left == NULL) {		//헤드 노드의 왼쪽 서브 트리가 비어있는 경우
		printf("Nothing to delete!\n");	//오류 메시지 출력
		return -1;			//비정상 함수 종료
	}

	Node* root = head->left;	//루트 노드를 저장할 노드 선언 및 헤드 노드의 왼쪽 서브 트리로 초기화
	Node* par = NULL;		//부모 노드를 저장할 노드 선언
	Node* temp = root;		//탐색할 노드를 저장할 노드 선언 및 루트 노드로 초기화

	while ((temp != NULL) && (temp->key != key)) {	//temp노드가 NULL이 되거나 입력 받은 키값과 일치하는 노드를 찾을때까지 반복
		if (temp->key != key) {				//temp노드의 키값이 입력 받은 키값과 일치하지 않는 경우
			par = temp;				//부모 노드를 temp노드로 초기화
			if (temp->key > key) temp = temp->left;	//temp노드의 키값이 입력 받은 키값보다 큰 경우 temp노드를 왼쪽 서브트리로 이동
			else temp = temp->right;		//작은 경우 오른쪽 서브트리로 이동
		}
	}

	if (temp == NULL) {				//입력 받은 키값을 찾지 못한경우
		printf("No node for key [%d]\n", key);	//오류 메시지 출력
		return -1;				//비정상 함수 종료
	}

	if ((temp->left == NULL) && (temp->right == NULL)) {	//탐색한 노드가 리프 노드인 경우
		if (par != NULL) {				//부모 노드가 존재하는 경우
			if (par->left == temp) {		//부모 노드의 왼쪽 서브트리가 탐색한 노드인 경우
				par->left = NULL;		//왼쪽 서브트리를 NULL로 초기화
			}
			else if (par->right == temp) {	//오른쪽 서브트리가 탐색한 노드인 경우
				par->right = NULL;	//오른쪽 서브트리를 NULL로 초기화
			}
		}
		else head->left = NULL;	//부모 노드가 존재하지 않는 경우, 즉 탐색한 노드가 루트 노드인 경우 루트 노드를 NULL로 초기화

		free(temp);	//탐색한 노드의 메모리를 해제
		return 1;	//함수 종료
	}

	if ((temp->left == NULL) || (temp->right == NULL)) {	//탐색한 노드가 자식 노드를 한 개 가진 경우
		Node* child;			//자식 노드를 저장할 노드 선언
		if (temp->left != NULL) {	//탐색한 노드의 왼쪽 서브트리에 자식 노드가 있는 경우
			child = temp->left;	//child 노드를 탐색한 노드의 왼쪽 서브트리로 초기화
		}
		if (temp->right != NULL) {	//오른쪽 서브트리에 자식 노드가 있는 경우
			child = temp->right;	//child 노드를 오른쪽 서브트리로 초기화
		}

		if (par != NULL) {			//부모 노드가 존재하는 경우
			if (par->left = temp) {		//부모 노드의 왼쪽 서브트리가 탐색한 노드인 경우
				par->left = child;	//부모 노드의 왼쪽 서브트리를 자식 노드로 초기화
			}
			if (par->right = temp) {	//오른쪽 서브트리가 탐색한 노드인 경우
				par->right = child;	//오른쪽 서브트리를 자식 노드로 초기화
			}
		}
		else root = child;	//부모 노드가 존재하지 않는 경우, 즉 탐색한 노드가 루트 노드인 경우 루트 노드를 자식 노드로 초기화

		free(temp);	//탐색한 노드의 메모리를 해제
		return 1;	//함수 종료
	}

	Node* candidate;		//후계자를 탐색할 노드 선언
	par = temp;			//부모 노드를 탐색한 노드로 초기화
	candidate = temp->right;	//후계자 노드를 탐색한 노드의 오른쪽 서브트리로 초기화

	while (candidate->left != NULL) {	//후계자 노드의 왼쪽 서브트리가 NULL이 될때까지 반복
		par = candidate;		//부모 노드를 후계자 노드로 초기화
		candidate = candidate->left;	//후계자 노드를 왼쪽 서브트리로 이동
	}

	if (par->right == candidate) {		//부모 노드의 오른쪽 서브트리가 후계자 노드일 경우
		par->right = candidate->right;	//부모 노드의 오른쪽 서브트리를 후계자 노드의 오른쪽 서브트리로 초기화
	}
	else {					//후계자 노드가 아닌 경우
		par->left = candidate->right;	//부모 노드의 왼쪽 서브트리를 후계자 노드의 오른쪽 서브트리로 초기화
	}

	temp->key = candidate->key;		//탐색한 노드의 키값을 후계자 노드의 키값으로 초기화

	free(candidate);	//후계자 노드의 메모리를 해제
	return 1;		//함수 종료
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL;	//스택이 비어있는 경우 비정상 함수 종료
	return stack[top--];		//탑에 있는 원소를 삭제하고 탑 위치를 1 감소
}

void push(Node* aNode)
{
	stack[++top] = aNode;	//탑 위치를 1 증가시키고 탑에 aNode 원소 추가
}



Node* deQueue()
{
	if (front == rear) return NULL;		//원형 큐가 비어있는 경우 비정상 함수 종료
	front = (front + 1) % MAX_QUEUE_SIZE;	//front 위치를 한칸 뒤로 초기화
	return queue[front];			//front 자리에 있는 원형 큐의 원소를 삭제
}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;	//rear 위치를 한칸 뒤로 초기화
	if (front == rear) return;		//원형 큐가 포화상태인 경우 비정상 함수 종료
	queue[rear] = aNode;			//rear 자리에 aNode 원소 추가
}

void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)	{					//스택 탑까지 반복
		printf("stack[%d] = %d\n", i, stack[i]->key);	//스택 원소 출력
	}
}
