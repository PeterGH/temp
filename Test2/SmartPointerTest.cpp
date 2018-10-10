#include "SmartPointerTest.h"
#include <vector>
using namespace std;

SmartPointerTest::AnObject::AnObject(void)
{
	cout << "AnObject Constructor" << endl;
}

SmartPointerTest::AnObject::~AnObject(void)
{
	cout << "AnObject Destructor" << endl;
}

void SmartPointerTest::AnObject::Method(void)
{
	cout << "AnObject Method" << endl;
}

void SmartPointerTest::AnObject::ReferObject(AnObject & o)
{
	cout << "AnObject ReferObject ";
	o.Method();
}

SmartPointerTest::BaseObject::BaseObject(void)
{
	cout << "BaseObject Constructor" << endl;
}

SmartPointerTest::BaseObject::~BaseObject(void)
{
	cout << "BaseObject Destructor" << endl;
}

SmartPointerTest::DerivedObject1::DerivedObject1(void)
{
	cout << "DerivedObject1 Constructor" << endl;
}

SmartPointerTest::DerivedObject1::~DerivedObject1(void)
{
	cout << "DerivedObject1 Destructor" << endl;
}

void SmartPointerTest::DerivedObject1::VirtualMethod(void)
{
	cout << "DerivedObject1 VirtualMethod" << endl;
}

SmartPointerTest::DerivedObject2::DerivedObject2(void)
{
	cout << "DerivedObject2 Constructor" << endl;
}

SmartPointerTest::DerivedObject2::~DerivedObject2(void)
{
	cout << "DerivedObject2 Destructor" << endl;
}

void SmartPointerTest::DerivedObject2::VirtualMethod(void)
{
	cout << "DerivedObject2 VirtualMethod" << endl;
}

void SmartPointerTest::Init(void)
{
	Add("Raw Pointer", [&]() {
		AnObject * anObject = new AnObject();
		anObject->Method();
		delete anObject;
	});

	Add("unique_ptr", [&]() {
		unique_ptr<AnObject> anObject(new AnObject());
		anObject->Method();
		AnObject::ReferObject(*anObject);
	});

	Add("inheritance", [&]() {
		BaseObject * anObject = new DerivedObject1();
		anObject->VirtualMethod();
		// Both DerivedObject1 destructor and BaseObject destructor get called
		// because the destructor of BaseObject is virtual
		delete anObject;
	});

	Add("unique_ptr inheritance", [&]() {
		unique_ptr<BaseObject> anObject(new DerivedObject1());
		anObject->VirtualMethod();
		// Both DerivedObject1 destructor and BaseObject destructor get called
		// because the destructor of BaseObject is virtual		
	});

	Add("unique_ptr inheritance2", [&]() {
		unique_ptr<DerivedObject1> anObject(new DerivedObject1());
		anObject->VirtualMethod();
		// Both DerivedObject1 destructor and BaseObject destructor get called
	});

	Add("vector raw pointer base type", [&]() {
		vector<BaseObject *> v;
		BaseObject * object1 = new DerivedObject1();
		BaseObject * object2 = new DerivedObject2();
		v.push_back(object1);
		v.push_back(object2);
		for_each (v.begin(), v.end(), [&](BaseObject * it) {
			it->VirtualMethod();
			// Both DerivedObject1 destructor and BaseObject destructor get called
			// because the destructor of BaseObject is virtual	
			delete it;
		});
	});

	Add("vector raw pointer derived type", [&]() {
		vector<BaseObject *> v;
		DerivedObject1 * object1 = new DerivedObject1();
		DerivedObject2 * object2 = new DerivedObject2();
		v.push_back(object1);
		v.push_back(object2);
		for_each (v.begin(), v.end(), [&](BaseObject * it) {
			it->VirtualMethod();
			// Both DerivedObject1 destructor and BaseObject destructor get called
			// because the destructor of BaseObject is virtual
			delete it;
		});
	});

	Add("vector unique_ptr", [&]() {
		vector<unique_ptr<AnObject>> v;
		v.push_back(unique_ptr<AnObject>(new AnObject()));
		for_each (v.begin(), v.end(), [&](unique_ptr<AnObject> & it) {
			it->Method();
		});
	});
	
	Add("vector unique_ptr base type", [&]() {
		vector<unique_ptr<BaseObject>> v;
		v.push_back(unique_ptr<BaseObject>(new DerivedObject1()));
		v.push_back(unique_ptr<BaseObject>(new DerivedObject2()));
		for_each (v.begin(), v.end(), [&](unique_ptr<BaseObject> & it) {
			it->VirtualMethod();
		});
	});

#if NULL	
	Add("vector unique_ptr", [&]() {
		vector<AnObject &> v;
		unique_ptr<AnObject> anObject(new AnObject());
		v.push_back(*anObject);
		for_each (v.begin(), v.end(), [&](AnObject & it) {
			it.Method();
		});
	});
	Add("vector unique_ptr2", [&]() {
		vector<unique_ptr<AnObject>> v;
		unique_ptr<AnObject> anObject(new AnObject());
		v.push_back(anObject);
		for_each (v.begin(), v.end(), [&](unique_ptr<AnObject> & it) {
			it.Method();
		});
	});
	Add("vector unique_ptr base type", [&]() {
		vector<unique_ptr<BaseObject>> v;
		unique_ptr<BaseObject> object1(new DerivedObject1());
		unique_ptr<BaseObject> object2(new DerivedObject2());
		v.push_back(object1);
		v.push_back(object2);
		for_each (v.begin(), v.end(), [&](unique_ptr<BaseObject> & it) {
			it->VirtualMethod();
		});
	});
#endif
}
