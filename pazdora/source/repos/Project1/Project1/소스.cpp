//일본게임 파즈도라 만들기 190103~  C++
//앞의 숫자는 코딩순서
#include<stdio.h> //005 문자입출력 가능하게하는 헤더 (아스키 입력이 필요하므로)
#include<stdlib.h> //014 013while 문에서 반복시키기전에 필드를 초기화시키기 위해 필요
#include<time.h> //022 문양을 랜덤으로 배치하기위해서 난수를 초기화하기위해 현재시간 취득하기 위한 헤더 
#include<conio.h> //002 윈도우창을 닫히지않게(콘솔의 입출력에 해당되는 헤더) 

#define FIELD_WIDTH 8  //004 게임필드 가로
#define FIELD_HEIGHT 8 //004 게임필드 세로

#define BLOCK_TYPE_MAX 7 //016 게임문양이 7가지이므로 설정, 

enum { // 017 게임문양을 7가지이나 아무것도없는 경우까지 포함하면 8가지임
	CELL_TYPE_NONE, //아무것도 없는경우
	CELL_TYPE_BLOCK_0,
	CELL_TYPE_BLOCK_1,
	CELL_TYPE_BLOCK_2,
	CELL_TYPE_BLOCK_3,
	CELL_TYPE_BLOCK_4,
	CELL_TYPE_BLOCK_5,
	CELL_TYPE_BLOCK_6,  //0~6 7가지
	CELL_TYPE_MAX   //8번째
};

char cellAA/*019 문양설정*/[][2 + 1/*020 문양은 전각 한문자이므로 크기설정은 이것*/] = {
	"ㆍ",//CELL_TYPE_NONE
	"○",//CELL_TYPE_BLOCK_0
	"△",//CELL_TYPE_BLOCK_1
	"□",//CELL_TYPE_BLOCK_2
	"●",//CELL_TYPE_BLOCK_3
	"▲",//CELL_TYPE_BLOCK_4
	"■",//CELL_TYPE_BLOCK_5
	"☆",//CELL_TYPE_BLOCK_6
	

};

int cells[FIELD_HEIGHT][FIELD_WIDTH]; //018 문양의갯수
int checked[FIELD_HEIGHT][FIELD_WIDTH]; //041 040이 무한으로 작동하는것을 방지
int cursorX, cursorY; //008 문양을 선택하는 좌표
/*int selectedX, selectedY; *///028 문양을 바꾸는 기능을 넣기전에, 선택된 바꿀문양의 변수설정 036진행하기전의 오리지날 코드
//036  1. 선택을 하지않은 상태에서 엔터를누르면 선택하는 과정을 시작
int selectedX=-1, selectedY=-1;  // 037 화면바깥에 있을경우 선택되지않음을 설정

