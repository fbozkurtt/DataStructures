//Tek yönlü liste Node
#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
template <typename Object>
class Node {
public:
	Object data;
	Node<Object>* next;
	Node(const Object& data = Object(), Node<Object>* next = NULL) {
		this->data = data;
		this->next = next;
	}
};
#endif
//Tek yönlü liste iterator
#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <Node.hpp>

template <typename Object>
class Iterator {
public:
	Node<Object>* current;
	Iterator() {
		current = NULL;
	}
	Iterator(Node<Object>* node) {
		current = node;
	}
	bool IsEndNode() {
		return current == NULL;
	}
	void StepNext() {
		if (!IsEndNode())
			current = current->next;
	}
	const Object& GetCurrentData()const {
		return current->data;
	}
};
#endif
//Tek yönlü Liste
#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <Iterator.hpp>
using namespace std;
template <typename Object>
class LinkedList {
private:
	Node<Object>* head;
	int size;
	Iterator<Object> IterateFromPrevIndex(int index) const {
		if (!(index < 0 || index > Count())) {
			int i = 0;
			Iterator<Object> itr(head);
			while (!itr.IsEndNode() && index != i++)
				itr.StepNext();
			return itr;
		}
		return NULL;
	}
	Iterator<Object> IterateFromFirstNode() const {
		if (!IsEmpty())
			return Iterator<Object>(head->next);
		return NULL;
	}
public:
	LinkedList() {
		head = new Node<Object>();
		size = 0;
	}
	bool IsEmpty() const {
		return head->next == NULL;
	}
	int Count() const {
		return size;
	}
	const Object& First() const {
		if (!IsEmpty())
			return head->next->data;
		return NULL;
	}
	const Object& Last() const {
		if (!IsEmpty())
			return IterateFromPrevIndex(size).GetCurrentData();
		return NULL;
	}
	void Add(const Object& obj) {
		Insert(Count(), obj);
	}
	void Insert(int index, const Object& obj) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		itr.current->next = new Node<Object>(obj, itr.current->next);
		size++;
	}
	void Remove(const Object& obj) {
		int index = IndexOf(obj);
		RemoveAt(index);
	}
	void RemoveAt(int index) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		if (itr.current->next != NULL) {
			Node<Object>* oldNode = itr.current->next;
			itr.current->next = itr.current->next->next;
			delete oldNode;
			size--;
		}
	}
	int IndexOf(const Object& obj) const {
		int index = 0;
		for (Iterator<Object> itr(head->next); !itr.IsEndNode(); itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return index;
			index++;
		}
		return -1;
	}
	bool Find(const Object& obj) const {
		for (Iterator<Object> itr(head->next); !itr.IsEndNode(); itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return true;
		}
		return false;
	}
	friend ostream& operator<<(ostream& screen, LinkedList& list) {
		if (list.IsEmpty())
			screen << "Liste bos";
		else {
			for (Iterator<Object> itr = list.IterateFromFirstNode(); !itr.IsEndNode(); itr.StepNext())
				screen << itr.GetCurrentData() << endl;
		}
		return screen;
	}
	void Clear() {
		while (!IsEmpty()) {
			RemoveAt(0);
		}
	}
	~LinkedList() {
		Clear();
		delete head;
	}
};
#endif
//tek yönlü liste test
#include <LinkedList.hpp>

