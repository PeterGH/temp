#pragma once
#include <map>
using namespace std;
namespace Test {
	class LRUCache {
	private:
		int _capacity;

		struct Item {
			int key;
			int value;
			struct Item * prev;
			struct Item * next;
			Item(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
		} *head, *tail;

		map<int, struct Item *> keys;

		void MoveFront(struct Item * p)
		{
			if (p == this->head) return;
			if (p == this->tail) {
				this->tail = p->prev;
				this->tail->next = nullptr;
			} else {
				p->prev->next = p->next;
				p->next->prev = p->prev;
			}
			p->next = this->head;
			this->head->prev = p;
			p->prev = nullptr;
			this->head = p;
		}

	public:
		// Use __declspec(dllexport) on method instead of class
		// Otherwise, there will be 'warning C4251' because the map
		// container is exported for this dll, which seems to be discouraged.

		__declspec(dllexport) LRUCache(int capacity)
			: _capacity(capacity), head(nullptr), tail(nullptr)
		{
		}

		__declspec(dllexport) ~LRUCache(void)
		{
			while (this->head != nullptr) {
				struct Item * p = this->head;
				this->head = this->head->next;
				delete p;
			}
		}

		__declspec(dllexport) int Get(int key)
		{
			if (this->keys.find(key) == this->keys.end()) {
				return -1;
			} else {
				struct Item * p = this->keys[key];
				MoveFront(p);
				return p->value;
			}
		}

		__declspec(dllexport) void Set(int key, int value)
		{
			struct Item * p;
			if (this->keys.find(key) == this->keys.end()) {
				if (this->keys.size() == this->_capacity) {
					int k = this->tail->key;
					if (this->head == this->tail) {
						delete this->head;
						this->head = nullptr;
						this->tail = nullptr;
					} else {
						p = this->tail;
						this->tail = p->prev;
						this->tail->next = nullptr;
						delete p;
					}
					this->keys.erase(k);
				}
				p = new struct Item(key, value);
				if (this->head == nullptr) {
					this->head = p;
					this->tail = p;
				} else {
					p->next = this->head;
					this->head->prev = p;
					this->head = p;
				}
				this->keys[key] = p;
			} else {
				// Whether or not to change the value,
				// it counts as an access.
				p = this->keys[key];
				p->value = value;
				MoveFront(p);
			}
		}
	};
}