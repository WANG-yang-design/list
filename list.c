#define _CRT_SECURE_NO_WARNINGS //2022版本解决scanf
#include <stdio.h>
#include <stdlib.h>
//for version 2010

// 定义链表节点结构体
typedef struct Node {
    int data;
    struct Node* prev;//前一个节点
    struct Node* next;//下一个
} Node;

 // 创建双向循环链表，可指定大小和输入节点内容（改进）
 Node* createList(int size) {
     int i;
	 Node* p;
	 Node* newNode;
	 Node* temp;
     Node* head = (Node*)malloc(sizeof(Node));  // 为链表头节点分配内存空间
     if (head == NULL) {  // 检查内存分配是否成功
         printf("内存分配失败！\n");
         return NULL;
     }
     head->prev = head;  // 初始化头节点的prev指针指向自身，构建循环链表的初始结构
     head->next = head;

     p = head;  // 设置一个指针p，初始指向头节点，用于遍历链表和插入新节点的操作辅助

     for (i = 0; i < size; i++) {
         newNode = (Node*)malloc(sizeof(Node));  // 为新节点分配内存空间
         if (newNode == NULL) {  // 如果内存分配失败
             printf("内存分配失败！\n");
             // 释放已分配的节点内存（从当前已插入的节点开始逐个释放，直到头节点）
             while (head != p) {
                 temp = p;
                 p = p->prev;
                 free(temp);
             }
             free(head);  // 最后释放头节点内存
             return NULL;
         }

         // 处理输入缓冲区遗留的换行符等，确保后续scanf能正确获取用户输入
         while (getchar() != '\n');

         printf("请输入第 %d 个节点的数据: ", i + 1);
         if (scanf("%d", &newNode->data) != 1) {  // 检查scanf是否成功读取到一个整数
             printf("输入数据格式错误，请输入整数！\n");
             free(newNode);  // 释放刚分配的新节点内存，因为输入不合法
             // 可选择继续释放已分配的其他节点内存并返回，这里选择直接返回，避免复杂逻辑，可根据需求调整
             return NULL;
         }

         newNode->next = p->next;  // 将新节点的next指针指向当前节点p的下一个节点
         newNode->prev = p;  // 将新节点的prev指针指向当前节点p
         p->next->prev = newNode;  // 更新当前节点p的下一个节点的prev指针，使其指向新节点
         p->next = newNode;  // 更新当前节点p的next指针，使其指向新节点
         p = newNode;  // 将指针p移动到新插入的节点位置，方便下一次插入操作
     }

     return head;  // 返回创建好的双向循环链表的头节点指针
 }

