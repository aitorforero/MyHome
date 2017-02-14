#include "List.h"



template <class T> 
List<T>::List()
{	
	_count = 0;
	_items = new T[0];
};

template <class T> 
void List<T>::add(T* item)
{
	if(!contains(item))
	{
		// Create the new array
		T* newArr = new T[_count + 1];

		// Copy old array to the new one
		memcpy(newArr, _items, _count * sizeof(T) );

		// Replace current with new array
		delete [] _items;
		_items = newArr;

		// Add item
		_items[_count]=item;
		_count++;
	};
};

template <class T> 
void List<T>::remove(T* item)
{
	int pos = indexOf(item);
	if (pos>=0) 
	{
			// Create the new array
		T* newArr = new T[_count - 1];
		
		int size =  sizeof(T);
		int destPos = pos * size;
		int sourcePos = destPos + size;
		int copySize = (_count - pos) * size;
			
		memcpy(destPos,sourcePos, copySize);	
		
		// Replace current with new array
		delete [] _items;
		_items = newArr;
		
		_count--;
	};


};

template <class T> 
int List<T>::indexOf(T* item)
{
	for(int index = 0;index<_count;index++)
	{
		if(&(_items[index])==&item)
		{
			break;
		};
	};
	
	if (index==_count)
	{
		index = -1;
	};
	
	return index;
}

template <class T> 
bool List<T>::contains(T* item)
{
	return indexOf(item)>=0;
}

template <class T> 
int List<T>::Count()
{
	return _count;
}

template <class T> 
T List<T>::item(int index)
{
	return _items[index];	
}

