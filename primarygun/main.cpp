#include <iostream>
#include <fstream>
#include <map>

using namespace std;


void read(const char* filename,map<double,double> &range, map<double,double> &energy)
{
  ifstream in(filename);
  double x,y;
  while(1)
  {
    in>>x>>y;
    if(!in.good()) break;
    range.insert(pair<double,double>(x,y));
    energy.insert(pair<double,double>(y,x));
    
  }
  cout<<"Find out [ "<<range.size()<<" ] data in file "<<filename<<endl;
}

double FindRange(double energy,map<double,double> &range)
{
  map<double,double>::iterator irange;
  irange = range.lower_bound(energy);
  if(irange==range.begin()) return (irange->second)/(irange->first)*energy;
  double x1(0),y1(0),x2(0),y2(0);
  y2=irange->second;x2=irange->first;
  irange--;
  y1=irange->second;x1=irange->first;
  return (y2-y1)/(x2-x1)*(energy-x1)+y1;
  
}

double GetDepositedEnergy(double ener,double thickness, map<double,double> &range,map<double,double> &energy)
{
  double Range=FindRange(ener,range);
  if(Range<=thickness) return ener;
  double ResduleR=Range-thickness;
  double Energy=FindRange(ResduleR,energy);
  return ener-Energy;
}
int main()
{
  map<double,double> range,depositedE;
  read("12C-12C.txt",range,depositedE);
  cout<<FindRange(0.5,range)<<endl;
  cout<<FindRange(120,range)<<endl;
  cout<<FindRange(50,depositedE)<<endl;
  cout<<GetDepositedEnergy(100,50,range,depositedE)<<endl;
  map<double,double> *it=&range;
  cout<<it->begin()->first<<endl;
  return 0;
}
