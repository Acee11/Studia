#pragma once

template<typename T>
class MySmartPtr
{
public:
    MySmartPtr(T* objectToManage);
    ~MySmartPtr();
    T& operator* ();
    T* operator->();
};

template<typename T>
MySmartPtr<T>::MySmartPtr(T *objectToManage)
{
    //implement me!
}

template<typename T>
MySmartPtr<T>::~MySmartPtr()
{
    //implement me!
}

template<typename T>
T* MySmartPtr<T>::operator->()
{
     //implement me!
}

template<typename T>
T& MySmartPtr<T>::operator*()
{
      //implement me!
}
