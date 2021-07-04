#include<iostream>
#include<Windows.h>
#include"Task.h"

using namespace std;
#define    MAX_SIZE 10


//节点的数据结构
typedef struct _QNode {
	int id;
	void (*handler)();//函数指针用来存放任务的（指向执行任务的函数）
	struct _QNode* next;     //指向下一个节点
}QNode;

typedef QNode* QueuePtr;

//队列的数据结构
typedef struct Queue {
	QueuePtr  front;   //对头指针
	QueuePtr  rear;    //队尾指针
	int length;        //队列的长度
}LinkQueue;

//队列的初始化，初始化空队列
void initQueue(LinkQueue* LQ);
//判断队列是否为空
int isEmpty(LinkQueue* LQ);

//判断队列是否为满
bool isFull(LinkQueue* LQ);
//节点元素入队
void EnterQueue(LinkQueue* LQ, QNode* node);
QueuePtr thread_task_clloc();
//打印队列元素
void print(LinkQueue* LQ);
//出队
void popQueue(LinkQueue* LQ);
int main() {
	LinkQueue* LQ = new LinkQueue;
	QNode* task = NULL;
	//队列初始化
	initQueue(LQ);
	
	//任务一入队
	task = thread_task_clloc();
	task->id = 1;
	task->handler = &task1;
	EnterQueue(LQ, task);
	
	//任务二入队
	task = thread_task_clloc();
	task->id = 2;
	task->handler = &task2;
	EnterQueue(LQ, task);
	print(LQ);
	cout << "销毁队列......" << endl;
	popQueue(LQ);

	 cout << "队列中的剩下的任务:" << endl;
	print(LQ);
	delete LQ;
	system("pause");
	return 0;
}

//队列的初始化，初始化空队列
void initQueue(LinkQueue* LQ) {
	if (!LQ)return;
	LQ->front = LQ->rear = NULL;
	LQ->length = 0;
}

//判断队列是否为空
int isEmpty(LinkQueue* LQ) {
	if (!LQ)return 1;
	if (LQ->rear == NULL) {
		return 1;
	}
	return 0;//不为空
}

//判断队列是否为满
bool isFull(LinkQueue* LQ) {
	if (!LQ || LQ->length == MAX_SIZE)return true;//队列已满
	return false;//否则对列不为空
}

//节点元素入队
void EnterQueue(LinkQueue* LQ, QNode* node) {
	if (!LQ || !node)return;
	if (isFull(LQ)) {
		cout << "队列已满..." << endl;
		return;
	}
	node->next = NULL;
	//如果队列为空，则直接将rear和front指针指向新的节点即可
	if (isEmpty(LQ)) {
		LQ->front = node;
		LQ->rear = node;
	}
	else {//否则直接将rear->next指向新的节点，然后再将rear指向新的节点
		//先将rear指针指针指向下一个节点的指针指向新的节点
		LQ->rear->next = node;
		//将rear指针指向新的节点
		LQ->rear = node;
	}
	LQ->length++;
}


//分配线程执行的任务节点
QueuePtr thread_task_clloc() {
	QNode* task;
	//为节点分配资源
	task =(QNode*)calloc(1, sizeof(QNode));
	if (!task)return NULL;
	return task;
}

//打印队列元素
void print(LinkQueue* LQ) {
	if (!LQ || isEmpty(LQ)) {
		cout << "队列为空..." << endl;
		return;
	}

	QNode* temp = LQ->front;

	while (temp) {
		cout << "id:" << temp->id << "\t执行的任务:";
		temp->handler();
		cout << "\n";
		temp = temp->next;
	}
	//跳出循环后temp为空
}

//出队
void popQueue(LinkQueue *LQ) {
	if (!LQ || isEmpty(LQ)) {
		cout << "队列为空..." << endl;
		return;
	}

	QNode* temp = NULL;
	temp = LQ->front;
	while (temp) {
		//删除第一个节点之前先将front对头指针指向下一个
		LQ->front = temp->next;
		delete temp;//将之前保存的front删掉
		//再将新的front所指向的位置赋值給temp
		temp=LQ->front;
	}
	LQ->rear = NULL;
	LQ->length = 0;
}

