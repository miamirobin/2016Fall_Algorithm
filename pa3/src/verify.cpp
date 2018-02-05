#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>

using namespace std;

class net
{
    public:
        net(){}
        net(int txs,int tys,int txt,int tyt){xs=txs;ys=tys;xt=txt;yt=tyt;}
        int xs;
        int ys;
        int xt;
        int yt;
        
        bool operator==(const net &rhs){return (xs==rhs.xs&&ys==rhs.xs&&xt==rhs.xt&&yt==rhs.yt);}
        bool checks(int txs,int tys){return xs==txs && ys==tys;}
        bool checkt(int txt,int tyt){return xt==txt && yt==tyt;}        
};  

class obstacle
{
	public:
		obstacle(){}
		obstacle(int _x1, int _y1, int _x2, int _y2){x1=_x1; y1=_y1; x2=_x2; y2=_y2;}
		int x1;
		int y1;
		int x2;
		int y2;	
};  

class route
{
    public:
        //left to right
        route(){}
        route(int x1,int y1,int x2,int y2);
        
        int x;
        int y;        
        bool linkup;//if false, go right
};  

class tile
{
    public:
        tile(){up=0;right=0;isObsUp=false;isObsRight=false;}
        int up;
        int right;
        bool isObsUp;
        bool isObsRight;
        
};      
  
class congestion
{
    public:
        void initialize(int horitiles, int vertitiles, vector<obstacle>& obslist);
        
        void registerroute(const route& troute ){temproute.push_back(troute);}
        
        void updatemapping();//dump temproute into mapping, called when the net's routing has no error
        void clearregister(){temproute.clear();}//clear mapping, called when the net's routing has error
        
        int calOverflow(int capacity);
        
    private:
        vector< vector<tile> > mapping;
        list<route> temproute;

};    

int main(int argc, char* argv[])
{
    ifstream casefile(argv[1]);
    ifstream routingfile(argv[2]);
    ofstream errorout("err.out");
    
    int horitiles;
    int vertitiles;
    int capacity;
    int nets;
    int obstacles;
    
        
    vector<net> netlist;
    vector<obstacle> obslist(0);
    vector<bool> routed;    
    congestion congestionmap;

    //parse input case
    {
        string skipstring;
        casefile>>skipstring>>horitiles>>vertitiles;
        casefile>>skipstring>>capacity;
        casefile>>skipstring>>skipstring>>nets;
        
        netlist.resize(nets);
        for(int i=0;i<nets;++i)
        {
            int netid;
            casefile>>netid;
            casefile>>netlist[i].xs>>netlist[i].ys>>netlist[i].xt>>netlist[i].yt;
        }
        
        //other initialization
        routed.assign(nets,false);
        congestionmap.initialize(horitiles,vertitiles, obslist);
    }        

    //parse routing result 
    int errorcount=0;
    int wirelength=0;
    while(1)
    {
        int netid;
        int routes;
        
        if( !(routingfile>>netid))
        {break;}
        
        net& nownet=netlist[netid];                
        
        if(!routed[netid])
        {routed[netid]=true;}
        else
        {errorout<<"net " << netid <<" routed more than once"<<endl;++errorcount;}
        
        routingfile>>routes;
        wirelength+=routes;
        
        if(routes==0)//has no routes
        {routed[netid]=false;}
        
        int prex,prey;
        int preerrorcount=errorcount;
        for(int i=0;i<routes;++i)
        {
            int x1,y1,x2,y2;
            routingfile>>x1>>y1>>x2>>y2;
            
            //check starting position
            if(i==0)
            {
                if(!nownet.checks(x1,y1))
                {errorout<<"net " << netid <<" starting position error"<<endl;++errorcount;}
                
                prex=x1;
                prey=y1;                
            }
            
            //check terminal position
            if(i==(routes-1))
            {
                if(!nownet.checkt(x2,y2))
                {errorout<<"net " << netid <<" ending position error"<<endl;++errorcount;}
            }

            //check disconnected
            if(prex!=x1 || prey!=y1)
            {errorout<<"net " << netid <<" disconnected between routes "<< i << " and " << i+1 <<endl;++errorcount;}

            //check invalid route
            if( !((x1==x2 && abs(y1-y2)==1) || (y1==y2 && abs(x1-x2)==1)))
            {errorout<<"net " << netid <<" route "<< i+1 << " is invalid (every route must be 1-tile step)"<<endl;++errorcount;}
            
            //check out of boundary
            if(x1<0 || x2<0 || y1<0 || y2<0 || x1>=horitiles || x2>=horitiles || y1>=vertitiles || y2>=vertitiles)
            {errorout<<"net " << netid <<" route "<< i+1 << " is invalid (out of boundary)"<<endl;++errorcount;}
            
            congestionmap.registerroute(route(x1,y1,x2,y2));
            
            //update for next iteration            
            prex=x2;
            prey=y2;                
        }
            
        if(preerrorcount<errorcount)
        {
            congestionmap.clearregister();
            wirelength-=routes;            
        }
        else
        {
            congestionmap.updatemapping();
        }
    }    

    //routed check
    for(int netid=0;netid<nets;++netid)    
    {
        if(!routed[netid])
        {errorout<<"net " << netid <<" is missing "<<endl;++errorcount;}
    }    

    int overflow=congestionmap.calOverflow(capacity);
    
        cout<<"overflow   : "<<overflow<<endl;
        cout<<"wirelength : "<<wirelength<<endl;    
        cout<<"error      : "<<errorcount<<endl;            

    return 0;
}    

