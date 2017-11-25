#ifndef _State_h
#define _State_h

template <class entity_type>
class State
{
	protected:
		entity_type* _owner;
	public:
		State(entity_type* owner):_owner(owner){};
		
		virtual void enter()=0;
		virtual void execute()=0;
		virtual void suspend()=0;
		virtual void resume()=0;
		virtual void exit()=0;
		virtual const char * getName()=0;
		
		virtual ~State(){};
};

#endif