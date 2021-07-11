int main(){
    int n;
    read(n);
    for(int k=2;k<=n;k=k+1){
        bool flag=false;
        for(int i=2;i*i<=k;i=i+1){
            if(k%i==0){flag=true;break;}
        }
        if(flag==false){ans=ans+k;}
    }
}