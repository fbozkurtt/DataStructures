#pragma once
//Open Hashing - Seperate Chaining
//Hash.hpp
#ifndef HASH_HPP
#define HASH_HPP

#include <iostream>
using namespace std;
#define MAX 101

struct Dugum {
	int veri;
	Dugum* ileri;
	Dugum(int veri, Dugum* ileri = NULL) {
		this->veri = veri;
		this->ileri = ileri;
	}
};
//Separate Chaining - Ayrık Zincirleme
class Hash {
private:
	Dugum* Dizi[MAX];
public:
	Hash();
	int HashCode(int);
	void Ekle(int);
	bool Cikar(int);
	void Temizle();
	bool Bul(int);
	bool Bosmu() const;
	void Yaz() const;
	~Hash();
};
#endif
//Hash.cpp
#include "Hash.hpp"

Hash::Hash() {
	for (int i = 0; i < MAX; i++)
		Dizi[i] = NULL;
}

void Hash::Ekle(int sayi) {
	if (Bul(sayi)) {
		cout << sayi << " zaten var!" << endl;
		return;
	}
	int indeks = HashCode(sayi);
	Dizi[indeks] = new Dugum(sayi, Dizi[indeks]);
}
bool Hash::Bul(int sayi) {
	int indeks = HashCode(sayi);
	Dugum* tmp = Dizi[indeks];
	while (tmp != NULL) {
		if (tmp->veri == sayi)
			return true;
		tmp = tmp->ileri;
	}
	return false;
}
bool Hash::Cikar(int sayi) {
	int indeks = HashCode(sayi);
	if (Dizi[indeks] == NULL)
		return false;
	if (Dizi[indeks]->veri == sayi) {//ilk düğümse direkt sil
		Dugum* sil = Dizi[indeks];
		Dizi[indeks] = Dizi[indeks]->ileri;
		delete sil;
		return true;
	}
	Dugum* onceki = Dizi[indeks];//ilk düğüm değilse bulana kadar ilerle sonra sil
	while (onceki->ileri != NULL) {
		if (onceki->ileri->veri == sayi) {
			Dugum* sil = onceki->ileri;
			onceki->ileri = sil->ileri;
			delete sil;
			return true;
		}
		onceki = onceki->ileri;
	}
	return false;
}

bool Hash::Bosmu() const {
	for (int i = 0; i < MAX; i++) {
		if (Dizi[i] != NULL)
			return false;
	}
	return true;
}

int Hash::HashCode(int sayi) {
	return sayi % MAX;//h(x) = x%101 hash fonksiyonu
}

void Hash::Temizle() {
	for (int i = 0; i < MAX; i++) {
		Dugum* tmp = Dizi[i];
		while (tmp != NULL) {
			Dugum* sil = tmp;
			tmp = tmp->ileri;
			delete sil;
		}
		Dizi[i] = NULL;
	}
}
Hash::~Hash() {
	Temizle();
}

void Hash::Yaz() const {
	for (int i = 0; i < MAX; i++) {
		if (Dizi[i] != NULL) {
			cout << "Dizi[" << i << "]=";
			for (Dugum* tmp = Dizi[i]; tmp != NULL; tmp = tmp->ileri) {
				cout << tmp->veri << "->";
			}
			cout << "NULL" << endl;
		}
	}
}
//test.cpp
#include "Hash.hpp"

int main() {
	Hash* hash = new Hash();
	hash->Ekle(100);
	hash->Ekle(55);
	hash->Ekle(1235);
	hash->Ekle(10000);
	hash->Ekle(1);
	hash->Ekle(102);
	hash->Ekle(102);
	hash->Ekle(102);
	hash->Yaz();
	delete hash;

	return 0;
}
//makefile
//hepsi: derle calistir
//
//derle :
//g++ - I . / include / -o . / lib / Hash.o - c . / src / Hash.cpp
//g++ - I . / include / -o . / bin / test . / lib / Hash.o . / src / test.cpp
//
//calistir :
//. / bin / test

//Double Hashing
//DoubleHashing.hpp
#ifndef DOUBLEHASHING_HPP
#define DOUBLEHASHING_HPP

#include <iostream>
using namespace std;

#define MAX 7
#define YAKINASAL 5


