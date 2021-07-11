void combinationUtil(int arr[], int data[],  int start, int end,  int index, int r);  
  
void printCombination(int arr[], int n, int r)  {   
    int data[r];  
    combinationUtil(arr, data, 0, n-1, 0, r);  
}  
  
void combinationUtil(int arr[], int data[], int start, int end,  int index, int r)  {  
    if (index == r)  {  
        for (int j = 0; j < r; j=j+1){
            print(data[j]);
            print(" ");
        }
            print();  
        return;  
    }  
    for (int i = start; i <= end &&  end - i + 1 >= r - index; i=i+1)  {  
        data[index] = arr[i];  
        combinationUtil(arr, data, i+1,  end, index+1, r);  
    }  
}  
  
int main(){
    int n;
    read(n);
    int arr[n];
    int i;
    for(i=0;i<n;i=i+1){
        read(arr[i]);
    }  
    int r=1;
    for(r=1;r<n/2;r=r+1){
        printCombination(arr, n, r);
    }    
}