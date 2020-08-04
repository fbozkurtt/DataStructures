#pragma once
//Stack.hpp
#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
using namespace std;

template <typename Object>
class Stack {
private:
	Object* items;
	int head;
	int length;
	int capacity;
	bool IsFull() {
		return length == capacity;
	}
	void Reserve(int capacity)
	{
		Object* tmp = new Object[capacity];
		for (int j = 0; j < length; j++)
			tmp[j] = items[j];
		if (items != NULL)
			delete[] items;
		items = tmp;
		this->capacity = capacity;
	}
public:
	Stack() {
		items = NULL;
		head = -1;
		length = 0;
		capacity = 0;
	}
	bool IsEmpty() const {
		return head == -1;
	}
	void Push(const Object& obj) {
		if (IsFull()) {
			Reserve(max(1, 2 * capacity));
		}
		head++;
		items[head] = obj;
		length++;
	}
	void Pop() {
		if (IsEmpty())
			return;
		head--;
		length--;
	}
	const Object& Top() const {
		if (IsEmpty())
			return NULL;
		return items[head];
	}
	void Clear() {
		head = -1;
		length = 0;
	}
	~Stack() {
		if (items != NULL)
			delete[] items;
		items = NULL;
	}
};
#endif
//Test.cpp
#include "Stack.hpp"

int main()
{
	Stack<int>* s1 = new Stack<int>();
	s1->Push(25);
	s1->Push(32);
	s1->Push(68);
	s1->Push(74);
	s1->Pop();
	cout << s1->Top();
	delete s1;
	cout << endl;

	Stack<string>* s2 = new Stack<string>();
	s2->Push("Mehmet");
	s2->Push("Veli");
	s2->Push("Ahmet");
	s2->Push("Sakarya");
	s2->Pop();
	cout << s2->Top();
	delete s2;
	return 0;
}
//makefile
//hepsi: derle calistir
//
//derle :
//g++ - I . / include / -o . / bin / test . / src / Test.cpp
//calistir :
//. / bin / test
//StackList.hpp Stack projesini kopyalarayak oluştur
#ifndef STACKLIST_HPP
#define STACKLIST_HPP
#include <iostream>
using namespace std;

template <typename Object>
class Node {
public:
	Object data;
	Node<Object>* next;
	Node(const Object& data, Node* next = NULL) {
		this->data = data;
		this->next = next;
	}
};


template <typename Object>
class Stack {
private:
	Node<Object>* head;
public:
	Stack() {
		head = NULL;
	}
	bool IsEmpty() const {
		return head == NULL;
	}
	void Push(const Object& obj) {
		head = new Node<Object>(obj, head);
	}
	void Pop() {
		if (IsEmpty())
			return;
		Node<Object>* tmp = head;
		head = head->next;
		delete tmp;
	}
	const Object& Top() const {
		if (IsEmpty())
			return NULL;
		return head->data;
	}
	void Clear() {
		while (!IsEmpty())
			Pop();
	}
	~Stack() {
		Clear();
	}
};
#endif
//Taban dönüştürme
//StackList'i kopyala
//Sayi.hpp
#ifndef SAYI_HPP
#define SAYI_HPP

#include "StackList.hpp"

class Sayi {
private:
	int deger;
	int taban;
	string donusturulen;

	string TabanDonustur();
public:
	Sayi();
	int Taban10Deger()const;
	friend ostream& operator<<(ostream&, Sayi&);
	friend istream& operator>>(istream&, Sayi&);
};

#endif
//Sayi.cpp
#include "Sayi.hpp"
string Sayi::TabanDonustur() {
	int sayi = deger;
	string rakamlar = "0123456789ABCDEF";
	string yeniSayi = "";
	Stack<int>* yigit = new Stack<int>();

	while (sayi > 0) {
		int kalan = sayi % taban;
		yigit->Push(kalan);
		sayi = sayi / taban;
	}

	while (!yigit->IsEmpty()) {
		yeniSayi = yeniSayi + rakamlar[yigit->Top()];
		yigit->Pop();
	}
	delete yigit;
	return yeniSayi;
}
Sayi::Sayi() {
	cin >> *this;
	donusturulen = TabanDonustur();
}
int Sayi::Taban10Deger()const {
	return deger;
}
ostream& operator<<(ostream& ekran, Sayi& sag) {
	ekran << "(" << sag.deger << ")10" << "=" << "(" << sag.donusturulen << ")" << sag.taban;
}
istream& operator>>(istream& girdi, Sayi& sag) {
	cout << "Sayi:";
	girdi >> sag.deger;
	cout << "Taban:";
	girdi >> sag.taban;
	return girdi;
}
//Test.cpp
#include "Sayi.hpp"

