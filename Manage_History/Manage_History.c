#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LINK_SIZE 256

typedef struct node {
    char link[MAX_LINK_SIZE];
    struct node* p_next;
} NODE;

void AddWebBrowsingHistory(NODE** pp_head, NODE** pp_tail);
void PrintWebBrowsingHistory(NODE* p_head);
void DeleteRecentHistory(NODE** pp_head, NODE** pp_tail);
void Delete_a_History(NODE** pp_head, NODE** pp_tail);
void ClearHistory(NODE** pp_head, NODE** pp_tail);
void PrintMenu();

int main()
{
    NODE* p_head = NULL;  
    NODE* p_tail = NULL;
    int num = 0;

    while (true) {
        PrintMenu();
        scanf("%d", &num);
        if (num == 1) AddWebBrowsingHistory(&p_head, &p_tail);
        else if (num == 2) PrintWebBrowsingHistory(p_head);
        else if (num == 3) DeleteRecentHistory(&p_head, &p_tail);
        else if (num == 4) Delete_a_History(&p_head, &p_tail);
        else if (num == 5) ClearHistory(&p_head, &p_tail);
        else if (num == 6) break;
        else printf("1에서 6까지 숫자 중 하나를 입력해주세요.\n");
    }
    ClearHistory(&p_head, &p_tail);
    return 0;
}

void AddWebBrowsingHistory(NODE** pp_head, NODE** pp_tail)
{
    char link[MAX_LINK_SIZE];
    printf("웹사이트 URL을 입력하세요 : ");
    scanf("%s", link);

    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    if (new_node == NULL) {
        printf("메모리 할당 실패\n");
        return;
    }
    new_node->p_next = *pp_head;
    strncpy(new_node->link, link, MAX_LINK_SIZE - 1);
    new_node->link[MAX_LINK_SIZE - 1] = '\0';
    *pp_head = new_node;

    if (*pp_tail == NULL) {  
        *pp_tail = new_node;
    }
}

void PrintWebBrowsingHistory(NODE* p_head)
{
    if (p_head == NULL) {
        printf("기록이 없습니다.\n");
        return;
    }
    NODE* p = p_head;
    printf("최근 방문 기록 :\n");
    int cnt = 0;
    while (p != NULL) { 
        printf("%d. %s\n", ++cnt, p->link);
        p = p->p_next;
    }
}

void DeleteRecentHistory(NODE** pp_head, NODE** pp_tail)
{
    if (*pp_head == NULL) {  
        printf("기록이 없습니다.\n");
        return;
    }
    NODE* p = *pp_head;
    *pp_head = p->p_next;
    free(p);

    if (*pp_head == NULL) {  
        *pp_tail = NULL;
    }
}

void Delete_a_History(NODE** pp_head, NODE** pp_tail)
{
    bool deleted = false;
    NODE* p = *pp_head;
    if (*pp_head == NULL) {  
        printf("기록이 없습니다.\n");
        return;
    }
    printf("삭제하고 싶은 기록의 번호나 주소를 입력하세요 : ");
    char link[MAX_LINK_SIZE];
    int number = -1;
    char* input = (char*)malloc(MAX_LINK_SIZE);
    scanf("%255s", input);

    char* endptr;
    number = strtol(input, &endptr, 10);
    NODE* p_prev = NULL;

    if (*endptr == '\0') {
        for (int i = 0; i < number - 1; i++) {
            if (p->p_next == NULL) {  
                printf("올바른 번호를 입력해주세요.\n");
                free(input);
                return;
            }
            p_prev = p;
            p = p->p_next;
        }
        if (p == *pp_head) {
            *pp_head = p->p_next;
            if (*pp_head == NULL) *pp_tail = NULL;
        }
        else if (p == *pp_tail) {
            *pp_tail = p_prev;
            (*pp_tail)->p_next = NULL;
        }
        else {
            p_prev->p_next = p->p_next;
        }
        free(p);
        deleted = true;
    }
    else {
        snprintf(link, sizeof(link), "%s", input);
        NODE* temp;
        while (p != NULL) {  
            if (strcmp(link, p->link) == 0) {
                if (p == *pp_head) {
                    *pp_head = p->p_next;
                    if (*pp_head == NULL) *pp_tail = NULL;
                }
                else if (p == *pp_tail) {
                    *pp_tail = p_prev;
                    (*pp_tail)->p_next = NULL;
                }
                else {
                    p_prev->p_next = p->p_next;
                }
                temp = p;
                p = p->p_next;
                free(temp);
                deleted = true;
            }
            else {
                p_prev = p;
                p = p->p_next;
            }
        }
    }

    free(input);
    if (!deleted) printf("삭제할 기록이 없습니다.\n");
}

void ClearHistory(NODE** pp_head, NODE** pp_tail)
{
    NODE* p = *pp_head;
    while (p != NULL) { 
        NODE* temp = p;
        p = p->p_next;
        free(temp);
    }
    *pp_head = NULL;
    *pp_tail = NULL;
}

void PrintMenu()
{
    printf("\n1. 웹사이트 방문 기록 추가\n");
    printf("2. 방문 기록 출력\n");
    printf("3. 최근 방문한 웹사이트 삭제\n");
    printf("4. 특정 웹사이트 방문 기록 삭제\n");
    printf("5. 방문 기록 초기화\n");
    printf("6. 종료\n");
    printf("메뉴를 선택하세요: ");
}