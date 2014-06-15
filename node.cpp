#include "node.h"
#include <stdlib.h>
#include "vect.h"
#include "consts.h"

inline double cube(double a)
{
  return a*a*a;
}

Node::Node(Body** bodies, int listLength, double nodeSize, Vect nodeCent, bool _isRoot)
{
  isRoot = _isRoot;
  _cent = nodeCent;
  _bodies = bodies;
  size = nodeSize;
  _m = 0;
  isLeaf = 0;

  _ne = NULL;
  _se = NULL;
  _sw = NULL;
  _nw = NULL;

  if(listLength != 1)
    {
      int neCounter, nwCounter, seCounter, swCounter;
      neCounter = nwCounter = seCounter = swCounter = 0;

      //prvi prolaz
      for(int i = 0; i < listLength; i++)
	{
	  if(bodies[i]->r.x > _cent.x)
	    {
	      if(bodies[i]->r.y > _cent.y)
		{
		  neCounter++;
		}
	      else
		{
		  seCounter++;
		}
	    }
	  else
	    {
	      if(bodies[i]->r.y > _cent.y)
		{
		  nwCounter++;
		}
	      else
		{
		  swCounter++;
		}
	    }
	  _m += bodies[i]->m;
	  _mCent += bodies[i]->r * bodies[i]->m;
	}
      Body** neBodies = new Body*[neCounter];
      Body** nwBodies = new Body*[nwCounter];
      Body** seBodies = new Body*[seCounter];
      Body** swBodies = new Body*[swCounter];
      //prvi prolaz
      _mCent /= _m;
      //drugi prolaz
      neCounter = nwCounter = seCounter = swCounter = 0;

      for(int i = 0; i < listLength; i++)
	{
	  if(bodies[i]->r.x > _cent.x)
	    {
	      if(bodies[i]->r.y > _cent.y)
		{
		  neBodies[neCounter] = bodies[i];
		  neCounter++;
		}
	      else
		{
		  seBodies[seCounter] = bodies[i];
		  seCounter++;
		}
	    }
	  else
	    {
	      if(bodies[i]->r.y > _cent.y)
		{
		  nwBodies[nwCounter] = bodies[i];
		  nwCounter++;
		}
	      else
		{
		  swBodies[swCounter] = bodies[i];
		  swCounter++;
		}
	    }
	}
      //drugi prolaz end

      Vect neCent, nwCent, seCent, swCent;

      neCent.x = _cent.x + nodeSize/2;
      neCent.y = _cent.y + nodeSize/2;

      nwCent.x = _cent.x - nodeSize/2;
      nwCent.y = _cent.y + nodeSize/2;

      seCent.x = _cent.x + nodeSize/2;
      seCent.y = _cent.y - nodeSize/2;

      swCent.x = _cent.x - nodeSize/2;
      swCent.y = _cent.y - nodeSize/2;
      
      //    cout << neCounter << " " << nwCounter << " " << seCounter << " " << swCounter << endl;
      
      if(neCounter != 0)
	_ne = new Node(neBodies, neCounter, nodeSize/2, neCent, 0);
      if(nwCounter != 0)
	_nw = new Node(nwBodies, nwCounter, nodeSize/2, nwCent, 0);
      if(seCounter != 0)
	_se = new Node(seBodies, seCounter, nodeSize/2, seCent, 0);
      if(swCounter != 0)
	_sw = new Node(swBodies, swCounter, nodeSize/2, swCent, 0);
      
      
    }
  else
    {
      _ne = NULL;
      _nw = NULL;
      _se = NULL;
      _sw = NULL;
      
      isLeaf = 1;

      _m = _bodies[0]->m;
      _mCent = bodies[0]->r;
      bodies[0]->myNode = this;
    }
}

Vect Node::DistanceFromNode(Body* _body)
{
  Vect dist = _body->r - _mCent;
  return dist;
}

Vect Node::CalcForce(Body* body)
{
  Vect Force;
  Force.x = 0;
  Force.y = 0;
  if(body->myNode == this)
  return Force;
  Vect VectDist = DistanceFromNode(body);
  double dist = VectDist.Int();

  if(dist / this->size > theta || isLeaf)
    {
      Force = VectDist * (-G * (body->m * this->_m) / cube(dist+eta));
    }
  else
    {
      Vect neForce, nwForce, seForce, swForce;
      if(_ne != NULL)
	neForce = _ne->CalcForce(body);
      if(_nw != NULL)
	nwForce = _nw->CalcForce(body);
      if(_se != NULL)
	seForce = _se->CalcForce(body);
      if(_sw != NULL)
	swForce = _sw->CalcForce(body);

      Force = neForce + nwForce + seForce + seForce;
    }
  return Force;
}
