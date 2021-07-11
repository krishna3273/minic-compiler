int main(){
    int n;
    bool flag=false;
    read(n);
    for(int i=2;i*i<=n;i=i+1){
        if( n % i == 0 ){
            flag=1;
            print("Not a prime");
        }
    }
    if(flag==false){
        print("Yes it is a prime");
    }
    return 0;
}