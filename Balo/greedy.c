#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct{
	char ten[20];
	int PA;
	float TL, DG, GT;
}dovat;

dovat *readfile(int *W, int *n){
	FILE *f;
	f = fopen("balo1.txt", "r");
	fscanf(f, "%f", W);
	dovat *ds;
	ds = (dovat*)malloc(sizeof(dovat));
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%f%f%[^\n]", &ds[i].TL, &ds[i].GT, &ds[i].ten);
		ds[i].PA = 0;
		ds[i].DG = ds[i].GT/ds[i].TL;
		i++;
		ds = (dovat*)realloc(ds, sizeof(dovat)*(i+1));
	}
	*n = i;
	fclose(f);
	return ds;
}

void in(dovat *ds, int n, int W){
	float tongW = 0, tongGT = 0;
	printf("-------Greedy-------\n");
	printf("|---|--------------------|------|------|------|------|\n");
	printf("|STT|        Ten         |  TL  |  GT  |  DG  |  PA  |\n");
	printf("|---|--------------------|------|------|------|------|\n");
	for(int i = 0; i < n; i++){
		printf("|%2d |%-20s|%6.2f|%6.2f|%6.2f| %4d |\n", i+1, ds[i].ten, ds[i].TL, ds[i].GT, ds[i].DG, ds[i].PA);
		tongW += ds[i].PA*ds[i].TL;
		tongGT += ds[i].PA*ds[i].GT;
	}
	printf("|---|--------------------|------|------|------|------|\n");
	printf("Phuong an: X(");
	for(int i = 0; i < n-1; i++)
		printf("%d, ", ds[i].PA);
	printf("%d)\n", ds[n-1].PA);
	printf("Trong luong: %.2f\n", tongW);
	printf("Gia tri: %.2f", tongGT);
}

void swap(dovat *x, dovat *y){
	dovat temp = *x;
	*x = *y;
	*y = temp;
}

void BubbleSort(dovat *dsdv, int n){
	for(int i = 0; i < n; i++){
		for(int j = n-1; j > i; j--){
			if(dsdv[j].DG > dsdv[j-1].DG){
				swap(&dsdv[j], &dsdv[j-1]);
			}
		}
	}
}

void Greedy(dovat *ds, int n, int W){
	for(int i = 0; i < n; i++){
		ds[i].PA = W/ds[i].TL;
		W -= ds[i].PA*ds[i].TL;
	}
}

int main(){
	dovat *ds;
	int n; 
	float W;
	ds = readfile(&W, &n);
	BubbleSort(ds, n);
	Greedy(ds, n, W);
	in(ds, n, W);
	
	return 0;
}
