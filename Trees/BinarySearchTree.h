#pragma once
//BST.hpp
#ifndef BST_HPP
#define BST_HPP

#include <cmath>
#include <iostream>
#define SIZE 10000
using namespace std;
template <typename Nesne>
class BST {
private:
	Nesne* elemanlar;
	int IndeksDolulugu[SIZE];

	int Ara(const Nesne& eleman, int suankiIndeks = 0) {
		while (true) {
			if (suankiIndeks == SIZE || IndeksDolulugu[suankiIndeks] == 0)
				return -1; // Eleman Yok
			if (elemanlar[suankiIndeks] == eleman && IndeksDolulugu[suankiIndeks] == 1) {
				return suankiIndeks;
			}
			else if (eleman < elemanlar[suankiIndeks])
				suankiIndeks = 2 * suankiIndeks + 1;
			else if (eleman > elemanlar[suankiIndeks])
				suankiIndeks = 2 * suankiIndeks + 2;
		}
	}
	bool ikininKatimi(int x)//ikinin kuvveti mi 2,4,8,16,32,64
	{
		while (((x % 2) == 0) && x > 1)
			x /= 2;
		return (x == 1);
	}
	int EnKucukDeger(int i = 0)
	{
		if (2 * i + 1 > SIZE)
			return i;
		else if (IndeksDolulugu[2 * i + 1] == 0)
			return i;
		else
			return EnKucukDeger(2 * i + 1);
	}
public:
	BST() {
		elemanlar = new Nesne[SIZE];
		Temizle();
	}
	void Ekle(const Nesne& eleman) {
		int suankiIndeks = 0;
		while (true) {
			if (IndeksDolulugu[suankiIndeks] == 0) {
				elemanlar[suankiIndeks] = eleman;
				IndeksDolulugu[suankiIndeks] = 1;
				break;
			}
			else if (eleman < elemanlar[suankiIndeks])
				suankiIndeks = 2 * suankiIndeks + 1;
			else if (eleman > elemanlar[suankiIndeks])
				suankiIndeks = 2 * suankiIndeks + 2;
			else
				return; // Aynı eleman var ağaca eklenmiyor
		}
	}
	bool Varmi(const Nesne& eleman) {
		if (Ara(eleman) == -1)
			return false;
		return true;
	}
	int Yukseklik(int indeks = 0) {
		if (IndeksDolulugu[indeks] == 0)
			return -1;
		return 1 + max(Yukseklik(2 * indeks + 1), Yukseklik(2 * indeks + 2));
	}
	void Sil(const Nesne& eleman, int ind = 0) {
		int i = Ara(eleman, ind);
		if (i == -1) return;
		else {
			IndeksDolulugu[i] = 0;
			if (IndeksDolulugu[2 * i + 2] == 0)// sağ çocuğu yok
			{
				if (IndeksDolulugu[2 * i + 1] == 1) //Sadece sol çocuğu varsa
				{
					int k = 2 * i + 1; int yedek[SIZE];
					for (int iter = 0; iter < SIZE; iter++) yedek[iter] = 0;
					yedek[0] = k; int index = 0;

					// BFS algoritması kullanılarak sol alt ağaçtaki düğümler silinen düğümün yerine getiriliyor.
					for (int iter = 0; iter < SIZE && yedek[iter] != 0; iter++)
					{
						for (int x = 0; x < SIZE; x++)
						{
							if (ikininKatimi(yedek[iter] + 1 - x))
							{
								elemanlar[(yedek[iter] + x - 1) / 2] = elemanlar[yedek[iter]];
								IndeksDolulugu[(yedek[iter] + x - 1) / 2] = 1;
								IndeksDolulugu[yedek[iter]] = 0;
								break;
							}
						}
						if (IndeksDolulugu[2 * yedek[iter] + 1] != 0)
						{
							yedek[++index] = 2 * yedek[iter] + 1;
						}
						if (IndeksDolulugu[2 * yedek[iter] + 2] != 0)
						{
							yedek[++index] = 2 * yedek[iter] + 2;
						}
					}
				}
			}
			else
			{
				if (IndeksDolulugu[2 * i + 1] == 0) //Sadece sağ çocuğu varsa
				{
					int k = 2 * i + 2; int yedek[SIZE];
					for (int iter = 0; iter < SIZE; iter++) yedek[iter] = 0;
					yedek[0] = k; int index = 0;

					// BFS algoritması kullanılarak sağ alt ağaçtaki düğümler silinen düğümün yerine getiriliyor.
					for (int iter = 0; iter < SIZE && yedek[iter] != 0; iter++) {
						for (int x = 0; x < SIZE; x++) {
							if (ikininKatimi((yedek[iter] + x) / 2 + 1)) {
								elemanlar[(yedek[iter] - 2 - x) / 2] = elemanlar[yedek[iter]];
								IndeksDolulugu[(yedek[iter] - 2 - x) / 2] = 1;
								break;
							}
						}
						IndeksDolulugu[yedek[iter]] = 0;
						if (IndeksDolulugu[2 * yedek[iter] + 1] != 0)
						{
							yedek[++index] = 2 * yedek[iter] + 1;
						}
						if (IndeksDolulugu[2 * yedek[iter] + 2] != 0)
						{
							yedek[++index] = 2 * yedek[iter] + 2;
						}
					}
				}
				else //İki çocuğu varsa
				{
					int x = EnKucukDeger(2 * i + 2);//sağ çocuk en solu yeni kök yap
					Nesne kopyalanacak = elemanlar[x];
					IndeksDolulugu[i] = IndeksDolulugu[x];
					elemanlar[i] = elemanlar[x];
					Sil(kopyalanacak, x);
				}
			}
		}
	}
	void Inorder(int suankiIndeks = 0) {
		if (suankiIndeks < SIZE && IndeksDolulugu[suankiIndeks] != 0) {
			Inorder(2 * suankiIndeks + 1);//SOL
			cout << elemanlar[suankiIndeks] << " ";//KÖK
			Inorder(2 * suankiIndeks + 2);//SAĞ
		}
	}
	void Preorder(int suankiIndeks = 0) {
		if (suankiIndeks < SIZE && IndeksDolulugu[suankiIndeks] != 0) {
			cout << elemanlar[suankiIndeks] << " ";//KÖK
			Preorder(2 * suankiIndeks + 1);//SOL
			Preorder(2 * suankiIndeks + 2);//SAĞ
		}
	}
	void Postorder(int suankiIndeks = 0) {
		if (suankiIndeks < SIZE && IndeksDolulugu[suankiIndeks] != 0) {
			Postorder(2 * suankiIndeks + 1);//SOL
			Postorder(2 * suankiIndeks + 2);//SAĞ
			cout << elemanlar[suankiIndeks] << " ";//KÖK
		}
	}
	void Levelorder() {
		for (int i = 0; i < SIZE; i++) {
			if (IndeksDolulugu[i] == 1)
				cout << elemanlar[i] << " ";
		}
	}
	void Temizle() {
		for (int i = 0; i < SIZE; i++)
			IndeksDolulugu[i] = 0;
	}
	~BST() {
		delete[] elemanlar;
	}
};

