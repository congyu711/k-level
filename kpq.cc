// kinetic priority queue
//
// Yu Cong 2023-7-30
// This is an C++ implementation of the kinetic heap data structure described in Timothy M. Chan's paper 'Remarks on k-Level Algorithms in the Plane'
// https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.44.9042&rep=rep1&type=pdf
// section 2.2

#define RANGE_MAX 1e10
#include <cmath>
#include <unordered_set>
#include <boost/heap/binomial_heap.hpp>
namespace kpq
{
  using namespace std;

  typedef pair<double, double> point;
  class line
  {
    // y=ax-b
  public:
    double a, b;
    line(double _a, double _b) : a(_a), b(_b) {}
    double gety(double x)
    {
      return x * a - b;
    }
  };
  inline double getx(const line &_l1, const line &_l2)
  {
    if (fabs(_l1.a - _l2.a) < 1e-5)
      return RANGE_MAX;
    return (double)(_l1.b - _l2.b) / (_l1.a - _l2.a);
  }

  /////////////////////////////////////////////////
  // You will need a vector to store all lines. 
  // All functions of KPQ operates on indices of that vector.
  // e.g. `vector<line> lines;`
  /////////////////////////////////////////////////

  template <class type, class cmp>
  class trivialKPQ
  {
  public:
    vector<line> *lines;
    bool fin;             // finish--KPQ.advance() label
    unordered_set<int> S; // store indices of lines
    type t, nextT;
    int top, nextTop;
    // int _top();
    // type _getnextT();
    virtual void _advance();
    virtual void _insert(int);
    virtual void _delete(int);
    // maintain nextTop and nextT
    virtual void _maintain();
    bool compare(const int, const int);
    trivialKPQ(type _t) : t(_t), nextT(-1 * _t), top(-1), nextTop(-1), fin(false) {}
    trivialKPQ(vector<line> *p) : trivialKPQ(-RANGE_MAX) { lines = p; }
    trivialKPQ() : trivialKPQ(-RANGE_MAX) { lines = nullptr; }
  };
  template <class type, class cmp>
  void trivialKPQ<type, cmp>::_maintain()
  {
    int ntp = -1;
    type nt = RANGE_MAX;
    for (auto e : S)
    {
      if (e == top)
        continue;
      auto x = getx((*lines)[top], (*lines)[e]);
      if (x > t && x < nt)
      {
        nt = x, ntp = e;
      }
    }
    if (ntp != -1)
      nextT = nt, nextTop = ntp;
    else
      nextT = RANGE_MAX, nextTop = top;
  }
  template <class type, class cmp>
  void trivialKPQ<type, cmp>::_advance()
  {
    t = nextT;
    top = nextTop;
    // find nextT and nextTop
    // O(S.size)
    _maintain();
  }
  template <class type, class cmp>
  bool trivialKPQ<type, cmp>::compare(const int a, const int b)
  {
    if ((*lines)[a].gety(t + 1e-8) == (*lines)[b].gety(t + 1e-8))
      return cmp()((*lines)[a].a, (*lines)[b].a);
    return cmp()((*lines)[a].gety(t + 1e-8), (*lines)[b].gety(t + 1e-8));
  }
  template <class type, class cmp>
  void trivialKPQ<type, cmp>::_insert(int l)
  {
    S.insert(l);
    // change top
    if (S.size() < 2)
    {
      top = l;
      return;
    }
    if (compare(l, top))
      top = l;
    _maintain();
  }
  template <class type, class cmp>
  void trivialKPQ<type, cmp>::_delete(int l)
  {
    S.erase(l);
    nextT = RANGE_MAX;
    // change top
    if (top == l)
    {
      if (S.empty())
      {
        return;
      }
      top = *S.begin();
      for (auto e : S)
      {
        if (cmp()((*lines)[e].gety(t + 1e-8), (*lines)[top].gety(t + 1e-8)))
          top = e;
      }
    }
    if (S.size())
      _maintain();
  }

