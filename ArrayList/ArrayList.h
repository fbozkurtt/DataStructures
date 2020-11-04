//ArrayList.hpp
#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

using namespace std;
template <typename Object>
class ArrayList {
private:
	Object* items;
	int length;
	int capacity;

	void Reserve(int newCapacity) {
		if (capacity >= newCapacity)
			return;
		Object* temp = new Object[newCapacity];
		for (int i = 0; i < length; i++)
			temp[i] = items[i];
		if (items != NULL)
			delete[] items;
		items = temp;
		capacity = newCapacity;
	}
public:
	ArrayList() {
		length = 0;
		capacity = 0;
		items = NULL;
	}
	int Size() const {
		return length;
	}
	bool IsEmpty() const {
		return Size() == 0;
	}
	int IndexOf(const Object& item) {
		for (int i = 0; i < length; i++) {
			if (items[i] == item) return i;
		}
		return -1;
	}
	const Object& ElementAt(int i)
	{
		if (i<0 || i>length)
			return NULL;
		return items[i];
	}
	void Remove(const Object& item)
	{
		RemoveAt(IndexOf(item));
		return;
	}
	void RemoveAt(int i) {
		if (i<0 || i>length)
			return;
		for (int j = i + 1; j < length; j++)
			items[j - 1] = items[j];
		length--;
	}
	void Add(const Object& yeni) {
		Insert(length, yeni);
	}
	void Insert(int i, const Object& yeni) {
		if (i<0 || i>length)
			return;
		if (length >= capacity)
			Reserve(max(1, 2 * capacity));
		for (int j = length - 1; j >= i; j--)
			items[j + 1] = items[j];
		items[i] = yeni;
		length++;
	}
	const Object& First() {
		if (length == 0)
			return NULL;
		return items[0];
	}
	const Object& Last() {
		if (length == 0)
			return NULL;
		return items[length - 1];
	}
	void Clear() {
		length = 0;
	}
	friend ostream& operator<<(ostream& screen, ArrayList<Object>& right) {
		screen << endl;
		for (int i = 0; i < right.length; i++) {
			screen << right.items[i];
			if (i + 1 != right.length)
				screen << " || ";
		}
		return screen;
	}
	~ArrayList() {
		if (items != NULL)
			delete[] items;
	}
};
#endif
//Test.cpp
#include<iostream>
#include "ArrayList.hpp"

using namespace std;

int main()
{
	ArrayList<string>* isimler = new ArrayList<string>();
	int sec = 0;
	string isim;
	do {
		system("CLS");
		cout << "1.Isim Ekle" << endl;
		cout << "2.Isim Sil" << endl;
		cout << "3.Konumdan Isim Sil" << endl;
		cout << "4.Konuma Isim Ekle" << endl;
		cout << "5.Konum Bul" << endl;
		cout << "6.Isim Sayisi" << endl;
		cout << "7.Ilk Isim" << endl;
		cout << "8.Son Isim" << endl;
		cout << "9.Isimleri Listele" << endl;
		cout << "10.Isimleri Temizle" << endl;
		cout << "11.Cikis" << endl;
		cout << "Secim:";
		cin >> sec;
		system("CLS");
		switch (sec) {
		case 1: {
			cout << "Isim:";
			cin.ignore();
			getline(cin, isim);
			isimler->Add(isim);
		}break;
		case 2: {
			cout << "Isim:";
			cin.ignore();
			getline(cin, isim);
			isimler->Remove(isim);
			cin.get();
		}break;
		case 3: {
			int konum;
			cout << "Konum:";
			cin >> konum;
			isimler->RemoveAt(konum);
			cin.get();
		}break;
		case 4: {
			string isim;
			int konum;
			cout << "Konum:";
			cin >> konum;
			cout << "Isim:";
			cin.ignore();
			getline(cin, isim);
			isimler->Insert(konum, isim);
			cin.get();
		}break;
		case 5: {
			string isim;
			cout << "Isim:";
			cin.ignore();
			getline(cin, isim);
			cout << "Konum:" << isimler->IndexOf(isim);
			cin.get();
		}break;
		case 6: {
			cout << "Isim Sayisi:" << isimler->Size() << endl;
			cin.ignore();
			cin.get();
		}break;
		case 7: {
			cout << "Ilk Isim:" << isimler->First() << endl;
			cin.ignore();
			cin.get();
		}break;
		case 8: {
			cout << "Son Isim:" << isimler->Last() << endl;
			cin.ignore();
			cin.get();
		}break;
		case 9: {
			cout << "ISIMLER";
			cout << *isimler << endl;
			cin.ignore();
			cin.get();
		}break;
		case 10: {
			isimler->Clear();
			cout << endl << "Tum isimler silindi." << endl;
			cin.ignore();
			cin.get();
		}break;
		case 11:
			break;
		default: {
			cout << endl << "Yanlis tercih!" << endl;
			cin.ignore();
			cin.get();
		}break;
		}
		system("CLS");
	} while (sec != 11);
	delete isimler;
}
//makefile
hepsi: derle calistir

derle :
g++ - I . / include - o . / bin / test . / lib / Hata.o . / src / Test.cpp

calistir :
. / bin / test

