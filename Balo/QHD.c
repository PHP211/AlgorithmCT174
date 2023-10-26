// Bai toan cai ba lo 1
// Moi do vat co so luong khong han che
// Du lieu cho trong file QHD_CaiBalo.INP
// Giai bai toan bang thuat toan QUY HOACH DONG

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	char TenDV[20];
	int TL, GT, PA;
} DoVat;

typedef int bang[50][100];// Ba lo co trong luong toi da 99 va co toi da 50 do vat

DoVat *ReadFromFile(int *W, int *n){
     FILE *f;
     f = fopen("balo1.txt", "r");
     fscanf(f, "%d",W); // Xac dinh trong luong Ba lo
	 DoVat *dsdv;
	 dsdv=(DoVat*)malloc(sizeof(DoVat));
	 int i=0;
 	 while (!feof(f)){
	   fscanf(f, "%d%d%[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].TenDV);
	   dsdv[i].PA=0;
	   i++;
	   dsdv=(DoVat*)realloc(dsdv,sizeof(DoVat)*(i+1));  
	 }
	 *n=i;
     fclose(f);
     return dsdv;
}

void InDSDV(DoVat *dsdv ,int n, int W){
	int i, TongTL=0, TongGT=0;
	printf("\nPhuong an Cai Ba lo 1 dung thuat toan QUY HOACH DONG nhu sau:\n");
		printf("|---|------------------|----------|---------|-----------|\n");
		printf("|STT|     Ten Do Vat   | T Luong  | Gia Tri | Phuong an |\n");
		printf("|---|------------------|----------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-18s|%5d     |%5d    |%6d     |\n",
		i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].PA);
		TongTL=TongTL+dsdv[i].PA * dsdv[i].TL;
		TongGT=TongGT+dsdv[i].PA * dsdv[i].GT;
	}	
	printf("|---|------------------|----------|---------|-----------|\n");	
	printf("Trong luong cua ba lo = %-9d\n",W);
	printf("Tong trong luong = %-9d\n",TongTL);
	printf("Tong gia tri = %-9d\n",TongGT);
}

void TaoBang(DoVat *dsdv,int n,int W, bang F,bang X){
	int x, y, k;
	int Fmax, Xmax, i;
	
	//2 dong dau
	for(i = 0; i <= W; i++){
		X[0][i] = i/dsdv[0].TL;
		F[0][i] = X[0][i]*dsdv[0].GT;
	}
	
	//cac dong con lai
	for(k = 1; k < n; k++){
		for(i = 0; i <= W; i++){
			Fmax = F[k-1][i];
			Xmax = 0;
			y = i/dsdv[k].TL;
			for(x = 1; x <= y; x++){
				if(F[k-1][i - x*dsdv[k].TL] + x*dsdv[k].GT > Fmax){
					Fmax = F[k-1][i - x*dsdv[k].TL] + x*dsdv[k].GT;
					Xmax = x;
				}
			}
			F[k][i] = Fmax;
			X[k][i] = Xmax;
		}
	}
}

void InBang(int n, int W, bang F, bang X){
	int V, k;
	for(k=0; k<n; k++){
		for(V=0; V<=W; V++){
			printf("|%3d%3d ",F[k][V], X[k][V]);
		}	 	
		printf("\n");
	}
}

void TraBang(DoVat *dsdv, int n, int W, bang X) {
	int k, V;
	V = W;
	for(k= n-1; k>=0; k--) {
	 	dsdv[k].PA = X[k][V];
	 	V = V - X[k][V] * dsdv[k].TL;
	}
}

int main(){
	int n, W;
	bang X,F;
	DoVat *dsdv;
	dsdv=ReadFromFile(&W, &n);
	
	TaoBang(dsdv,n,W,F,X);
	InBang(n,W,F,X);
	printf("\n");
	TraBang(dsdv,n,W,X);
	InDSDV(dsdv,n,W);
	
	free(dsdv);
	return 0;
}
