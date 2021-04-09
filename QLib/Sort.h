#ifndef _SORT_H_
#define _SORT_H_

#include "Object.h"

namespace QLib
{

template <typename T>
class Sort : public Object
{
private:
    Sort();
    Sort(const Sort &);
    Sort & operator = (const Sort &);
private:
    static void swap(T & a , T & b);
    static int partition(T array[], int begin, int end, bool min2max);
    static void quickSort(T array[], int begin, int end, bool min2max);
public:
    static void selectSort(T array[], int len, bool min2max = true);
    static void insertSort(T array[], int len, bool min2max = true);
    static void bubbleSort(T array[], int len, bool min2max = true);
    static void quickSort(T array[], int len, bool min2max = true);
};

template <typename T>
void Sort<T>::swap(T & a , T & b)
{
    T temp = a; 
    a = b; 
    b = temp;
}

template <typename T>
int Sort<T>::partition(T array[], int begin, int end, bool min2max)
{
    T pv = array[begin];
    
    while(begin < end)
    {
        while((begin < end) && (min2max ? (array[end] > pv) : (array[end] < pv)))
        {
            end--;
        }
        swap(array[begin], array[end]);
        while((begin < end) && (min2max ? (array[begin] <= pv) : (array[begin] > pv)))
        {
            begin++;
        }
        swap(array[begin], array[end]);
    }

    array[begin] = pv;
    return begin;
}

template <typename T>
void  Sort<T>::selectSort(T array[], int len, bool min2max)
{
    for(int i = 0; i < len; i++)
    {
        int k = i;
        for(int j = i+1; j < len; j++)
        {
            if(min2max? (array[k] > array[j]) : (array[k]<array[j]))
            {
                k = j;
            }
        }
        if(k != i)
        {
            swap(array[i], array[k]);
        }
    }
}

template <typename T>
void Sort<T>::insertSort(T array[], int len, bool min2max)
{
    for(int i = 1; i < len; i++)
    {
        int k = i;
        T e = array[i];
        for(int j = i - 1; (j >= 0) && (min2max ? array[j] > e : array[j] < e); j--)
        {
            array[j+1] = array[j];
            k = j;
        }
        if(k != i)
        {
            array[k] = e;
        }
    }
}

template <typename T>
void Sort<T>::bubbleSort(T array[], int len, bool min2max)
{
    bool exchange = true;

    for(int i = 0; (i < len) && exchange; i++)
    {
        exchange = false;
        for(int j = len -1; j > i; j--)
        {
            if(min2max ? (array[j] < array[j-1]) : (array[j] > array[j-1]))
            {
                swap(array[j], array[j - 1]);
                exchange = true;
            }
        }
    }

}

template <typename T>
void Sort<T>::quickSort(T array[], int begin, int end, bool min2max)
{
    if(begin < end)
    {
        int pivot = partition(array, begin, end, min2max);
        quickSort(array, begin, pivot - 1, min2max);
        quickSort(array, pivot + 1, end, min2max);
    }
}

template <typename T>
void Sort<T>::quickSort(T array[], int len, bool min2max)
{
    quickSort(array, 0 ,len - 1, min2max);
}

}

#endif
