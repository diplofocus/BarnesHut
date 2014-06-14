#ifndef __CLASSES_H__
#define __CLASSES_H__

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "vect.h"

class Node;

class Body
{
 public:
  Vect r,v,a,F;
  double m;
  Node* myNode;

  Body(){}

  Body(Vect _r, Vect _v, double _m)
  {
    r = _r;
    v = _v;
    m = _m;
  }
  ~Body();
};

class Node
{
 public:
  double _m;//done
  Vect _mCent;//done
  Vect _cent;//done
  double size; //done

  Vect CalcForce(Body* body);
  Vect DistanceFromNode(Body* _body);

  Node* _ne;
  Node* _nw;
  Node* _se;
  Node* _sw;
  Body** _bodies;

  //  int _count;

  bool isRoot;
  bool isLeaf;


 public:
  static double getSize(Body** bodies, int listLength)
  {
    if (bodies == NULL) { return 0; }

    double sizemax = 0;
    for (int i = 0; i < listLength; i++)
      {
	if(abs(bodies[i]->r.x) > sizemax)
	  sizemax = abs(bodies[i]->r.x);
	if(abs(bodies[i]->r.y) > sizemax)
	  sizemax = abs(bodies[i]->r.y);
      }
    //added abs to return
    return abs(sizemax);
  }

  ~Node()
    {
      if (_nw != NULL) delete _nw;
      if (_ne != NULL) delete _ne;
      if (_se != NULL) delete _se;
      if (_sw != NULL) delete _sw;
      if (_bodies != NULL && !isRoot) delete [] _bodies;
    }

  Node(Body** bodies,int listLength, double nodeSize, Vect nodeCent, bool _isRoot);

int BHcount()
{
  int num = 1;
  if(_ne != NULL)
    {
      num+=_ne->BHcount();
    }
  if(_nw != NULL)
    {
      num+=_nw->BHcount();
    }
  if(_se != NULL)
    {
      num+=_se->BHcount();
    }
  if(_sw != NULL)
    {
      num+=_sw->BHcount();
    }
  return num;
}
};

#endif
