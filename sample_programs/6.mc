void insertionSort(int arr[], int n)  {  
    int i, key, j;  
    for (i = 1;i < n;i=i+1) {  
        key = arr[i];  
        j = i - 1;  
        while (j >= 0 && arr[j] > key) {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }
        arr[j + 1] = key;  
    }  
}  
int main(){
    int i,n;
    read(n); 
    int arr[n];
    for(i=0;i<n;i=i+1){
        read(arr[i]);
    }
    insertionSort(arr, n);  
    for (i = 0; i < n; i=i+1){  
        print(arr[i]); 
    }
    return 0; 
}
