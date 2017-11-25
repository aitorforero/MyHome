#ifndef _List_h
#define _List_h
#include <Arduino.h>
#include <string.h>
#include <DebugUtils.h>

template <class T> 
class List
{
	private:
		int _count = 0;
		T* _items = nullptr;

		void resizeIfNecesaryFor(int length)
		{
			if (_count < length) {
				// resize it
			    T* newItems = (T*) calloc (length * 2, sizeof(T*));
				memcpy(newItems, _items, _count * sizeof(T*));
				if(_items) free(_items);
				_items = newItems;
			}
		}

	public:
		~List()
		{
			if(_items) free(_items);			
		}

		void add(const T& item)
		{
			resizeIfNecesaryFor(_count+1);
			_items[_count] = item;		
			_count++;
		};

		void remove(const T& item) {
			removeAt(indexOf(item));
		};

		void removeAt(int index)
		{
			for(int i=index; i<_count-1; i++)
			{
				_items[i] = _items[i+1];
			}

			_count--;
		}

	int indexOf(const T& item)
	{
		int i = 0;
		bool found = false;
		while(!found && (i < _count))
		{
			if (memcmp(&_items[i], &item,sizeof(item)) == 0)
			{
				found = true;
			} 
			i++;
		}

		if(found)
		{
			return i;
		}
		else
		{
			return -1;
		}
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
		T res = _items[index]; 
		return res;	
	};

    bool isEmpty() {
		if (_count == 0) 
		{ 
			return true;
		}
		else
		{
			return false;
		}
    };

};

#endif