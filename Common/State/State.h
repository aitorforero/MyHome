#ifndef _State_h
#define _State_h

template <class entity_type>
class State
{
		
	public:
		virtual void enter(entity_type* owner)=0;
		virtual State<entity_type>* execute(entity_type* owner)=0;
		virtual void exit(entity_type* owner)=0;
};

#endif