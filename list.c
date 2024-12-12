#define _CRT_SECURE_NO_WARNINGS //2022�汾���scanf
#include <stdio.h>
#include <stdlib.h>
//for version 2010

// ��������ڵ�ṹ��
typedef struct Node {
    int data;
    struct Node* prev;//ǰһ���ڵ�
    struct Node* next;//��һ��
} Node;

 // ����˫��ѭ��������ָ����С������ڵ����ݣ��Ľ���
 Node* createList(int size) {
     int i;
	 Node* p;
	 Node* newNode;
	 Node* temp;
     Node* head = (Node*)malloc(sizeof(Node));  // Ϊ����ͷ�ڵ�����ڴ�ռ�
     if (head == NULL) {  // ����ڴ�����Ƿ�ɹ�
         printf("�ڴ����ʧ�ܣ�\n");
         return NULL;
     }
     head->prev = head;  // ��ʼ��ͷ�ڵ��prevָ��ָ����������ѭ������ĳ�ʼ�ṹ
     head->next = head;

     p = head;  // ����һ��ָ��p����ʼָ��ͷ�ڵ㣬���ڱ�������Ͳ����½ڵ�Ĳ�������

     for (i = 0; i < size; i++) {
         newNode = (Node*)malloc(sizeof(Node));  // Ϊ�½ڵ�����ڴ�ռ�
         if (newNode == NULL) {  // ����ڴ����ʧ��
             printf("�ڴ����ʧ�ܣ�\n");
             // �ͷ��ѷ���Ľڵ��ڴ棨�ӵ�ǰ�Ѳ���Ľڵ㿪ʼ����ͷţ�ֱ��ͷ�ڵ㣩
             while (head != p) {
                 temp = p;
                 p = p->prev;
                 free(temp);
             }
             free(head);  // ����ͷ�ͷ�ڵ��ڴ�
             return NULL;
         }

         // �������뻺���������Ļ��з��ȣ�ȷ������scanf����ȷ��ȡ�û�����
         while (getchar() != '\n');

         printf("������� %d ���ڵ������: ", i + 1);
         if (scanf("%d", &newNode->data) != 1) {  // ���scanf�Ƿ�ɹ���ȡ��һ������
             printf("�������ݸ�ʽ����������������\n");
             free(newNode);  // �ͷŸշ�����½ڵ��ڴ棬��Ϊ���벻�Ϸ�
             // ��ѡ������ͷ��ѷ���������ڵ��ڴ沢���أ�����ѡ��ֱ�ӷ��أ����⸴���߼����ɸ����������
             return NULL;
         }

         newNode->next = p->next;  // ���½ڵ��nextָ��ָ��ǰ�ڵ�p����һ���ڵ�
         newNode->prev = p;  // ���½ڵ��prevָ��ָ��ǰ�ڵ�p
         p->next->prev = newNode;  // ���µ�ǰ�ڵ�p����һ���ڵ��prevָ�룬ʹ��ָ���½ڵ�
         p->next = newNode;  // ���µ�ǰ�ڵ�p��nextָ�룬ʹ��ָ���½ڵ�
         p = newNode;  // ��ָ��p�ƶ����²���Ľڵ�λ�ã�������һ�β������
     }

     return head;  // ���ش����õ�˫��ѭ�������ͷ�ڵ�ָ��
 }

