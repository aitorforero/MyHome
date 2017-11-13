#ifndef _List_h
#define _List_h
#include <Arduino.h>
#include <DebugUtils.h>
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
class 
List
{
	private:
	 int _count;
	 ListItem<T> * _items= NULL;
	
public:
	List()
	{	
		_count = 0;
		_items = NULL;
	};

	void add(const T& item)
	{
		ListItem<T>*  newItem = new ListItem<T>(item); 
		if(!this->_items) {
			this->_items = newItem;
		} else {
			ListItem<T>* last = this->_items;
			while(last->next){
				last = last->next;
			}
			last->next = newItem;
			newItem->previous = last;
		}		
		
		_count++;
	};

	void remove(const T& item) {
	    ListItem<T>* toDestroy;
		bool destroy = false;

		if (_items->item == item) {
			INFO_PRINT("Found first")
			toDestroy = _items;
			_items = toDestroy->next;
			destroy = true;
		} else {
			ListItem<T>* current = _items;
			while(!destroy && current->next != NULL) {
				if(current->item == item) {
					INFO_PRINT("Found!")
					toDestroy = current;
				   	current->previous->next = current->next;
					destroy = true;
				} else {
					INFO_PRINT("This is not")
					current = current->next;
				}
			}
		}

		if (destroy)
		{
			INFO_PRINT("destroying")
			delete toDestroy;
			_count--;
		}
		else
		{
			INFO_PRINT("Not found!")
		}
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
		int i = 0;
		ListItem<T>* current = _items;
		while (i<index) {
			current = current->next;
			i++;
		};
		return current->item;	
	};

};

#endif