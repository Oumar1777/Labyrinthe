// BAH Saikou Oumar
// g++ -Wall Labyrinthe.cpp -o labyrinthe
// ./labyrinthe

#ifndef Labyrinthe_hpp
#define Labyrinthe_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;

class Labyrinthe
{
private:
    int nb_lignes;
    int nb_colonnes;
    int taille;
    char* grille;
    int* pile;
    int sommet;
    std::string aff;

    // Retourne le caract?e ?afficher pour la valeur val.
    char getAff(char val);

public:
    /// Constructeurs et destructeurs
    Labyrinthe(int nLignes, int nColonnes); //Cr? un labyrinthe vide.
    Labyrinthe(char data[]) ; //Cr? un labyrinthe ?partir d'un descripteur.
    ~Labyrinthe(); //D?ruit le labyrinthe courant.

    /// M?hodes d'acc?
    int getID(int ligne, int colonne); //Retourne l'identifiant d'une cellule.
    int getLigne(int id); //Retourne la ligne de la cellule d'identifiant id.
    int getCol(int id); //Retourne la colonne de la cellule d'identifiant id.
    void modifie(int ligne, int colonne, char x); //Modifie la valeur d'une cellule.
    char lit(int ligne, int colonne); //Retourne la valeur de la cellule de coordonn?s (i,j).

    /// M?hode d'acc? suppl?entaires
    int getNbLignes(); //Retourne le nombre de lignes de la grille.
    int getNbColonnes(); //Retourne le nombre de lignes de la grille.
    int lit(int id); //Retourne la valeur de la cellule id.
    void modifie(int id, char x); //Modifie la valeur de la cellule id.

    /// M?hodes d'affichage
    // Initialise les caract?es utilis? pour l'affichage. Si motif contient n caract?es alors
    // motif[i] est affich?pour repr?enter une case de valeur i entre 0 et n-2.
    // Toute autre valeur provoque l'affichage du caract?e motif[n-1].
    void setAff(const char* motifs);
    void affiche(); // Affiche le labyrinthe.
    void afficheDescr(); //Affiche le descripteur du labyrinthe courant.

    /// M?hode de haut niveau
    bool connexe(); //V?ifie si toutes les cellules de valeur 0 sont connect?s.
    void genLaby(int nb); //Produit un labyrinthe al?toire connexe avec nb cases blanches.
    int distMin(int id1, int id2); //Retourne la distance minimum entre les cases id1 et id2.

    /// M?hodes suppl?entaires
    void push(int x);
    int pop();
    int caseRandom();

};

#endif /* Labyrinthe_hpp */

Labyrinthe::Labyrinthe(int nLignes, int nColonnes)
{
    this->nb_lignes = nLignes;
    this->nb_colonnes = nColonnes;
    this->taille = nLignes * nColonnes;
    this->grille = new char[taille];
    this->pile = new int[taille];
    this->sommet = 0;
    for(int i = 0; i < taille; i++)
    {
        this->grille[i] = 0;
    }
}

Labyrinthe::Labyrinthe(char data[])
{
    this->nb_lignes = (int) data[0];
    this->nb_colonnes = (int) data[1];
    this->taille = this->nb_lignes * this->nb_colonnes;
    this->grille = new char[taille];
    this->pile = new int[taille];
    this->sommet = 0;
    for(int i = 0; i < taille; i++)
    {
        this->grille[i] = data[i+2];
    }
}

Labyrinthe::~Labyrinthe()
{
    delete[] this->grille;
}

int Labyrinthe::getID(int ligne, int colonne)
{
    return this->nb_colonnes * ligne + colonne;
}

int Labyrinthe::getLigne(int id)
{
    return id / this->nb_colonnes;
}

int Labyrinthe::getCol(int id)
{
    return id % this->nb_colonnes;
}

void Labyrinthe::modifie(int ligne, int colonne, char x)
{
    this->grille[getID(ligne, colonne)] = x;
}

char Labyrinthe::lit(int ligne, int colonne)
{
    if(ligne < 0 || ligne >= nb_lignes || colonne < 0 || colonne >= nb_colonnes)
		return -1;
	else
        return this->grille[getID(ligne, colonne)];
}

int Labyrinthe::getNbLignes()
{
    return this->nb_lignes;
}

int Labyrinthe::getNbColonnes()
{
    return this->nb_colonnes;
}

int Labyrinthe::lit(int id)
{
    return this->grille[id];
}

void Labyrinthe::modifie(int id, char x){
    this->grille[id] = x;
}

void Labyrinthe::setAff(const char* motifs)
{
    this->aff = motifs;
}

void Labyrinthe::affiche()
{
    int n = (int)aff.size();
    int val;

    for(int i = -1; i <= nb_lignes; i++)
    {
        for(int j = -1; j <= nb_colonnes; j++)
        {
            val = lit(i,j);
            if(val >= 0 && val < n-1)
            {
                cout << aff[val] << " ";
            }
            else
            {
                cout << aff[n-1] << " ";
            }
        }
        cout << endl;
    }
}

