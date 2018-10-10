#include <iostream>
#include "Test.h"

using namespace std;

class AnObject {
public:
	AnObject(void)
	{
		cout << "AnObject Constructor" << endl;
	}

	~AnObject(void)
	{
		cout << "AnObject Destructor" << endl;
	}

	void Method(void)
	{
		cout << "AnObject Method" << endl;
	}

	static void ReferObject(AnObject & o)
	{
		cout << "AnObject ReferObject ";
		o.Method();
	}
};

class BaseObject {
public:
	BaseObject(void)
	{
		cout << "BaseObject Constructor" << endl;
	}

	// Has to make the destructor virtual
	// Otherwise, the destructor of derived object will not be called
	// if delete a pointer of base type.
	virtual ~BaseObject(void)
	{
		cout << "BaseObject Destructor" << endl;
	}

	virtual void VirtualMethod(void) = 0;
};

class DerivedObject1 : public BaseObject {
public:
	DerivedObject1(void)
	{
		cout << "DerivedObject1 Constructor" << endl;
	}

	~DerivedObject1(void)
	{
		cout << "DerivedObject1 Destructor" << endl;
	}

	void VirtualMethod(void)
	{
		cout << "DerivedObject1 VirtualMethod" << endl;
	}
};

class DerivedObject2 : public BaseObject {
public:
	DerivedObject2(void)
	{
		cout << "DerivedObject2 Constructor" << endl;
	}

	~DerivedObject2(void)
	{
		cout << "DerivedObject2 Destructor" << endl;
	}

	void VirtualMethod(void)
	{
		cout << "DerivedObject2 VirtualMethod" << endl;
	}
};

class AnotherObject {
private:
	unique_ptr<AnObject> anObject;
public:
	AnotherObject(void)
	{
		anObject = unique_ptr<AnObject>(new AnObject());
		cout << "AnotherObject Constructor" << endl;
	}

	~AnotherObject(void)
	{
		cout << "AnotherObject Destructor" << endl;
	}
};

void SmartPointerTest::Init(void)
{
	Add("unique_ptr", [&]() {
		{
			AnObject * anObject = new AnObject();
			anObject->Method();
			delete anObject;
		}
		{
			cout << endl;
			unique_ptr<AnObject> anObject(new AnObject());
			anObject->Method();
			AnObject::ReferObject(*anObject);
		}
		{
			cout << endl;
			BaseObject * anObject = new DerivedObject1();
			anObject->VirtualMethod();
			// Both DerivedObject1 destructor and BaseObject destructor get called
			// because the destructor of BaseObject is virtual
			delete anObject;
		}
		{
			cout << endl;
			unique_ptr<BaseObject> anObject(new DerivedObject1());
			anObject->VirtualMethod();
			// Both DerivedObject1 destructor and BaseObject destructor get called
			// because the destructor of BaseObject is virtual		
		}
		{
			cout << endl;
			unique_ptr<DerivedObject1> anObject(new DerivedObject1());
			anObject->VirtualMethod();
			// Both DerivedObject1 destructor and BaseObject destructor get called
		}
		{
			cout << endl;
			vector<BaseObject *> v;
			BaseObject * object1 = new DerivedObject1();
			BaseObject * object2 = new DerivedObject2();
			v.push_back(object1);
			v.push_back(object2);
			for_each(v.begin(), v.end(), [&](BaseObject * it) {
				it->VirtualMethod();
				// Both DerivedObject1 destructor and BaseObject destructor get called
				// because the destructor of BaseObject is virtual	
				delete it;
			});
		}
		{
			cout << endl;
			vector<BaseObject *> v;
			DerivedObject1 * object1 = new DerivedObject1();
			DerivedObject2 * object2 = new DerivedObject2();
			v.push_back(object1);
			v.push_back(object2);
			for_each(v.begin(), v.end(), [&](BaseObject * it) {
				it->VirtualMethod();
				// Both DerivedObject1 destructor and BaseObject destructor get called
				// because the destructor of BaseObject is virtual
				delete it;
			});
		}
		{
			cout << endl;
			vector<unique_ptr<AnObject>> v;
			v.push_back(unique_ptr<AnObject>(new AnObject()));
			for_each(v.begin(), v.end(), [&](unique_ptr<AnObject> & it) {
				it->Method();
			});
		}
		{
			cout << endl;
			vector<unique_ptr<BaseObject>> v;
			v.push_back(unique_ptr<BaseObject>(new DerivedObject1()));
			v.push_back(unique_ptr<BaseObject>(new DerivedObject2()));
			for_each(v.begin(), v.end(), [&](unique_ptr<BaseObject> & it) {
				it->VirtualMethod();
			});
		}
		{
			cout << endl;
			unique_ptr<AnotherObject> anotherObject(new AnotherObject());
		}
	});
}