// 在指定位置插入节点
 void insertNode(Node* head, int pos, int data) {
     int i;
	 Node* oldNext;
	 Node* tail;
	 Node* temp;
     Node* newNode = (Node*)malloc(sizeof(Node));
     Node* p = head;
     if (newNode == NULL) {
         printf("内存分配失败！\n");
         return;
     }
     newNode->data = data;

     if (pos == 0) {
         // 插入位置为0时，将新节点作为头节点插入的操作
         oldNext = head->next;  // 保存原头节点的下一个节点指针

         // 调整新节点的指针关系
         newNode->next = oldNext;
         newNode->prev = head;

         // 更新原头节点的下一个节点的prev指针，使其指向新节点
         oldNext->prev = newNode;

         // 更新原头节点的next指针，使其指向新节点
         head->next = newNode;

         // 让新节点成为链表新的头节点
         head = newNode;
     }
     else {
         // 插入位置不是0时，先遍历链表，查找插入位置
         p = head;
         for (i = 0; i < pos; i++) {
             p = p->next;
             if (p == head) {
                 // 如果遍历过程中指针p再次指向头节点，说明指定位置超出链表范围
                 printf("指定位置超出链表范围，插入到链表末尾\n");
                 break;
             }
         }

         if (p == head) {
             // 以下是插入到链表末尾的操作
             // 先获取原链表的尾节点（双向循环链表中头节点的prev指针指向尾节点）
             tail = head->prev;

             // 将新节点的next指针指向头节点，建立与头节点的连接
             newNode->next = head;

             // 将新节点的prev指针指向原尾节点，建立与原尾节点的连接
             newNode->prev = tail;

             // 更新原尾节点的next指针，使其指向新节点
             tail->next = newNode;

             // 更新头节点的prev指针，使其指向新节点，完成新节点插入到末尾的操作
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
     // 返回更新后的头节点指针（确保调用函数处能获取到正确的头节点）
     return;
 }


// 删除指定位置节点
int deleteNode(Node* head, int pos) {
    int i;
    Node* p = head->next;
    for (i = 0; i < pos; i++) {
        p = p->next;
        if (p == head) {
            printf("指定位置超出链表范围，无法删除\n");
            return -1;
        }
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

// 修改指定位置节点内容
int modifyNode(Node* head, int pos, int newData) {
    int i;
    Node* p = head->next;
    for (i = 0; i < pos; i++) {
        p = p->next;
        if (p == head) {
            printf("指定位置超出链表范围，无法修改\n");
            return -1;
        }
    }
    p->data = newData;
}

// 根据位置查询节点内容
int queryByPos(Node* head, int pos) {
    int i;
    Node* p = head->next;
    for (i = 0; i < pos; i++) {
        p = p->next;
        if (p == head) {
            printf("指定位置超出链表范围，查询失败\n");
            return -1;
        }
    }
    return p->data;
}

// 根据内容查询位置（简单查找第一个匹配的）
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
    printf("未找到对应数据的节点\n");
    return -1;
}

// 正向打印链表
void printForward(Node* head) {
    Node* p = head->next;
    while (p != head) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 反向打印链表
void printBackward(Node* head) {
    Node* p = head->prev;
    while (p != head) {
        printf("%d ", p->data);
        p = p->prev;
    }
    printf("\n");
}

// 释放链表内存
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
        printf("\n1.创建一个双向循环链表\n");
        printf("2.增加结点（能在任意位置增加）\n");
        printf("3.删除结点（能删除任意位置结点）\n");
        printf("4.修改结点内容\n");
        printf("5.查询结点内容（根据位置查内容或者根据内容查位置）\n");
        printf("6.正向显示所有结点内容\n");
        printf("7.反向显示所有结点内容\n");
        printf("8.退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (head != NULL) {
                freeList(head);
            }
            printf("请输入要创建的链表大小: ");
            scanf("%d", &size);
            if (size <= 0) {  // 检查输入的链表大小是否合法
                printf("输入的链表大小不合法，请输入正整数！\n");
                break;
            }
            head = createList(size);
            printf("\n双向循环链表已创建:\n");
            printForward(head);
            break;
        case 2:
            if (head == NULL) {
                printf("无效的选择，请重新输入!\n");
                break;
            }
            printf("请输入要插入的位置和数据（以空格隔开）: ");
            scanf("%d %d", &pos, &data);
            if (pos < 0) {  // 检查插入位置是否合法
                printf("插入位置不合法，请输入大于等于0的整数位置！\n");
                break;
            }
            insertNode(head, pos, data);
            printf("\n插入数据后新的的链表为：");
            printForward(head);
            break;
        case 3:
            if (head == NULL) {
                printf("\n无效的选择，请重新输入!\n");
                break;
            }
            printf("请输入要删除的位置: ");
            scanf("%d", &pos);
            if (pos < 0) {  // 检查删除位置是否合法
                printf("删除位置不合法，请输入大于0的整数位置！\n");
                break;
            }
            result=deleteNode(head, pos);
            if (result != -1){
                printf("\n删除后的链表为：");
                printForward(head);
                break;
            }
            break;
        case 4:
            if (head == NULL) {
                printf("\n无效的选择，请重新输入!\n");
                break;
            }
            printf("请输入要修改的位置和新数据（以空格隔开）: ");
            scanf("%d %d", &pos, &data);
            if (pos < 0) {  // 检查修改位置是否合法
                printf("修改位置不合法，请输入大于0的整数位置！\n");
                break;
            }
            result=modifyNode(head, pos, data);
            if (result != -1) {
                printf("\n新的的链表为：");
                printForward(head);
                break;
            }
            break;
        case 5:
            if (head == NULL) {
                printf("\n无效的选择，请重新输入!\n");
                break;
            }
            printf("请输入1按位置查询，输入2按内容查询: ");
            scanf("%d", &queryChoice);
            if (queryChoice == 1) {
                printf("请输入要查询的位置: ");
                scanf("%d", &pos);
                if (pos < 0) {  // 检查查询位置是否合法
                    printf("查询位置不合法，请输入大于0的整数位置！\n");
                    break;
                }
                result = queryByPos(head, pos);
                if (result != -1) {
                    printf("该位置节点内容为: %d\n", result);
                }
                break;
            } if (queryChoice == 2) {
                printf("请输入要查询的内容: ");
                scanf("%d", &data);
                result = queryByData(head, data);
                if (result != -1) {
                    printf("\n该内容所在位置为: %d\n", result);
                }
                break;
            }
            else {
                printf("\n无效的输入!\n");
            }
            break;
        case 6:
            if (head == NULL) {
                printf("\n无效的选择，请重新输入!\n");
                break;
            }
            printf("\n正向显示所有结点内容:\n");
            printForward(head);
            break;
        case 7:
            if (head == NULL) {
                printf("\n无效的选择，请重新输入!\n");
                break;
            }
            printf("\n反向显示所有结点内容:\n");
            printBackward(head);
            break;
        case 8:
            if (head != NULL) {
                freeList(head);
                return 0;
            }
            else {//原本是空链表
                return 0;
            }
            printf("已退出程序\n");

        default:
            printf("无效的选择，请重新输入\n");
        }
    }
    return 0;
}