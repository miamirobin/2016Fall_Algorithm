//  李友岐 2016
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <vector>
using namespace std;

void outputfile(const string& ofileName,int yy,vector<int> &count,int n,int num[],int ol);
void go(int s[],int q,int w,int x,int y,int num[],int n,vector<int> &count);


int main( int argc, char** argv )
{   int n=0;
    fstream fin;
    fin.open(argv[1],ios::in);
    char line[100];
    while(fin.getline(line,sizeof(line),'\n')){
       n+=1;
    }
    fin.close();
    
    ifstream ffin(argv[1]);
    int num[n-1][2];
    ffin >> num[n-2][0];
    for(int i=0;i<n-2;i++){
        for(int k=0;k<2;k++){
            ffin >> num[i][k];
        }
    }
    ffin.close();

    int yy=num[n-2][0];
    
    int i;
    int **m,**s, *pData;
    m = (int **)malloc(yy*sizeof(int *)+yy*yy*sizeof(int));
    s = (int **)malloc(yy*sizeof(int *)+yy*yy*sizeof(int));
    for (i = 0, pData = (int *)(m+yy); i < yy; i++, pData += yy){
        m[i]=pData;
    }
    for (i = 0, pData = (int *)(s+yy); i < yy; i++, pData += yy){
        s[i]=pData;
    }

    
    for (int i=0;i<yy;i++){
        m[i][i]=0;
    }
    for (int l=2;l<yy+1;l++){
        for (int i=0;i<yy+1-l;i++){
            int j=i+l-1;
            m[i][j]=0;
            for (int k=i;k<j;k++){
                int q=m[i][k]+m[k+1][j];
                for (int p=0;p<n-2;p++){
                    if (((num[p][0]==i) && (num[p][1]==j))||((num[p][0]==j) && (num[p][1]==i) )){
                        q+=1;
                    }
                }
                
                if (q>m[i][j]){
                    m[i][j]=q;
                    s[i][j]=k;
                }
          
            }
        }
    }
    cout<<m[0][yy-1]<<endl;
    int ol=m[0][yy-1];
    free(m);
    vector<int> count;
    for (int i=0;i<yy;i++){
        count.push_back(yy);
    }
    go(s[0],yy,yy,0,yy-1,num[0],n,count);
    outputfile(argv[2],yy,count,n,num[0],ol);
    cout << (double)clock() / CLOCKS_PER_SEC << " S"<<endl;
    return 0;
}


void go(int s[],int q,int w,int x,int y,int num[],int n,vector<int> &count)
{
    

    int e=s[x*w+y];
    int r=e+1;
    
    for (int p=0;p<n-2;p++){
        if (((num[p*2+0]==x) && (num[p*2+1]==y))||((num[p*2+0]==y) && (num[p*2+1]==x) )){
            count[num[p*2+0]]=1;
        }
    }
    
    if (y>e &&e>x){
        go(s,q,w,x,e,num, n,count);
    }
    if (x<r && r<y){
        go(s,q,w,r,y,num ,n,count);
    }
}
void outputfile(const string& ofileName,int yy,vector<int> &count,int n,int num[],int ol)
{
    ofstream ofile(ofileName.c_str());
    ofile<<ol<<endl;
    for (int i=0;i<yy;i++){
        if (count[i]==1){
            for (int p=0;p<n-2;p++){
                if (num[p*2+0]==i){
                    cout<<num[p*2+0]<<" "<<num[p*2+1]<<endl;
                    ofile<<num[p*2+0]<<" "<<num[p*2+1]<<endl;
                    break;
                }
            }
        }
    }
    ofile.close();
}