int main() {
	LinkedList<string>* names = new LinkedList<string>();
	int input = 0;
	string name;
	int index;
	do {
		system("CLS");
		cout << "1.  isim ekle" << endl;
		cout << "2.  isim sil" << endl;
		cout << "3.  konumdan isim sil" << endl;
		cout << "4.  konumdan isim ekle" << endl;
		cout << "5.  konum bul" << endl;
		cout << "6.  isim sayisi" << endl;
		cout << "7.  ilk isim" << endl;
		cout << "8.  son isim" << endl;
		cout << "9.  isimleri listele" << endl;
		cout << "10. isimleri temizle" << endl;
		cout << "11. cikis" << endl;
		cout << "secim:" << endl;
		cin >> input;
		system("CLS");
		switch (input) {
		case 1:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Add(name);
			break;
		case 2:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Remove(name);
			break;
		case 3:
			cout << "konum:";
			cin >> index;
			names->RemoveAt(index);
			break;
		case 4:
			cout << "konum:";
			cin >> index;
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Insert(index, name);
			break;
		case 5:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			cout << "konum:" << names->IndexOf(name);
			cin.get();
			break;
		case 6:
			cout << "isim sayisi:" << names->Count() << endl;
			cin.ignore();
			cin.get();
			break;
		case 7:
			cout << "ilk isim:" << names->First() << endl;
			cin.ignore();
			cin.get();
			break;
		case 8:
			cout << "son isim:" << names->Last() << endl;
			cin.ignore();
			cin.get();
			break;
		case 9:
			cout << "isimler:" << endl;
			cout << *names << endl;
			cin.ignore();
			cin.get();
			break;
		case 10:
			names->Clear();
			cout << endl << "isimler silindi." << endl;
			cin.ignore();
			cin.get();
			break;
		case 11:
			cout << "cikiliyor..";
			cin.ignore();
			cin.get();
			break;
		default:
			cout << endl << "hatali giris!" << endl;
			cin.ignore();
			cin.get();
			break;
		}
		system("CLS");
	} while (input != 11);
	delete names;
	return 0;
}
#ifndef CIRCULARLINKEDLIST_HPP
#define CIRCULARLINKEDLIST_HPP
#include <Iterator.hpp>
using namespace std;
template <typename Object>
class CircularLinkedList {
private:
	Node<Object>* head;
	int size;
	Iterator<Object> IterateFromPrevIndex(int index) const {
		if (!(index < 0 || index > Count())) {
			int i = 0;
			Iterator<Object> itr(head);
			while (!itr.IsEndNode() && index != i++)
				itr.StepNext();
			return itr;
		}
		return NULL;
	}
	Iterator<Object> IterateFromFirstNode() const {
		if (!IsEmpty())
			return Iterator<Object>(head->next);
		return NULL;
	}
	void UpdateLastNode() {
		Node<Object>* lastNode = IterateFromPrevIndex(size).current;
		lastNode->next = head->next;
	}
public:
	CircularLinkedList() {
		head = new Node<Object>();
		size = 0;
	}
	bool IsEmpty() const {
		return head->next == NULL;
	}
	int Count() const {
		return size;
	}
	const Object& First() const {
		if (!IsEmpty())
			return head->next->data;
		return NULL;
	}
	const Object& Last() const {
		if (!IsEmpty())
			return IterateFromPrevIndex(size).GetCurrentData();
		return NULL;
	}
	void Add(const Object& obj) {
		Insert(Count(), obj);
	}
	void Insert(int index, const Object& obj) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		itr.current->next = new Node<Object>(obj, itr.current->next);
		size++;
		if (index == 0)
			UpdateLastNode();
	}
	void Remove(const Object& obj) {
		int index = IndexOf(obj);
		RemoveAt(index);
	}
	void RemoveAt(int index) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		if (itr.current->next != NULL) {
			Node<Object>* oldNode = itr.current->next;
			itr.current->next = itr.current->next->next;
			delete oldNode;
			size--;
			if (size == 0)
				itr.current->next = NULL;
			if (index == 0 && size != 0)
				UpdateLastNode();
		}
	}
	int IndexOf(const Object& obj) const {
		int index = 0;
		for (Iterator<Object> itr(head->next); !itr.IsEndNode(); itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return index;
			index++;
		}
		return -1;
	}
	bool Find(const Object& obj) const {
		for (Iterator<Object> itr(head->next); !itr.IsEndNode(); itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return true;
		}
		return false;
	}
	friend ostream& operator<<(ostream& screen, CircularLinkedList& list) {
		if (list.IsEmpty())
			screen << "Liste bos";
		else {
			int i = 0;
			for (Iterator<Object> itr = list.IterateFromFirstNode(); i < list.size; itr.StepNext(), i++)
				screen << itr.GetCurrentData() << endl;
		}
		return screen;
	}
	void PrintAllFromIndex(int index) {
		if (index < 0 || index >= Count())
			return;
		if (IsEmpty())
			cout << "Liste bos" << endl;
		Iterator<Object> itr = IterateFromPrevIndex(index);
		int i = 0;
		for (itr.StepNext(); i < size; itr.StepNext(), i++)
			cout << itr.GetCurrentData() << endl;
	}
	void Clear() {
		while (!IsEmpty()) {
			RemoveAt(0);
		}
	}
	~CircularLinkedList() {
		Clear();
		delete head;
	}
};
#endif
//Tek yönlü dairesel liste test
#include <CircularLinkedList.hpp>

