#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 300

double eng_eval(double J[N][N],int *cof)
{
    int i,j;
    double eng;
    for(i=0;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            eng+=J[i][j]*cof[i]*cof[j];
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
    srand((unsigned int) time(NULL));

    int row,col;        //row, col;  
    double cpl,J[N][N];        // coupling;  
    int i,j;
    int cof[N],min_f[N];
    int *pmin,*pc,*pmid;
    double min_energy,eng;
   
   pc=cof;
   pmin=min_f;

    for (i=0;i<N;i++)
    {
        for (j=0;j<N;j++)
        J[i][j]=0.;
    }
    while (!feof(fp)) 
    {
        fscanf(fp,"%d%d%lf",&row,&col,&cpl);
        if(row<=col)    J[row][col]=cpl;
        else    J[col][row]=cpl;
    }
min_energy=1.e9;
    for(i=0;i<10;i++)
    {
        for (j=0;j<N;j++)
        {
            pc[j]=2*(rand()%2)-1;
        }

        eng=eng_eval(J,pc);
        if(eng<min_energy)
        {
            min_energy=eng;
            pmid=pmin;
            pmin=pc;
            pc=pmid;
        }

    }
    printf("\n%f\n",min_energy);
    printf("v\t");
   for(i=0;i<N;i++)
   {
       printf("%d\t",pmin[i]);
   }


    fclose(fp);
    printf("\n\n");
    return 0;
}