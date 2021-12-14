#include<stdio.h>

#define ROW 3
#define COL 5

double SimplexTable[ROW][COL];

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

int main() {
    /*// puts
    puts("dies ist puts");
    
    // putchar
    putchar('c');

    // putc
    //putc('c', stdout);

    // nl
    printf("\n");
    
    // printf with different format specifiers
    // printf int
    int int1 = 14;
    printf("decimal: %d\n", int1);
    
    // printf float
    float float1 = 1.5;
    printf("float: %f\n", float1);
    
    // printf double
    double double1 = 1.23;
    printf("double: %lf\n", double1);

    // character
    char char1 = 'n';
    printf("char: %c\n", char1);

    // string
    char* string1 = "ich bin ein string1";
    printf("string: %s\n", string1);*/

    double sampledata[ROW][COL] = { {29, 45, 0, 0, 0},
								{2, 8, 1, 0, 60},
								{4, 4, 0, 1, 60} };
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			SimplexTable[i][j] = sampledata[i][j];
		}
	}

    ShowTable(10);

	return 0;
}