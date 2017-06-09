#ifndef _List_h
#define _List_h

// http://codereview.stackexchange.com/questions/60484/stl-vector-implementation
#include <Arduino.h>

template <class T>
class ListItem {
	public:
		ListItem<T> *previous;
	    ListItem<T> *next;
	    T item;
		ListItem(const T& newItem) {
			item = newItem;
			previous = NULL;
			next = NULL;
		}
	
};


template <class T> 
class List
{
	private:
	 int _count;
	 ListItem<T> * _items;
	
public:
	List()
	{	
		_count = 0;
		_items = NULL;
	};

	void add(const T& item)
	{
		ListItem<T>*  newItem = new ListItem<T>(item); 
		if(!_items) {
			_items = newItem;
		} else {
			ListItem<T> *last = _items;
			while(last->next){
				last = last->next;
			}
			last->next = newItem;
		}		
		
		_count++;
	};

	void remove(const T& item) {
	    ListItem<T>* toDestroy;
		
		if (_items->item == item) {
			toDestroy = _items;
			_items = toDestroy->next;
		} else {
			bool destroy = false;
			ListItem<T>* current = _items;
			while(!destroy && current->next != NULL) {
				if(current->item == item) {
					toDestroy = current;
				   	current->previous->next = current->next;
					destroy = true;
				} else {
					current = current->next;      
				}
			}
		}

		delete toDestroy;
		count--;
	};

	int indexOf(const T& item)
	{
		int index;
		for(index = 0;index<_count;index++)
		{
			if(_items[index]->item==item)
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
		return _items[index].item;	
	};

};

#endif