#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct{
	char ten[50];
	float TL, GT, DG;
	int PA;
}dovat;

dovat *readfile(float *W, int *n){
	FILE *f;
	f = fopen("balo1.txt", "r");
	fscanf(f, "%f", W);
	int i = 0;
	dovat *dsdv;
	dsdv = (dovat*)malloc(sizeof(dovat));
	while(!feof(f)){
		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].ten);
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		dsdv[i].PA = 0;
		i++;
		dsdv = (dovat*)realloc(dsdv, sizeof(dovat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
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

void in(dovat *dsdv, int n, float W){
	float tongTL = 0, tongGT = 0;
	printf("|---|------------------|------|------|------|------|\n");
	printf("|STT|      Do vat      |  TL  |  GT  |  DG  |  PA  |\n");
	printf("|---|------------------|------|------|------|------|\n");
	for(int i = 0; i < n; i++){
		printf("|%2d |%-18s|%6.2f|%6.2f|%6.2f|%6d|\n", i+1, dsdv[i].ten, dsdv[i].TL, dsdv[i].GT, dsdv[i].DG, dsdv[i].PA);
		tongTL += dsdv[i].PA*dsdv[i].TL;
		tongGT += dsdv[i].PA*dsdv[i].GT;
	}
	printf("|---|------------------|------|------|------|------|\n");
	printf("Phuong an: X(");
	for(int i = 0; i < n-1; i++){
		printf("%d, ", dsdv[i].PA);
	}
	printf("%d)\n", dsdv[n-1].PA);
	printf("Tong TL: %.2f\n", tongTL);
	printf("Tong GT: %.2f", tongGT);
}

void greedy(dovat *dsdv, int n, float W){
	for(int i = 0; i < n; i++){
		dsdv[i].PA = W/dsdv[i].TL;
		W -= dsdv[i].PA*dsdv[i].TL;
	}
}

int main(){
	dovat *dsdv;
	int n;
	float W;
	dsdv = readfile(&W, &n);
	BubbleSort(dsdv, n);
	greedy(dsdv, n, W);
	in(dsdv, n, W);
	return 0;
}
