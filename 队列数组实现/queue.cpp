#include<iostream>
#include<stdlib.h>

using namespace std;
//���е����ݽṹ
#define MAX_SIZE 50
typedef int DataType;
typedef struct Queue {
	DataType queue[MAX_SIZE];
	int front;//��ͷָ��
	int rear;//��βָ��
}SqueQue;

//���еĳ�ʼ��
int initQueue(SqueQue* q) {
	if (!q)return 0;
	q->front = 0; 
	q->rear = 0;
	return 1;
}
//�ж϶����Ƿ�Ϊ��

int isEmpty(SqueQue* q) {
	if (!q)return 0;
	if (q->front == q->rear) {
		return 1;
	}
	return 0;
}

//�ж϶����Ƿ�Ϊ��
int isFull(SqueQue* q) {
   
	if (!q)return 0;
	if (q->rear == MAX_SIZE) {
		cout << "��������" << endl;
		return 1;
	}
	return 0;
}


//�������в���Ԫ��
int insert(SqueQue* q, DataType data) {
	if (!q||isFull(q))return 0;//��������
	q->queue[q->rear]= data;
	q->rear++;
	return 1;
}
//��ӡ����Ԫ��

//Ԫ�س��ӣ��Ƚ��ȳ�

void outQueue(SqueQue* q, DataType& data) {
	if (!q)return;
	if (isEmpty(q)) {
		cout << "����Ϊ��..." << endl;
		return;
	}
	
	data = q->queue[q->front];
	//�Ӷ�ͷ���ӣ��ӵڶ���Ԫ�ؿ�ʼ��ÿ�ζ�Ҫ�������Ԫ����ǰ�ƶ�һ��λ��
	for (int i = q->front + 1; i < q->rear; i++) {
		q->queue[i - 1] = q->queue[i];
	}
	//�ƶ���Ϻ�rearָ����ǰ�ƶ�һ��λ��
	q->rear--;
}

void print(SqueQue* q) {
	if (!q || isEmpty(q)) {
		cout << "����Ϊ��" << endl;
		return ;
	}
	int i = q->front;
	for (i = q->front; i < q->rear; i++) {
		cout << q->queue[i] << "\t";
	}

	cout << endl;
}

//ָ�����ӵ�Ԫ��

int  specific_outElem(SqueQue* q, DataType data,DataType &elem) {
	if (!q)return 0;
	if (isEmpty(q)) {
		cout << "����Ϊ�գ�û�п��Գ��ӵ�Ԫ��" << endl;
		return 0;
	}
	int i = q->front;//ͨ������ѭ�����ҵ�data���ڵ��±�λ��
	while (i < q->rear) {
		if (data == q->queue[i]) {
			break;//�ҵ���data�ڶ����е��±�λ��
		}
		i++;
	}

	if (i == q->rear) {
		cout << "������û��" << data << "Ԫ��" << endl;
		return 0;
	}
	elem = q->queue[i];
	//����ѭ�����ҵ���dataԪ�����ڵ��±�λ��
	//ֱ�ӽ�i�����Ԫ����ǰ�ƶ�һ��λ�ã�rear--����

	for (int j = i + 1; j < q->rear; j++) {
		q->queue[j - 1] = q->queue[j];
	}
	//�ƶ���Ϻ�rearָ����ǰ�ƶ�һ��λ�ü���
	q->rear--;
	return 1;
}

////��Ԫ�ص��±����
//
//int Index(SqueQue* q, int index) {
//	if (!q || isEmpty(q)) {
//		cout << "����Ϊ��..." << endl;
//		return 0;//����0��ʾ����Ϊ��
//	}
//	if (index < 0||index>=q->rear) {
//		cout << "�±�λ�ò��ںϷ���Χ��:" << endl;
//		return -1;//����-1�������±�λ�ò��Ϸ�
//	}
//	DataType elem = 0;
//	elem = q->queue[index];
//	return elem;
//}


//�ڶ��ֳ��ӷ�ʽ��ÿ�γ��Ӻ�ֱ�ӽ���ͷָ������ƣ�ֱ��=��βָ�����ڵ�λ��
void outQueue2(SqueQue* q, DataType& data) {

	
	if (!q) {
		return;
	}
	if (isEmpty(q)) {
		cout << "����Ϊ��..." << endl;
		return;
	}
	data = q->queue[q->front];
	//����ͷָ������ƶ�����һ��λ��
	q->front++;
}

int main() {
	SqueQue* q = new SqueQue;
	//��ʼ��
	if (initQueue(q))cout << "��ʼ���ɹ�!" << endl;
    //Ԫ�����
	for (int i = 0; i < 7; i++) {
		insert(q, i);
	}
	//��ӡԪ��
	print(q);

	int elem;
	/*if (specific_outElem(q, 6, elem)) {
		cout << "���ӳɹ�������Ԫ��:" << elem << endl;
	}
	cout << "���Ӻ�ʣ�µ�Ԫ��:";
	print(q);
	int data = 0;*/

	cout << "�Զ�ͷָ������ƶ��ķ�ʽ����..." << endl;
	outQueue2(q, elem);
	cout << "����Ԫ��:" << elem << endl;
	cout << "ʣ�µ�Ԫ��:";
	print(q);
	/*cout << "Ԫ�����γ���..." << endl;

	while (q->rear!=q->front) {
		outQueue(q, data);
		cout << data << "\t";
	}
	cout << "\n";
	cout << "������ʣ���Ԫ��:";
	print(q);*/

	/*cout << "��ָ�����±�λ��Ԫ�س���:" << "\n\n\n";
	cout << "����Ԫ��:" << Index(q, 5) << endl;*/
	delete q;
	system("pause");
	return 0;
}