int main() {
	CircularLinkedList<string>* names = new CircularLinkedList<string>();
	int input = 0;
	string name;
	int index;
	do {
		system("CLS");
		cout << "1.  isim ekle" << endl;
		cout << "2.  isim sil" << endl;
		cout << "3.  konumdan isim sil" << endl;
		cout << "4.  konumdan isim ekle" << endl;
		cout << "5.  konum bul" << endl;
		cout << "6.  isim sayisi" << endl;
		cout << "7.  ilk isim" << endl;
		cout << "8.  son isim" << endl;
		cout << "9.  isimleri listele" << endl;
		cout << "10. isimleri temizle" << endl;
		cout << "11. cikis" << endl;
		cout << "12. isimleri konumdan itibaren listele" << endl;
		cout << "secim:" << endl;
		cin >> input;
		system("CLS");
		switch (input) {
		case 1:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Add(name);
			break;
		case 2:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Remove(name);
			break;
		case 3:
			cout << "konum:";
			cin >> index;
			names->RemoveAt(index);
			break;
		case 4:
			cout << "konum:";
			cin >> index;
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Insert(index, name);
			break;
		case 5:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			cout << "konum:" << names->IndexOf(name);
			cin.get();
			break;
		case 6:
			cout << "isim sayisi:" << names->Count() << endl;
			cin.ignore();
			cin.get();
			break;
		case 7:
			cout << "ilk isim:" << names->First() << endl;
			cin.ignore();
			cin.get();
			break;
		case 8:
			cout << "son isim:" << names->Last() << endl;
			cin.ignore();
			cin.get();
			break;
		case 9:
			cout << "isimler:" << endl;
			cout << *names << endl;
			cin.ignore();
			cin.get();
			break;
		case 10:
			names->Clear();
			cout << endl << "isimler silindi." << endl;
			cin.ignore();
			cin.get();
			break;
		case 11:
			cout << "cikiliyor..";
			cin.ignore();
			cin.get();
			break;
		case 12:
			cout << "konum:";
			cin >> index;
			cout << "isimler:" << endl;
			names->PrintAllFromIndex(index);
			cin.ignore();
			cin.get();
			break;
		default:
			cout << endl << "hatali giris!" << endl;
			cin.ignore();
			cin.get();
			break;
		}
		system("CLS");
	}while (input != 11);
	delete names;
	return 0;
}
//çift yönlü liste node
#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
template <typename Object>
class Node {
public:
	Object data;
	Node<Object>* next;
	Node<Object>* prev;
	Node(const Object& data = Object(), Node<Object>* next = NULL, Node<Object>* prev = NULL) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
};
#endif
//çift yönlü liste iteratör
#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <Node.hpp>