#endif
//Test.cpp
#include "BST.hpp"

int main() {
	BST<int>* agac = new BST<int>();
	agac->Ekle(15);
	agac->Ekle(1);
	agac->Ekle(157);
	agac->Ekle(215);
	agac->Ekle(120);
	agac->Ekle(132);
	agac->Ekle(310);
	agac->Ekle(500);
	agac->Ekle(125);
	agac->Ekle(137);
	agac->Ekle(300);
	agac->Ekle(115);
	cout << "Inorder :";
	agac->Inorder();
	cout << endl << "Preorder :";
	agac->Preorder();
	cout << endl << "Postorder :";
	agac->Postorder();
	cout << endl << endl;
	agac->Sil(15);
	cout << "Kok silindikten sonra:" << endl;
	cout << "Inorder :";
	agac->Inorder();
	cout << endl << "Preorder :";
	agac->Preorder();
	cout << endl << "Postorder :";
	agac->Postorder();
	cout << endl << endl;
	cout << "Yukseklik:" << agac->Yukseklik() << endl;
	cout << endl << "Level Order :";
	agac->Levelorder();
	cout << endl << endl;
	delete agac;
	return 0;
}
//BinarySearchTree.hpp
#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <cmath>
#include <iostream>
using namespace std;
template <typename Nesne>
struct Dugum {
	Nesne veri;
	Dugum<Nesne>* sol;
	Dugum<Nesne>* sag;
	Dugum(const Nesne& vr, Dugum<Nesne>* sl = NULL, Dugum<Nesne>* sg = NULL) {
		veri = vr;
		sol = sl;
		sag = sg;
	}
};

template <typename Nesne>
class BinarySearchTree {
private:
	Dugum<Nesne>* root;

