int main(){
    int m, n, c, d, A[10][10], B[10][10], ans[10][10]; 
    print("Enter the number of rows and columns of matrix");
    read(m);
    read(n);
    print("Enter the elements of A matrix");

    for (c = 0;c < m;c=c+1){
        for (d=0;d<n;d=d+1){
            read(A[c][d]);
        }
    }

    print("Enter the elements of B matrix");

    for (c = 0; c < m;c=c+1){
        for (d = 0 ;d < n;d=d+1){
            read(B[c][d]);
        }
    }

    print("ans of entered matrices     ");

    for (c = 0; c < m;c=c+1) {
        for (d = 0 ;d < n;d=d+1) {
            ans[c][d] = A[c][d] + B[c][d];
            print(ans[c][d]);
        }
    }
}