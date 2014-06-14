#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

int proxy;

int main()
{

  ofstream outp;
  outp.open("in.txt");

  for(int i = 0; i < 500; i++)
    {
      double x = rand();
      double y = rand();
      outp << x << "\t" << y << "\t" << 100000 << endl;
    }
  outp.close();

  ifstream in;
  in.open("in.txt");
  double a,b,c;
  while(in >> a >> b >> c)
    {
      cout << a << "\t" << b << "\t" << c << endl;
    }

  return 0;
}