void Labyrinthe::afficheDescr()
{
    for(int i = 0; i < nb_lignes; i++)
    {
        for(int j = 0; j < nb_colonnes; j++)
        {
            cout << (int)lit(i,j) << "\t";
        }
        cout << endl;
    }

}

void Labyrinthe::push(int x)
{
	pile[sommet] = x;
	sommet++;
}

int Labyrinthe::pop()
{
	if(sommet == 0)
		return -1;
	else
	{
		sommet--;
		int x = pile[sommet];
		pile[sommet] = 0;
		return x;
	}
}

bool Labyrinthe::connexe()
{
    int nbrCasesBl = 0, nbrCasesMarq = 0, id = -1, i, j;

    for(i = 0; i < nb_lignes; i++)
    {
        for(j = 0; j < nb_colonnes; j++)
        {
            if(lit(i,j) == 0)
            {
                nbrCasesBl++;
				if(id == -1)
					id = getID(i,j);
            }
        }
    }

    if(nbrCasesBl == 0)
        return false;
    else
    {
        modifie(id, 2);
        push(id);
        while(sommet > 0)
        {
            id = pop();
            i = getLigne(id);
            j = getCol(id);

            if(lit(i, j-1) == 0)
			{
				modifie(i, j-1, 2);
				push(getID(i, j-1));
			}
			if(lit(i, j+1) == 0)
			{
				modifie(i, j+1, 2);
				push(getID(i, j+1));
			}
			if(lit(i-1, j) == 0)
			{
				modifie(i-1, j, 2);
				push(getID(i-1, j));
			}
			if(lit(i+1, j) == 0)
			{
				modifie(i+1, j, 2);
				push(getID(i+1, j));
			}
        }

        for(i = 0; i < nb_lignes; i++)
		{
			for(j = 0; j < nb_colonnes; j++)
			{
				if(lit(i, j) ==  2)
				{
					modifie(i, j, 0);
					nbrCasesMarq++;
				}
			}
		}

        return (nbrCasesBl == nbrCasesMarq )&& (nbrCasesMarq != 0);
    }
}

void Labyrinthe::genLaby(int nb)
{
    modifie(0, 0, 0);
	modifie(nb_lignes - 1, nb_colonnes - 1, 0);

    int nb_cases = nb_lignes * nb_colonnes;
	int nb_cases_noirs = 0;
	int la_case, essai = 0;

	while(nb_cases - nb_cases_noirs > nb && essai != 25)
	{
		la_case = (int)(rand() % (nb_cases-2) + 1);

		if( lit(la_case) == 0)
		{
			modifie(la_case, 1);

			if(connexe())
			{
				nb_cases_noirs++;
				essai = 0;
			}
			else
			{
				modifie(la_case, 0);
				essai++;
			}
		}
	}
}

int Labyrinthe::distMin(int id1, int id2)
{
    int* filer = new int[taille];
    int id, val, i, j, k = 0, ind = 0;
    modifie(id1, -1);
    filer[ind] = id1;
    ind++;

    while(ind > k && id != id2)
    {
        id = filer[k];
        i = getLigne(id);
        j = getCol(id);
        val = lit(i, j);

        if(lit(i, j-1) == 0)
        {
            modifie(i, j-1, val - 1);
            filer[ind] = getID(i, j-1);
            ind++;
        }
        if(lit(i, j+1) == 0)
        {
            modifie(i, j+1, val - 1);
            filer[ind] = getID(i, j+1);
            ind++;
        }
        if(lit(i-1, j) == 0)
        {
            modifie(i-1, j, val - 1);
            filer[ind] = getID(i-1, j);
            ind++;
        }
        if(lit(i+1, j) == 0)
        {
            modifie(i+1, j, val - 1);
            filer[ind] = getID(i+1, j);
            ind++;
        }
        k++;
    }

    k = -lit(id2) - 1;

    for(i = 0; i < nb_lignes; i++)
    {
        for(j = 0; j < nb_colonnes; j++)
        {
            if(lit(i,j) < 0)
            {
                modifie(i, j, 0);
            }
        }
    }
    delete[] filer;
    return k;
}

int Labyrinthe::caseRandom()
{
    int caseR;
    do{
        caseR = rand() % (getNbLignes() * getNbColonnes());
    }while(lit(caseR) == 1);
    return caseR;
}

/*
int main(int argc, const char * argv[])
{
    srand((unsigned)time(NULL));
    Labyrinthe* laby = new Labyrinthe(10,10);
    laby->setAff(" X0");
    laby->genLaby(70);
    laby->affiche();
    int x = laby->caseRandom();
    int y = laby->caseRandom();
    cout << "Distance (0, 0) = " << laby->distMin(0, 0) << endl;
    cout << "Distance ("<< x <<","<< y <<") = " << laby->distMin(x, y) << endl;
    cout << "Distance (0, 99) = " << laby->distMin(0, 99) << endl;

    return 0;
}
*/
