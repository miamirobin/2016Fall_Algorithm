
//
//  Created by James Lee on 2016/10/9.
//  Copyright © 2016年 James Lee. All rights reserved.
#include <algorithm>
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

void insertsort(vector<AlgString> &vec){
    for (int i=1;i<(int)vec.size();i++){
        cerr << '\r' << fixed << setprecision(2) << (double)(((double)(i+1))/vec.size())*100.0 << "%";
        AlgString Str = vec[i];
        for (int j=i-1;j>=0;j--){
            if (vec[j].m_string>Str.m_string){
                
                vec[j+1]=vec[j];
                if (j==0){
                    vec[j]=Str;
                }
                
            }
            else{
                vec[j+1]=Str;
                break;
            }
        }
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
   
    
    
    
    
    extern vector<AlgString> lex_string_vector;
    insertsort(lex_string_vector);
    
    outputfile(argv[2], u);

    cout<<endl<< u.QueryTotalStringCount()<<endl;
       for( int i = 0 ; i < u.QueryTotalStringCount() ; i++ ){
           //cout << u.QueryString(i) << " " << u.QueryOrder(i)<< endl;
       }
    // Display the accumulated time
    cout << "The execution spends " << t.End() << " seconds" << endl;
   
    return 1;
}
