#ifndef _Stack_h
#define _Stack_h
#include <Arduino.h>
#include <DebugUtils.h>
#include "List.h"

template <class T> 
class Stack {
	private:
		List<T> _items;
   
  	public:
		Stack(){};
	
		T pop() {
			T value = peek();
			_items.remove(value);
			return value;
		};
	
		T peek() {
			return _items.item(_items.count()-1);
		};
	
		void push(const T& item) {
			_items.add(item);
		};
	
		bool isEmpty() {
			return (_items.count()==0);
		};
};   
#endif