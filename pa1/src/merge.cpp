//  Created by James Lee on 2016/10/9.
//  Copyright © 2016年 James Lee. All rights reserved.
//
#include <cstdio>
#include <iostream>
#include "parser.h"
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
void outputfile(const string& ofileName, AlgParser& u){
    ofstream ofile(ofileName.c_str());
    ofile << u.QueryTotalStringCount() << endl;
    for(int j = 0; j < u.QueryTotalStringCount(); j++){
        ofile << u.QueryString(j) << " " << u.QueryOrder(j) << endl;
    }
    ofile.close();
}

void merge(vector<AlgString> &vec,int p,int q,int r)
{
    int n1=q-p+1;
    int   n2=r-q;
    vector<AlgString> L(n1+1);
    vector<AlgString> R(n2+1);
    for (int i=0;i<n1;i++){L[i]=vec[p+i-1];}
    for (int i=0;i<n2;i++){R[i]=vec[q+i];}
    //cout<<R[0]<<endl;
    L[n1].m_string="zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    R[n2].m_string="zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    
    

    int i=0,j=0;
    for (int k=p-1;k<r;k++){
        
        if (L[i].m_string<R[j].m_string){vec[k]=L[i];i+=1;}
        else if (L[i].m_string==R[j].m_string){
            if(L[j].m_order<R[j].m_order){vec[k]=L[i];i+=1;}
            else{vec[k]=R[j];j+=1;}
        }
        else{vec[k]=R[j];j+=1;}
    }
}
void mergesort(vector<AlgString> &vec,int p,int r){
    if (p<r){
        int q=(p+r)/2;
    
        mergesort(vec,p,q);
        mergesort(vec, q+1,r);
        merge(vec,p,q,r);}
    
}
int main( int argc, char** argv )
{
    // Declare the functional objects
    AlgParser u;
    AlgTimer t;
    // Pass the arguement 1 as the input file name
    u.Parse( argv[1] );
    // Start timer
    t.Begin();
    // Display all strings and word numbers
    
    
    
    extern vector<AlgString> lex_string_vector;
    int p=1,r=lex_string_vector.size();
    mergesort(lex_string_vector,p,r);
    //getchar() ;
    outputfile(argv[2], u);

    cout<< u.QueryTotalStringCount()<<endl;
       for( int i = 0 ; i < u.QueryTotalStringCount() ; i++ ){
         //cout << u.QueryString(i) << " " << u.QueryOrder(i)<< endl;
           
       }
    // Display the accumulated time
    cout << "The execution spends " << t.End() << " seconds" << endl;
   
    return 1;
}
