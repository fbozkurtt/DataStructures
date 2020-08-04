#pragma once
//Queue.hpp
#ifndef KUYRUK_HPP
#define KUYRUK_HPP

#include <cmath>
template <typename Object>
class Queue {
private:
	int front;
	int back;
	int capacity;
	int length;
	Object* items;

	void reserve(int yeniKapasite) {
		Object* temp = new Object[yeniKapasite];
		for (int i = front, j = 0; j < length; j++) {
			temp[j] = items[i];
			i = (i + 1) % capacity;
		}
		capacity = yeniKapasite;
		delete[] items;
		items = temp;
		front = 0;
		back = length - 1;
	}
public:
	Queue() {
		capacity = 1;
		front = 0;
		back = -1;
		length = 0;
		items = new Object[capacity];
	}
	void clear() {
		front = 0;
		back = -1;
		length = 0;
	}
	int count() const {
		return length;
	}
	bool isEmpty() const {
		if (length == 0) return true;
		return false;
	}
	/// Kuyrukta en öndeki elemanı getirir
	const Object& peek() const {
		if (isEmpty())
			return NULL;
		return items[front];
	}
	void enqueue(const Object& item) {
		if (length == capacity) reserve(2 * capacity);
		back = (back + 1) % capacity;
		items[back] = item;
		length++;
	}
	void dequeue() {
		if (isEmpty())
			return;
		front = (front + 1) % capacity;
		length--;
	}
	~Queue() {
		delete[] items;
	}
};
#endif
//Test.cpp
#include "Queue.hpp"
#include <iostream>
using namespace std;
struct Ogrenci {
	int no;
	string adSoyad;
	Ogrenci(int numara, string isim) {
		no = numara;
		adSoyad = isim;
	}
	friend ostream& operator<<(ostream& ekran, Ogrenci& sag) {
		ekran << sag.no << " " << sag.adSoyad << endl;
		return ekran;
	}
};

int main() {
	Queue<int>* kuyruk = new Queue<int>();
	kuyruk->enqueue(15);
	kuyruk->enqueue(16);
	kuyruk->enqueue(17);
	kuyruk->enqueue(18);
	kuyruk->enqueue(19);
	kuyruk->enqueue(20);
	kuyruk->enqueue(21);

	kuyruk->dequeue();
	kuyruk->dequeue();
	kuyruk->dequeue();

	kuyruk->enqueue(1);
	kuyruk->enqueue(2);
	kuyruk->enqueue(3);
	kuyruk->enqueue(4);
	kuyruk->enqueue(5);
	kuyruk->enqueue(6);
	kuyruk->enqueue(7);
	cout << kuyruk->peek() << endl << endl;
	delete kuyruk;

	Queue<Ogrenci*>* kuyruk2 = new Queue<Ogrenci*>();
	Ogrenci* ali = new Ogrenci(224, "Ali Yilmaz");
	Ogrenci* mehmet = new Ogrenci(100, "Mehmet Korkmaz");
	Ogrenci* veli = new Ogrenci(500, "veli sari");
	kuyruk2->enqueue(ali);
	kuyruk2->enqueue(mehmet);
	cout << *(kuyruk2->peek()) << endl;
	kuyruk2->dequeue();
	cout << *(kuyruk2->peek()) << endl;
	kuyruk2->enqueue(veli);
	kuyruk2->enqueue(ali);
	cout << *(kuyruk2->peek()) << endl;
	delete ali;
	delete mehmet;
	delete veli;
	delete kuyruk2;
	return 0;
}
//makefile
//hepsi: derle calistir
//
//derle :
//g++ - I . / include / -o . / bin / test . / src / Test.cpp
//
//calistir :
//. / bin / test

//Kuyruk Liste, Queue'yi kopyala
//Queue.hpp
#ifndef KUYRUK_HPP
#define KUYRUK_HPP
#include <iostream>

template <typename Object>
class Node {
public:
	Object item;
	Node<Object>* next;
	Node(Object itm, Node<Object>* nxt = NULL) {
		item = itm;
		next = nxt;
	}
};