int main() {
	Sayi* s = new Sayi();
	cout << *s;
	delete s;
	return 0;
}
//makefile
//hepsi: derle calistir
//
//derle :
//g++ - I . / include / -o . / lib / Sayi.o - c . / src / Sayi.cpp
//g++ - I . / include / -o . / bin / Test . / lib / Sayi.o . / src / Test.cpp
//
//calistir :
//. / bin / Test

//infixToPostfix
//StackList'i kopyala
//Postfix.hpp
#ifndef POSTFIX_HPP
#define POSTFIX_HPP

#include "StackList.hpp"
#include <cctype>
#include <cstdlib>

class Postfix {
private:
	string ifade; //postfix ifade

	bool OncelikDusukmu(char, char);
	void PostfixAktar(Stack<char>*, string&);
	string infixToPostfix(string);
public:
	Postfix(string);
	double Hesapla();
	string postfix()const;
	friend ostream& operator<<(ostream&, Postfix&);
};

#endif
//Postfix.cpp
#include "Postfix.hpp"
bool Postfix::OncelikDusukmu(char op1, char op2) {//op2'nin önceliği op1'den düşükse true değilse false döner
	if (op1 == '(') return false;
	else if (op2 == '(') return false;
	else if (op2 == ')')return true;
	else if (op1 == '*' || op1 == '/') return true;
	else if (op2 == '*' || op2 == '/') return false;
	else return true;
}
void Postfix::PostfixAktar(Stack<char>* yigit, string& postfix) {
	postfix += yigit->Top();
	postfix += " ";
	yigit->Pop();
}
string Postfix::infixToPostfix(string infix) {
	int uzunluk = infix.length();
	Stack<char>* stack = new Stack<char>();
	string postfix = "";
	for (int i = 0; i < uzunluk; i++) {
		if (isdigit(infix[i])) {
			while (isdigit(infix[i])) {
				postfix += infix[i];
				i++;
			}
			postfix += " ";
			i--;
		}
		else if (infix[i] == '(') {
			stack->Push(infix[i]);
		}
		else if (infix[i] == '*' || infix[i] == '+' || infix[i] == '-' || infix[i] == '/') {
			while (!stack->IsEmpty() && stack->Top() != '(') {
				if (OncelikDusukmu(stack->Top(), infix[i])) {
					PostfixAktar(stack, postfix);
				}
				else {
					break;
				}
			}
			stack->Push(infix[i]);
		}
		else if (infix[i] == ')') {
			while (!stack->IsEmpty() && stack->Top() != '(') {
				PostfixAktar(stack, postfix);
			}
			if (!stack->IsEmpty()) stack->Pop();
		}
	}
	while (!stack->IsEmpty()) {
		PostfixAktar(stack, postfix);
	}
	delete stack;
	return postfix;
}
Postfix::Postfix(string infix) {
	ifade = infixToPostfix(infix);
}
double Postfix::Hesapla() {
	double sonuc;
	int uzunluk = ifade.length();
	Stack<double>* stack = new Stack<double>();
	for (int i = 0; i < uzunluk; i++) {
		if (isspace(ifade[i])) continue;
		if (isdigit(ifade[i])) {
			string sayi = "";
			while (isdigit(ifade[i])) {
				sayi += ifade[i];
				i++;
			}
			double s;
			s = atof(sayi.c_str());
			stack->Push(s);
			i--;
			continue;
		}
		else {
			double sayi2 = stack->Top();
			stack->Pop();
			double sayi1 = stack->Top();
			stack->Pop();
			switch (ifade[i]) {
			case '+':
				stack->Push(sayi1 + sayi2);
				break;
			case '-':
				stack->Push(sayi1 - sayi2);
				break;
			case '*':
				stack->Push(sayi1 * sayi2);
				break;
			case '/':
				stack->Push(sayi1 / sayi2);
				break;
			}
		}
	}
	if (!stack->IsEmpty()) {
		sonuc = stack->Top();
		stack->Pop();
	}
	delete stack;
	return sonuc;
}
string Postfix::postfix()const {
	return ifade;
}
ostream& operator<<(ostream& ekran, Postfix& sag) {
	ekran << sag.ifade << endl;
	return ekran;
}
//Test.cpp
#include "Postfix.hpp"

int main()
{
	string infix;
	cout << "Infix ifade:";
	cin >> infix;
	Postfix* p = new Postfix(infix);
	cout << "Postfix: " << *p << endl;
	cout << "Sonuc=" << p->Hesapla() << endl;

	delete p;
	return 0;
}
//makefile
//hepsi: derle calistir
//
//derle :
//g++ - I . / include / -o . / lib / Postfix.o - c . / src / Postfix.cpp
//g++ - I . / include / -o . / bin / Test . / lib / Postfix.o . / src / Test.cpp
//
//calistir :
//. / bin / Test