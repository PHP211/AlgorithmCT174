#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char ten[20];
	int TL, GT, PA;
}dovat;

typedef int bang[50][100]; //50 do vat co trong luong toi da 99

dovat *readfile(int *W, int *n){
	FILE *f;
	f = fopen("balo1.txt", "r");
	fscanf(f, "%d", W);
	dovat *dsdv;
	dsdv = (dovat*)malloc(sizeof(dovat));
	int i = 0;
	while(!feof(f)){
		fscanf(f, "%d%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].ten);
		dsdv[i].PA = 0;
		i++;
		dsdv = (dovat*)realloc(dsdv, sizeof(dovat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}

void in(dovat *dsdv, int n, int W){
	int tongW = 0, tongGT = 0;
	printf("------QUY HOACH DONG------");
	printf("\nPhuong an Cai Ba lo 1 dung thuat toan QUY HOACH DONG nhu sau:\n");
	printf("|---|------------------|----------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat   | T Luong  | Gia Tri | Phuong an |\n");
	printf("|---|------------------|----------|---------|-----------|\n");
	for(int i = 0; i < n; i++){
		printf("|%2d |%-18s|%5d     |%5d    |%6d     |\n", i+1, dsdv[i].ten, dsdv[i].TL, dsdv[i].GT, dsdv[i].PA);
		tongW += dsdv[i].PA*dsdv[i].TL;
		tongGT += dsdv[i].PA*dsdv[i].GT;
	}
	printf("|---|------------------|----------|---------|-----------|\n");
	printf("\nTrong luong ban dau: %d", W);
	printf("\nTong gia tri: %d", tongGT);
	printf("\nTong trong luong: %d", tongW);
}

void taobang(dovat *dsdv, int n, int W, bang F, bang X){
	int x, y, k;
	int Fmax, Xmax, V;
	
	//2 dong dau
	for(V = 0; V <= W; V++){
		X[0][V] = V/dsdv[0].TL;
		F[0][V] = X[0][V]*dsdv[0].GT;
	}
	
	//cac dong con lai
	for(k = 1; k < n; k++){
		for(V = 0; V <= W; V++){
			Fmax = F[k-1][V];
			Xmax = 0;
			y = V/dsdv[k].TL;
			for(x = 1; x <= y; x++){
				if(F[k-1][V-x*dsdv[k].TL] + x*dsdv[k].GT > Fmax){
					Fmax = F[k-1][V-x*dsdv[k].TL] + x*dsdv[k].GT;
					Xmax = x;
				}
			}
			F[k][V] = Fmax;
			X[k][V] = Xmax;
		}
	}
}

void inbang(int n, int W, bang F, bang X){
	for(int k = 0; k < n; k++){
		for(int V = 0; V <= W; V++){
			printf("|%4d%2d", F[k][V], X[k][V]);
		}
		printf("\n");
	}
}

void trabang(dovat *dsdv, int n, int W, bang X){
	int k, V;
	V = W;
	for(k = n-1; k >= 0; k--){
		dsdv[k].PA = X[k][V];
		V -= X[k][V]*dsdv[k].TL;
	}
}

int main(){
	bang F, X;
	dovat *dsdv;
	int W, n;
	
	dsdv = readfile(&W, &n);
	taobang(dsdv, n, W, F, X);
	inbang(n, W, F, X);
	trabang(dsdv, n, W, X);
	in(dsdv, n, W);
}
