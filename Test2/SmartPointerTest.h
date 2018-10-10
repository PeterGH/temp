#pragma once

#include "..\Algorithm\Test.h"

class SmartPointerTest : public My::TestClass
{
private:
	class AnObject 
	{
	public:
		AnObject(void);
		~AnObject(void);
		void Method(void);
		static void ReferObject(AnObject & o);		
	};

	class BaseObject
	{
	public:
		BaseObject(void);
		// Has to make the destructor virtual
		// Otherwise, the destructor of derived object will not be called
		// if delete a pointer of base type.
		virtual ~BaseObject(void);
		virtual void VirtualMethod(void) = 0;
	};

	class DerivedObject1 : public BaseObject
	{
	public:
		DerivedObject1(void);
		~DerivedObject1(void);
		void VirtualMethod(void);
	};

	class DerivedObject2 : public BaseObject
	{
	public:
		DerivedObject2(void);
		~DerivedObject2(void);
		void VirtualMethod(void);
	};

public:
	SmartPointerTest(void) {}
	~SmartPointerTest(void) {}
	void Init(void);
};

