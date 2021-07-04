#include<iostream>
#include<Windows.h>
#include<iomanip>

using namespace std;

#define MaxSize 10

//�ڵ�����ݽṹ
typedef int DataType;
typedef struct _Node {
	int data;//�ڵ��������
	struct _Node* next;//�ڵ��ָ����
}Node;

typedef Node* QueuePtr;//���ڶ��屣��Node���͵��������

typedef struct _Queue {
	int length;    //���ڼ��������нڵ�ĸ���
	QueuePtr rear; // ��ͷָ��,����ָ������еĵ�һ��Ԫ��
	QueuePtr front;// ��βָ�룬����ָ����������һ��Ԫ��
}LinkQueue;


void init(LinkQueue* L);//��ʼ��
bool isEmpty(LinkQueue* L);//�ж϶���֪���Ƿ�Ϊ��
int EnterQueue(LinkQueue* L, DataType data);//Ԫ�����
int deleteQueue(LinkQueue* L, DataType& data);//Ԫ�س���
void  PrintQueue(LinkQueue* L);              //��ӡ�����е�Ԫ�� 
void GetHeadElem(LinkQueue* L, DataType& data);//��ȡ����Ԫ��
void GetBackElem(LinkQueue* L, DataType& data);//��ȡ��βԪ��
void clreaQueue(LinkQueue* L);
//���±���Ҷ����е�Ԫ��
int findElemByIndex(LinkQueue* L, int index, DataType& data);
int getSize(LinkQueue* L);//��ȡ����Ԫ�ظ���
int main() {
	LinkQueue* L = new LinkQueue;
	DataType data=-1;
	DataType firstElem, lastElem;
	init(L);
	//���
	for (int i = 0; i < 5; i++) {
		EnterQueue(L,i);
	}
	cout << "���е�Ԫ��:" << endl;
	PrintQueue(L);

	/*cout << "Ԫ���еĵĶ�������:" << endl;
	PrintQueue(L);
	GetHeadElem(L, firstElem);
	GetBackElem(L, lastElem);
	cout << "�����еĵ�һ��Ԫ��:" << firstElem << endl <<
		"���һ��Ԫ��:" << lastElem << endl;
	
	clreaQueue(L);
	cout << "��ն��к�:" << endl;
	cout<<"length:"<<L->length;
	PrintQueue(L);*/
	findElemByIndex(L, 2, data);
	cout << "�ڶ���Ԫ�ص�ֵΪ:" << data << "\n\n\n";
	cout << "�����е�Ԫ�ظ���Ϊ:" << getSize(L) << "\n\n\n";
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
		return true;//����Ϊ��
	}
	return false;//���в�Ϊ��
}

bool isFull(LinkQueue* L) {
	if (!L)return false;
	if (L->length == MaxSize)return true;
	return false;//����û����
}

int EnterQueue(LinkQueue* L, DataType data) {
	if (!L)return 0;

	//������Ѿ����ˣ��ǾͲ����������
	if (isFull(L)) {
		cout << "��������!";
		return 0;
	}
	Node* qnode = new Node;//����һ���µĽڵ�
	//�������Ϊ�գ�ֱ�ӽ�rear��frontָ��ָ���µ�node�ڵ�
	if (isEmpty(L)) {
		
		qnode->data = data;
		L->rear = qnode;
		L->front = qnode;
		qnode->next = NULL;
		L->length++;
		return 1;
	}
	//�������Ѿ���һ�����߶���ڵ���
	//��1�����µĽڵ����������һ���ڵ��λ����
	//��2���ٽ�rearָ��ָ�����һ���ڵ��λ�ü���
	qnode->data = data;
	L->rear->next = qnode;//�����һ���ڵ����һ��ָ��ָ���µĽڵ�
	L->rear = qnode;//��rearָ��ָ���µĽڵ�
	qnode->next = NULL;
	L->length++;
	return 1;
}

int deleteQueue(LinkQueue* L, DataType& data) {
	if (!L)return 0;

    //�������Ϊ�գ��Ǿ�û�г��ӵ�Ԫ��
	if (isEmpty(L)) {
		cout << "����Ϊ��..." << endl;
		return 0;
	}
	Node* temp = L->front;
	
	L->front = temp->next;
	//front����һ��Ԫ��Ϊ�գ���rear�ÿ�
	if (!L->front == NULL)L->rear = NULL;
	data = temp->data;
	delete temp;
	L->length++;//�����е�Ԫ�ؼ�һ
	return 1;
}

//��������
void  PrintQueue(LinkQueue* L) {
	if (!L)return;
	Node* temp = L->front;

	while (temp) {
		cout <<setw(3)<< temp->data << "\t";
		//��temp������һ��λ��
		temp = temp->next;
	}
	cout << endl;

	//����ѭ��ʱ��tempΪ��
}

//��ȡ����Ԫ��

void GetHeadElem(LinkQueue* L, DataType& data) {
	if (!L || isEmpty(L)) {
		cout << "����Ϊ��..." << endl;
		return;
	}
	data = L->front->data;
}

//��ȡ��βԪ��

void GetBackElem(LinkQueue *L,DataType &data) {
	if (!L || isEmpty(L)) {
		cout << "����Ϊ��.." << endl;
		return;
	}
	Node* temp = L->front;
	int index = 1;
	//ͨ��ѭ��������ÿ����һ�μ�����index+1
	while (temp->next) {
		temp = temp->next;
	}
	//����ѭ��ʱ��tempָ�������һ���ڵ㣬������һ������NULL
	data = temp->data;
}

void clreaQueue(LinkQueue* L) {
	if (!L || isEmpty(L)) {
		cout << "�����Ѿ�Ϊ��..." << endl;
		return;
	}

	Node* temp = L->front;
	while (temp) {
		//����ͷָ��ָ����һ���ڵ�λ�ã�
		L->front = temp->next;
		delete temp;
		temp = L->front;
	}
	L->length = 0;
	L->rear = L->front = NULL;
}

//���±�λ�ò��Ҷ����е�Ԫ��
int findElemByIndex(LinkQueue* L, int index,DataType &data) {
	if (!L||isEmpty(L))return 0;
	if (index < 1) {
		cout << "����±�λ�ò��Ϸ�:" << endl;
		return 0;
	}
	int i = 1;
	Node* temp = L->front;
	while (temp->next&&i<index) {
		temp = temp->next;
		i++;
	}
	//����ѭ�����������
	//1.�п��ܱ�������������е�Ԫ�ػ�û���ҵ��±�Ϊindex��Ԫ��
	//2.����ʱ��û���������һ���ڵ���ҵ����±�Ϊindex��Ԫ��
	if (!temp->next&&i<index) {
		cout << "���޴�ֵ:" << endl;
		return 0;
	}
	data = temp->data;
	return 1;
}
//��ȡ���еĽڵ����
int getSize(LinkQueue* L) {
	return L->length;
}