// ��ָ��λ�ò���ڵ�
 void insertNode(Node* head, int pos, int data) {
     int i;
	 Node* oldNext;
	 Node* tail;
	 Node* temp;
     Node* newNode = (Node*)malloc(sizeof(Node));
     Node* p = head;
     if (newNode == NULL) {
         printf("�ڴ����ʧ�ܣ�\n");
         return;
     }
     newNode->data = data;

     if (pos == 0) {
         // ����λ��Ϊ0ʱ�����½ڵ���Ϊͷ�ڵ����Ĳ���
         oldNext = head->next;  // ����ԭͷ�ڵ����һ���ڵ�ָ��

         // �����½ڵ��ָ���ϵ
         newNode->next = oldNext;
         newNode->prev = head;

         // ����ԭͷ�ڵ����һ���ڵ��prevָ�룬ʹ��ָ���½ڵ�
         oldNext->prev = newNode;

         // ����ԭͷ�ڵ��nextָ�룬ʹ��ָ���½ڵ�
         head->next = newNode;

         // ���½ڵ��Ϊ�����µ�ͷ�ڵ�
         head = newNode;
     }
     else {
         // ����λ�ò���0ʱ���ȱ����������Ҳ���λ��
         p = head;
         for (i = 0; i < pos; i++) {
             p = p->next;
             if (p == head) {
                 // �������������ָ��p�ٴ�ָ��ͷ�ڵ㣬˵��ָ��λ�ó�������Χ
                 printf("ָ��λ�ó�������Χ�����뵽����ĩβ\n");
                 break;
             }
         }

         if (p == head) {
             // �����ǲ��뵽����ĩβ�Ĳ���
             // �Ȼ�ȡԭ�����β�ڵ㣨˫��ѭ��������ͷ�ڵ��prevָ��ָ��β�ڵ㣩
             tail = head->prev;

             // ���½ڵ��nextָ��ָ��ͷ�ڵ㣬������ͷ�ڵ������
             newNode->next = head;

             // ���½ڵ��prevָ��ָ��ԭβ�ڵ㣬������ԭβ�ڵ������
             newNode->prev = tail;

             // ����ԭβ�ڵ��nextָ�룬ʹ��ָ���½ڵ�
             tail->next = newNode;

             // ����ͷ�ڵ��prevָ�룬ʹ��ָ���½ڵ㣬����½ڵ���뵽ĩβ�Ĳ���
             head->prev = newNode;
         }
         else {
             temp = p->next;

             newNode->next = temp;
             newNode->prev = p;
             temp->prev = newNode;
             p->next = newNode;
         }
     }
     // ���ظ��º��ͷ�ڵ�ָ�루ȷ�����ú������ܻ�ȡ����ȷ��ͷ�ڵ㣩
     return;
 }


