// Ajouts dans Plateau.h
#ifndef PLATEAU_H
#define PLATEAU_H

class Plateau
{
	public:
		Plateau();
		~Plateau();
		
		void initPlateau();
		
		int getPiece(int x,int y);
		void setPiece(int x,int y, int val);
		void getroi(int couleur,int &x,int &y);
		bool check(int x,int y);

		int deplacerPiece(int xd,int yd,int xa,int ya);
		int evalmov(int xd,int yd,int xa,int ya);
		
		//pion
		int evalPionB(int xd,int yd,int xa,int ya);
		int evalPionN(int xd,int yd,int xa,int ya);
		
		//cavalier
		int evalCavalB(int xd,int yd,int xa,int ya);
		int evalCavalN(int xd,int yd,int xa,int ya);
		
		//fou
		int evalFouB(int xd,int yd,int xa,int ya);
		int evalFouN(int xd,int yd,int xa,int ya);
		
		//tour
		int evalTourB(int xd,int yd,int xa,int ya);
		int evalTourN(int xd,int yd,int xa,int ya);
		
		//dame
		int evalDameB(int xd,int yd,int xa,int ya);
		int evalDameN(int xd,int yd,int xa,int ya);
		
		//roi
		int evalRoiB(int xd,int yd,int xa,int ya);        
		int evalRoiN(int xd,int yd,int xa,int ya);
		
		//ia
		void ia();
		int finPartie();
	
	private:
		int p[8][8];
		int dernierDoublePasX = -1;
		int dernierDoublePasY = -1;

		bool roiBDejaBouge = false;
		bool roiNDejaBouge = false;
		bool tourBGaucheDejaBouge = false;
		bool tourBDroiteDejaBouge = false;
		bool tourNGaucheDejaBouge = false;
		bool tourNDroiteDejaBouge = false;
		
};

struct coord{
	int x,y;
};

struct coordDA{
	int xd,yd,xa,ya;
};

#endif
