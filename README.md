
```
PROCEDURE MAIN() 
BEGIN 
	
	PRINT_LINE “Dizinin eleman sayisini giriniz” 
	GET_VAL “$n_i” 
	
	PRINT_LINE “Dizinin elemanlarini giriniz” 
	
	FOR k_i <- 0..n_i LOOP 
	BEGIN 
		GET_VAL “$arr_i[k_i]” 
	END  
	
	max_i <- 0 
	maxind_i <- -1 
	
	FOR k_i <- 0..n_i LOOP 
	BEGIN 
		IF (arr_i[k_i] > max_i) THEN 
		BEGIN 
		max_i <- arr_i[k_i] 
		maxind_i <- k_i 
		END 
	END 

	PRINT_LINE “Dizinin en buyuk elemani $max_i, $maxind_i. indiste bulunmaktadir.” 

END

```



```c
#include<stdio.h>

void main(){
	int k, n, max=0, maxind=-1, arr[100];
	
	printf(“Dizinin eleman sayisini giriniz \n”);
	
	scanf(“%d”, &n);
	printf(“Dizinin elemanlarini giriniz \n”);
	
	for (k=0; k<n; k++) 
		scanf(“%d”, &arr[k]);
	
	for (k=0; k<n; k++){
		if(arr[k] > max){
			max=arr[k];
			maxind=k;
		}
	}

	printf(“Dizinin en buyuk elemani %d, %d. indiste bulunmaktadir.\n”, max, maxind);
}
```