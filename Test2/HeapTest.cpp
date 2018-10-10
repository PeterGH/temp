#include "HeapTest.h"

void HeapTest::Init(void)
{
	Add("Max Heap Push", [&](){
		My::Heap<int> heap;

		printf_s("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		printf_s("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(1);
		printf_s("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(2);
		printf_s("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(-1);
		printf_s("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
		}

		printf_s("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());
	});

	Add("Max Heap Pop", [&](){
		My::Heap<int> heap;

		for (int i = 0; i < 10; i++) {
			heap.Push(i);
		}

		printf_s("Pushed 0..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		for (int i = 0; i < 10; i++) {
			int v = heap.Pop();
			printf_s("Popped %d, is %sheap\n", v, heap.IsHeap() ? "" : "not ");
			heap.Print();
			ASSERT1(heap.IsHeap());
		}
	});

	Add("Max Heap", [&](){
		vector<int> input;

		for (int i = 0; i < 10; i++) {
			input.push_back(i);
		}

		My::Heap<int> heap(input);
		printf_s("Constructor([0..9]), is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());
	});

	Add("Max Heap 1", [&](){
		My::Heap<int> heap(1);

		printf_s("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		printf_s("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(1);
		printf_s("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(2);
		printf_s("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(-1);
		printf_s("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
		}

		printf_s("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());
	});

	Add("Max Heap 2", [&](){
		// This example shows the heap keeps the smallest two numbers from the input
		
		My::Heap<int> heap(2);

		printf_s("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		printf_s("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(1);
		printf_s("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(2);
		printf_s("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(-1);
		printf_s("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
		}

		printf_s("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());
	});

	Add("Min Heap Push", [&](){
		My::Heap<int, greater<int>> heap;

		printf_s("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		printf_s("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(1);
		printf_s("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(2);
		printf_s("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(-1);
		printf_s("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
		}

		printf_s("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());
	});

	Add("Min Heap Pop", [&](){
		My::Heap<int, greater<int>> heap;

		for (int i = 0; i < 10; i++) {
			heap.Push(i);
		}

		printf_s("Pushed 0..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		for (int i = 0; i < 10; i++) {
			int v = heap.Pop();
			printf_s("Popped %d, is %sheap\n", v, heap.IsHeap() ? "" : "not ");
			heap.Print();
			ASSERT1(heap.IsHeap());
		}
	});

	Add("Min Heap", [&](){
		vector<int> input;

		for (int i = 0; i < 10; i++) {
			input.push_back(i);
		}

		My::Heap<int, greater<int>> heap(input);
		printf_s("Constructor([0..9]), is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());
	});

	Add("Min Heap 1", [&](){
		My::Heap<int, greater<int>> heap(1);

		printf_s("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		printf_s("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(1);
		printf_s("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(2);
		printf_s("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(-1);
		printf_s("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
		}

		printf_s("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());
	});

	Add("Min Heap 2", [&](){
		// This example shows the heap keeps the greatest two numbers from the input
		
		My::Heap<int, greater<int>> heap(2);

		printf_s("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		printf_s("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(1);
		printf_s("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(2);
		printf_s("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		heap.Push(-1);
		printf_s("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
		}

		printf_s("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print();
		ASSERT1(heap.IsHeap());
	});
}
