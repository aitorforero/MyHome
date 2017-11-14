#ifndef _List_h
#define _List_h
#include <Arduino.h>
#include <DebugUtils.h>

template <class T>
class ListItem {
	public:
		ListItem<T> *previous;
	    ListItem<T> *next;
	    T * item;
		ListItem(T * newItem) {
			item = newItem;
			previous = 0;
			next = 0;
		}
	
};

template <class T> 
class 
List
{
	private:
	 int _count;
	 ListItem<T> * _items;
	
public:
	List()
	{	
		_count = 0;
		_items = 0;
	};

	void add(const T& item)
	{
		ListItem<T>*  newItem = new ListItem<T>((T*)&item); 

		if(_count==0) {
			_items = newItem;
		} else {
			ListItem<T>* last = _items;
			while(last->next){
				last = last->next;
			}
			last->next = newItem;
			newItem->previous = last;
		}		
		
		_count++;
		INFO_PRINT("Created new item!")
		INFO_PRINT((int)newItem)
	};

	void remove(const T& item) {
	    ListItem<T>* toDestroy;
		bool destroy = false;

		if (_items->item == &item) {
			toDestroy = _items;
			_items = toDestroy->next;
			destroy = true;
		} else {
			ListItem<T>* current = _items->next;
			while(!(destroy || !current)) {
				if(current->item == &item) {
					toDestroy = current;
				   	current->previous->next = current->next;
					destroy = true;
				} else {
					current = current->next;
				}
			}
		}

		if (destroy)
		{
			delete toDestroy;
			_count--;
		}
	};

	int indexOf(const T& item)
	{
		int index;
		for(index = 0;index<_count;index++)
		{
			if(_items[index]->item==&item)
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
		int i = 0;
		ListItem<T>* current = _items;
		while (i<index) {
			current = current->next;
			i++;
		};
		return *(current->item);	
	};

};

#endif