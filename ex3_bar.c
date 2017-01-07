#include <stdio.h>

#define N 3
#define M 3

/*calculates |a-b|*/
int calcDistance(int a, int b)
{
    int distance=0;
    distance=a-b;
    if(distance>=0) return distance;
    else return (distance*(-1));
}

/*return 1 if i,j are in the array boundaries, and 0 otherwise*/
int isCellLegal(int i, int j)
{
    if((i<0) || (i>=N) || (j<0) || (j>=M))
        return 0;
    else return 1;
}

/*returns 1 if there is a neighbour with distance <= 1, and 0 otherwise*/
int isNeighbourClose(int mat[N][M], int i, int j, int a, int b)
{
    int distance;
    distance=calcDistance(mat[i][j],mat[a][b]);
    if(distance>1) return 0;
    else return 1;
}

/*returns 1 if the cell is extreme(see PDF) and 0 otherwise*/
int isCellExtreme(int mat[N][M], int i, int j)
{
    int count=0, n, m;
    for(n=-1;n<2;n++){
        for(m=-1;m<2;m++){
            //if((i=!(i+n)) && (j=!(j+m))) {
            if ( !(n==0 && m==0) ) //TODO: looks better - it's easy to understand why
                if(isCellLegal((i+n),(j+m))){
                    if(isNeighbourClose(mat, i, j, (i+n), (j+m))){
                        count++; //TODO: counter is redundant just write here "return 1"
                    }
                }
            }
        }
    if (count) return 0; //TODO: see comment above. write here "return 0" and finish function. no if needed
    else return 1; // TODO: you got confused between the return values - i flipped them
}

/*returns the average value of the neighbours of cell i,j in mat[N][M]*/
int calcNeighboursAverage(int mat[N][M], int i, int j)
{
    int avg=0, count=0, sum=0, n, m;
    for(n=-1;n<2;n++){
        for(m=-1;m<2;m++){
            if(isCellLegal((i+n),(j+m))){
                if((n!=0) || (m!=0)){ //TODO: you wrote =! instead of !=
                    sum+=mat[n][m];
                    count++;}}}}
    avg=(sum/count);
    return avg;
}

/*returns the minimum value of a neighbour of the cell i,j in mat[N][M]*/
int getMinOfNeighbours(int mat[N][M], int i, int j)
{
    int min=0, n, m;
    for(n=-1;n<1;n++){
        for(m=-1;m<2;m++){
            switch(isCellLegal((i+n),(j+m))) //TODO: WRONG use of switch - should be if isCellLegal((i+n),(j+m)) update max and break
                case 1:
                    min=mat[i+n][j+m];
            break;}}
    for(n=-1;n<1;n++){
        for(m=-1;m<2;m++){
            if(isCellLegal((i+n),(j+m)))
                if((n!=0) || (m!=0)) //TODO: you wrote =! instead of !=
                    min=min>mat[i+n][j+m]?mat[i+n][j+m]:min;}}
    return min;
}

/*blurs extreme pixels and puts how many there were in numOfExtremePixels.
and how many were corrected with neighbour's average in numOfExtremePixelsCorrectedWithAvg*/
void blurImage(int mat[N][M], int* numOfExtremePixels, int* numOfExtremePixelsCorrectedWithAvg)
{
    int extreme=0, num=0, n, m;
    for(n=0 ; n<N ; n++){
        for(m=0 ; m<M ; m++){ //TODO: add spaces ya kamtzan
            if(isCellExtreme(mat, n, m)) {
                mat[n][m]=calcNeighboursAverage(mat, n, m);
                extreme++;
                num++; //TODO: bad name
                if(isCellExtreme(mat, n, m)) {
                    mat[n][m]=getMinOfNeighbours(mat, n, m);
                    num--;
                }
            } //TODO: I changed indentation - more readable now
        }
    }
    *numOfExtremePixels=extreme;
    *numOfExtremePixelsCorrectedWithAvg=num;
    return;
}

/*fills the matrix mat[N][M] with values from the user*/
void recieveMatrix(int mat[N][M])
{
    int i, j;
    for(i=0;i<N;i++)
        for(j=0;j<M;j++)
            scanf("%d", &mat[i][j]);
    getchar();
}

void printMatrix(int mat[N][M])
{
    int i, j;
    for(i = 0; i < N; i++) {
        for(j = 0; j < M; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int mat[N][M];
    int numOfExtremePixels=0, numOfExtremePixelsCorrectedWithAvg=0;
    printf("Please insert an image\n");
    recieveMatrix(mat);
    blurImage(mat, &numOfExtremePixels, &numOfExtremePixelsCorrectedWithAvg);
    printf("This is the blurred image:\n");
    printMatrix(mat);
    printf("Total extreme pixels found: %d\n", numOfExtremePixels);
    printf("Extreme pixels corrected by average: %d\n", numOfExtremePixelsCorrectedWithAvg);
    return 0;
}