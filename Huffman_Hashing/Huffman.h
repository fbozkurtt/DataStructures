#pragma once
//Dugum.hpp
#ifndef DUGUM_HPP
#define DUGUM_HPP

#include <iostream>
using namespace std;

class Dugum {
public:
	char karakter;
	int frekans;	// Dosyada kaç kez tekrarlandığı
	string kod; 	// 01 kod karşılığı
	Dugum* sol;
	Dugum* sag;
	Dugum(char kr, int frek, Dugum* sl = NULL, Dugum* sg = NULL);
	bool Yaprakmi() const;
	bool operator==(Dugum&);
	bool operator!=(Dugum&);
	bool operator>(Dugum&);
};
#endif
//Huffman.hpp
#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <fstream>
#include <cstring>

#include "Dugum.hpp"

class Huffman {
private:
	int harfler;  			// harflerin ASCII karşılıkları
	string girdi;			// dosyadan okunan girdi
	Dugum* root;

	Dugum* AgacOlustur(int[]);
	void KodOlustur(Dugum*, string);
	int MinDugumIndeks(Dugum* dugumler[]);
	void DosyaOku(string);
	void inorder(Dugum*);
	void SilDugum(Dugum*);
public:
	Huffman(string);
	void Kodla();
	friend ostream& operator<<(ostream&, Huffman&);
	~Huffman();
};
#endif
//Dugum.cpp
#include "Dugum.hpp"

Dugum::Dugum(char kr, int frek, Dugum* sl, Dugum* sg) {
	karakter = kr;
	frekans = frek;
	sol = sl;
	sag = sg;
	kod = "";
}
bool Dugum::Yaprakmi() const {
	if (sol == NULL && sag == NULL) return true;
	return false;
}
bool Dugum::operator==(Dugum& sag) {
	if (this->karakter == sag.karakter) return true;
	else return false;
}
bool Dugum::operator!=(Dugum& sag) {
	if (this->karakter != sag.karakter) return true;
	else return false;
}
bool Dugum::operator>(Dugum& sag) {
	if (this->frekans > sag.frekans) return true;
	else return false;
}
//Huffman.cpp
#include "Huffman.hpp"

Huffman::Huffman(string dosyaYolu) {
	harfler = 256;
	girdi = "";
	DosyaOku(dosyaYolu);
	root = NULL;
}
void Huffman::DosyaOku(string dosyaYolu) {
	string satir;
	ifstream dosya(dosyaYolu.c_str());
	if (dosya.is_open())
	{
		while (getline(dosya, satir))
		{
			girdi += satir;
			girdi += '\n';
		}
		dosya.close();
	}
}
void Huffman::Kodla() {
	char karakterler[girdi.size() - 1];

	strcpy(karakterler, girdi.c_str());

	//Frekansları say
	int frek[harfler];
	// frekansları sıfırla
	for (int i = 0; i < harfler; i++)
		frek[i] = 0;

	for (int i = 0; i < girdi.size() - 1; i++)
		frek[karakterler[i]]++;

	// Huffman ağacını oluştur
	root = AgacOlustur(frek);

	// 01 kodlar oluşturuluyor
	KodOlustur(root, "");
}
Dugum* Huffman::AgacOlustur(int frek[]) {
	// dosyada var olan karakterler için düğüm olustur.
	Dugum* dugumler[harfler];
	for (int i = 0; i < harfler; i++) {
		if (frek[i] > 0) {
			dugumler[i] = new Dugum((char)i, frek[i]);
		}
		else {
			dugumler[i] = NULL;
		}
	}
	while (true) {
		int ilkIndeks = MinDugumIndeks(dugumler);// birinci en küçük düğüm			
		Dugum* min1 = dugumler[ilkIndeks];
		dugumler[ilkIndeks] = NULL;
		int ikinciIndeks = MinDugumIndeks(dugumler);// ikinci en küçük düğüm
		if (ikinciIndeks == -1) {
			return min1;//ikinci en küçük bulunamadıysa (yani tek bir düğüm var ise) tek düğümlük ağaç oluşur min1 de kök olarak belirlenir ve çıkılır
		}
		Dugum* min2 = dugumler[ikinciIndeks];
		dugumler[ikinciIndeks] = NULL;
		dugumler[ilkIndeks] = new Dugum(0, min1->frekans + min2->frekans, min1, min2);//en küçük iki düğümden bir ağaç oluşturup kök değerinin iki düğümün frekansının toplamı olarak belirler
	}

}
int Huffman::MinDugumIndeks(Dugum* dugumler[]) {
	Dugum* min;
	int minIndeks = -1;

	// ilk null olmayan düğümü min al
	for (int i = 0; i < harfler; i++) {//ascii tablosu(harfler)'nun tamamı dolu olmayacağı için ilk kullanılan yani dolu olan harf minimum kabul edilir
		if (dugumler[i] != NULL) {
			min = dugumler[i];
			minIndeks = i;
			break;
		}
	}

	for (int i = 0; i < harfler; i++)//üstteki döngüde bulunan minimum değeri kendinden sonra gelen her dolu ascii harfiyle karşılaştırılır karşılaştırılan düğümün frekansı kendisininkinden küçükse o düğüm yeni min olur harfler (ascii) bitene kadar devam eder
	{
		if (dugumler[i] == NULL) continue;

		if (*min > * (dugumler[i])) {
			min = dugumler[i];
			minIndeks = i;
		}
	}
	return minIndeks;
}
void Huffman::KodOlustur(Dugum* alt_dugum, string kod) {
	if (!alt_dugum->Yaprakmi()) {
		KodOlustur(alt_dugum->sol, kod + '0');
		KodOlustur(alt_dugum->sag, kod + '1');
	}
	else {
		alt_dugum->kod = kod;
	}
}
ostream& operator<<(ostream& ekran, Huffman& sag) {
	ekran << "Huffman Agacindaki Karakterler ve Kodlari:" << endl;
	sag.inorder(sag.root);
	return ekran;
}
void Huffman::inorder(Dugum* alt_dugum) {
	if (alt_dugum != NULL) {
		inorder(alt_dugum->sol);
		if (alt_dugum->Yaprakmi())
			cout << alt_dugum->karakter << ":" << alt_dugum->kod << endl;
		inorder(alt_dugum->sag);
	}
}
void Huffman::SilDugum(Dugum* alt_dugum) {
	if (alt_dugum == NULL)
		return;
	SilDugum(alt_dugum->sol);
	SilDugum(alt_dugum->sag);
	delete alt_dugum;
	alt_dugum = NULL;
}
Huffman::~Huffman() {
	// çöp oluşmaması için ağaç temizleniyor.
	SilDugum(root);
}
//test.cpp
#include "Huffman.hpp"

int main() {
	Huffman* huffman = new Huffman("dene.txt");
	huffman->Kodla();
	cout << *huffman;
	delete huffman;
	return 0;
}
//dene.txt
//muallim
//umut
//alim
//ulu
//uma

//makefile
//hepsi: derle calistir
//
//derle :
//g++ - I . / include / -o . / lib / Dugum.o - c . / src / Dugum.cpp
//g++ - I . / include / -o . / lib / Huffman.o - c . / src / Huffman.cpp
//g++ - I . / include / -o . / bin / test . / lib / Huffman.o . / lib / Dugum.o . / src / test.cpp
//
//calistir :
//. / bin / test

