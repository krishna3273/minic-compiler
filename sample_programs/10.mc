int main(){
    int m, n, p, q, k, sum = 0;

    print("Enter number of rows and columns of A matrix");
    read( m);
    read(n);
    print("Enter elements of A matrix");
    int A[m][n];
    for (int c = 0;c < m ;c=c+1){
        for (int d = 0;d < n ;d=d+1){
            read(A[c][d]);
        }
    }

    print("Enter number of rows and columns of B matrix");
    read( p, q);


    if(n != p){
        print("The matrices can't be multiplied with each other.");
    }
    else{
        int B[p][q];
        print("Enter elements of B matrix");
        for (int c = 0;c < p ;c=c+1){
            for (int d = 0;d < q ;d=d+1){
                read(B[c][d]);
            }
        }

        int  ans[m][q];
        for (int c = 0;c < m;c=c+1 ) {
            for (int d = 0; d < q ;d=d+1) {
                for (k = 0; k < p; k=k+1) {
                    sum = sum + A[c][k]*B[k][d];
                }
            ans[c][d] = sum;
            sum = 0;
            }
        }

        print("Product of the matrices:");

        for (int c = 0;c < m;c=c+1 ) {
            for (int d = 0;d < q;d=d+1 ){
                print( ans[c][d]);
            }
        }
    }
    return 0;
}