template <typename Object>
class Queue {
private:
	Node<Object>* front;
	Node<Object>* back;
	int length;

public:
	Queue() {
		front = back = NULL;
		length = 0;
	}
	void clear() {
		while (!isEmpty()) dequeue();
	}
	int count() const {
		return length;
	}
	bool isEmpty() const {
		if (length == 0) return true;
		return false;
	}
	/// Kuyrukta en öndeki elemanı getirir
	const Object& peek() {
		if (isEmpty())
			return NULL;
		return front->item;
	}
	void enqueue(const Object& item) {
		Node<Object>* last = new Node<Object>(item);
		if (isEmpty()) front = back = last;
		else {
			back->next = last;
			back = last;
		}
		length++;
	}
	void dequeue() {
		if (isEmpty())
			return;
		Node<Object>* eskiOn = front;
		front = front->next;
		delete eskiOn;
		length--;
	}
	~Queue() {
		clear();
	}
};
#endif
//Test.cpp
#include "Queue.hpp"
using namespace std;
struct Ogrenci {
	int no;
	string adSoyad;
	Ogrenci(int numara, string isim) {
		no = numara;
		adSoyad = isim;
	}
	friend ostream& operator<<(ostream& ekran, Ogrenci& sag) {
		ekran << sag.no << " " << sag.adSoyad << endl;
		return ekran;
	}
};

int main() {
	Queue<Ogrenci*>* kuyruk = new Queue<Ogrenci*>();
	Ogrenci* ali = new Ogrenci(224, "Ali Yilmaz");
	Ogrenci* mehmet = new Ogrenci(100, "Mehmet Korkmaz");
	Ogrenci* veli = new Ogrenci(500, "veli sari");
	kuyruk->enqueue(ali);
	kuyruk->enqueue(mehmet);
	cout << *(kuyruk->peek()) << endl;
	kuyruk->dequeue();
	cout << *(kuyruk->peek()) << endl;
	kuyruk->enqueue(veli);
	kuyruk->enqueue(ali);
	cout << *(kuyruk->peek()) << endl;
	delete ali;
	delete mehmet;
	delete veli;
	delete kuyruk;
	return 0;
}
//Öncelikli kuyruk, kuyruklisteyi kopyala
//Queue.hpp
#ifndef KUYRUK_HPP
#define KUYRUK_HPP
#include <iostream>

template <typename Object>
class Node {
public:
	Object item;
	Node<Object>* next;
	Node(Object itm, Node<Object>* nxt = NULL) {
		item = itm;
		next = nxt;
	}
};

template <typename Object>
class Queue {
private:
	Node<Object>* front;
	Node<Object>* back;
	int length;

	Node<Object>* previousMaxNode() {
		Node<Object>* prev = NULL;
		Node<Object>* tmp = front;
		Object max = front->item;
		while (tmp->next != NULL) {
			if (tmp->next->item > max) {
				max = tmp->next->item;
				prev = tmp;
			}
			tmp = tmp->next;
		}
		return prev;
	}
public:
	Queue() {
		front = back = NULL;
		length = 0;
	}
	void clear() {
		while (!isEmpty()) dequeue();
	}
	int count() const {
		return length;
	}
	bool isEmpty() const {
		if (length == 0) return true;
		return false;
	}
	/// Kuyrukta en öndeki elemanı getirir
	const Object& peek() {
		if (isEmpty())
			return NULL;
		return front->item;
	}
	const Object& peekMax() {
		if (isEmpty())
			return NULL;
		Node<Object>* prev = previousMaxNode();
		if (prev == NULL)
			return peek();
		return prev->next->item;
	}
	void enqueue(const Object& item) {
		Node<Object>* last = new Node<Object>(item);
		if (isEmpty()) front = back = last;
		else {
			back->next = last;
			back = last;
		}
		length++;
	}
	void dequeue() {
		if (isEmpty())
			return;
		Node<Object>* eskiOn = front;
		front = front->next;
		delete eskiOn;
		length--;
	}
	void dequeueMax() {
		if (isEmpty())
			return;
		Node<Object>* prev = previousMaxNode();
		Node<Object>* tmp;
		if (prev == NULL) {
			dequeue();
		}
		else {
			if (prev->next == back) back = prev; // en son eleman silinecekse
			tmp = prev->next;
			prev->next = prev->next->next;
			delete tmp;
			length--;
		}
	}
	~Queue() {
		clear();
	}
};
#endif
//Test.cpp
#include "Queue.hpp"
using namespace std;
int main() {
	Queue<int>* kuyruk = new Queue<int>();

	kuyruk->enqueue(724);
	kuyruk->enqueue(1225);
	kuyruk->enqueue(531);
	kuyruk->enqueue(850);
	kuyruk->dequeueMax();
	cout << kuyruk->peek() << endl;
	cout << kuyruk->peekMax() << endl;

	delete kuyruk;
	return 0;
}