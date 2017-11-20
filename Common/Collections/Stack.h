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
			DEBUG_PRINT("popping...")
			T value = peek();
			_items.remove(value);
			return value;
		};
	
		T peek() {
			DEBUG_PRINT("Peeking value stored address:...")
			T res = _items.item(_items.count()-1) ;
			DEBUG_PRINT((int) &res)
			return res;
		};
	
		void push(const T& item) {
			DEBUG_PRINT("Pushing...")
			_items.add(item);
		};
	
		bool isEmpty() {
			return _items.isEmpty();
		};
};   
#endif