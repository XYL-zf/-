#include<iostream>
#include<stdlib.h>

using namespace std;
//队列的数据结构
#define MAX_SIZE 50
typedef int DataType;
typedef struct Queue {
	DataType queue[MAX_SIZE];
	int front;//队头指针
	int rear;//队尾指针
}SqueQue;

//对列的初始化
int initQueue(SqueQue* q) {
	if (!q)return 0;
	q->front = 0; 
	q->rear = 0;
	return 1;
}
//判断对列是否为空

int isEmpty(SqueQue* q) {
	if (!q)return 0;
	if (q->front == q->rear) {
		return 1;
	}
	return 0;
}

//判断对列是否为满
int isFull(SqueQue* q) {
   
	if (!q)return 0;
	if (q->rear == MAX_SIZE) {
		cout << "对列已满" << endl;
		return 1;
	}
	return 0;
}


//往对列中插入元素
int insert(SqueQue* q, DataType data) {
	if (!q||isFull(q))return 0;//对列已满
	q->queue[q->rear]= data;
	q->rear++;
	return 1;
}
//打印对列元素

//元素出队：先进先出

void outQueue(SqueQue* q, DataType& data) {
	if (!q)return;
	if (isEmpty(q)) {
		cout << "对列为空..." << endl;
		return;
	}
	
	data = q->queue[q->front];
	//从对头出队，从第二个元素开始，每次都要讲后面的元素向前移动一个位置
	for (int i = q->front + 1; i < q->rear; i++) {
		q->queue[i - 1] = q->queue[i];
	}
	//移动完毕后将rear指针向前移动一个位置
	q->rear--;
}

void print(SqueQue* q) {
	if (!q || isEmpty(q)) {
		cout << "对列为空" << endl;
		return ;
	}
	int i = q->front;
	for (i = q->front; i < q->rear; i++) {
		cout << q->queue[i] << "\t";
	}

	cout << endl;
}

//指定出队的元素

int  specific_outElem(SqueQue* q, DataType data,DataType &elem) {
	if (!q)return 0;
	if (isEmpty(q)) {
		cout << "对列为空，没有可以出队的元素" << endl;
		return 0;
	}
	int i = q->front;//通过遍历循环，找到data所在的下标位置
	while (i < q->rear) {
		if (data == q->queue[i]) {
			break;//找到了data在对列中的下标位置
		}
		i++;
	}

	if (i == q->rear) {
		cout << "对列中没有" << data << "元素" << endl;
		return 0;
	}
	elem = q->queue[i];
	//跳出循环后，找到了data元素所在的下标位置
	//直接将i后面的元素向前移动一个位置，rear--即可

	for (int j = i + 1; j < q->rear; j++) {
		q->queue[j - 1] = q->queue[j];
	}
	//移动完毕后将rear指针向前移动一个位置即可
	q->rear--;
	return 1;
}

////按元素的下标出队
//
//int Index(SqueQue* q, int index) {
//	if (!q || isEmpty(q)) {
//		cout << "对列为空..." << endl;
//		return 0;//返回0表示对列为空
//	}
//	if (index < 0||index>=q->rear) {
//		cout << "下标位置不在合法范围内:" << endl;
//		return -1;//返回-1，代表下标位置不合法
//	}
//	DataType elem = 0;
//	elem = q->queue[index];
//	return elem;
//}


//第二种出队方式，每次出队后直接将队头指针向后移，直到=队尾指针所在的位置
void outQueue2(SqueQue* q, DataType& data) {

	
	if (!q) {
		return;
	}
	if (isEmpty(q)) {
		cout << "对列为空..." << endl;
		return;
	}
	data = q->queue[q->front];
	//将队头指针向后移动到下一个位置
	q->front++;
}

int main() {
	SqueQue* q = new SqueQue;
	//初始化
	if (initQueue(q))cout << "初始化成功!" << endl;
    //元素入队
	for (int i = 0; i < 7; i++) {
		insert(q, i);
	}
	//打印元素
	print(q);

	int elem;
	/*if (specific_outElem(q, 6, elem)) {
		cout << "出队成功，出队元素:" << elem << endl;
	}
	cout << "出队后剩下的元素:";
	print(q);
	int data = 0;*/

	cout << "以对头指针向后移动的方式出队..." << endl;
	outQueue2(q, elem);
	cout << "出队元素:" << elem << endl;
	cout << "剩下的元素:";
	print(q);
	/*cout << "元素依次出队..." << endl;

	while (q->rear!=q->front) {
		outQueue(q, data);
		cout << data << "\t";
	}
	cout << "\n";
	cout << "对列中剩余的元素:";
	print(q);*/

	/*cout << "按指定的下标位让元素出队:" << "\n\n\n";
	cout << "出队元素:" << Index(q, 5) << endl;*/
	delete q;
	system("pause");
	return 0;
}