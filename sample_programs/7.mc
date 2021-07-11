  
int getMax(int arr[], int n) { 
    int mx = arr[0]; 
    for (int i = 1;i < n;i=i+1) {
        if(arr[i] > mx) {
            mx = arr[i];
        }
    }
    return mx; 
} 
  
void countSort(int arr[], int n, int exp) { 
    int output[n];
    int i, count[10];
    for(i=0;i<10;i=i+1){
        count[i]=0;
    } 
    for (i = 0;i < n ;i=i+1) {
        count[ (arr[i]/exp)%10 ]+=1;
    }
  
    for (i = 1;i < 10;i=i+1){
        count[i] += count[i - 1];
    }
  
    for (i = n - 1; i >= 0;i=i+1) { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]-=1; 
    } 
  
    for (i = 0;i < n;i=i+1) {
        arr[i] = output[i];
    } 
} 
 
void radixsort(int arr[], int n) { 
    int m = getMax(arr, n); 
    for (int exp = 1;m/exp > 0; exp *= 10;){
        countSort(arr, n, exp);
    }
} 

int main(){
    read(n);
    int a[n];
    for(i=0;i<n;i=i+1){
        read(a[i]);
    }
    radixsort(arr, n); 
    for (int i = 0;i < n;i=i+1){
        print(arr[i]);
    } 
    return 0;
}