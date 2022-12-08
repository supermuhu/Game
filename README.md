#include<windows.h>
#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
long long score = 0;
typedef struct{
	int x,y;
}point;
int gift = 0;
void Setwindowsize(SHORT width, SHORT height){
   HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
   SMALL_RECT Windowsize;
   Windowsize. Top=0;
   Windowsize. Left=0;
   Windowsize. Right=width;
   Windowsize.Bottom=height;
   SetConsoleWindowInfo(hStdout, 1, &Windowsize);
}
void GoTo_xy(SHORT posX, SHORT posY)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}
void SetColor(int backgound_color, int text_color){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
//
//0 = Black      
//1 = Blue
//2 = Green 
//3 = Aqua
//4 = Red    
//5 = Purple    
//6 = Yellow
//7 = White   
//8 = Gray
//9 = Light Blue
//10 = Light Green
//11 = Light Aqua
//12 = Light Red
//13 = Light Purple
//14 = Light Yellow
//15 = Bright White
//
}
void printWord(int x,int y,string c,int a,int b){
	GoTo_xy(x,y);
	SetColor(a,b);
	cout << c << endl;
	SetColor(0,7);
}
void Title(){
	printf("%80s\n"," [[[[|]]]]     [|]       ||]         [|]         [|]    [|]   [|][||||]");
	SetColor(0,1); //color
	printf("%80s\n","[[[     ]]]    [||[]     ||]        [|||]        [||  [|]     [||      ");
	SetColor(0,2); //color
	printf("%80s\n","     [[]]    [|| []    ||]       [|| ||]       [||[|]       [||      ");
	SetColor(0,3); //color
	printf("%80s\n"," [[|]]      [||  []   ||]      [|||||||]      [||[|]       [||[||||]");
	SetColor(0,4); //color
	printf("%80s\n","[[]]        [||   []  ||]     [||     ||]     [||[|]       [||      ");
	SetColor(0,5); //color
	printf("%80s\n","[[[     ]]]    [||     []||]    [||       ||]    [||  [|]     [||      ");
	SetColor(0,6); //color
	printf("%80s\n"," [[[[|]]]]     [||       [|]   [|]         [|]   [|]    [|]   [|][||||]");
	SetColor(0,7);
}
void inmatrix(int a[25][50],point head){
	SetColor(15,0);
	for(int i = 0 ; i < 25 ; i++){
		GoTo_xy(20,12+i);
		for(int j = 0 ; j < 50 ; j++){
			if(i == head.x && j == head.y){ // head
				SetColor(10,15);
				cout << ":";
				SetColor(15,0);
				continue;
			}
			switch(a[i][j]){
				case 0: // field
					cout << " ";
					break;
				case 2: // section
					SetColor(10,15);
					cout << " ";
					SetColor(15,0);
					break;
				case 3: // food
					SetColor(3,15);
					cout << " ";
					SetColor(15,0);
					break;
				case 4: // gift
					SetColor(12,15);
					cout << " ";
					SetColor(15,0);
					break;
			}
		}
	}
	SetColor(12,0);
	GoTo_xy(60,38);
	cout << "Point: ";
	cout << "   " <<score<< "   " << endl;
	SetColor(0,7);
}
void TestLose(){
	printWord(38,40,"  Thua cmm roi  ",4,0);
	printWord(35,41," Enter to play again ",7,1);
}
void random(int a[25][50]){
	srand(time(NULL));
	if(gift == 5){
		int k = rand() % (23 - 0 + 1) + 0,l = rand() % (48 - 0 + 1) + 0;
		while(1<2){
			if(a[k][l] == 0){
				if(a[k+1][l] != 2 && a[k][l+1] != 2 && a[k+1][l+1] != 2){
					a[k][l] = 4; a[k+1][l] = 4; a[k][l+1] = 4; a[k+1][l+1] = 4; gift = 0; break;
				}else{
					k = rand() % (23 - 0 + 1) + 0, l = rand() % (48 - 0 + 1) + 0;
				}
			}else{
				k = rand() % (23 - 0 + 1) + 0,l = rand() % (48 - 0 + 1) + 0;
			}
		}
	}else{
		int k = rand() % (24 - 0 + 1) + 0,l = rand() % (49 - 0 + 1) + 0;
		while(1<2){
			if(a[k][l] == 0){
				a[k][l] = 3; gift++; break;
			}else{
				k = rand() % (24 - 0 + 1) + 0, l = rand() % (49 - 0 + 1) + 0;
			}
		}
	}
}
void runtail(point &tail,int a[25][50],int b[25][50]){
	a[tail.x][tail.y] = 0;
	switch(b[tail.x][tail.y]){
		case 2: // right
			b[tail.x][tail.y] = 0;
			if(tail.y == 49) tail.y = -1;
			tail.y += 1;
			break;
		case 3: // left
			b[tail.x][tail.y] = 0;
			if(tail.y == 0) tail.y = 50;
			tail.y -= 1;
			break;
		case 4: // up
			b[tail.x][tail.y] = 0;
			if(tail.x == 0) tail.x = 25;
			tail.x -= 1;
			break;
		case 5: // down
			b[tail.x][tail.y] = 0;
			if(tail.x == 24) tail.x = -1;
			tail.x += 1;
			break;
	}
}
bool eat(int a[25][50],point &head,bool &count){
	switch(a[head.x][head.y]){
		case 2: // section
			count = false;
			return false;
		case 3: // food
			a[head.x][head.y] = 2;
			random(a);
			score += 1;
			return false;
		case 4: // gift
			if(a[head.x][head.y-1] == 4) a[head.x][head.y-1] = 0;
			if(a[head.x-1][head.y] == 4) a[head.x-1][head.y] = 0;
			if(a[head.x-1][head.y-1] == 4) a[head.x-1][head.y-1] = 0;
			if(a[head.x][head.y+1] == 4) a[head.x][head.y+1] = 0;
			if(a[head.x-1][head.y+1] == 4) a[head.x-1][head.y+1] = 0;
			if(a[head.x+1][head.y+1] == 4) a[head.x+1][head.y+1] = 0;
			if(a[head.x+1][head.y] == 4) a[head.x+1][head.y] = 0;
			if(a[head.x+1][head.y-1] == 4) a[head.x+1][head.y-1] = 0;
			a[head.x][head.y] = 2;
			random(a);
			score += 3;
			return false;
		default: // continually go
			a[head.x][head.y] = 2;
			return true;
	}
}
void right(int a[25][50],int b[25][50],bool &count,point &head,point &tail){
	b[head.x][head.y] = 2;
	if(head.y == 49) head.y = -1;
	head.y+=1;
	b[head.x][head.y] = 2;
	if(eat(a,head,count)) runtail(tail,a,b);
}
void left(int a[25][50],int b[25][50],bool &count,point &head,point &tail){
	b[head.x][head.y] = 3;
	if(head.y == 0) head.y = 50;
	head.y -= 1;
	b[head.x][head.y] = 3;
	if(eat(a,head,count)) runtail(tail,a,b);
}
void up(int a[25][50],int b[25][50],bool &count,point &head,point &tail){
	b[head.x][head.y] = 4;
	if(head.x == 0) head.x = 25;
	head.x -= 1;
	b[head.x][head.y] = 4;
	if(eat(a,head,count)) runtail(tail,a,b);
}
void down(int a[25][50],int b[25][50],bool &count,point &head,point &tail){
	b[head.x][head.y] = 5;
	if(head.x == 24) head.x = -1;
	head.x += 1;
	b[head.x][head.y] = 5;
	if(eat(a,head,count)) runtail(tail,a,b);
}
void game(){
	Title();
	int n;
	GoTo_xy(35,20);
	cout << "Nhap toc do: "; cin >> n;
	bool count = true;
	int a[25][50] = {0};
	int b[25][50] = {0};
	a[0][0] = 2;
	point head,tail;
	head.x = 0; head.y = 0;
	tail.x = 0; tail.y = 0;
	random(a);
	inmatrix(a,head);
	char c,d;
	for(;;){
		if(!count){
			TestLose();
			char c = getch();
			if(c == -32) c = getch();
			if(c == 13){
				system("cls");
				game();
			}
			else return;
		}
		if(kbhit()){
			c = getch();
			if(c == -32) c = getch();
			if(d == 72 && c == 80) c = 72;
			else if(d == 80 && c == 72) c = 80;
			else if(d == 75 && c == 77) c = 75;
			else if(d == 77 && c == 75) c = 77;
			d = c;
		}
		switch(c){
			case 72:
				up(a,b,count,head,tail);
				inmatrix(a,head);
				Sleep(n);
				break;
			case 80:
				down(a,b,count,head,tail);
				inmatrix(a,head);
				Sleep(n);
				break;
			case 75:
				left(a,b,count,head,tail);
				inmatrix(a,head);
				Sleep(n);
				break;
			case 77:
				right(a,b,count,head,tail);
				inmatrix(a,head);
				Sleep(n);
				break;
		}
	}
}
int main(){
	Setwindowsize(90,45);
	game();
	system("pause");
	return 0;
}