template <typename Object>
class Iterator {
public:
	Node<Object>* current;
	Iterator() {
		current = NULL;
	}
	Iterator(Node<Object>* node) {
		current = node;
	}
	bool IsEndNode() {
		return current == NULL;
	}
	void StepNext() {
		if (!IsEndNode())
			current = current->next;
	}
	void StepBack() {
		if (!IsEndNode())
			current = current->prev;
	}
	const Object& GetCurrentData()const {
		return current->data;
	}
};
#endif
//çift yönlü liste
#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP
#include <Iterator.hpp>
using namespace std;
template <typename Object>
class DoublyLinkedList {
private:
	Node<Object>* head;
	int size;
	Iterator<Object> IterateFromPrevIndex(int index) const {
		if (!(index < 0 || index > Count())) {
			int i = 0;
			Iterator<Object> itr(head);
			while (!itr.IsEndNode() && index != i++)
				itr.StepNext();
			return itr;
		}
		return NULL;
	}
	Iterator<Object> IterateFromFirstNode() const {
		if (!IsEmpty())
			return Iterator<Object>(head->next);
		return NULL;
	}
public:
	DoublyLinkedList() {
		head = new Node<Object>();
		size = 0;
	}
	bool IsEmpty() const {
		return head->next == NULL;
	}
	int Count() const {
		return size;
	}
	const Object& First() const {
		if (!IsEmpty())
			return head->next->data;
		return NULL;
	}
	const Object& Last() const {
		if (!IsEmpty())
			return IterateFromPrevIndex(size).GetCurrentData();
		return NULL;
	}
	void Add(const Object& obj) {
		Insert(Count(), obj);
	}
	void Insert(int index, const Object& obj) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		Node<Object>* newNext = itr.current->next;
		itr.current->next = new Node<Object>(obj, newNext, itr.current);
		if (newNext != NULL)
			newNext->prev = itr.current->next;
		size++;
	}
	void Remove(const Object& obj) {
		int index = IndexOf(obj);
		RemoveAt(index);
	}
	void RemoveAt(int index) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		if (itr.current->next != NULL) {
			Node<Object>* oldNode = itr.current->next;
			itr.current->next = itr.current->next->next;
			if (oldNode->next != NULL)
				oldNode->next->prev = oldNode->prev;
			delete oldNode;
			size--;
		}
	}
	int IndexOf(const Object& obj) const {
		int index = 0;
		for (Iterator<Object> itr(head->next); !itr.IsEndNode(); itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return index;
			index++;
		}
		return -1;
	}
	bool Find(const Object& obj) const {
		for (Iterator<Object> itr(head->next); !itr.IsEndNode(); itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return true;
		}
		return false;
	}
	friend ostream& operator<<(ostream& screen, DoublyLinkedList& list) {
		if (list.IsEmpty())
			screen << "Liste bos";
		else {
			for (Iterator<Object> itr = list.IterateFromFirstNode(); !itr.IsEndNode(); itr.StepNext())
				screen << itr.GetCurrentData() << endl;
		}
		return screen;
	}
	void PrintAllFromIndexReversed(int index) {
		for (Iterator<Object> itr = IterateFromPrevIndex(index + 1); itr.current != head; itr.StepBack())
			cout << itr.GetCurrentData() << endl;
	}
	void PrintAllReversed() {
		PrintAllFromIndexReversed(size - 1);
	}
	void Clear() {
		while (!IsEmpty()) {
			RemoveAt(0);
		}
	}
	~DoublyLinkedList() {
		Clear();
		delete head;
	}
};
#endif
//çift yönlü liste test
#include <DoublyLinkedList.hpp>

