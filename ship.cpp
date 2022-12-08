#include<windows.h>
#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
typedef struct{
	int x,y;
}ship;
int score = 0;
bool lose = false;
int bullet = 0;
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
bool lost(int a[35][100]){
	for(int i = 1 ; i < 99 ; i++){
		if(a[33][i] == 2) return true;
	}
	return false;
}
void randomPoint(int a[35][100],int x){
	srand(time(NULL)); 
	int l = rand() % (98 - 1 + 1) + 1;
	while(1<2){
		if(a[1][l] == 0){
			a[1][l] = x;
			return;
		}else{
			l = rand() % (98 - 1 + 1) + 1;
		}
	}
}
void random(int a[35][100],int &gift){
	if(gift == 1){
		randomPoint(a,5);
		gift = -1;
	}
	randomPoint(a,2);
}
void inmatrix(int a[35][100]){
	for(int i = 0 ; i < 35 ; i++){
		GoTo_xy(0,2+i);
		for(int j = 0 ; j < 100 ; j++){
			switch (a[i][j]){
				case 0:
					SetColor(0,15);
					cout << " ";
					break;
				case 1: // border
					SetColor(15,0);
					cout << " ";
					break;
				case 2: // aim
					SetColor(12,0);
					cout << " ";
					break;
				case 3: // ship
					SetColor(10,0);
					cout << " ";
					break;
				case 4: // bullet
					SetColor(0,15);
					cout << "o";
					break;
				case 5: // gift
					SetColor(6,0);
					cout << " ";
					break;
			}
		}
	}
	cout << endl;
	SetColor(12,0);
	GoTo_xy(80,38);
	cout << "Point: ";
	cout << "   " << score << "   " << endl;
	SetColor(0,7);
}
void setborder(int a[35][100]){
	for(int i = 0 ; i < 100 ; i++){
		a[0][i] = 1;
		a[34][i] = 1;
	}
	for(int i = 0 ; i < 35 ; i++){
		a[i][0] = 1;
		a[i][99] = 1;
	}
	a[33][49] = 3;
}
void run(int a[35][100],ship &left,ship &right){
	bool check[35][100] = {false};
	for(int i = 1 ; i < 34 ; i++){
		for(int j = 1 ; j < 99 ; j++){
			switch(a[i][j]){
				case 2:
					if(!check[i][j]){
						a[i][j] = 0;
						if(a[i+1][j] == 4){
						 	a[i+1][j] = 0;
						 	score += 1;
						}else if(a[i+1][j] == 3){
							a[i+1][j] = 0;
							lose = true;
						}else{
							a[i+1][j] = 2;
							check[i+1][j] = true;
						}
					}
					break;
				case 4:
					if(!check[i][j]){
						a[i][j] = 0;
						if(i-1 == 0) continue;
						if(a[i-1][j] == 2){
							a[i-1][j] = 0;
							score += 1;
						}else if(a[i-1][j] == 3){
							a[i-2][j] = 4;
							check[i-2][j] = true;
						}else if(a[i-1][j] == 5){
							a[i][j] = 5;
							a[i-1][j] = 4;
							check[i][j] = true;
							check[i-1][j] = true;
						}else{
							a[i-1][j] = 4;
							check[i-1][j] = true;
						}
					}
					break;
				case 5:
					if(!check[i][j]){
						a[i][j] = 0;
						if(i == 33) return;
						if(a[i+1][j] == 3 && !check[i][j]){
							bullet++;
							if(bullet%2 == 0) left.y -= 1;
							else right.y += 1;
						}else if(a[i+1][j] == 4){
							a[i][j] = 4;
							a[i+1][j] = 5;
							check[i][j] = true;
							check[i-1][j] = true;
						}else{
							a[i+1][j] = 5;
							check[i+1][j] = true;
						}
					}
					break;
			}
		}
	}
}
void conditionmove(int a[35][100],ship &s,ship &left, ship &right){
	switch(a[s.x][s.y]){
		case 2:
			a[s.x][s.y] = 0;
			lose = true;
			return;
		case 4:
			run(a,left,right);
			break;
		case 5:
			bullet++;
			if(bullet%2 == 0)left.y -= 1;
			else right.y += 1;
			break;
	}
}
void move(int a[35][100],char c,ship &s,ship &left, ship &right){
	switch (c){
		case 72:
			//up;
			if(s.x > 1){
				a[s.x][s.y] = 0;
				s.x -= 1;
				left.x -= 1;
				right.x -= 1;
				conditionmove(a,s,left,right);
				a[s.x][s.y] = 3;
			}
			break;
		case 80:
			//down;
			if(s.x < 33){
				a[s.x][s.y] = 0;
				s.x += 1;
				left.x += 1;
				right.x += 1;
				conditionmove(a,s,left,right);
				a[s.x][s.y] = 3;
			}
			break;
		case 75:
			//left;
			if(s.y > 1){
				a[s.x][s.y] = 0;
				s.y -= 1;
				left.y -= 1;
				right.y -= 1;
				conditionmove(a,s,left,right);
			}else{
				a[s.x][s.y] = 0;
				left.y += 97;
				right.y += 97;
				s.y = 98;
			}
			a[s.x][s.y] = 3;
			break;
		case 77:
			//right;
			if(s.y < 98){
				a[s.x][s.y] = 0;
				s.y += 1;
				left.y += 1;
				right.y += 1;
				conditionmove(a,s,left,right);
			}else{
				a[s.x][s.y] = 0;
				left.y -= 97;
				right.y -= 97;
				s.y = 1;
			}
			a[s.x][s.y] = 3;
			break;
		case 32:
			// shoot
			if(s.x == 1) return;
			int k = min(right.y,98);
			while(k >= left.y && k >= 1){
				a[s.x-1][k] = 4;
				k--;
			}
			break;
	}
}
void game(){
	int a[35][100] = {0};
	setborder(a);
	inmatrix(a);
	ship s;
	s.x = 33; s.y = 49;
	ship left, right;
	left.x = 33 ; left.y = 49;
	right.x = 33 ; right.y = 49;
	for(int count = 0,gift = -1;1<2;count ++){
		srand(time(NULL));
		gift = rand()%10;
		char c;
		if(kbhit()){
			c = getch();
			if(c == -32) c = getch();
			move(a,c,s,left,right);
			if(count % 6 == 0) run(a,left,right);
		}else{
			if(count % 6 == 0) run(a,left,right);
		}
		if(count == 40){
			random(a,gift);
			count = 0;
		}
		inmatrix(a);
		if(lost(a) || lose){
			printWord(41,37,"  Thua cmm roi  ",4,0);
			return;
		}
	}	
}
int main(){
	Setwindowsize(100,40);
	game();
	system("pause");
	return 0;
}
