#ifndef _List_h
#define _List_h

template <class T> 
class List
{
public:
    void add(T* item);
	void remove(T* item);
	int indexOf(T* item);
	bool contains(T* item);
	int count();
	T item(int index);
	List();
private:
	int _count;
    T* _items;
};

#endif