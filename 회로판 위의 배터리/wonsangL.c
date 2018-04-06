/*
����ð�: 0.00492
�޸�: 8312
����: 140
*/
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct node {
	int index;
	float value;
	struct node* previous;
	struct node* next;
}NODE;

void insertion(NODE** head, NODE** tail, int index, float value);
float getDistance(NODE* head, NODE* tail, float avg, int* count);

int main(void)
{
	int T, test_case, N;
	float buffer, distX, distY, sumX = 0, sumY = 0; // x / y��ǥ�� �ִ밪�� ���� �����ϴ� ����

	setbuf(stdout, NULL);

	scanf("%d", &T);
	for (test_case = 0; test_case < T; test_case++)
	{
		scanf("%d", &N);

		int *countX = (int*)calloc(N, sizeof(int));
		int *countY = (int*)calloc(N, sizeof(int));

		NODE* headX = NULL; // ��ũ�� ����Ʈ�� head(�ּҰ�)
		NODE* tailX = NULL; // ��ũ�� ����Ʈ�� tail(�ִ밪)
		
		NODE* headY = NULL;
		NODE* tailY = NULL;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 4; j++) {
				scanf("%f", &buffer);

				if (j % 2 == 0) {
					insertion(&headX, &tailX, i, buffer);
					countX[i]++;
					sumX += buffer;
				}
				else {
					insertion(&headY, &tailY, i, buffer);
					countY[i]++;
					sumY += buffer;
				}
			}
		}

		sumX /= N * 2;
		sumY /= N * 2;

		distX = getDistance(headX, tailX, sumX, countX);
		distY = getDistance(headY, tailY, sumY, countY);

		printf("Case #%d\n", test_case + 1);
		printf("%g\n", MAX(distX, distY));
	}

	return 0;
}

//������������ �����Ͽ� ��ũ�� ����Ʈ�� ����
void insertion(NODE** head, NODE** tail, int index, float value) {
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->index = index;
	newNode->value = value;
	newNode->next = NULL;
	newNode->previous = NULL;

	if (*head == NULL) {
		*head = newNode;
		*tail = newNode;
		return;
	}

	NODE* current = *head;
	NODE* previous = NULL;

	while (current != NULL) {
		if (current->value > newNode->value) {
			if (previous == NULL) {
				newNode->next = current;
				*head = newNode;
				return;
			}

			previous->next = newNode;
			newNode->previous = previous;
			newNode->next = current;
			current->previous = newNode;
			return;
		}

		previous = current;
		current = current->next;
	}
	
	previous->next = newNode;
	newNode->previous = previous;
	*tail = newNode;
}

float getDistance(NODE* head, NODE* tail, float avg, int* count) {
	while (1) {
		if (head->index == tail->index) {	
			//�ּҰ��� �ִ밪�� ���� ���� �ȿ� ���� ���
			int headCount = 0, tailCount = 0;
			NODE* tempHead = head;
			NODE* tempTail = tail;

			while (tempHead->value <= avg) {
				tempHead = tempHead->next;
				headCount++;
			}

			while (tempTail->value >= avg) {
				tempTail = tempTail->previous;
				tailCount++;
			}

			//��հ��� ���簪(�ִ�, �ּ�) ���̿� �����ϴ� ���� ���� ��� ����

			if (headCount > tailCount) {
				count[tail->index]--;
				tail = tail->previous;
			}
			else {
				count[head->index]--;
				head = head->next;
			}

		}

		//�ִ밪 �ּҰ��� ����
		if (count[head->index] > 1) {
			count[head->index]--;
			head = head->next;
		}

		if (count[tail->index] > 1) {
			count[tail->index]--;
			tail = tail->previous;
		}

		if (count[head->index] == 1 && count[tail->index] == 1)
			break;
	}

	return (tail->value - head->value) / 2.0;
}