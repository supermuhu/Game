#include<windows.h>
#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
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
void setwheel(int a[7][11]){
	a[0][5] = 2; a[6][5] = 2; a[3][1] = 2; a[3][9] = 2;
	a[1][2] = 2; a[1][8] = 2; a[5][2] = 2; a[5][8] = 2;
	a[2][1] = 2; a[4][1] = 2; a[4][9] = 2; a[2][9] = 2;
	a[0][4] = 2; a[0][6] = 2; a[6][4] = 2; a[6][6] = 2;
	a[0][3] = 2; a[0][7] = 2; a[6][3] = 2; a[6][7] = 2;
}
void inmatran(int a[7][11],int site){
	
	for(int i = 0 ; i < 7 ; i++){
		//GoTo_xy(site,i);
		GoTo_xy(0,i);
		for(int j = 0 ; j < 11 ; j++){
			if(a[i][j] == 2) cout << "o";
			else cout << " ";
		}
		cout << endl;
	}
}
void spin(int a[7][11],int count){
	for(int i = 0 ; i < 7 ; i ++){
		for(int j = 0 ; j < 11 ; j++){
			a[i][j] = 1;
		}
	}
	setwheel(a);
	switch(count){
		case 1:
			a[2][2]=2;a[2][3]=2;a[3][4]=2;a[3][6]=2;a[4][7]=2;a[4][8]=2;
			a[1][6]=2;a[2][6]=2;a[4][4]=2;a[5][4]=2;
			break;
		case 2:
			a[2][3]=2;a[3][4]=2;a[3][6]=2;a[4][7]=2;
			a[2][6]=2;a[1][7]=2;a[4][4]=2;a[5][3]=2;      
			break;                                                                                                                                                                                                                                                                                              
		case 3:
			a[1][3]=2;a[2][4]=2;a[4][6]=2;a[5][7]=2;
			a[2][7]=2;a[3][6]=2;a[4][4]=2;a[4][3]=2;
			break;
		case 4:
			a[1][4]=2;a[2][4]=2;a[4][6]=2;a[5][7];
			a[2][8]=2;a[2][7]=2;a[3][6]=2;a[3][4]=2;a[4][3]=2;a[4][2]=2;
			break;
		case 5:
			for(int i = 1 ; i < 7-1 ; i += 2){
				a[i][5] = 2;
			}
			for(int i = 2 ; i < 11-1 ; i += 2){
				a[3][i] = 2;
			}
			break;
	}
}
void wheel(){
	int n=7,m=11;
	int a[7][11];
	setwheel(a);
	inmatran(a,0);
	for(int count = 1,site = 1,site2 = 20;;count++,site++,site2++){
		spin(a,count);
		inmatran(a,site);
		if(count == 5) count = 0;
		Sleep(100);
	}
}
int main(){
	wheel();
	return 0;
}
