
//
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



int partition(vector<AlgString> &vec,int a,int b)
{
    int i = a-1;
    for(int j=a;j<b;j++){
        if(vec[j].m_string<vec[b].m_string || (vec[j].m_string==vec[b].m_string && vec[j].m_order<=vec[b].m_order)){
            i++;
            AlgString temp=vec[i];
            vec[i]=vec[j];
            vec[j]=temp;
        }
    }
    i++;
    AlgString tem=vec[i];
    vec[i]=vec[b];
    vec[b]=tem;
    return i;
}


void quicksort(vector<AlgString> &vec,int p,int r)
{
    if(p<r){
        int q = partition(vec,p,r);
        quicksort(vec,p,q-1);
        quicksort(vec,q+1,r);
    }
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
   //
    //string c[]={"gr","ggrewrewrwrwrwrw","ac"};
    //vector<string> b(c,c+3);
    
    
    
    
    extern vector<AlgString> lex_string_vector;
    int p=0,r=lex_string_vector.size()-1;
    
    quicksort(lex_string_vector,p,r);
    //getchar();
    outputfile(argv[2], u);

    cout<< u.QueryTotalStringCount()<<endl;
    for( int i = 0 ; i < u.QueryTotalStringCount() ; i++ ){
        //cout << u.QueryString(i) << " " << u.QueryOrder(i)<< endl;
    }
    // Display the accumulated time
    cout << "The execution spends " << t.End() << " seconds" << endl;
   
    return 1;
}
