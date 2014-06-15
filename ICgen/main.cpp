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

  for(int i = 0; i < 5; i++)
    {
      double x = rand() / 1E5 - 0.5 * 1e3;
      double y = rand() / 1E5 - 0.5 * 1e3;
      double vx = rand() / 1e7 - 0.5 * 1e2;
      double vy = rand() / 1e7 - 0.5 * 1e2;
      outp << x << "\t" << y << "\t" << vx << "\t" << vy << "\t" << 1000000 << endl;
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
