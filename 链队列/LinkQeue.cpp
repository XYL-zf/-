#include<iostream>
#include<Windows.h>
#include<iomanip>

using namespace std;

#define MaxSize 10

//节点的数据结构
typedef int DataType;
typedef struct _Node {
	int data;//节点的数据域
	struct _Node* next;//节点的指针域
}Node;

typedef Node* QueuePtr;//用于定义保存Node类型的链表队列

typedef struct _Queue {
	int length;    //用于计数队列中节点的个数
	QueuePtr rear; // 对头指针,用于指向队列中的第一个元素
	QueuePtr front;// 队尾指针，用于指向对列中最后一个元素
}LinkQueue;


void init(LinkQueue* L);//初始化
bool isEmpty(LinkQueue* L);//判断队列知否是否为空
int EnterQueue(LinkQueue* L, DataType data);//元素入队
int deleteQueue(LinkQueue* L, DataType& data);//元素出队
void  PrintQueue(LinkQueue* L);              //打印对列中的元素 
void GetHeadElem(LinkQueue* L, DataType& data);//获取队首元素
void GetBackElem(LinkQueue* L, DataType& data);//获取队尾元素
void clreaQueue(LinkQueue* L);
//按下标查找队列中的元素
int findElemByIndex(LinkQueue* L, int index, DataType& data);
int getSize(LinkQueue* L);//获取队列元素个数
int main() {
	LinkQueue* L = new LinkQueue;
	DataType data=-1;
	DataType firstElem, lastElem;
	init(L);
	//入队
	for (int i = 0; i < 5; i++) {
		EnterQueue(L,i);
	}
	cout << "对中的元素:" << endl;
	PrintQueue(L);

	/*cout << "元素中的的队列如下:" << endl;
	PrintQueue(L);
	GetHeadElem(L, firstElem);
	GetBackElem(L, lastElem);
	cout << "队列中的第一个元素:" << firstElem << endl <<
		"最后一个元素:" << lastElem << endl;
	
	clreaQueue(L);
	cout << "清空对列后:" << endl;
	cout<<"length:"<<L->length;
	PrintQueue(L);*/
	findElemByIndex(L, 2, data);
	cout << "第二个元素的值为:" << data << "\n\n\n";
	cout << "队列中的元素个数为:" << getSize(L) << "\n\n\n";
	system("pause");
	return 0;
}

void init(LinkQueue* L) {
	if (!L)return;
	L->length = 0;
	L->front = L->rear = NULL;

}

bool isEmpty(LinkQueue* L) {
	if (!L)return false;
	if (L->rear== NULL) {
		return true;//队列为满
	}
	return false;//队列不为空
}

bool isFull(LinkQueue* L) {
	if (!L)return false;
	if (L->length == MaxSize)return true;
	return false;//队列没有满
}

int EnterQueue(LinkQueue* L, DataType data) {
	if (!L)return 0;

	//如果队已经满了，那就不能再入队了
	if (isFull(L)) {
		cout << "队列已满!";
		return 0;
	}
	Node* qnode = new Node;//生成一个新的节点
	//如果队列为空，直接将rear和front指针指向新的node节点
	if (isEmpty(L)) {
		
		qnode->data = data;
		L->rear = qnode;
		L->front = qnode;
		qnode->next = NULL;
		L->length++;
		return 1;
	}
	//队列中已经有一个或者多个节点了
	//（1）将新的节点链接在最后一个节点的位置上
	//（2）再将rear指针指向最后一个节点的位置即可
	qnode->data = data;
	L->rear->next = qnode;//将最后一个节点的下一个指针指向新的节点
	L->rear = qnode;//将rear指针指向新的节点
	qnode->next = NULL;
	L->length++;
	return 1;
}

int deleteQueue(LinkQueue* L, DataType& data) {
	if (!L)return 0;

    //如果队列为空，那就没有出队的元素
	if (isEmpty(L)) {
		cout << "队列为空..." << endl;
		return 0;
	}
	Node* temp = L->front;
	
	L->front = temp->next;
	//front的下一个元素为空，将rear置空
	if (!L->front == NULL)L->rear = NULL;
	data = temp->data;
	delete temp;
	L->length++;//队列中的元素减一
	return 1;
}

//遍历队列
void  PrintQueue(LinkQueue* L) {
	if (!L)return;
	Node* temp = L->front;

	while (temp) {
		cout <<setw(3)<< temp->data << "\t";
		//将temp更新下一个位置
		temp = temp->next;
	}
	cout << endl;

	//跳出循环时，temp为空
}

//获取队首元素

void GetHeadElem(LinkQueue* L, DataType& data) {
	if (!L || isEmpty(L)) {
		cout << "对列为空..." << endl;
		return;
	}
	data = L->front->data;
}

//获取队尾元素

void GetBackElem(LinkQueue *L,DataType &data) {
	if (!L || isEmpty(L)) {
		cout << "链表为空.." << endl;
		return;
	}
	Node* temp = L->front;
	int index = 1;
	//通过循环遍历，每遍历一次计数器index+1
	while (temp->next) {
		temp = temp->next;
	}
	//跳出循环时，temp指向了最后一个节点，再往后一个就是NULL
	data = temp->data;
}

void clreaQueue(LinkQueue* L) {
	if (!L || isEmpty(L)) {
		cout << "对列已经为空..." << endl;
		return;
	}

	Node* temp = L->front;
	while (temp) {
		//将对头指针指向下一个节点位置，
		L->front = temp->next;
		delete temp;
		temp = L->front;
	}
	L->length = 0;
	L->rear = L->front = NULL;
}

//按下标位置查找对列中的元素
int findElemByIndex(LinkQueue* L, int index,DataType &data) {
	if (!L||isEmpty(L))return 0;
	if (index < 1) {
		cout << "你的下标位置不合法:" << endl;
		return 0;
	}
	int i = 1;
	Node* temp = L->front;
	while (temp->next&&i<index) {
		temp = temp->next;
		i++;
	}
	//跳出循环有两种情况
	//1.有可能遍历完队列中所有的元素还没有找到下标为index的元素
	//2.遍历时还没遍历到最后一个节点就找到了下标为index的元素
	if (!temp->next&&i<index) {
		cout << "查无此值:" << endl;
		return 0;
	}
	data = temp->data;
	return 1;
}
//获取队列的节点个数
int getSize(LinkQueue* L) {
	return L->length;
}