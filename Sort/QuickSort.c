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

int FindPivot(recordtype a[], int first, int last){
	int k = first+1;
	while(k <= last && a[k].key == a[first].key) k++;
	if(k > last) return -1;
	if(a[k].key > a[first].key) return k;
	return first;
}

int Partition(recordtype a[], int first, int last, int pivot){
	int L = first;
	int R = last;
	while(L <= R){
		while(a[L].key < pivot) L++;
		while(a[R].key >= pivot) R--;
		if(L < R) swap(&a[R], &a[L]);
	}
	return L;
}

void QuickSort(recordtype a[], int first, int last){
	int pivotindex, pivot, p;
	pivotindex = FindPivot(a, first, last);
	if(pivotindex != -1){
		pivot = a[pivotindex].key;
		p = Partition(a, first, last, pivot);
		QuickSort(a, first, p-1);
		QuickSort(a, p, last);
	}
}

int main(){
	recordtype a[100];
	int n;
	ReadData(a, &n);
	printf("Du lieu ban dau:\n");
	PrintData(a, n);
	QuickSort(a, 0, n);
	printf("\nDu lieu sau khi thuc hien sap xep:\n");
	PrintData(a, n);
	return 0;
}