/* 038 아래는 문양이 몇개가 모였는지 취득하는 함수 */
int getConnectedBlockCount(int _x, int _y, int _cellType, int _count) { /*count는 모인 갯수*/
	if (/* 040 모이는 조건*/
		(_x < 0) || (_x >= FIELD_WIDTH) || (_y < 0) || (_y >= FIELD_HEIGHT)
		|| checked[_y][_x] //042 문양이 이 좌표에 위치하면 스킵
		|| (cells[_y][_x] == CELL_TYPE_NONE) /* 043 문양이 아무것도 없으면 스킵 */
	    || (cells[_y][_x] != _cellType)    /* 044  문양이 같지 않아도 스킵 */
		)
		return _count;

	_count++;
	checked[_y][_x] = true;
	// 045 반시계방향으로,  연결되어있는 문양의 갯수파악
	_count = getConnectedBlockCount(_x, _y-1,_cellType, _count);  //상
	_count = getConnectedBlockCount(_x-1, _y, _cellType, _count);  //좌
	_count = getConnectedBlockCount(_x, _y+1, _cellType, _count);  //하
	_count = getConnectedBlockCount(_x+1, _y, _cellType, _count);  //우


}
int main() { //001 프로그램의 엔트리포인트 
	srand((unsigned int/* 024 023과정에서 필요로함으로 입력*/)time(NULL));// 023 time(null)은 난수를 섞는 함수
	for (int y = 0; y < FIELD_HEIGHT; y++) //025 모든 필드에 랜덤으로 문양을 배치 
		for (int x = 0; x < FIELD_WIDTH; x++)  
			cells[y][x] = CELL_TYPE_BLOCK_0/*027 랜덤으로 배치문양의 시작*/ + rand() % BLOCK_TYPE_MAX;/*문양의 총갯수*/ //026 이곳애 문양을 랜덤으로 배치
	//여기까지 코딩하면 문양이 랜덤으로 배치됨
	while (1) { /* 013 반복시킴*/
		system("cls"); //015 014헤더를 사용함으로서  system함수 사용가능해짐 cls는 dos커멘드 화면을 클리어시키는 명령어
		// 여기까지 진행함으로서 문양을 이동시키는 코드가 완성됨
		for (int y = 0; y < FIELD_HEIGHT; y++){//006 문양을 세로로 배치, 필드의 세로크기만큼 
			for (int x = 0; x < FIELD_WIDTH; x++) // 005 문양을 가로로 배치, 필드의 가로크기만큼 
					if ((x == cursorX) && (y == cursorY)) //009 x,y 가 일치하면
						printf("◎"); // 010 이문양을 표시
					else
						printf("%s", cellAA[cells[y][x]]); //021 선택되지 않은 셀에 표시할 문양 0에서 6까지의 문양
			//여기까지는 아직 문양배치하지는 않은상태임
			if (y == selectedY)//029  전체셀중에 어디에있는 문양이 선택되었는지 표시함 가로줄만
				printf("←");
			printf("\n"); //007
		}

		for (int x = 0; x < FIELD_WIDTH; x++) //030 전체셀중에 어디에있는 문양이 선택되었는지 표시함 세로줄만
			printf("%s", (x == selectedX) ? "↑":" "); /*031 맞으면 화살표 아니면 공백 표시*/ 
		/*x의 좌표가  selectedX라면 *//*?만약에*//* :는 그렇지 않으면*/
		switch /* 011 입력에따라 움직이도록 */ (_getch()) { //003 _getch는 키보드의 입력대기
		case 'w': cursorY--; break; //키보드의  w 상
		case 's': cursorY++; break;  //하
		case 'a': cursorX--; break;  //좌
		case 'd': cursorX++; break;  //우
		default: /* 032 문양을 이동후 선택을하게되면 화살표도 같이 이동하게 만들기*/
			if (selectedX < 0) { //038 2. 선택을 한상태에서 엔터를 누르면 문양을 바꾸는 과정 진행, 0이라는것은 화면범위밖이라는것
				selectedX = cursorX;  // 033 덮어씌움
				selectedY = cursorY;  // 034 여기까지하면 문양이동시 화살표도 같이 이동되는과정 완성
			}
			else { // 039 바꾸는 과정
				int temp = cells[cursorY][cursorX];// 040문양을 바꾸기전에 일단대기시킴
				cells[cursorY][cursorX] =  cells[selectedY][selectedX]; // 041 새로운문양 덮어씌우기
				cells[selectedY][selectedX] =  temp; //042 원래문양 덮어씌우기
				selectedX =
					selectedY = -1;  //043 문양을 바꾼뒤 선택해제 (다시 새로운문양을 선택할수있도록)
			}
			break; 
		/* 035 문양을 바꾸는 과정의 논리과정 
		      1. 선택을 하지않은 상태에서 엔터를누르면 선택하는 과정
		      2. 선택을 한상태에서 엔터를 누르면 문양을 바꾸는 과정 
			  위의 두가지 과정이 필요함
		*/
		} // 012 여기까지 작성하면 실행후 종료되버림 그러니까 while문으로 반복시킴
	}
}