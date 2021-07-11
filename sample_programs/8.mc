void merge(int arr[], int l, int m, int r) { 
    int i, j, k; 
    int temp[r-l+1];
    i = l;
    j = m+1; 
    k = 0;
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            temp[k] = L[i]; 
            i=i+1; 
        } 
        else{ 
            temp[k] = R[j]; 
            j=j+1; 
        } 
        k=k+1; 
    } 
 
    while (i < n1) { 
        temp[k] = L[i]; 
        i=i+1; 
        k=k+1; 
    } 
    while (j < n2) { 
        temp[k] = R[j]; 
        j=j+1; 
        k=k+1; 
    } 
    for(i=l;i<r;i+=1){
        arr[i]=temp[i-l];
    }
} 
void mergeSort(int arr[], int l, int r) { 
    if (l < r) { 
        int m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
} 

int main(){
    read(n);
    int a[n];
    for(i=0;i<n;i=i+1){
        read(a[i]);
    }

    mergeSort(arr, 0, arr_size - 1); 
    for(i=0;i<n;i=i+1){
            print(a[i]);
            print(" ");
    }
    return 0; 
}