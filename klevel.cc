// k-level
//
// Yu Cong 2023-7-30
// This is a C++ implementation of the k-level algorithm described
// in Timothy M. Chan's paper 'Remarks on k-Level Algorithms in the Plane'
// https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.44.9042&rep=rep1&type=pdf
// section 2.2

#include "kpq.cc"
namespace klevel
{
  using namespace std;
  using namespace kpq;

  /// @brief this function computes (top) k-level of a set of lines
  /// @param k k for k-level
  /// @param lines ptr to the set of lines
  /// @return a vector of lines on klevel
  template<typename T>
  vector<int> klevel(int k, vector<line<T>> *lines)
  {
    vector<int> res;
    kineticPriorityQueue<T, less<T>> upper(k, lines);
    kineticPriorityQueue<T, greater<T>> lower(lines->size() - k, lines);
    auto t = -RANGE_MAX;
    // find k-level for the initial t and init upper&lower
    // can be done in O(n)
    // TODO: O(n) initialization
    vector<int> idxs(lines->size());
    for (int i = 0; i < idxs.size(); i++)
      idxs[i] = i;
    sort(idxs.begin(), idxs.end(), [&](int a, int b)
         { return (*lines)[a].gety(t) > (*lines)[b].gety(t); });
    for (int i = 0; i < k; i++)
      upper._insert(idxs[i]);
    for (int i = k; i < idxs.size(); i++)
      lower._insert(idxs[i]);
    auto pushback = [&]() -> void
    {   if(res.empty()||res.end()[-1]!=upper.top) 
        res.push_back(upper.top);
    };
    pushback();
    while (1)
    {
      T t0 = getx((*lines)[upper.top], (*lines)[lower.top]);
      if (t0 < t)
        t0 = RANGE_MAX;
      t = min({upper.nextT, lower.nextT, t0});
      if (t == RANGE_MAX)
        break;
      if (t == t0)
      {
        int uppermin = upper.top, lowermax = lower.top;

        upper._insert(lowermax);
        while (upper.t < t0)
          upper._advance();
        upper._delete(uppermin);
        while (upper.nextT < t0)
          upper._advance();
        lower._insert(uppermin);
        while (lower.t < t0)
          lower._advance();
        lower._delete(lowermax);
        while (lower.nextT < t0)
          lower._advance();
        pushback();
        t+=1e-10;
        if (min(upper.nextT, lower.nextT) == RANGE_MAX)
          break;
      }
      else if (t == upper.nextT)
      {
        upper._advance();
        pushback();
      }
      else
        lower._advance();
    }
    return res;
  }
}