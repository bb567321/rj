#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct
{
    int x;
    int y;
} PosType;
typedef struct
{
    PosType seat;
    int di;
} SElemType;
typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

int Init1[8][8] = { {0} };
int Init2[8][8] =
{
    {2,3,4,4,4,4,3,2},
    {3,4,6,6,6,6,4,3},
    {4,6,8,8,8,8,6,4},
    {4,6,8,8,8,8,6,4},
    {4,6,8,8,8,8,6,4},
    {4,6,8,8,8,8,6,4},
    {3,4,6,6,6,6,4,3},
    {2,3,4,4,4,4,3,2},
};
int HTry1[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int HTry2[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void MarkPrint(PosType pos);
PosType NextPos(PosType curpos,int x);
void FootPrint(PosType &curpos,int surstep);
int Pass(PosType &curpos);
int InitStack(SqStack &S);
void DestroyStack(SqStack &S);
int StackEmpty(SqStack &S);
int Push(SqStack &S,SElemType e);
int Pop(SqStack &S,SElemType &e);
void print(int curstep);

int main()
{
    SqStack S;
    SElemType e;
    PosType Mincurpos,curpos,start;
    int curstep;

    InitStack(S);
    printf("请输入起始位置<坐标例如：0 0>");
    scanf("%d%d",&start.x,&start.y);
    curpos = start;
    curstep = 1;
    do
    {
        if(Pass(curpos))
        {
            FootPrint(curpos,curstep);
            e.di = 0;
            e.seat= curpos;
            Push(S,e);
            if(curstep == 64)
            {
                print(curstep);
                DestroyStack(S);
                return 1;
            }
            curpos = NextPos(curpos,e.di);
            curstep ++;
        }
        else
        {
            if(!StackEmpty(S))
            {
                Pop(S,e);
                curstep --;
                while(e.di == 7 && !StackEmpty(S))
                {
                    MarkPrint(e.seat);
                    Pop(S,e);
                    curstep --;
                }
                if(e.di < 7)
                {
                    Mincurpos = curpos;
                    e.di ++;
                    curpos = NextPos(e.seat,e.di);
                    while(Mincurpos.x == curpos.x && Mincurpos.y == curpos.y && e.di < 7)
                    {
                        e.di ++;
                        curpos = NextPos(e.seat,e.di);
                    }
                    Push(S,e);
                    curstep ++;

                }
            }
        }
    }
    while(!StackEmpty(S));
    DestroyStack(S);
    return 0;
}

void print(int curstep)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
            printf("%3d",Init1[i][j]);
        printf("\n");
    }
    printf("\n");
    printf("\n");
    getchar();
}

void MarkPrint(PosType pos)
{
    Init1[pos.x][pos.y] = 0;
}

PosType NextPos(PosType curpos,int x)
{
    PosType MinCurpos,temp;

    MinCurpos.x = -1;
    MinCurpos.y = -1;
    for(; x < 8; x++)
    {
        temp.x = curpos.x + HTry1[x];
        temp.y = curpos.y + HTry2[x];
        if(temp.x < 0 || temp.x > 7 || temp.y < 0 || temp.y > 7 || Init1[temp.x][temp.y])
        {
            continue;
        }
        if(MinCurpos.x == -1 && MinCurpos.y == -1)
            MinCurpos = temp;
        else if( Init2[MinCurpos.x][MinCurpos.y] > Init2[ temp.x][temp.y] )
            MinCurpos= temp;
    }
    if(MinCurpos.x == -1 && MinCurpos.y == -1)
        return curpos;
    return MinCurpos;
}

void FootPrint(PosType &curpos,int curstep)
{
    Init1[curpos.x][curpos.y] = curstep;
}

int Pass(PosType &curpos)
{
    if(!Init1[curpos.x][curpos.y])
        return 1;
    else
        return 0;
}

void DestroyStack(SqStack &S)
{
    S.base = S.top;
    S.stacksize = 0;
}

int StackEmpty(SqStack &S)
{
    if(S.base == S.top)
        return 1;
    else
        return 0;
}

int InitStack(SqStack &S)
{
    S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base)
        return 0;
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return 1;
}

int Push(SqStack &S,SElemType e)
{
    if(S.top - S.base >= S.stacksize )
    {
        S.base = (SElemType*)realloc(S.base,(STACK_INIT_SIZE+STACKINCREMENT )*sizeof(SElemType));
        if(!S.base)
            return 0;
        S.top = S.base +S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return 1;
}

int Pop(SqStack &S,SElemType &e)
{
    if(S.top == S.base)
        return 0;
    e = *--S.top;
    return 1;
}
