#include<stdio.h>

#define ROW 3
#define COL 5

double SimplexTable[ROW][COL];
double TempState[COL]; // 最大化計算用

void X2Calc(); // x2に関するシンプレックス法 
void X1Calc(); // x1に関するシンプレックス法
void Result(); // x1, x2の解と最大値の表示
void Maxim(int pivot_row, int pivot_col); //最大化計算
void GaussCalc(int pivot_row, int pivot_col); //ガウス消去法計算
void Exchange(int pivot_row, int pivot_col); //移項計算
void Input(); //入力データ
void ShowTable(short step); //シンプレックス表の表示（計算ステップ）

int main() {
	Input();
	X2Calc(); //x2から決め打ち
	X1Calc(); //x1の計算
	Result(); //最終結果
	return 0;
}

void X2Calc() {
	//x2同士の比較
	int i, j;
	int pivot_row, pivot_col;
	//各行の大きさを計算
	double row1val = SimplexTable[1][4] / SimplexTable[1][1]; //1行目の重み
	double row2val = SimplexTable[2][4] / SimplexTable[2][1]; //2行目の重み
	// 1行目のほうが小さい場合
	if (row1val < row2val) {
		i = 1; //1行目でピボットをつくる
		double tmp = SimplexTable[1][1];
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] = SimplexTable[i][j] / tmp;
		}
		ShowTable(1);
		pivot_row = 1;
		pivot_col = 1;
		GaussCalc(pivot_row, pivot_col);
		ShowTable(2);
		Exchange(pivot_row, pivot_col);
		Maxim(pivot_row, pivot_col);
		ShowTable(3);
	}
	else {
		i = 2; //2行目でピボットをつくる
		double tmp = SimplexTable[2][1];
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] = SimplexTable[i][j] / tmp;
		}
		ShowTable(1);
		pivot_row = 2;
		pivot_col = 1;
		GaussCalc(pivot_row, pivot_col);
		ShowTable(2);
		Exchange(pivot_row, pivot_col);
		Maxim(pivot_row, pivot_col);
		ShowTable(3);
	}
}

void X1Calc() {
	//2行目x1の計算
	int i = 2, j;
	int pivot_row, pivot_col;
	double tmp = SimplexTable[2][0];
	for (j = 0; j < COL; j++) {
		SimplexTable[i][j] = SimplexTable[i][j] / tmp;
	}
	ShowTable(4);
	pivot_row = 2;
	pivot_col = 0;
	GaussCalc(pivot_row, pivot_col);
	ShowTable(5);
	Exchange(pivot_row, pivot_col);
	Maxim(pivot_row, pivot_col);
	ShowTable(6);
}

void Result() {
	int i, j, k = 0;
	double result[3]; // x1, x2, f の値がそれぞれ入る
	for (i = 1; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			if (SimplexTable[i][j] == 1) {
				//その行の最後の要素が解
				result[k] = SimplexTable[i][COL - 1]; 
				k++;
			}
		}
	}
	//最大値を入れる
	result[k] = SimplexTable[0][COL - 1];
	printf("\n***** Result *****\n");
	printf("x1 = %lf, ", result[0]);
	printf("x2 = %lf, ", result[1]);
	printf("f = %lf\n", result[2]);
}

void Maxim(int pivot_row, int pivot_col) {
	int i, j;
	//計算する最大化列のコピー
	double temp = SimplexTable[0][pivot_col];
	//最大値の確保
	double tempf = SimplexTable[0][COL - 1];
	//1行目を代入
	if (pivot_row == 1) {
		double x1temp = SimplexTable[0][0];
		i = 1;
		for (j = 0; j < COL; j++) {
			SimplexTable[0][j] = temp * TempState[j];
		}
		SimplexTable[0][0] += x1temp; //残ったx1の計算
		SimplexTable[0][pivot_col] = 0; //x2は0に
	}
	else {
		double x3temp = SimplexTable[0][2];
		i = 2;
		for (j = 0; j < COL; j++) {
			SimplexTable[0][j] = temp * TempState[j];
		}
		SimplexTable[0][2] += x3temp; //残ったx3の計算
		SimplexTable[0][pivot_col] = 0; //x1は0に
	}

	//既に値が代入されている（計算がなされている）場合
	if (SimplexTable[0][COL - 1] != 0) {
		SimplexTable[0][COL - 1] += tempf;
	}
}

void GaussCalc(int pivot_row, int pivot_col) {
	int i, j;
	//1行目がピボットならば2行目が計算対象
	if (pivot_row == 1) {
		i = 2;
		double tmp = SimplexTable[i][pivot_col] / SimplexTable[pivot_row][pivot_col];//何倍する必要があるか
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] -= (SimplexTable[pivot_row][j] * tmp);
		}
	}
	else {
		i = 1;
		double tmp = SimplexTable[i][pivot_col] / SimplexTable[pivot_row][pivot_col];
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] -= (SimplexTable[pivot_row][j] * tmp);
		}
	}
}

void Exchange(int pivot_row, int pivot_col) {
	int i, j;
	
	//1行目を符号反転
	if (pivot_row == 1) {
		i = 1;
		for (j = 0; j < COL; j++) {
			TempState[j] = SimplexTable[i][j] * (-1);
		}
		//最後の要素は反転しない
		TempState[COL - 1] = TempState[COL - 1] * (-1);
	}
	else {
		i = 2;
		for (j = 0; j < COL; j++) {
			//最後の要素は反転しない
			TempState[j] = SimplexTable[i][j] * (-1);
		}		
		//最後の要素は反転しない
		TempState[COL - 1] = TempState[COL - 1] * (-1);
	}
}

void ShowTable(short step) {
	int i, j;
	printf("\n------------------Simplex Table Step = %d-----------------\n", step);
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			printf("%10lf ", SimplexTable[i][j]);
		}
		printf("\n");
	}
}

void Input() {
	double sampledata[ROW][COL] = { {29, 45, 0, 0, 0},
								{2, 8, 1, 0, 60},
								{4, 4, 0, 1, 60} };
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] = sampledata[i][j];
		}
	}
	ShowTable(0); //計算ステップ0
}