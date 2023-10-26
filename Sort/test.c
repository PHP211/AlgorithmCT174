#include <stdio.h>

typedef struct{
	int key;
	float other;
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
	*n = i;
	fclose(f);
}

void PrintData(recordtype a[], int n){
	for(int i = 0; i < n; i++){
		printf("%2d   %3d   %.2f\n", i+1, a[i].key, a[i].other);
	}
}

void swap(recordtype *x, recordtype *y){
	recordtype temp = *x;
	*x = *y;
	*y = temp;
}

void PushDown(recordtype a[], int first, int last){
	int r = first;
	while(r <= (last-1)/2){
		if(last == 2*r+1){
			if(a[r].key > a[last].key) swap(&a[r], &a[last]);
			r = last;
		}
		else if(a[r].key > a[2*r+1].key && a[2*r+1].key <= a[2*r+2].key){
			swap(&a[2*r+1], &a[r]);
			r = 2*r+1;
		}
		else if(a[r].key > a[2*r+2].key){
			swap(&a[2*r+2], &a[r]);
			r = 2*r+2;
		}
		else r = last;
	}
}

void HeapSort(recordtype a[], int n){
	for(int i = (n-2)/2; i >= 0; i--){
		PushDown(a, i, n-1);
	}
	for(int i = n-1; i >= 2; i--){
		swap(&a[i], &a[0]);
		PushDown(a, 0, i-1);
	}
	swap(&a[0], &a[1]);
}

int main(){
	recordtype a[100];
	int n;
	printf("Du lieu ban dau:\n");
	ReadData(a, &n);
	PrintData(a, n);
	printf("Du lieu sau khi sap xep:\n");
	HeapSort(a, n);
	PrintData(a, n);
	return 0;
}
