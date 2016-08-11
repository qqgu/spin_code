#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 300

double 
eng_eval(double J[N][N], int *cof)
{
	int i, j;
	double	eng;
	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			eng += J[i][j] * cof[i] * cof[j];
		}
	}
	return eng;
}

int main(int argc, char *argv[])
{

	FILE *fp = fopen(argv[1], "r");
	if (NULL == fp) {
		printf("Can't open file: %s !\n", argv[1]);
		return -1;
	}
	srand((unsigned int)time(NULL));

	int	row, col;
	//row, col;
	double	cpl, J[N][N];
	//coupling;
	int	i,j;
	int	cof[N];
	int cir;
    double aver;
	double eng;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
		J[i][j] = 0.;
	}
	while (!feof(fp)) {
		fscanf(fp, "%d%d%lf", &row, &col, &cpl);
		if (row <= col)
			J[row][col] = cpl;
		else
			J[col][row] = cpl;
    }
/*********  initial configuration and energu  **************/
	for (j = 0; j < N; j++) {
		cof[j] = 2 * (rand() % 2) - 1;
	}
	eng = eng_eval(J, cof);
//    printf("ini energy%f\n", eng);
/***********  Updata the configutation *********************/   
	for (cir = 0; cir < 2000; cir++) {
		aver=0.;
		i = rand() % N;
		for (j = 0; j < N; j++)
        {
			if (i < j) aver += J[i][j] * cof[j];
			if (i > j) aver += J[j][i] * cof[j];
		}
/****** if flip i spin lower energy, then flip it  *********/
		if (cof[i] * aver > 0) {
			eng-=2*cof[i]*aver;
            cof[i] = -cof[i];
        }
	}
//	if (eng==eng_eval(J,cof)) printf("right!\n");
	printf("%f\n", eng);
	printf("v\t");
	for (i = 0; i < N; i++) {
		printf("%d\t", cof[i]);
	}
	printf("\n");

	fclose(fp);
	return 0;
}
