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
	int i = 0;
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

void PushDown(recordtype a[], int first, int last){
	int r = first;
	while(r <= (last-1)/2){
		if(last == 2*r+1){
			if(a[r].key > a[last].key) swap(&a[r], &a[last]);
			r = last;
		}
		else if(a[r].key > a[2*r+1].key && a[2*r+1].key <= a[2*r+2].key){
			swap(&a[r].key, &a[2*r+1].key);
			r = 2*r+1;
		}
		else if(a[r].key > a[2*r+2].key){
			swap(&a[r].key, &a[2*r+2].key);
			r = 2*r+2;
		}
		else r = last;
	}
}

void HeapSort(recordtype a[], int n){
	int i;
	for(i = (n-2)/2; i >= 0; i--){
		PushDown(a, i, n-1);
	}
	for(i = n-1; i > 1; i--){
		swap(&a[i], &a[0]);
		PushDown(a, 0, i-1);
	}
	swap(&a[1], &a[0]);
}

int main(){
	recordtype a[100];
	int n;
	ReadData(a, &n);
	printf("Du lieu ban dau:\n");
	PrintData(a, n);
	HeapSort(a, n);
	printf("\nDu lieu sau khi thuc hien sap xep:\n");
	PrintData(a, n);
	return 0;
}
