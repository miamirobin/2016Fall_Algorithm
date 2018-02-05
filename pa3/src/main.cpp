//**************************************************************************
 //* File       [ main.cpp ]
 //* Author     [ yochi ]
// 李友岐
// * Usage      [ ./parser [inputfileName] ]
// * Date       [ 2017/1/19 created ]
//**************************************************************************/

#include "parser.h"
#include <iostream>     // std::cout
#include <cmath>        // std::abs
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
using namespace std;
int main(int argc, char **argv){
    if( argc < 2 ){ cout << "Usage: ./parser [input_file_name]" << endl; return 1; }

    AlgParser parser;

    // read the file in the first argument
    if( ! parser.read( argv[1] ) ) { return 1; }

    // show the information of the input
    //cout << "grid " << parser.gNumHTiles() << " " << parser.gNumVTiles() << endl;
    //cout << "capacity " << parser.gCapacity() << endl;
    //cout << "num net " << parser.gNumNets() << endl;
    for (int idNet = 0; idNet < parser.gNumNets(); ++idNet){
        pair<int, int> posS = parser.gNetStart( idNet );
        pair<int, int> posE = parser.gNetEnd( idNet );
        //cout << idNet << " " << posS.first << " " << posS.second << " "
                           //  << posE.first << " " << posE.second << endl;
    }
    int i=0;
    int **mm, *pData;
    int aa=parser.gNumHTiles();
    int bb=parser.gNumVTiles();
    mm = (int **)malloc(aa*bb*sizeof(int *)+aa*aa*bb*bb*sizeof(int));
    for (i = 0, pData = (int *)(mm+aa*bb); i < aa*bb; i++, pData += aa*bb){
        mm[i]=pData;
    }
    //int mm[parser.gNumHTiles()][parser.gNumVTiles()];
    
    for (int k=0;k<aa*bb;k++) {
        for (int j=0;j<aa*bb;j++){
            mm[k][j]=0;
        }
    }
    
    ofstream ofile(argv[2]);
    
    for (int idNet = 0; idNet < parser.gNumNets(); ++idNet){
        pair<int, int> posS = parser.gNetStart( idNet );
        pair<int, int> posE = parser.gNetEnd( idNet );
        int a=posE.first-posS.first;
        int b=posE.second-posS.second;
        
        int c1=abs(a);
        int d1=abs(b);
        int c=0;
        int d=0;
        if (c1>0){ c=a/abs(a);}
        if (d1>0){ d=b/abs(b);}
        int e1=posS.first;
        int e2=posS.second;
        int f1=e1+c;
        int f2=e2;
        int g1=posE.first;
        int g2=posE.second;
        ofile<<idNet<<" "<<c1+d1<<endl;
        //int q=0;
        //cout<<idNet<<" "<<c1+d1<<endl;
        while (e1!=g1 or e2!=g2){
            int cost1=mm[e2*aa+e1][e2*aa+e1+c];
            int cost2=mm[e2*aa+e1][(e2+d)*aa+e1];
            //int cost3=mm[e2*aa+e1][e2*aa+e1-c];
            //int cost4=mm[e2*aa+e1][(e2-d)*aa+e1];
            
            if (d1==0){
                f1=e1+c;
                f2=e2;
                mm[e2*aa+e1][e2*aa+e1+c]+=1;
                mm[e2*aa+e1+c][e2*aa+e1]+=1;
                c1-=1;
            }
            else if(c1==0){
                f1=e1 ;
                f2=e2+d;
                mm[e2*aa+e1][(e2+d)*aa+e1]+=1;
                mm[(e2+d)*aa+e1][e2*aa+e1]+=1;
                d1-=1;
            }
            else{
                if (cost1<cost2 or (cost1==cost2 and c1>=d1)){
                    f1=e1+c;
                    f2=e2;
                    mm[e2*aa+e1][e2*aa+e1+c]+=1;
                    mm[e2*aa+e1+c][e2*aa+e1]+=1;
                    c1-=1;
                }
                else{
                    f1=e1 ;
                    f2=e2+d;
                    mm[e2*aa+e1][(e2+d)*aa+e1]+=1;
                    mm[(e2+d)*aa+e1][e2*aa+e1]+=1;
                    d1-=1;
                }
            }
            
            ofile<<e1<<" "<<e2<<" "<<f1<<" "<<f2<<endl;
           
            e1=f1;
            e2=f2;
        }
            
    
    }
    ofile.close();
    return 0;
}

