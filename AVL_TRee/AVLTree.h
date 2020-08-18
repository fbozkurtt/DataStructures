#pragma once
//AVLTree.hpp
#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cmath>
#include <iostream>

using namespace std;

template <typename Nesne>
struct Dugum {
	Nesne veri;
	Dugum<Nesne>* sol;
	Dugum<Nesne>* sag;
	int yukseklik;
	Dugum(const Nesne& vr, Dugum<Nesne>* sl = NULL, Dugum<Nesne>* sg = NULL) {
		veri = vr;
		sol = sl;
		sag = sg;
		yukseklik = 0;//düğümün yüksekliği başlangıçta sıfırdır
	}
};

template <typename Nesne>
class AVLTree {
private:
	Dugum<Nesne>* root;

	Dugum<Nesne>* AraveEkle(Dugum<Nesne>* alt_Dugum, const Nesne& yeni) {
		if (alt_Dugum == NULL) {
			alt_Dugum = new Dugum<Nesne>(yeni);
		}
		else if (yeni < alt_Dugum->veri) {//küçükse sola ekler
			alt_Dugum->sol = AraveEkle(alt_Dugum->sol, yeni);//sol alt çocuk yerine yeni bir ağaç oluşturur

			if (Yukseklik(alt_Dugum->sol) - Yukseklik(alt_Dugum->sag) == 2) {//yükseklik farkı birden büyükse dengeler
				// Sol Sol Durumu 
				if (yeni < alt_Dugum->sol->veri)
					alt_Dugum = SolCocukIleDegistir(alt_Dugum);//tek dönüş
				else { //Sol Sağ Durumu
					alt_Dugum->sol = SagCocukIleDegistir(alt_Dugum->sol); //çift dönüş
					alt_Dugum = SolCocukIleDegistir(alt_Dugum);
				}
			}
		}
		else if (yeni > alt_Dugum->veri) {//büyükse sağa ekler
			alt_Dugum->sag = AraveEkle(alt_Dugum->sag, yeni);

			if (Yukseklik(alt_Dugum->sag) - Yukseklik(alt_Dugum->sol) == 2) {
				// Sağ Sağ Durumu
				if (yeni > alt_Dugum->sag->veri)
					alt_Dugum = SagCocukIleDegistir(alt_Dugum);
				else {// Sağ Sol Durumu 
					alt_Dugum->sag = SolCocukIleDegistir(alt_Dugum->sag);
					alt_Dugum = SagCocukIleDegistir(alt_Dugum);
				}
			}
		}
		else; // bişey yapma

		//Yüksekliği güncelle
		alt_Dugum->yukseklik = Yukseklik(alt_Dugum);
		return alt_Dugum;
	}
	Dugum<Nesne>* SolCocukIleDegistir(Dugum<Nesne>* alt_Dugum)//sağa dönüş
	{
		Dugum<Nesne>* tmp = alt_Dugum->sol;
		alt_Dugum->sol = tmp->sag;
		tmp->sag = alt_Dugum;

		// Yükseklikleri Güncelle 
		alt_Dugum->yukseklik = Yukseklik(alt_Dugum);
		tmp->yukseklik = max(Yukseklik(tmp->sol), alt_Dugum->yukseklik) + 1;

		return tmp;
	}
	Dugum<Nesne>* SagCocukIleDegistir(Dugum<Nesne>* alt_Dugum)//sola dönüş
	{
		Dugum<Nesne>* tmp = alt_Dugum->sag;
		alt_Dugum->sag = tmp->sol;
		tmp->sol = alt_Dugum;

		// Yükseklikleri Güncelle 
		alt_Dugum->yukseklik = Yukseklik(alt_Dugum);
		tmp->yukseklik = max(Yukseklik(tmp->sag), alt_Dugum->yukseklik) + 1;

		return tmp;
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
		if (alt_Dugum == NULL) return;
		if (seviye == 0) cout << alt_Dugum->veri << " ";
		else {
			SeviyeyiYazdir(alt_Dugum->sol, seviye - 1);
			SeviyeyiYazdir(alt_Dugum->sag, seviye - 1);
		}
	}
	int Yukseklik(Dugum<Nesne>* alt_Dugum)const {
		if (alt_Dugum == NULL)
			return -1; // Ortada düğüm yoksa yükseklik anlamsızdır. Kodun çalışması adına -1 verilmektedir.
		return 1 + max(Yukseklik(alt_Dugum->sol), Yukseklik(alt_Dugum->sag));
	}
	bool DugumSil(Dugum<Nesne>*& alt_Dugum)
	{
		Dugum<Nesne>* silinecekDugum = alt_Dugum;

		if (alt_Dugum->sag == NULL)//sağ çocuğu yoksa
			alt_Dugum = alt_Dugum->sol;//sol çocuğu yerine geçsin
		else if (alt_Dugum->sol == NULL)//sol çocuğu yoksa
			alt_Dugum = alt_Dugum->sag;//sağ çocuğu yerine geçsin
		else {//iki çocuğu da varsa solun en sağı yerine geçsin
			silinecekDugum = alt_Dugum->sol;
			Dugum<Nesne>* ebeveynDugum = alt_Dugum;
			while (silinecekDugum->sag != NULL) {
				ebeveynDugum = silinecekDugum;
				silinecekDugum = silinecekDugum->sag;
			}
			alt_Dugum->veri = silinecekDugum->veri;
			if (ebeveynDugum == alt_Dugum)
				alt_Dugum->sol = silinecekDugum->sol;
			else
				ebeveynDugum->sag = silinecekDugum->sol;
		}
		delete silinecekDugum;
		return true;
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
	AVLTree() {
		root = NULL;
	}
	bool Bosmu() const {
		return root == NULL;
	}
	void Ekle(const Nesne& yeni)
	{
		root = AraveEkle(root, yeni);
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
		while (!Bosmu()) DugumSil(root);
	}
	int Yukseklik()const {
		return Yukseklik(root);
	}
	~AVLTree() {
		Temizle();
	}
};

#endif
//Test.cpp
#include "AVLTree.hpp"

int main() {
	AVLTree<int>* agac = new AVLTree<int>();
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
	cout << endl << "Level Order :";
	agac->Levelorder();
	cout << endl << endl;
	cout << "Yukseklik:" << agac->Yukseklik() << endl;
	delete agac;
	return 0;
}
//makefile
//hepsi: derle calistir
//
//derle :
//g++ - I . / include / -o . / bin / test . / src / test.cpp
//
//calistir :
//. / bin / test

