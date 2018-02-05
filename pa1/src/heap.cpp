
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
class Heap{
    public:
    Heap();
    Heap(size_t size){
        heap.reserve(size);
    }
    
    void insert(AlgString node){
        heap.push_back(node);
        heapifyup(heap.size()-1);
    }
    
    AlgString pop(){
        AlgString algStr = heap[0];
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        heapifydown(0);
        return algStr;
    }
    
    protected:
    void heapifydown(size_t node){
        size_t left = (node+1)*2-1, right = (node+1)*2, min;
        
        if(left >= heap.size()) return;
        else if(right >= heap.size()) min = left;
        else min = (heap[left].m_string < heap[right].m_string) ? left : right;
        
        if(heap[min].m_string < heap[node].m_string){
            AlgString algStr = heap[node];
            heap[node] = heap[min];
            heap[min]  = algStr;
            heapifydown(min);
        }
    }
    
    void heapifyup(size_t node){
        size_t parent = ((node+1)/2)-1;
        if(node != 0 && heap[parent].m_string > heap[node].m_string){
            AlgString algStr = heap[node];
            heap[node] = heap[parent];
            heap[parent] = algStr;
            heapifyup(parent);
        }else{
            heapifydown(node);
        }
    }
    
    private:
    vector<AlgString> heap;
    
};

void heapsort(vector<AlgString>& array){
    Heap heap(array.size());
    for(size_t i = 0; i < array.size(); ++i){
        cerr << '\r' << fixed << setprecision(2) << (double)(((double)i)/((double) array.size()))*50.0 << "%";
        heap.insert(array[i]);
    }
    for(size_t i = 0; i < array.size(); ++i){
        cerr << '\r' << fixed << setprecision(2) << (double)(((double)i)/((double) array.size()))*50.0+50.0 << "%";
        array[i] = heap.pop();
    }
    cerr << endl;
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
    
    
    
    
    extern vector<AlgString> lex_string_vector;
    
    int r=u.QueryTotalStringCount();
    //build_max_heap(lex_string_vector,r);
    heapsort(lex_string_vector);
    
    outputfile(argv[2], u);
    cout<<u.QueryTotalStringCount()<<endl;
    
    // Display the accumulated time
    cout << "The execution spends " << t.End() << " seconds" << endl;
   
    return 1;
}
