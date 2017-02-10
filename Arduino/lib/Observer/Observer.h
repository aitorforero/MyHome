#ifndef _Observer_h
#define _Observer_h

class Subject;


class Observer
{
public:
    virtual ~Observer();        // Destructor
    virtual void Notify(Subject* subject)=0; //Pure Virtual
    Observer();
private:
    Observer(const Observer& yRef);
    Observer& operator=(const Observer& yRef); 
};

#endif