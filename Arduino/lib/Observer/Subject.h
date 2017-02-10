#ifndef _Subject_h
#define _Subject_h

class Observer;


class Subject
{
public:
     
    virtual ~Subject();        //destructor
 
    bool AddObserver(Observer* observer);
    bool RemoveObserver(Observer* observer);
    bool NotifyObservers();
protected:
    //constructor is protected because this class is abstract, it’s only meant to be inherited!
    Subject();
private:
    vector<Observer*> m_ObserverVec;
    // -------------------------
    // Disabling default copy constructor and default
    // assignment operator.
    // -------------------------
    Subject(const Subject& yRef);                                
    Subject& operator=(const Subject& yRef); 
};
