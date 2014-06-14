#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <cmath>


#include "node.h"
#include "vect.h"
#include "consts.h"

using namespace std;

inline double cubed(double a)
{
  return a*a*a;
}

double Etot;
int frame = 0;
int main()
{
  frame++;
  ofstream out;
  out.open("out.txt");
  ifstream in;
  in.open("in.txt");

  Body** bodies = new Body* [elements];
  for(int i = 0; i < elements; i++)
    {
      bodies[i] = new Body();
    }

  for(int i = 0; i < elements; i = i)
    {
      double in_x, in_y, in_m, in_vx, in_vy;
      while(in >> in_x >> in_y >> in_m)
	{
	  bodies[i]->r.x = in_x;
	  bodies[i]->r.y = in_y;
	  bodies[i]->m = in_m;
	  i++;
	}
    }
  
  Vect center;

  for(double t = 0; t < tmax; t += dt)
    {
      frame++;
      double size = Node::getSize(bodies, elements);
      Node* root = new Node(bodies, elements, size, center, 1);
      
      for(int i = 0; i < elements; i++)
	{
	  bodies[i]->F = root->CalcForce(bodies[i]);
	  bodies[i]->a = bodies[i]->F / bodies[i]->m;
	  bodies[i]->v += bodies[i]->a * dt;
	  bodies[i]->r += bodies[i]->v * dt;

	}

      if(frame % snapshot == 0)
	{
	  // for(int j = 0; j < elements; j++)
	  //	{
	  //	  out << bodies[j]->r.x << " " << bodies[j]->r.y << endl;
	  //	}
	  
	  for(int k = 0; k < elements; k++)
	    {
	      Etot += bodies[k]->m * (bodies[k]->v.Int() * bodies[k]->v.Int()) / 2;
	    }
	  out << t << "\t" << Etot << endl;
	  
	}

      delete root;
    }
  out.close();
  return 0;

}
