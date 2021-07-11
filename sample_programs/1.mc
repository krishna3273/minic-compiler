int main(){
    int n,k;
    int ans=0;
    read(n);
    read(k);
    for(int i=1;i<=n;i=i+1){
        int temp=1;
        for(int j=0;j<k;j=j+1){
            temp=temp*i;
        }
        ans=ans+temp;
    }
    print(ans);
    return 0;
}