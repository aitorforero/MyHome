#ifndef _List_h
#define _List_h

// http://codereview.stackexchange.com/questions/60484/stl-vector-implementation


template <class T> 
class List
{
	private:
	 int _count;
	 T* _items;
	
public:
	List()
	{	
		_count = 0;
		_items = new T[0];
	};

	void add(const T& item)
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
			_items[_count] = item;
			_count++;
		};
	};

	void remove(const T& item)
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

			memcpy(destPos, sourcePos, copySize);	

			// Replace current with new array
			delete [] _items;
			_items = newArr;

			_count--;
		};
	};

	int indexOf(const T& item)
	{
		int index;
		for(index = 0;index<_count;index++)
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
	};

	bool contains(const T& item)
	{
		return indexOf(item)>=0;
	};


	int count()
	{
		return _count;
	};

	T item(int index)
	{
		return _items[index];	
	};

};

#endif