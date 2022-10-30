#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <utility>
#include <string>

using namespace std;


const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template <class ValType>
class TVector
{
protected:
  ValType* pVector;
  int Size;       
  int StartIndex;
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector& v);                
  ~TVector();                                
  int GetSize() { return Size; }   
  int GetStartIndex() { return StartIndex; }
  ValType& operator[](int pos);
  bool operator==(const TVector& v) const;
  bool operator!=(const TVector& v) const;
  TVector& operator=(const TVector& v);

  TVector  operator+(const ValType& val);
  TVector  operator-(const ValType& val);
  TVector  operator*(const ValType& val);

  TVector  operator+(const TVector& v);
  TVector  operator-(const TVector& v);
  ValType  operator*(const TVector& v);

  friend istream& operator>>(istream& in, TVector& v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }

  friend ostream& operator<<(ostream& out, const TVector& v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si)
{
  if ((s < 1) || (s > MAX_VECTOR_SIZE) || (si < 0) || (si > MAX_MATRIX_SIZE - 1))
    throw string("Wrong arguments");
  pVector = new ValType[s]{};
}

template <class ValType>
TVector<ValType>::TVector(const TVector<ValType>& v)
{
  Size = v.Size;
  StartIndex = v.StartIndex;
  pVector = new ValType[Size];
  for (int i = 0; i < Size; i++)
    pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::~TVector()
{
  delete[] pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int pos)
{
  pos -= StartIndex;
  if ((pos < 0) || (pos >= Size))
    throw string("Wrong argument");
  return pVector[pos];
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector& v) const
{
  if (this == &v)
    return true;
  if (Size != v.Size)
    return false;
  if (StartIndex != v.StartIndex)
    return false;
  for (int i = 0; i < Size; i++) {
    if (pVector[i] != v.pVector[i])
      return false;
  }
  return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector& v) const
{
  return !(*this == v);
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
  if (this == &v)
    return *this;
  if (Size != v.Size) {
    ValType* tmp = new ValType[v.Size];
    delete[] pVector;
    pVector = tmp;
    Size = v.Size;
  }
  StartIndex = v.StartIndex;
  for (int i = 0; i < Size; i++)
    pVector[i] = v.pVector[i];
  return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] + val;
  return out;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] - val;
  return out;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] * val;
  return out;

}

template <class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
  if ((Size != v.Size) || (StartIndex != v.StartIndex))
    throw string("Different size of TVector's");
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] + v.pVector[i];
  return out;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
  if ((Size != v.Size) || (StartIndex != v.StartIndex))
    throw string("Different size of TVector's");
  TVector<ValType> out(Size, StartIndex);
  for (int i = 0; i < Size; i++)
    out.pVector[i] = pVector[i] - v.pVector[i];
  return out;

}

template <class ValType>
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
  if ((Size != v.Size) || (StartIndex != v.StartIndex))
    throw string("Different size of TVector's");
  ValType sum = 0;
  for (int i = 0; i < Size; i++)
    sum += pVector[i] * v.pVector[i];
  return sum;
}

template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);
  TMatrix(const TMatrix& mt);
  TMatrix(const TVector<TVector<ValType> >& mt);
  bool operator==(const TMatrix& mt) const;
  bool operator!=(const TMatrix& mt) const;
  TMatrix& operator= (const TMatrix& mt);
  TMatrix  operator+ (const TMatrix& mt);
  TMatrix  operator- (const TMatrix& mt);

  friend istream& operator>>(istream& in, TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }

  friend ostream& operator<<(ostream& out, const TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s)
{
  if ((s < 1) || (s > MAX_MATRIX_SIZE))
    throw string("Wrong argument");
  for (int i = 0; i < s; i++) {
    TVector<ValType> tmp(s - i, i);
    this->pVector[i] = tmp;
  }
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
  TVector<TVector<ValType> >(mt) {}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
  TVector<TVector<ValType> >(mt) {}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
  return TVector<TVector<ValType>>:: operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
  return !(*this == mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
  if (this == &mt)
    return *this;
  TVector<ValType>* tmp = new TVector<ValType>[mt.Size];
  delete[] this->pVector;
  this->pVector = tmp;
  this->Size = mt.Size;
  for (int i = 0; i < this->Size; i++) {
    this->pVector[i] = mt.pVector[i];
  }
  return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
  return TVector<TVector<ValType>>:: operator+(mt);
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
  return TVector<TVector<ValType>>:: operator-(mt);
}

#endif