#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H
#include <iostream>
#include <vector>
#include <functional>


template<class T>

class SegmentTree{

public:
  
	SegmentTree(std::vector<T> data, T value, function<T( T , T )> builder );
	
   void update(T p, T value);

	T query(int l, int r, function<T( T , T )> builder ,int value);

private:

	T *tree;

	void BuildTree(std::vector<T>data,function<T( T , T )> builder );

   int N;
};


template<class T> SegmentTree<T>::SegmentTree(std::vector<T> data,
                                                T value,function<T(T,T)>builder)
{
   BuildTree(data,builder);
}


template<class T> void SegmentTree<T>::BuildTree(std::vector<T> data, function<T( T , T )> builder )
{

   int n = data.size();
   N=n;
   tree = new T[(2*n)+1];
   
   for( int i=0;i<n;i++)
   {
   		tree[i+n]=data[i];
   }

   for(int i=n-1;i>0;i--)
   {
       tree[i] = builder( tree[ i<<1 ] , tree[ i<<1|1 ] );
   }

}

template<class T> T SegmentTree<T>::query(int l,int r,function<T( T , T )> builder,int value)
{
		int res = value;
  		for (l += N, r += N; l < r; l >>= 1, r >>= 1)
  	{
    	if (l&1) res = builder(tree[l++],res);
    	if (r&1) res = builder(tree[--r],res);
  	}
  return res;

}

template<class T> void SegmentTree<T>::update( T p, T value )
{
   for (tree[p += N] = value; p > 1; p=p>>1) tree[p>>1] = tree[p] + tree[p^1];
}

#endif // SEGMENTTREE_H

