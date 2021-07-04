#include<iostream>
#include<Windows.h>
#include"Task.h"

using namespace std;
#define    MAX_SIZE 10


//�ڵ�����ݽṹ
typedef struct _QNode {
	int id;
	void (*handler)();//����ָ�������������ģ�ָ��ִ������ĺ�����
	struct _QNode* next;     //ָ����һ���ڵ�
}QNode;

typedef QNode* QueuePtr;

//���е����ݽṹ
typedef struct Queue {
	QueuePtr  front;   //��ͷָ��
	QueuePtr  rear;    //��βָ��
	int length;        //���еĳ���
}LinkQueue;

//���еĳ�ʼ������ʼ���ն���
void initQueue(LinkQueue* LQ);
//�ж϶����Ƿ�Ϊ��
int isEmpty(LinkQueue* LQ);

//�ж϶����Ƿ�Ϊ��
bool isFull(LinkQueue* LQ);
//�ڵ�Ԫ�����
void EnterQueue(LinkQueue* LQ, QNode* node);
QueuePtr thread_task_clloc();
//��ӡ����Ԫ��
void print(LinkQueue* LQ);
//����
void popQueue(LinkQueue* LQ);
int main() {
	LinkQueue* LQ = new LinkQueue;
	QNode* task = NULL;
	//���г�ʼ��
	initQueue(LQ);
	
	//����һ���
	task = thread_task_clloc();
	task->id = 1;
	task->handler = &task1;
	EnterQueue(LQ, task);
	
	//��������
	task = thread_task_clloc();
	task->id = 2;
	task->handler = &task2;
	EnterQueue(LQ, task);
	print(LQ);
	cout << "���ٶ���......" << endl;
	popQueue(LQ);

	 cout << "�����е�ʣ�µ�����:" << endl;
	print(LQ);
	delete LQ;
	system("pause");
	return 0;
}

//���еĳ�ʼ������ʼ���ն���
void initQueue(LinkQueue* LQ) {
	if (!LQ)return;
	LQ->front = LQ->rear = NULL;
	LQ->length = 0;
}

//�ж϶����Ƿ�Ϊ��
int isEmpty(LinkQueue* LQ) {
	if (!LQ)return 1;
	if (LQ->rear == NULL) {
		return 1;
	}
	return 0;//��Ϊ��
}

//�ж϶����Ƿ�Ϊ��
bool isFull(LinkQueue* LQ) {
	if (!LQ || LQ->length == MAX_SIZE)return true;//��������
	return false;//������в�Ϊ��
}

//�ڵ�Ԫ�����
void EnterQueue(LinkQueue* LQ, QNode* node) {
	if (!LQ || !node)return;
	if (isFull(LQ)) {
		cout << "��������..." << endl;
		return;
	}
	node->next = NULL;
	//�������Ϊ�գ���ֱ�ӽ�rear��frontָ��ָ���µĽڵ㼴��
	if (isEmpty(LQ)) {
		LQ->front = node;
		LQ->rear = node;
	}
	else {//����ֱ�ӽ�rear->nextָ���µĽڵ㣬Ȼ���ٽ�rearָ���µĽڵ�
		//�Ƚ�rearָ��ָ��ָ����һ���ڵ��ָ��ָ���µĽڵ�
		LQ->rear->next = node;
		//��rearָ��ָ���µĽڵ�
		LQ->rear = node;
	}
	LQ->length++;
}


//�����߳�ִ�е�����ڵ�
QueuePtr thread_task_clloc() {
	QNode* task;
	//Ϊ�ڵ������Դ
	task =(QNode*)calloc(1, sizeof(QNode));
	if (!task)return NULL;
	return task;
}

//��ӡ����Ԫ��
void print(LinkQueue* LQ) {
	if (!LQ || isEmpty(LQ)) {
		cout << "����Ϊ��..." << endl;
		return;
	}

	QNode* temp = LQ->front;

	while (temp) {
		cout << "id:" << temp->id << "\tִ�е�����:";
		temp->handler();
		cout << "\n";
		temp = temp->next;
	}
	//����ѭ����tempΪ��
}

//����
void popQueue(LinkQueue *LQ) {
	if (!LQ || isEmpty(LQ)) {
		cout << "����Ϊ��..." << endl;
		return;
	}

	QNode* temp = NULL;
	temp = LQ->front;
	while (temp) {
		//ɾ����һ���ڵ�֮ǰ�Ƚ�front��ͷָ��ָ����һ��
		LQ->front = temp->next;
		delete temp;//��֮ǰ�����frontɾ��
		//�ٽ��µ�front��ָ���λ�ø�ֵ�otemp
		temp=LQ->front;
	}
	LQ->rear = NULL;
	LQ->length = 0;
}

