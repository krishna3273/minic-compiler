int main(){
    int limit=100000000; 
    read(limit); 
    int x, y, z = 0; 
    int m = 2;
    while (z < limit) { 
        for (int n = 1;n<m;n=n+1) { 
            x = m * m - n * n; 
            y = 2 * m * n; 
            z = m * m + n * n; 
            if (z > limit){
                break; 
            }
            print(x, y, z); 
        } 
        m=m+1; 
    }
}