int main() {
	DoublyLinkedList<string>* names = new DoublyLinkedList<string>();
	int input = 0;
	string name;
	int index;
	do {
		system("CLS");
		cout << "1.  isim ekle" << endl;
		cout << "2.  isim sil" << endl;
		cout << "3.  konumdan isim sil" << endl;
		cout << "4.  konumdan isim ekle" << endl;
		cout << "5.  konum bul" << endl;
		cout << "6.  isim sayisi" << endl;
		cout << "7.  ilk isim" << endl;
		cout << "8.  son isim" << endl;
		cout << "9.  isimleri listele" << endl;
		cout << "10. isimleri temizle" << endl;
		cout << "11. cikis" << endl;
		cout << "12. isimleri konumdan basa kadar tersten listele" << endl;
		cout << "13. isimleri tersten listele" << endl;
		cout << "secim:" << endl;
		cin >> input;
		system("CLS");
		switch (input) {
		case 1:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Add(name);
			break;
		case 2:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Remove(name);
			break;
		case 3:
			cout << "konum:";
			cin >> index;
			names->RemoveAt(index);
			break;
		case 4:
			cout << "konum:";
			cin >> index;
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Insert(index, name);
			break;
		case 5:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			cout << "konum:" << names->IndexOf(name);
			cin.get();
			break;
		case 6:
			cout << "isim sayisi:" << names->Count() << endl;
			cin.ignore();
			cin.get();
			break;
		case 7:
			cout << "ilk isim:" << names->First() << endl;
			cin.ignore();
			cin.get();
			break;
		case 8:
			cout << "son isim:" << names->Last() << endl;
			cin.ignore();
			cin.get();
			break;
		case 9:
			cout << "isimler:" << endl;
			cout << *names << endl;
			cin.ignore();
			cin.get();
			break;
		case 10:
			names->Clear();
			cout << endl << "isimler silindi." << endl;
			cin.ignore();
			cin.get();
			break;
		case 11:
			cout << "cikiliyor..";
			cin.ignore();
			cin.get();
			break;
		case 12:
			cout << "konum:";
			cin >> index;
			names->PrintAllFromIndexReversed(index);
			cin.ignore();
			cin.get();
			break;
		case 13:
			names->PrintAllReversed();
			cin.ignore();
			cin.get();
			break;
		default:
			cout << endl << "hatali giris!" << endl;
			cin.ignore();
			cin.get();
			break;
		}
		system("CLS");
	} while (input != 11);
	delete names;
	return 0;
}
//çift yönlü dairesel liste
#ifndef CIRCULARDOUBLYLINKEDLIST_HPP
#define CIRCULARDOUBLYLINKEDLIST_HPP
#include <Iterator.hpp>
using namespace std;
template <typename Object>
class CircularDoublyLinkedList {
private:
	Node<Object>* head;
	int size;
	Iterator<Object> IterateFromPrevIndex(int index) const {
		if (!(index < 0 || index > Count())) {
			int i = 0;
			Iterator<Object> itr(head);
			while (!itr.IsEndNode() && index != i++)
				itr.StepNext();
			return itr;
		}
		return NULL;
	}
	Iterator<Object> IterateFromFirstNode() const {
		if (!IsEmpty())
			return Iterator<Object>(head->next);
		return NULL;
	}
public:
	CircularDoublyLinkedList() {
		head = new Node<Object>();
		size = 0;
	}
	bool IsEmpty() const {
		return head->next == NULL;
	}
	int Count() const {
		return size;
	}
	const Object& First() const {
		if (!IsEmpty())
			return head->next->data;
		return NULL;
	}
	const Object& Last() const {
		if (!IsEmpty())
			return head->next->prev->data;
		return NULL;
	}
	void Add(const Object& obj) {
		Insert(Count(), obj);
	}
	void Insert(int index, const Object& obj) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		Node<Object>* newNext = itr.current->next;
		itr.current->next = new Node<Object>(obj, newNext, itr.current);
		if (newNext != NULL) {
			Node<Object>* last = newNext->prev;
			newNext->prev = itr.current->next;
			if (index == 0) {
				head->next->prev = last;
				last->next = head->next;
			}
		}
		if (size == 0) {
			head->next->next = head->next;
			head->next->prev = head->next;
		}
		size++;
	}
	void Remove(const Object& obj) {
		int index = IndexOf(obj);
		RemoveAt(index);
	}
	void RemoveAt(int index) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		if (itr.current->next != NULL) {
			Node<Object>* oldNode = itr.current->next;
			itr.current->next = itr.current->next->next;
			oldNode->next->prev = oldNode->prev;
			delete oldNode;
			if (index == 0)
				head->next->prev->next = head->next;
			size--;
			if (size == 0)
				itr.current->next = NULL;
		}
	}
	int IndexOf(const Object& obj) const {
		int index = 0;
		for (Iterator<Object> itr(head->next); index < size; itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return index;
			index++;
		}
		return -1;
	}
	bool Find(const Object& obj) const {
		int index = 0;
		for (Iterator<Object> itr(head->next); index < size; itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return true;
		}
		return false;
	}
	friend ostream& operator<<(ostream& screen, CircularDoublyLinkedList& list) {
		if (list.IsEmpty())
			screen << "Liste bos";
		else {
			int index = 0;
			for (Iterator<Object> itr = list.IterateFromFirstNode(); index < list.size; itr.StepNext(), index++)
				screen << itr.GetCurrentData() << endl;
		}
		return screen;
	}
	void PrintAllFromIndexReversed(int index) {
		int i = 0;
		for (Iterator<Object> itr = IterateFromPrevIndex(index + 1); i < size; itr.StepBack(), i++)
			cout << itr.GetCurrentData() << endl;
	}
	void PrintAllReversed() {
		PrintAllFromIndexReversed(size - 1);
	}
	void Clear() {
		while (!IsEmpty()) {
			RemoveAt(0);
		}
	}
	~CircularDoublyLinkedList() {
		Clear();
		delete head;
	}
};
#endif
//çift yönlü dairesel liste test
#include <CircularDoublyLinkedList.hpp>

