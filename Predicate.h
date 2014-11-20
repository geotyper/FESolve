
#ifndef PREDICATE_H
#define PREDICATE_H


namespace fesolv {

template<class T,class C> class Predicate
{
  public:
	bool operator()(T* t,C c) const
	{return t->GetNumber() == c;}
};

template<class T, class P, class D> inline T
find_if(T firstIter, T lastIter, P pred, D d)
{
    for (; firstIter != lastIter; ++firstIter)
    {
        if (pred(*firstIter, d))
			break;
    }
    return (firstIter);
}

} //end namespace

#endif