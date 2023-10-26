#include <stdio.h>

typedef int keytype;
typedef float othertype;

typedef struct{
	keytype key;
	othertype other;
}recordtype;

void ReadData(recordtype a[], int *n){
	FILE *f;
	f = fopen("data.txt", "r");
	int i;
	if(f != NULL){
		while(!feof(f)){
			fscanf(f, "%d%f", &a[i].key, &a[i].other);
			i++;
		}
	}
	else printf("Loi doc file!");
	fclose(f);
	*n = i;
}

void PrintData(recordtype a[], int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%2d   %3d   %.2f\n", i+1, a[i].key, a[i].other);
	}
}

void swap(recordtype *a, recordtype *b){
	recordtype temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void BubbleSort(recordtype a[], int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = n-1; j > i; j--){
			if(a[j].key < a[j-1].key){
				swap(&a[j], &a[j-1]);
			}
		}
	}
}

int main(){
	recordtype a[100];
	int n;
	ReadData(a, &n);
	printf("Du lieu ban dau:\n");
	PrintData(a, n);
	BubbleSort(a, n);
	printf("\nDu lieu sau khi thuc hien sap xep:\n");
	PrintData(a, n);
	return 0;
}