  template <class type, class cmp, class binomialHeap = boost::heap::binomial_heap<pair<type, int>, boost::heap::compare<std::greater<pair<type, int>>>>>
  class kineticPriorityQueue : public trivialKPQ<type, cmp>
  {
  public:
    binomialHeap pq;
    vector<typename binomialHeap::handle_type> pq_handlers;
    trivialKPQ<type, cmp> Q;
    vector<trivialKPQ<type, cmp> *> subKPQs;
    unordered_map<int, int> mp; // l is in subkpq No.mp[l]
    int r;                      // r=ceil(log n)
    void _maintain();
    void _advance();
    void _insert(int);
    void _delete(int);
    kineticPriorityQueue(int sz, vector<line> *p)
    {
      this->lines = p;
      r = ceil(log((double)sz));
      subKPQs.resize(r, nullptr);
      for (int i = 0; i < r; i++)
        pq_handlers.push_back(pq.push(make_pair(RANGE_MAX, i)));
      Q = trivialKPQ<type, cmp>(p);
      if (sz < 200)
      {
        for (int i = 0; i < r; i++)
        {
          subKPQs[i] = new trivialKPQ<type, cmp>(p);
        }
      }
      else
      {
        for (int i = 0; i < r; i++)
        {
          subKPQs[i] = new kineticPriorityQueue<type, cmp, binomialHeap>(ceil(1.0 * sz / r), p);
        }
      }
    }
  };

  template <class type, class cmp, class binomialHeap>
  void kineticPriorityQueue<type, cmp, binomialHeap>::_maintain()
  {
    this->top = Q.top;
    type nxt = pq.top().first;
    // if(min(Q.nextT,nxt)==this->nextT)   this->nextT=RANGE_MAX,this->nextTop=-1;
    this->nextT = min(Q.nextT, nxt);
  }
  template <class type, class cmp, class binomialHeap>
  void kineticPriorityQueue<type, cmp, binomialHeap>::_advance()
  {
    this->t = this->nextT;
    type nxt = pq.top().first;
    int p = pq.top().second;
    if (this->t == subKPQs[p]->nextT)
    {
      auto pmin = subKPQs[p]->top;
      subKPQs[p]->_advance();
      pq.update(pq_handlers[p], make_pair(subKPQs[p]->nextT, p));
      auto nextpmin = subKPQs[p]->top;
      if (pmin != nextpmin)
      {
        // Q.t=this->t;
        // Q._maintain();
        Q._delete(pmin);
        Q._insert(nextpmin);
        while (Q.nextT < this->t)
          Q._advance();
      }
    }
    else if (this->t == Q.nextT)
      Q._advance();
    _maintain();
  }
  template <class type, class cmp, class binomialHeap>
  void kineticPriorityQueue<type, cmp, binomialHeap>::_insert(int l)
  {
    this->S.insert(l);
    // find smallest |P.set|, this can be done faster
    // but O(r) still doesn't affect total complexity
    int p = -1, maxpsize = 0x07fffffff;
    for (int i = 0; i < r; i++)
    {
      if (maxpsize > subKPQs[i]->S.size())
      {
        maxpsize = subKPQs[i]->S.size();
        p = i;
      }
    }
    mp.insert(make_pair(l, p));
    if (subKPQs[p]->S.size())
      Q._delete(subKPQs[p]->top);
    subKPQs[p]->_insert(l);
    pq.update(pq_handlers[p], make_pair(subKPQs[p]->nextT, p));
    Q._insert(subKPQs[p]->top);
    _maintain();
  }
  template <class type, class cmp, class binomialHeap>
  void kineticPriorityQueue<type, cmp, binomialHeap>::_delete(int l)
  {
    this->S.erase(l);
    auto P = subKPQs[mp[l]];
    Q._delete(P->top);
    P->_delete(l);
    pq.update(pq_handlers[mp[l]], make_pair(P->nextT, mp[l]));
    mp.erase(l);
    Q._insert(P->top);
    _maintain();
  }
}