// Eksi değer kabul edilmeyen Double Hashing
class DoubleHashing {
private:
	int* tablo;
	int elemanSayisi;

public:
	DoubleHashing();
	int Hash1(int);
	int Hash2(int);
	bool Dolumu()const;
	void Ekle(int);
	bool Ara(int);
	void Cikar(int);
	void Temizle();
	void Yaz();
	~DoubleHashing();
};
#endif
//DoubleHashing.cpp
#include "DoubleHashing.hpp"

DoubleHashing::DoubleHashing() {
	tablo = new int[MAX];
	Temizle();
}
int DoubleHashing::Hash1(int anahtar) {
	return anahtar % MAX;
}
int DoubleHashing::Hash2(int anahtar) {
	return YAKINASAL - (anahtar % YAKINASAL);
}
bool DoubleHashing::Dolumu()const {
	return elemanSayisi == MAX;
}
void DoubleHashing::Ekle(int anahtar) {
	if (Dolumu())
		return;
	int indeks = Hash1(anahtar);
	if (tablo[indeks] != -1) { // Çarpışma Olur
		int adimSayisi = Hash2(anahtar);
		int i = 1;
		while (true) {
			int yeniIndeks = (indeks + i * adimSayisi) % MAX;//sona gelince başa sarması için
			if (tablo[yeniIndeks] == -1) { // Çarpışma yoksa ekle. varsa zaten while içinde yeni indis oluşturup tekrar deneyecek
				tablo[yeniIndeks] = anahtar;
				break;//ekleyince çık
			}
			i++;
		}
	}
	else {
		tablo[indeks] = anahtar;//boşsa direkt ekle
	}
	elemanSayisi++;
}
bool DoubleHashing::Ara(int anahtar) {
	if (elemanSayisi == 0)
		return false;
	int indeks = Hash1(anahtar);
	if (tablo[indeks] == anahtar)
		return true;
	int adimSayisi = Hash2(anahtar);
	int i = 1;
	while (i <= elemanSayisi) {
		int yeniIndeks = (indeks + i * adimSayisi) % MAX;
		if (tablo[yeniIndeks] == anahtar)
			return true;
		i++;
	}
	return false;
}
void DoubleHashing::Cikar(int anahtar) {
	if (elemanSayisi == 0)
		return;
	int indeks = Hash1(anahtar);
	if (tablo[indeks] == anahtar) {//ilk hashle hesaplanan indisteyse -1 yapar yani silip çıkar
		tablo[indeks] = -1;
		elemanSayisi--;
		return;
	}
	int adimSayisi = Hash2(anahtar);
	int i = 1;
	while (i <= elemanSayisi) {//eğer ilk hash ile hesaplanamazsa ikinci hash ile hesaplanıp eleman bulunmaya çalışılır
		int yeniIndeks = (indeks + i * adimSayisi) % MAX;
		if (tablo[yeniIndeks] == anahtar) {//eleman bulununca silinir
			tablo[yeniIndeks] = -1;
			elemanSayisi--;
			return;
		}
		i++;
	}
	cout << "eleman yok" << endl;
}
void DoubleHashing::Temizle() {
	elemanSayisi = 0;
	for (int i = 0; i < MAX; i++)
		tablo[i] = -1;
}
void DoubleHashing::Yaz() {
	for (int i = 0; i < MAX; i++)
	{
		if (tablo[i] != -1)
			cout << "[" << i << "]\t:" << tablo[i] << endl;
		else
			cout << "[" << i << "]\t:" << endl;
	}
}
DoubleHashing::~DoubleHashing() {
	delete[] tablo;
}
//test.cpp
#include "DoubleHashing.hpp"

int main() {
	int dizi[] = { 76,93,40,47,10,55 };
	DoubleHashing* tablo = new DoubleHashing();
	for (int i = 0; i < 6; i++)
		tablo->Ekle(dizi[i]);
	tablo->Yaz();
	delete tablo;
}
//makefile
//hepsi: derle calistir
//
//derle :
//g++ - I . / include / -o . / lib / DoubleHashing.o - c . / src / DoubleHashing.cpp
//g++ - I . / include / -o . / bin / Test . / lib / DoubleHashing.o . / src / Test.cpp
//
//calistir :
//. / bin / Test