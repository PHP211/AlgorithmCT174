#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	char ten[20];
	int TL, GT, PA;	
}dovat;

typedef int bang[50][100];//50 do vat co toi da 99 trong luong

dovat *readfile(int *W, int *n){
	FILE *f;
	f = fopen("balo1.txt", "r");
	dovat *ds;
	ds = (dovat*)malloc(sizeof(dovat));
	int i = 0;
	fscanf(f, "%d", W);
	while(!feof(f)){
		fscanf(f, "%d%d%[^\n]", &ds[i].TL, &ds[i].GT, &ds[i].ten);
		ds[i].PA = 0;
		i++;
		ds = (dovat*)realloc(ds, sizeof(dovat)*(i+1));
	}
	*n = i;
	fclose(f);
	return ds;
}

void in(dovat *ds, int n, int W){
	int tongW = 0, tongGT = 0;
	printf("-------QHD-------\n");
	printf("|---|--------------------|------|------|------|\n");
	printf("|STT|        Ten         |  TL  |  GT  |  PA  |\n");
	printf("|---|--------------------|------|------|------|\n");
	for(int i = 0; i < n; i++){
		printf("|%2d |%-20s|%6d|%6d|%6d|\n", i+1, ds[i].ten, ds[i].TL, ds[i].GT, ds[i].PA);
		tongW += ds[i].PA*ds[i].TL;
		tongGT += ds[i].PA*ds[i].GT;
	}
	printf("|---|--------------------|------|------|------|\n");
	printf("Trong luong: %d\n", tongW);
	printf("Gia tri: %d", tongGT);
}

void TaoBang(dovat *ds, int n, int W, bang F, bang X){
	int x, y, k;
	int Fmax, Xmax, V;
	
	//2 dong dau
	for(V = 0; V <= W; V++){
		X[0][V] = V/ds[0].TL;
		F[0][V] = X[0][V]*ds[0].GT;
	}
	
	//cac dong con lai
	for(k = 1; k < n; k++){
		for(V = 0; V <= W; V++){
			Fmax = F[k-1][V];
			Xmax = 0;
			y = V/ds[k].TL;
			for(x = 1; x <= y; x++){
				if(F[k-1][V-x*ds[k].TL] + x*ds[k].GT > Fmax){
					Fmax = F[k-1][V-x*ds[k].TL] + x*ds[k].GT;
					Xmax = x;
				}
			}
			F[k][V] = Fmax;
			X[k][V] = Xmax;
		}
	}
}

void InBang(int n, int W, bang F, bang X){
	for(int k = 0; k < n; k++){
		for(int V = 0; V <= W; V++){
			printf("|%4d%2d", F[k][V], X[k][V]);
		}
		printf("\n");
	}
}

void TraBang(dovat *ds, int n, int W, bang X){
	int k, V;
	V = W;
	for(k = n-1; k >= 0; k--){
		ds[k].PA = X[k][V];
		V -= X[k][V] * ds[k].TL;
	}
}

int main(){
	bang F, X;
	dovat *ds;
	int W, n;
	
	ds = readfile(&W, &n);
	TaoBang(ds, n, W, F, X);
	InBang(n, W, F, X);
	TraBang(ds, n, W, X);
	in(ds, n, W);
}
