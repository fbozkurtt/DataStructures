#pragma once
//HeapTree.hpp
#ifndef HEAPTREE_HPP
#define HEAPTREE_HPP

#include <iostream>
using namespace std;

//Min-Heap Tree
class HeapTree {
private:
	int* elemanlar;
	int dugumSayisi;
	int kapasite;

	int SolCocukIndeks(int);
	int SagCocukIndeks(int);
	int EbeveynDugumIndeks(int);
	void HeapYukari(int);
	void HeapAsagi(int);
public:
	HeapTree(int);
	bool Bosmu();
	void Ekle(int);
	int EnKucuguCikar();
	~HeapTree();
};
#endif
//HeapTree.cpp
#include "HeapTree.hpp"

int HeapTree::SolCocukIndeks(int dugumIndeks) {
	return 2 * dugumIndeks + 1;
}
int HeapTree::SagCocukIndeks(int dugumIndeks) {
	return 2 * dugumIndeks + 2;
}
int HeapTree::EbeveynDugumIndeks(int dugumIndeks) {
	return (dugumIndeks - 1) / 2;
}
HeapTree::HeapTree(int kapasite) {
	elemanlar = new int[kapasite];
	dugumSayisi = 0;
	this->kapasite = kapasite;
}
bool HeapTree::Bosmu() {
	return (dugumSayisi == 0);
}

void HeapTree::HeapYukari(int dugumIndeks) {
	int ebeveynIndeks, tmpVeri;
	if (dugumIndeks != 0) {//Köke gelene kadar kaydır
		ebeveynIndeks = EbeveynDugumIndeks(dugumIndeks);
		if (elemanlar[ebeveynIndeks] > elemanlar[dugumIndeks]) {//ebevyn daha büyükse çocukla yerini değiştir
			tmpVeri = elemanlar[ebeveynIndeks];
			elemanlar[ebeveynIndeks] = elemanlar[dugumIndeks];
			elemanlar[dugumIndeks] = tmpVeri;
			HeapYukari(ebeveynIndeks);
		}
	}
}

void HeapTree::HeapAsagi(int dugumIndeks) {
	int solCocukIndeks, sagCocukIndeks, enKucukIndeks, tmpVeri;
	solCocukIndeks = SolCocukIndeks(dugumIndeks);
	sagCocukIndeks = SagCocukIndeks(dugumIndeks);

	if (sagCocukIndeks >= dugumSayisi) {//sağ çocucuğu yoksa
		if (solCocukIndeks >= dugumSayisi) return;//ve sol çocuğu da yoksa çık
		else
			enKucukIndeks = solCocukIndeks;//sağ çocuğu yoksa ama sol çocuğu yoksa sol çocuk yeni küçük olur
	}
	else {//sağ çocuk varsa
		if (elemanlar[solCocukIndeks] <= elemanlar[sagCocukIndeks])//ve sol çocuk sağ çocuktan küçük veya eşitse
			enKucukIndeks = solCocukIndeks;//sol çocuk yeni küçük çocuk olur
		else
			enKucukIndeks = sagCocukIndeks;//sağ çocuk sol çocuktan küçükse sağ çocuk yeni küçük olur
	}
	if (elemanlar[dugumIndeks] > elemanlar[enKucukIndeks]) {//hangi çocuğun yeni küçük olduğu belirlendikten sonra çocukla ebeveyn yer değişir
		tmpVeri = elemanlar[enKucukIndeks];
		elemanlar[enKucukIndeks] = elemanlar[dugumIndeks];
		elemanlar[dugumIndeks] = tmpVeri;
		HeapAsagi(enKucukIndeks);//işlem aşağı yönde devam ederek ağaç tekrar heapleştirir
	}
}

void HeapTree::Ekle(int sayi) {
	if (dugumSayisi == kapasite)
		return;
	elemanlar[dugumSayisi] = sayi;//dizinin son indisi aynı zamanda ağacın en alt sağı olacağından yeni eleman buraya eklenir
	dugumSayisi++;
	HeapYukari(dugumSayisi - 1);//Heapleştirme işlemi
}

int HeapTree::EnKucuguCikar() {
	if (Bosmu())
		return -1;
	int enKucuk = elemanlar[0];//Kök ağaçtaki en küçük eleman olacağı için kökü alır
	elemanlar[0] = elemanlar[dugumSayisi - 1];//En alt sağdaki elemanı kök yapar
	dugumSayisi--;
	if (dugumSayisi > 0)
		HeapAsagi(0);//Kökten başlayarak ağacı tekrar heapleştirir

	return enKucuk;
}

HeapTree::~HeapTree() {
	delete[] elemanlar;
}
//Test.cpp
#include "HeapTree.hpp"
#include <cstdlib>

int main() {
	HeapTree* heapAgaci = new HeapTree(100);
	int* dizi = new int[25];

	cout << "Dizi ilk Hali:" << endl;
	for (int i = 0; i < 25; i++) {
		dizi[i] = rand() % 100 + 1;
		heapAgaci->Ekle(dizi[i]);
		cout << dizi[i] << " ";
	}
	int indeks = 0;
	while (!heapAgaci->Bosmu()) dizi[indeks++] = heapAgaci->EnKucuguCikar();

	cout << endl << "Dizi Siralanmis Hali:" << endl;
	for (int i = 0; i < 25; i++) {
		cout << dizi[i] << " ";
	}
	cout << endl;
	delete[] dizi;
	delete heapAgaci;
	return 0;
}
//makefile
//hepsi: derle calistir
//
//derle :
//g++ - I . / include / -o . / lib / HeapTree.o - c . / src / HeapTree.cpp
//g++ - I . / include / -o . / bin / test . / lib / HeapTree.o . / src / test.cpp
//
//calistir :
//. / bin / test