// ɾ��ָ��λ�ýڵ�
int deleteNode(Node* head, int pos) {
    int i;
    Node* p = head->next;
    for (i = 0; i < pos; i++) {
        p = p->next;
        if (p == head) {
            printf("ָ��λ�ó�������Χ���޷�ɾ��\n");
            return -1;
        }
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

// �޸�ָ��λ�ýڵ�����
int modifyNode(Node* head, int pos, int newData) {
    int i;
    Node* p = head->next;
    for (i = 0; i < pos; i++) {
        p = p->next;
        if (p == head) {
            printf("ָ��λ�ó�������Χ���޷��޸�\n");
            return -1;
        }
    }
    p->data = newData;
}

// ����λ�ò�ѯ�ڵ�����
int queryByPos(Node* head, int pos) {
    int i;
    Node* p = head->next;
    for (i = 0; i < pos; i++) {
        p = p->next;
        if (p == head) {
            printf("ָ��λ�ó�������Χ����ѯʧ��\n");
            return -1;
        }
    }
    return p->data;
}

// �������ݲ�ѯλ�ã��򵥲��ҵ�һ��ƥ��ģ�
int queryByData(Node* head, int data) {
    Node* p = head->next;
    int pos = 0;
    while (p != head) {
        if (p->data == data) {
            return pos;
        }
        p = p->next;
        pos++;
    }
    printf("δ�ҵ���Ӧ���ݵĽڵ�\n");
    return -1;
}

// �����ӡ����
void printForward(Node* head) {
    Node* p = head->next;
    while (p != head) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// �����ӡ����
void printBackward(Node* head) {
    Node* p = head->prev;
    while (p != head) {
        printf("%d ", p->data);
        p = p->prev;
    }
    printf("\n");
}

// �ͷ������ڴ�
void freeList(Node* head) {
    Node* p = head->next;
    Node* next;
    while (p != head) {
        next = p->next;
        free(p);
        p = next;
    }
    free(head);
}

int main() {
    Node* head = NULL;
    int choice, pos, data, size;
    int queryChoice, result;
    while (1) {
        printf("\n1.����һ��˫��ѭ������\n");
        printf("2.���ӽ�㣨��������λ�����ӣ�\n");
        printf("3.ɾ����㣨��ɾ������λ�ý�㣩\n");
        printf("4.�޸Ľ������\n");
        printf("5.��ѯ������ݣ�����λ�ò����ݻ��߸������ݲ�λ�ã�\n");
        printf("6.������ʾ���н������\n");
        printf("7.������ʾ���н������\n");
        printf("8.�˳�\n");
        printf("���������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (head != NULL) {
                freeList(head);
            }
            printf("������Ҫ�����������С: ");
            scanf("%d", &size);
            if (size <= 0) {  // �������������С�Ƿ�Ϸ�
                printf("����������С���Ϸ�����������������\n");
                break;
            }
            head = createList(size);
            printf("\n˫��ѭ�������Ѵ���:\n");
            printForward(head);
            break;
        case 2:
            if (head == NULL) {
                printf("��Ч��ѡ������������!\n");
                break;
            }
            printf("������Ҫ�����λ�ú����ݣ��Կո������: ");
            scanf("%d %d", &pos, &data);
            if (pos < 0) {  // ������λ���Ƿ�Ϸ�
                printf("����λ�ò��Ϸ�����������ڵ���0������λ�ã�\n");
                break;
            }
            insertNode(head, pos, data);
            printf("\n�������ݺ��µĵ�����Ϊ��");
            printForward(head);
            break;
        case 3:
            if (head == NULL) {
                printf("\n��Ч��ѡ������������!\n");
                break;
            }
            printf("������Ҫɾ����λ��: ");
            scanf("%d", &pos);
            if (pos < 0) {  // ���ɾ��λ���Ƿ�Ϸ�
                printf("ɾ��λ�ò��Ϸ������������0������λ�ã�\n");
                break;
            }
            result=deleteNode(head, pos);
            if (result != -1){
                printf("\nɾ���������Ϊ��");
                printForward(head);
                break;
            }
            break;
        case 4:
            if (head == NULL) {
                printf("\n��Ч��ѡ������������!\n");
                break;
            }
            printf("������Ҫ�޸ĵ�λ�ú������ݣ��Կո������: ");
            scanf("%d %d", &pos, &data);
            if (pos < 0) {  // ����޸�λ���Ƿ�Ϸ�
                printf("�޸�λ�ò��Ϸ������������0������λ�ã�\n");
                break;
            }
            result=modifyNode(head, pos, data);
            if (result != -1) {
                printf("\n�µĵ�����Ϊ��");
                printForward(head);
                break;
            }
            break;
        case 5:
            if (head == NULL) {
                printf("\n��Ч��ѡ������������!\n");
                break;
            }
            printf("������1��λ�ò�ѯ������2�����ݲ�ѯ: ");
            scanf("%d", &queryChoice);
            if (queryChoice == 1) {
                printf("������Ҫ��ѯ��λ��: ");
                scanf("%d", &pos);
                if (pos < 0) {  // ����ѯλ���Ƿ�Ϸ�
                    printf("��ѯλ�ò��Ϸ������������0������λ�ã�\n");
                    break;
                }
                result = queryByPos(head, pos);
                if (result != -1) {
                    printf("��λ�ýڵ�����Ϊ: %d\n", result);
                }
                break;
            } if (queryChoice == 2) {
                printf("������Ҫ��ѯ������: ");
                scanf("%d", &data);
                result = queryByData(head, data);
                if (result != -1) {
                    printf("\n����������λ��Ϊ: %d\n", result);
                }
                break;
            }
            else {
                printf("\n��Ч������!\n");
            }
            break;
        case 6:
            if (head == NULL) {
                printf("\n��Ч��ѡ������������!\n");
                break;
            }
            printf("\n������ʾ���н������:\n");
            printForward(head);
            break;
        case 7:
            if (head == NULL) {
                printf("\n��Ч��ѡ������������!\n");
                break;
            }
            printf("\n������ʾ���н������:\n");
            printBackward(head);
            break;
        case 8:
            if (head != NULL) {
                freeList(head);
                return 0;
            }
            else {//ԭ���ǿ�����
                return 0;
            }
            printf("���˳�����\n");

        default:
            printf("��Ч��ѡ������������\n");
        }
    }
    return 0;
}