route::route(int x1,int y1,int x2,int y2)
{
    if(x1==x2)
    {
        x=x1;
        y=min(y1,y2);
        linkup=true;
    }
    else
    {
        x=min(x1,x2);
        y=y1;
        linkup=false;
    }    
}    

void congestion::initialize(int horitiles, int vertitiles, vector<obstacle>& obslist)
{
    mapping.resize(horitiles);
    for(int i=0;i<horitiles;++i)
    {
        mapping[i].resize(vertitiles);
        
        for(int j=0; j<vertitiles; ++j)
        {
        	for(int o=0; o<(int)obslist.size(); ++o)
        	{
        		if((i>=obslist[o].x1)&&(i<=obslist[o].x2)&&(j>=obslist[o].y1)&&(j<=obslist[o].y2)){
        			if((j-1)>=0)
        				mapping[i][j-1].isObsUp=true;
        			if((i-1)>=0)
        				mapping[i-1][j].isObsRight=true;
        			mapping[i][j].isObsUp=true;
        			mapping[i][j].isObsRight=true;
        		}       		
        	}
        }
    } 
}    

//dump temproute into mapping, called when the net's routing has no error
void congestion::updatemapping()
{
    //list<route> temproute
    
    for(list<route>::iterator iter=temproute.begin();iter!=temproute.end();++iter)
    {
        if(iter->linkup)
        {++(mapping[iter->x][iter->y].up);}
        else
        {++(mapping[iter->x][iter->y].right);};        
    }    

    temproute.clear();
}    

int congestion::calOverflow(int capacity)
{
    int overflow=0;
    for(int i=0;i< static_cast<int>(mapping.size()); ++i)
    {
        for(int j=0; j< static_cast<int>(mapping[i].size()); ++j)
        {
        	int upcapacity=capacity;
        	int rightcapacity=capacity;
        	if(mapping[i][j].isObsUp)
        	{
        		upcapacity=0;
        	}
        	if(mapping[i][j].isObsRight)
        	{
        		rightcapacity=0;
        	}
            overflow+=max(0,mapping[i][j].up-upcapacity);
            overflow+=max(0,mapping[i][j].right-rightcapacity);            
        }    
    } 
    return overflow;
}    
