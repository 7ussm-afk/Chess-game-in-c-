#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Plateau.h"
using namespace std;
 
void AfficherPlateau(Plateau p) {
    // column numbers
    cout << " ";
    for(int k = 0; k < 8; k++) {
        cout << "    " << k;
    }
    cout << endl;

    for(int i = 0; i < 8; i++) {
        //  row 
        cout << "   +";
        for(int k = 0; k < 8; k++) {
            cout << "----+";
        }
        cout << endl;

        // row number and opening 
        cout << i << " |";

        for(int j = 0; j < 8; j++) {
            bool isBlackSquare = (i + j) % 2;

            
            if (isBlackSquare) {
                cout << "\033[48;5;22m";  // Dark green
            } else {
                cout << "\033[48;5;180m"; // Light beige
            }

            
            cout << "\033[30m";

            // Display the piece
            switch(p.getPiece(i,j)) {
                case 0:  cout << "    "; break;
                case 1:  cout << " PB "; break;
                case 2:  cout << " TB "; break;
                case 3:  cout << " CB "; break;
                case 4:  cout << " FB "; break;
                case 5:  cout << " DB "; break;
                case 6:  cout << " RB "; break;
                case -1: cout << " PN "; break;
                case -2: cout << " TN "; break;
                case -3: cout << " CN "; break;
                case -4: cout << " FN "; break;
                case -5: cout << " DN "; break;
                case -6: cout << " RN "; break;
            }

            // Reset color and add border
            cout << "\033[0m|";
        }

        cout << " " << i << endl;
    }

    // Bottom border
    cout << "   +";
    for(int k = 0; k < 8; k++) {
        cout << "----+";
    }
    cout << endl;

    // Bottom column numbers
     cout << " ";
    for(int k = 0; k < 8; k++) {
        cout << "    " << k;
    }
    cout << endl << endl;
}


void saisirDepart(int &xd,int &yd,Plateau p,int tour)
{
	int valide=0;
	do{
		cout<<"Veuillez saisir une ligne de depart : ";
		cin>>xd;
		cout<<"Veuillez saisir une col de depart : ";
		cin>>yd;
		if((tour==1)&&(p.getPiece(xd,yd)<0))
		{
			valide=1;
		}
		else if((tour==0)&&(p.getPiece(xd,yd)>0))
		{
			valide=1;
		}
		else
		{
			cout << "\033[1;31m" << "c'est pas votre tour!!!" << "\033[0m" << endl;

		}
	}while(((xd<0)||(xd>7)||(yd<0)||(yd>7)||(p.getPiece(xd,yd)==0))||(valide==0));
}

void saisirArrivee(int &xa,int &ya)
{
	cout<<"Veuillez saisir une ligne d arrivee : ";
	cin>>xa;
	cout<<"Veuillez saisir une col d arrivee : ";
	cin>>ya;
}



int menu()
{
    int choix;
    
    
    cout <<"\033[1;33m" <<"\n  +---------------------------------------+" <<"\033[0m"<<endl;
    cout <<"\033[1;36m"<< "  |                 MENU                  |" <<"\033[0m" <<endl;
    cout <<"\033[1;33m"<< "  +---------------------------------------+" <<"\033[0m"<< endl;
    cout <<"\033[1;32m"<< "  |  1. Mode Joueur contre Joueur         |" <<"\033[0m"<< endl;
    cout <<"\033[1;32m"<< "  |  2. Mode Joueur contre Ordinateur     |" <<"\033[0m"<< endl;
    cout <<"\033[1;33m"<< "  +---------------------------------------+" <<"\033[0m"<< endl << endl;
    cout << "\033[1;35;47m"<< "Votre choix : "<<"\033[0m";
    cin >> choix;
    system("cls");
    return choix;
    
}

int main()
{
	int choix;
	//declarer le plateau de jeu
	Plateau p;
	do{
		choix=menu();
	}while((choix!=1)&&(choix!=2));
	if(choix==1)
	{
		// 0 : Blanc //// 1 : Noir
		int tour=0,verif;
		int xd,xa,yd,ya;
		//Affichage du plateau de jeu
		do
		{
			AfficherPlateau(p);	
			//Deplacer une Piece
		
			saisirDepart(xd,yd,p,tour);
			saisirArrivee(xa,ya);
			verif=p.deplacerPiece(xd,yd,xa,ya);
			if(verif==1)
			{
				if(tour==1)
				{
					tour=0;
				}
				else
				{
					tour=1;
				}
			}
			system("cls");
		}while(p.finPartie());		
	}
	else if(choix==2)
	{
		int verif,tour=0; // 0 pour H et 1 pour M
		int xd,xa,yd,ya;
		do
		{
			AfficherPlateau(p);	
			if(tour==0)
			{
				saisirDepart(xd,yd,p,tour);
				saisirArrivee(xa,ya);
				verif=p.deplacerPiece(xd,yd,xa,ya);
				if(verif==1)
				{
					tour=1;
				}			
			}
			else
			{
				p.ia();
				tour=0;
			}
		system("cls");
		}while(p.finPartie());		
		
	}
	return 0;
}