	void AraveEkle(Dugum<Nesne>*& alt_Dugum, const Nesne& yeni) {
		if (alt_Dugum == NULL)
			alt_Dugum = new Dugum<Nesne>(yeni);
		else if (yeni < alt_Dugum->veri)
			AraveEkle(alt_Dugum->sol, yeni);
		else if (yeni > alt_Dugum->veri)
			AraveEkle(alt_Dugum->sag, yeni);
		else return; // Ayný eleman var.
	}
	bool AraveSil(Dugum<Nesne>*& alt_Dugum, const Nesne& yeni)
	{
		if (alt_Dugum == NULL)
			return false; //Eleman yok
		if (alt_Dugum->veri == yeni)
			return DugumSil(alt_Dugum);
		else if (yeni < alt_Dugum->veri)
			return AraveSil(alt_Dugum->sol, yeni);
		else
			return AraveSil(alt_Dugum->sag, yeni);
	}
	bool DugumSil(Dugum<Nesne>*& alt_Dugum)
	{
		Dugum<Nesne>* silinecekDugum = alt_Dugum;

		if (alt_Dugum->sag == NULL)
			alt_Dugum = alt_Dugum->sol;
		else if (alt_Dugum->sol == NULL)
			alt_Dugum = alt_Dugum->sag;
		else {
			silinecekDugum = alt_Dugum->sol;
			Dugum<Nesne>* ebeveynDugum = alt_Dugum;
			while (silinecekDugum->sag != NULL) {
				ebeveynDugum = silinecekDugum;
				silinecekDugum = silinecekDugum->sag;
			}
			alt_Dugum->veri = silinecekDugum->veri;
			if (ebeveynDugum == alt_Dugum)
				alt_Dugum->sol = silinecekDugum->sol;
			else ebeveynDugum->sag = silinecekDugum->sol;
		}
		delete silinecekDugum;
		return true;
	}
	void Inorder(Dugum<Nesne>* alt_Dugum) const {
		if (alt_Dugum != NULL) {
			Inorder(alt_Dugum->sol);
			cout << alt_Dugum->veri << " ";
			Inorder(alt_Dugum->sag);
		}
	}
	void Preorder(Dugum<Nesne>* alt_Dugum) const {
		if (alt_Dugum != NULL) {
			cout << alt_Dugum->veri << " ";
			Preorder(alt_Dugum->sol);
			Preorder(alt_Dugum->sag);
		}
	}
	void Postorder(Dugum<Nesne>* alt_Dugum) const {
		if (alt_Dugum != NULL) {
			Postorder(alt_Dugum->sol);
			Postorder(alt_Dugum->sag);
			cout << alt_Dugum->veri << " ";
		}
	}
	void SeviyeyiYazdir(Dugum<Nesne>* alt_Dugum, int seviye)const {
		if (alt_Dugum == NULL)
			return;
		if (seviye == 0)
			cout << alt_Dugum->veri << " ";
		else {
			SeviyeyiYazdir(alt_Dugum->sol, seviye - 1);
			SeviyeyiYazdir(alt_Dugum->sag, seviye - 1);
		}
	}
	int Yukseklik(Dugum<Nesne>* alt_Dugum)const {
		if (alt_Dugum == NULL)
			return -1; // Ortada düðüm yoksa yükseklik anlamsýzdýr. Kodun çalýþmasý adýna -1 verilmektedir.
		return 1 + max(Yukseklik(alt_Dugum->sol), Yukseklik(alt_Dugum->sag));
	}
	bool Ara(Dugum<Nesne>* alt_Dugum, const Nesne& aranan) {
		if (alt_Dugum == NULL)
			return false;
		if (alt_Dugum->veri == aranan)
			return true;
		if (aranan < alt_Dugum->veri)
			return Ara(alt_Dugum->sol, aranan);
		if (aranan > alt_Dugum->veri)
			return Ara(alt_Dugum->sag, aranan);
	}
public:
	BinarySearchTree() {
		root = NULL;
	}
	bool Bosmu() const {
		return root == NULL;
	}
	void Ekle(const Nesne& yeni)
	{
		AraveEkle(root, yeni);
	}
	void Sil(const Nesne& veri)
	{
		AraveSil(root, veri);
	}
	void Inorder() const {
		Inorder(root);
	}
	void Preorder() const {
		Preorder(root);
	}
	void Postorder() const {
		Postorder(root);
	}
	void Levelorder()const {
		int h = Yukseklik();
		for (int level = 0; level <= h; level++)
			SeviyeyiYazdir(root, level);
	}
	bool Arama(const Nesne& aranan) {
		return Ara(root, aranan);
	}
	void Temizle() {
		while (!Bosmu())
			DugumSil(root);
	}
	int Yukseklik()const {
		return Yukseklik(root);
	}
	~BinarySearchTree() {
		Temizle();
	}
};

#endif

