// Bai toan Cai ba lo 2
// Moi do vat co so luong xac dinh
// Du lieu cho trong file CaiBalo2.INP
// Giai bai toan bang thuat toan NHANH CAN

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	char TenDV[20];
	float TL, GT, DG;
	int SL, PA;
} DoVat;

DoVat * ReadFromFile(float *W, int *n){
     FILE *f;
     f = fopen("CaiBalo2.INP", "r");
     fscanf(f, "%f",W); // Xac dinh trong luong Ba lo
	 DoVat *dsdv;
	 dsdv=(DoVat*)malloc(sizeof(DoVat));
	 int i=0;
 	 while (!feof(f)){
	   fscanf(f, "%f%f%d%[^\n]",&dsdv[i].TL,&dsdv[i].GT,&dsdv[i].SL,&dsdv[i].TenDV);
	   dsdv[i].DG=dsdv[i].GT/dsdv[i].TL;
	   dsdv[i].PA=0;
	   i++;
	   dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));  
	 }
	 *n=i;
     fclose(f);
     return dsdv;
}

void swap(DoVat *x, DoVat *y){
	DoVat Temp;
	Temp = *x;
	*x   = *y;
	*y   = Temp;
}

void BubbleSort(DoVat *dsdv, int n){
	int i,j;
	for(i=0; i<=n-2; i++)
	   for (j=n-1; j>=i+1; j--){
	   	 if (dsdv[j].DG>dsdv[j-1].DG) 
			swap(&dsdv[j],&dsdv[j-1]);
	  }   
}

void InDSDV(DoVat *dsdv ,int n, float W){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("\nPhuong an Cai Ba lo 2 dung thuat toan NHANH CAN nhu sau:\n");
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     |T. Luong | Gia Tri |So luong | Don gia | Phuong an |\n");
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-20s|%9.2f|%9.2f|%5d    |%9.2f|%6d     |\n",
		i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].SL,dsdv[i].DG, dsdv[i].PA);
		TongTL=TongTL+dsdv[i].PA * dsdv[i].TL;
		TongGT=TongGT+dsdv[i].PA * dsdv[i].GT;
	}	
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");	
	printf("Trong luong cua ba lo = %-9.2f\n",W);
	printf("Tong trong luong = %-9.2f\n",TongTL);
	printf("Tong gia tri = %-9.2f\n",TongGT);
}

void nutgoc(float W, float *V, float *CT, float *GLNTT, float *TGT, float DG_Max){
	*TGT = 0;
	*V = W;
	*CT = *V * DG_Max;
	*GLNTT = 0;
}

void GLNTT(float TGT, float *GLNTT, int x[], DoVat *ds, int n){
	if(*GLNTT < TGT){
		*GLNTT = TGT;
		for(int i = 0; i < n; i++){
			ds[i].PA = x[i];
		}
	}
}

int min(int a, int b){
	return a<b? a:b;
}

void nhanhcan(int i, float *TGT, float *CT, float *V, float *GLNTT, int x[], DoVat *ds, int n){
	int j, yk;
	yk = min(ds[i].SL, *V/ds[i].TL);
	for(j = yk; j >= 0; j--){
		*TGT += j*ds[i].GT;
		*V -= j*ds[i].TL;
		*CT = *TGT + (*V)*ds[i+1].DG; 
		if(*CT > *GLNTT){
			x[i] = j;
			if((i == n-1) || (*V == 0))
				GLNTT(*TGT, GLNTT, x, ds, n);
			else nhanhcan(i+1, TGT, CT, V, GLNTT, x, ds, n);
		}
		x[i] = 0;
		*TGT -= j*ds[i].GT;
		*V == j*ds[i].TL;	
	}
}
	
int main(){
	DoVat * dsdv;	// Danh sach cac do vat (mang dong cua cac do vat)
	int n; 			// luu so luong do vat
	float W; 		// Luu trong luong cua Ba lo
	
	float CT; 		// Luu can tren
	float TGT; 		// Luu Tong gia tri cua cac vat da duoc chon tai moi nut
	float V; 		// Luu Trong luong con lai cua Ba lo tai moi nut
	float GLNTT; 	// Luu Gia lon nhat tam thoi 
	
	dsdv = ReadFromFile(&W, &n);
	
	int x[n];		// Luu phuong an tot nhat tam thoi
	
	BubbleSort(dsdv,n);
	butgoc(W, &V, &CT, &GLNTT, &TGT, dsdv[0].DG);
	nhanhcan(0, &TGT, &CT, &V, &GLNTT, x, dsdv, n);
	InDSDV(dsdv,n,W);
	
	free(dsdv);
	return 0;
}
