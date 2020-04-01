#include <iostream>
#include <vector>

class matrix
{   
    public:
    std::vector <std::vector <long long>> mat;
    matrix(std::vector <std::vector <long long>> x){
        mat=x;
    };
    matrix(){
    };
    //sets the matrix size to n by m
    matrix(int n,int m=0){
        this->mat.resize(n);
        for(int i=0;i<n;i++)this->mat[i].assign(m,0);
    };
    matrix add(matrix m1,matrix m2){
        matrix m3(m1.mat.size(),m1.mat[0].size());
        for(int i=0;i<m1.mat.size();i++){
            for(int j=0;j<m1.mat[0].size();j++){
                m3.mat[i][j]=m1.mat[i][j]+m2.mat[i][j];
            }
        }
        return m3;
    }
    matrix multiply(matrix m1,matrix m2,long long mod=1e9+7)
    {
        matrix m3(m1.mat.size(),m2.mat[0].size());
        for(int i=0;i<m1.mat.size();i++){
            for(int k=0;k<m2.mat[0].size();k++){
                for(int j=0;j<m1.mat[i].size();j++){
                    m3.mat[i][k]=(m3.mat[i][k]+m1.mat[i][j]*m2.mat[j][k])%mod;
                }
            }
        }
        return m3;
    }
    void show(){
        for(int i=0;i<mat.size();i++){
            for(int j=0;j<mat[0].size();j++)
            std::cout<<mat[i][j]<<" ";
            std::cout<<"\n";
        }
    }
};

class SquareMatrix:public matrix{
    public:
    std::vector <std::vector <long long>> Identity;
    SquareMatrix():matrix(){
    }
    SquareMatrix(int n):matrix(n,n){
        Identity.resize(n);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                Identity[i].push_back(i==j);
    }
    SquareMatrix(std::vector <std::vector <long long>> x):matrix(x){
        Identity=x;
        for(int i=0;i<x.size();i++)
            for(int j=0;j<x.size();j++)
                Identity[i][j]=(i==j);
    }
    matrix helper(long long power,long long mod=1e9+7){
        matrix X;
        if(power==0){
            X.mat=Identity;
            return X;
        }
        if((power&1)){
            X=helper((power>>1),mod);
            return multiply(multiply(X,X,mod),*this,mod);    
        }
        X=helper((power>>1),mod);
        return multiply(X,X,mod);
    }
    SquareMatrix ModExpo(long long power,long long mod=1e9+7){
        SquareMatrix ans(helper(power,mod).mat);
        return ans;
    }
};


int main(){
    SquareMatrix x(2);
    x.mat={{1,2},{3,4}};
    SquareMatrix y;
    y=x.ModExpo(10000000000000ll);
    y.show();
    return 0;
}