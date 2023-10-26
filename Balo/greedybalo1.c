#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char ten[50];
	float TL, GT, DG;
	int PA;
}dovat;

dovat *ReadFile(float *W, int *n){
	FILE *f;
	f = fopen("balo1.txt", "r");
	fscanf(f, "%f", W);
	dovat *dsdv;
	dsdv = (dovat*)malloc(sizeof(dovat));
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].ten);
		dsdv[i].PA = 0;
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
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

void inDSDV(dovat *dsdv, int n, float W){
	int i;
	float tongW = 0, tongGT = 0;
	printf("Cai balo 1 su dung thuat toan tham an:\n");
	printf("Trong luong cua balo: %.2f\n", W);
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat   | T Luong | Gia Tri | Don Gia | Phuong an |\n");
	printf("|---|------------------|---------|---------|---------|-----------|\n");
	for(i = 0; i < n; i++){
		printf("|%2d |%-18s|%9.2f|%9.2f|%9.2f|%6d     |\n",i+1,dsdv[i].ten,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG,dsdv[i].PA);
		tongW += dsdv[i].PA * dsdv[i].TL;
		tongGT +=dsdv[i].PA * dsdv[i].GT;
	}	
	printf("|---|------------------|---------|---------|---------|-----------|\n");	
	printf("Phuong an (theo thu tu DG giam dan): X(");
	for(i=0; i<n-1; i++){
		printf("%d,", dsdv[i].PA);
	}	
	printf("%d)", dsdv[n-1].PA);
	printf("\nTong trong luong = %-9.2f\n",tongW);
	printf("Tong gia tri = %-9.2f\n",tongGT);
}

void Greedy(dovat *dsdv, int n, float W){
	for(int i = 0; i < n; i++){
		dsdv[i].PA = W/dsdv[i].TL;
		W -= dsdv[i].PA*dsdv[i].TL;
	}
}

int main(){
	int n;
	float W;
	dovat *dsdv;
	dsdv = ReadFile(&W, &n);
	BubbleSort(dsdv, n);
	Greedy(dsdv, n, W);
	inDSDV(dsdv, n, W);
	free(dsdv);
	return 0;
}
