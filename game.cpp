#include<iostream>
#include<conio.h>
#include<dos.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 115
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int score=0;
int rand_pos;
int pos;
int select_arrow = 0;

void play();



//_______________________STACK__________________________
class Stack
{
    public:
    int top;
    unsigned capacity;
    char* array;
};

// function to create a stack of given
// capacity. It initializes size of stack as 0
Stack* createStack(unsigned capacity)
{
    Stack* stack = new Stack();
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = new char[(stack->capacity * sizeof(char))];
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(Stack* stack)
{ return stack->top == stack->capacity - 1; }

// Stack is empty when top is equal to -1
int isEmpty(Stack* stack)
{ return stack->top == -1; }

// Function to add an item to stack.
// It increases top by 1
void push(Stack* stack, char item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to remove an item from stack.
// It decreases top by 1
char pop(Stack* stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}







void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void gameover(){
	system("cls");
	cout<<endl;
    gotoxy(42,5); cout<<" ------------------------------ ";
    gotoxy(42,6); cout<<" |          GAME OVER         | ";
    gotoxy(42,7); cout<<" ------------------------------";
    gotoxy(55,9); cout<<"SCORE: "<<score;
	gotoxy(48,15);
    cout<<" _____         _____";
    gotoxy(48,16);
    cout<<"|     |       |     |";
    gotoxy(48,17);
    cout<<"|  A  |       |  D  |";
    gotoxy(48,18);
    cout<<"|_____|       |_____|";
    gotoxy(48,19);
    cout<<"REPLAY          MENU";
    score=0;
	if (getch() == 'a')
        play();

}

void win(){
	system("cls");
	score +=1;
	cout<<endl;
    gotoxy(42,5); cout<<" ------------------------------ ";
    gotoxy(42,6); cout<<" |           You Win          | ";
    gotoxy(42,7); cout<<" ------------------------------";
    gotoxy(55,9); cout<<"SCORE: "<<score;
	gotoxy(48,15);
    cout<<" _____         _____";
    gotoxy(48,16);
    cout<<"|     |       |     |";
    gotoxy(48,17);
    cout<<"|  A  |       |  D  |";
    gotoxy(48,18);
    cout<<"|_____|       |_____|";
    gotoxy(48,19);
    cout<<"CONTINUE        MENU";
	if (getch() == 'a')
        play();
    }


void instructions(){

	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n1. A random pattern will appear to you like this\n           XOOXOO ";
	cout<<"\n\n2. After 3 second it will disappear";
	cout<<"\n\n3. You should choose the reversed pattern";
	cout<<"\n\n         OXXXOX  XXOXOX  OOXOOX";
	cout<<"\n\n                           ^";
	cout<<"\n                           ^";
	cout<<"\n                           ^";
	cout<<"\n\n\n\n\nPress any key to go back to menu";
	getch();
}
char rand_char (){
if (rand()%2 ==1)
    return 'X';
else
    return 'O';
}


void play(){

    system("cls");
    char ch;

    for(int i=3; i>0; i--){
        gotoxy(SCREEN_WIDTH/2,10); cout<<i;
        Sleep(500);
        system("cls");
        Sleep(500);
    }

    gotoxy(2,2);
    cout<<"SCORE:";
    gotoxy(10,2);
    cout<<score;

    Stack* stack = createStack(6);

    for (int i=0; i<6; i++){
            char x = rand_char();
        gotoxy(SCREEN_WIDTH/2+i-3,10); cout<<x; push(stack,x);
    }
    gotoxy(0,5);
    cout<<"------------------------------------------------------------------------------------------------------------------------";
    for(int i=0; i<=120; i++){
        gotoxy(i,5);    cout<<" ";
        Sleep(40);
    }
    for (int i=0; i<6; i++){
        gotoxy(SCREEN_WIDTH/2+i-3,10); cout<<' ';
    }

    rand_pos = rand()%3;
    for (int i=0; i<rand_pos; i++){
        pos = SCREEN_WIDTH*i/4+15;
        for (int j=0; j<6; j++){
            gotoxy(pos+j,10); cout<<rand_char();
        }
    }
    pos = SCREEN_WIDTH*rand_pos/4+15;
    for (int i=0; i<6; i++){
        gotoxy(pos+i,10); cout<<pop(stack);
    }

    for (int i=(rand_pos+1); i<4; i++){
        pos = SCREEN_WIDTH*i/4+15;
        for (int j=0; j<6; j++){
            gotoxy(pos+j,10); cout<<rand_char();
        }
    }
    gotoxy(45,18);
    cout<<" _____       _____       _____";
    gotoxy(45,19);
    cout<<"|     |     |     |     |     |";
    gotoxy(45,20);
    cout<<"|  A  |     |  S  |     |  D  |";
    gotoxy(45,21);
    cout<<"|_____|     |_____|     |_____|";
    gotoxy(45,22);
    cout<<" LEFT         OK         RIGHT";

    do{
    pos = SCREEN_WIDTH*select_arrow/4+15;
    for (int i=0; i<3;i++){
        gotoxy(pos+3,12+i); cout<<'^';
    }
    ch = getch();
    if (ch == 'd' && select_arrow<3)
        select_arrow += 1;

    else if (ch == 'a' && select_arrow>0)
        select_arrow -= 1;

    for (int i=0; i<3;i++){
        gotoxy(pos+3,12+i); cout<<' ';
    }

    }while(ch != 's');

    if (select_arrow == rand_pos)
        win();
    else
        gameover();
}

int main()
{
    gotoxy(50,9);
    for(int i=0; i<13; i++){
        cout<<"Original Work"[i];
        Sleep(100);
    }

    gotoxy(46,10);
    for(int i=0; i<21; i++){
        cout<<"EECE Cairo University"[i];
        Sleep(100);
    }
    Sleep(2000);

    while(1){
        setcursor(0,0);
        srand( (unsigned)time(NULL));


        system("cls");
        gotoxy(42,5); cout<<" ------------------------------ ";
        gotoxy(42,6); cout<<" |         MEMORY FLIP        | ";
        gotoxy(42,7); cout<<" ------------------------------";
        gotoxy(50,9); cout<<"1. Start Game";
        gotoxy(50,10); cout<<"2. Instructions";
        gotoxy(50,11); cout<<"3. Quit";

        char op = getche();

        if( op=='1')
            play();
        else if
            ( op=='2') instructions();
        else if
            ( op=='3') exit(0);
    }

	return 0;
}
