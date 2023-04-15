#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_SIZE 10
#define MAX 100
int count = 0;
int cnt = 0;
typedef struct {
    short r;
    short c;
} element;

typedef struct {
    element data[MAX];
    int top;
} StackType;

void init_stack(StackType* s) {
    s->top = -1;
}

int is_empty(StackType* s) {
    return (s->top == -1);
}

int is_full(StackType* s) {
    return (s->top == (MAX - 1));
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else {
        s->data[++(s->top)] = item;
    }
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else {

        return s->data[(s->top)--];
    }
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else {
        return s->data[s->top];
    }
}
//��ġ �˷���
element here = { 1, 0 }, entry = { 1,0 };

//�̷�
char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1','1','1','1','1','1','1','1','1','1'},
    {'e','1','0','1','0','0','0','1','0','1'},
    {'0','0','0','1','0','0','0','1','0','1'},
    {'0','1','0','0','0','1','1','0','0','1'},
    {'1','0','0','0','1','0','0','0','0','1'},
    {'1','0','0','0','1','0','0','0','0','1'},
    {'1','0','0','0','0','0','1','0','1','1'},
    {'1','0','1','1','1','0','1','1','0','1'},
    {'1','1','0','0','0','0','0','0','0','x'},
    {'1','1','1','1','1','1','1','1','1','1'}
};

//
void push_loc(StackType* s, int r, int c) {

    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return; //�̷θ� ����� RETURN ó��

    if (maze[r][c] != '1' && maze[r][c] != '.') { //���� �ƴϰ� �̹� �� ���� �ƴϸ� push
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
        cnt += 1;
    }
    
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) { //�̷� ���
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void) {
    int r, c;
    
    StackType s;


    init_stack(&s);
    here = entry;
    while (maze[here.r][here.c] != 'x') { //�����Ҷ�����

        
        r = here.r;
        c = here.c;
        
        
        maze[r][c] = '.'; //��ġ�� .ǥ���ϱ�
        maze_print(maze); //�ٲ� �̷� ����ϱ�
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);
        
        if (cnt == 0) {
            count += 1;
        }

        cnt = 0;
        

        if (is_empty(&s)) {
            printf("����\n");
            return;
        }
        else
            here = pop(&s);



    }
    printf("����\n");
    printf("count : %d", count);
    return 0;
}