int main() {
	CircularDoublyLinkedList<string>* names = new CircularDoublyLinkedList<string>();
	int input = 0;
	string name;
	int index;
	do {
		system("CLS");
		cout << "1.  isim ekle" << endl;
		cout << "2.  isim sil" << endl;
		cout << "3.  konumdan isim sil" << endl;
		cout << "4.  konumdan isim ekle" << endl;
		cout << "5.  konum bul" << endl;
		cout << "6.  isim sayisi" << endl;
		cout << "7.  ilk isim" << endl;
		cout << "8.  son isim" << endl;
		cout << "9.  isimleri listele" << endl;
		cout << "10. isimleri temizle" << endl;
		cout << "11. cikis" << endl;
		cout << "12. isimleri konumdan basa kadar tersten listele" << endl;
		cout << "13. isimleri tersten listele" << endl;
		cout << "secim:" << endl;
		cin >> input;
		system("CLS");
		switch (input) {
		case 1:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Add(name);
			break;
		case 2:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Remove(name);
			break;
		case 3:
			cout << "konum:";
			cin >> index;
			names->RemoveAt(index);
			break;
		case 4:
			cout << "konum:";
			cin >> index;
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			names->Insert(index, name);
			break;
		case 5:
			cout << "isim:";
			cin.ignore();
			getline(cin, name);
			cout << "konum:" << names->IndexOf(name);
			cin.get();
			break;
		case 6:
			cout << "isim sayisi:" << names->Count() << endl;
			cin.ignore();
			cin.get();
			break;
		case 7:
			cout << "ilk isim:" << names->First() << endl;
			cin.ignore();
			cin.get();
			break;
		case 8:
			cout << "son isim:" << names->Last() << endl;
			cin.ignore();
			cin.get();
			break;
		case 9:
			cout << "isimler:" << endl;
			cout << *names << endl;
			cin.ignore();
			cin.get();
			break;
		case 10:
			names->Clear();
			cout << endl << "isimler silindi." << endl;
			cin.ignore();
			cin.get();
			break;
		case 11:
			cout << "cikiliyor..";
			cin.ignore();
			cin.get();
			break;
		case 12:
			cout << "konum:";
			cin >> index;
			names->PrintAllFromIndexReversed(index);
			cin.ignore();
			cin.get();
			break;
		case 13:
			names->PrintAllReversed();
			cin.ignore();
			cin.get();
			break;
		default:
			cout << endl << "hatali giris!" << endl;
			cin.ignore();
			cin.get();
			break;
		}
		system("CLS");
	} while (input != 11);
	delete names;
	return 0;
}