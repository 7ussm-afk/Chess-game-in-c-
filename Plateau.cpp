#include "Plateau.h"
#include <cstdlib>
#include <vector>

Plateau::Plateau()
{
	initPlateau();
}

Plateau::~Plateau()
{
	
}

void Plateau::initPlateau()
{
	for(int i=2;i<6;i++)
	{
		for(int j=0;j<8;j++)
		{
			p[i][j]=0;
		}
	}

	for(int j=0;j<8;j++)
	{
		p[1][j]=-1;
	}
	for(int j=0;j<8;j++)
	{
		p[6][j]=1;
	}
	p[7][0]=2;
	p[7][1]=3;
	p[7][2]=4;
	p[7][3]=5;
	p[7][4]=6;
	p[7][5]=4;
	p[7][6]=3;
	p[7][7]=2;
	
	p[0][0]=-2;
	p[0][1]=-3;
	p[0][2]=-4;
	p[0][3]=-5;
	p[0][4]=-6;
	p[0][5]=-4;
	p[0][6]=-3;
	p[0][7]=-2;
}

int Plateau::getPiece(int x,int y)
{
	return p[x][y];
}

void Plateau::setPiece(int x,int y, int val)
{
	p[x][y]=val;
}

int Plateau::evalPionB(int xd,int yd,int xa,int ya)
{
	// déplacement simple ou double
	if (xd == 6 && xa == 4 && yd == ya && p[5][ya] == 0 && p[4][ya] == 0) return 1;
	if ((xa == xd - 1) && (ya == yd) && p[xa][ya] == 0) return 1;
	// capture normale
	if ((xa == xd - 1) && (abs(ya - yd) == 1) && p[xa][ya] < 0) return 1;
	// prise en passant
	if (xd == 3 && xa == 2 && abs(ya - yd) == 1 && xa == dernierDoublePasX && ya == dernierDoublePasY) return 1;
	return 0;
}

int Plateau::evalPionN(int xd,int yd,int xa,int ya)
{
	if (xd == 1 && xa == 3 && yd == ya && p[2][ya] == 0 && p[3][ya] == 0) return 1;
	if ((xa == xd + 1) && (ya == yd) && p[xa][ya] == 0) return 1;
	if ((xa == xd + 1) && (abs(ya - yd) == 1) && p[xa][ya] > 0) return 1;
	if (xd == 4 && xa == 5 && abs(ya - yd) == 1 && xa == dernierDoublePasX && ya == dernierDoublePasY) return 1;
	return 0;
}

int Plateau::evalCavalB(int xd,int yd,int xa,int ya)
{
	if (((xd == xa + 2 && (yd == ya - 1 || yd == ya + 1)) ||  //on peut faire abs(xa - xd) , mais 
         (xd == xa - 2 && (yd == ya - 1 || yd == ya + 1)) ||  //on a decider de travailler avec les cas
         (yd == ya - 2 && (xd == xa - 1 || xd == xa + 1)) ||  //pour que les regles du chess soient claires
         (yd == ya + 2 && (xd == xa - 1 || xd == xa + 1))) 
         && p[xa][ya] <= 0)
	{
		return 1;	
	}

	return 0;
}

int Plateau::evalCavalN(int xd, int yd, int xa, int ya)
{
    if (((xd == xa + 2 && (yd == ya - 1 || yd == ya + 1)) ||  // Déplacement 2 vers le bas + 1 horizontal
         (xd == xa - 2 && (yd == ya - 1 || yd == ya + 1)) ||  // Déplacement 2 vers le haut + 1 horizontal
         (yd == ya - 2 && (xd == xa - 1 || xd == xa + 1)) ||  // Déplacement 2 à gauche + 1 vertical
         (yd == ya + 2 && (xd == xa - 1 || xd == xa + 1)))    // Déplacement 2 à droite + 1 vertical
         && p[xa][ya] >= 0)  // Case vide (0) ou pièce blanche (>0)
    {
        return 1;  // Mouvement valide
    }
    return 0;  // Mouvement invalide
}

int Plateau::evalFouB(int xd,int yd,int xa,int ya)
{
	int dx = (xa - xd);
	int dy = (ya - yd);
	
	int X,Y; //les pas (steps)
	int x,y; //compteur pour le chemin
	
	//verification du mvt legale
	if(abs(dx) != abs(dy))
	{
		return 0;
	}
	
	if(dx > 0) //deplacement en avant par ligne
	{
		X = 1;
	}
	else
	{
		X = -1;
	}
	
	if(dy > 0) //deplacement en avant par colonne
	{
		Y = 1;
	}
	else
	{
		Y = -1;
	}
	
	//verifier si le chemin est vide
	x = xd + X;
	y = yd + Y;
	
	while(x != xa && y != ya)
	{
		if(p[x][y] != 0)
		{
			return 0;
		}
		
		x = x + X;
		y = y + Y;
	}
	
	if (p[xa][ya] <= 0)
    {
    	return 1;	
	}    

    return 0;
}

int Plateau::evalFouN(int xd,int yd,int xa,int ya)
{
	int dx = (xa - xd);
	int dy = (ya - yd);
	
	int X,Y; //les pas (steps)
	int x,y; //compteur pour le chemin
	
	//verification du mvt legale
	if(abs(dx) != abs(dy))
	{
		return 0;
	}
	
	if(dx > 0) //deplacement en avant par ligne
	{
		X = 1;
	}
	else
	{
		X = -1;
	}
	
	if(dy > 0) //deplacement en avant par colonne
	{
		Y = 1;
	}
	else
	{
		Y = -1;
	}
	
	//verifier si le chemin est vide
	x = xd + X;
	y = yd + Y;
	
	while(x != xa && y != ya)
	{
		if(p[x][y] != 0)
		{
			return 0;
		}
		
		x = x + X;
		y = y + Y;
	}
	
	if (p[xa][ya] >= 0)
    {
    	return 1;	
	}    

    return 0;
}

int Plateau::evalTourB(int xd, int yd, int xa, int ya)
{
    int dx = xa - xd; 
    int dy = ya - yd; 

    
    if (dx == 0 || dy == 0)
    {
        int X = 0;
        int Y = 0;

        if (xa > xd)
        {
        	X = 1;
		}
              
        else if (xa < xd)
        {
        	X = -1;
		}     

        
        if (ya > yd)
        {
        	Y = 1;
		}
              
        else if (ya < yd)
        {
        	Y = -1;
		}

        int x = xd + X;
        int y = yd + Y;

        
        while (x != xa || y != ya)
        {
            if (p[x][y] != 0)
            {
            	return 0;
			}

            x += X; 
            y += Y; 
        }

        if (p[xa][ya] <= 0)
        {
        	return 1;
		}
             
    }
    return 0; 
}

int Plateau::evalTourN(int xd, int yd, int xa, int ya)
{
    int dx = xa - xd; 
    int dy = ya - yd; 

    
    if (dx == 0 || dy == 0)
    {
        int X = 0;
        int Y = 0;

        if (xa > xd)
        {
        	X = 1;
		}
              
        else if (xa < xd)
        {
        	X = -1;
		}     

        
        if (ya > yd)
        {
        	Y = 1;
		}
              
        else if (ya < yd)
        {
        	Y = -1;
		}

        int x = xd + X;
        int y = yd + Y;

        
        while (x != xa || y != ya)
        {
            if (p[x][y] != 0)
            {
            	return 0;
			}

            x += X; 
            y += Y; 
        }

        if (p[xa][ya] >= 0)
        {
        	return 1;
		}
             
    }
    return 0; 
}

int Plateau::evalDameB(int xd,int yd,int xa,int ya)
{
	if(evalFouB(xd,yd,xa,ya) == 1 || evalTourB(xd,yd,xa,ya) == 1)
	{
		return 1;
	}
	return 0;
}

int Plateau::evalDameN(int xd,int yd,int xa,int ya)
{
	if(evalFouN(xd,yd,xa,ya) == 1 || evalTourN(xd,yd,xa,ya) == 1)
	{
		return 1;
	}
	return 0;
}

int Plateau::evalRoiB(int xd,int yd,int xa,int ya)
{
	if(xd == xa + 1 || xd == xa - 1 ||     //if (abs(xa - xd) <= 1 && abs(ya - yd) <= 1)
	   yd == ya + 1 || yd == ya - 1 ||
	  (xd == xa + 1 && yd == ya + 1)||
	  (xd == xa + 1 && yd == ya - 1)|| 
	  (xd == xa - 1 && yd == ya + 1)||
	  (xd == xa - 1 && yd == ya - 1))
	  {
	  	if(p[xa][ya] <= 0)
	  	{
	  		return 1;	
		}
	  }
	  return 0;
}

int Plateau::evalRoiN(int xd,int yd,int xa,int ya)
{
	if(xd == xa + 1 || xd == xa - 1 ||     //if (abs(xa - xd) <= 1 && abs(ya - yd) <= 1)
	   yd == ya + 1 || yd == ya - 1 ||
	  (xd == xa + 1 && yd == ya + 1)||
	  (xd == xa + 1 && yd == ya - 1)|| 
	  (xd == xa - 1 && yd == ya + 1)||
	  (xd == xa - 1 && yd == ya - 1))
	  {
	  	if(p[xa][ya] >= 0)
	  	{
	  		return 1;	
		}
	  }
	  return 0;
}

int Plateau::deplacerPiece(int xd,int yd,int xa,int ya)
{
	int res = evalmov(xd, yd, xa, ya);
	if (res == 1)
	{
		// Sauvegarde pour prise en passant
		if (abs(p[xd][yd]) == 1 && abs(xa - xd) == 2)
		{
			dernierDoublePasX = xa;
			dernierDoublePasY = ya;
		}
		else
		{
			dernierDoublePasX = -1;
			dernierDoublePasY = -1;
		}

		// Roque : déplacement du roi + tour
		if (p[xd][yd] == 6 && xd == 7 && yd == 4) roiBDejaBouge = true;
		if (p[xd][yd] == -6 && xd == 0 && yd == 4) roiNDejaBouge = true;
		if (p[xd][yd] == 2 && xd == 7 && yd == 0) tourBGaucheDejaBouge = true;
		if (p[xd][yd] == 2 && xd == 7 && yd == 7) tourBDroiteDejaBouge = true;
		if (p[xd][yd] == -2 && xd == 0 && yd == 0) tourNGaucheDejaBouge = true;
		if (p[xd][yd] == -2 && xd == 0 && yd == 7) tourNDroiteDejaBouge = true;

		// Gestion du roque (Blanc)
		if (p[xd][yd] == 6 && xd == 7 && yd == 4 && xa == 7 && ya == 6)
		{
			// Petit roque blanc
			p[7][5] = p[7][7];
			p[7][7] = 0;
		}
		else if (p[xd][yd] == 6 && xd == 7 && yd == 4 && xa == 7 && ya == 2)
		{
			// Grand roque blanc
			p[7][3] = p[7][0];
			p[7][0] = 0;
		}
		// Gestion du roque (Noir)
		if (p[xd][yd] == -6 && xd == 0 && yd == 4 && xa == 0 && ya == 6)
		{
			p[0][5] = p[0][7];
			p[0][7] = 0;
		}
		else if (p[xd][yd] == -6 && xd == 0 && yd == 4 && xa == 0 && ya == 2)
		{
			p[0][3] = p[0][0];
			p[0][0] = 0;
		}

		// Prise en passant
		if (abs(p[xd][yd]) == 1 && p[xa][ya] == 0 && yd != ya)
		{
			// Le pion a pris en diagonale une case vide => prise en passant
			p[xd][ya] = 0;
		}

		p[xa][ya] = p[xd][yd];
		p[xd][yd] = 0;
		
		
		// Promotion simple en Dame (Queen)
		if (p[xa][ya] == 1 && xa == 0) {
    	p[xa][ya] = 5; // Dame Blanche
		}
		else if (p[xa][ya] == -1 && xa == 7) {
   		p[xa][ya] = -5; // Dame Noire
		}

		return 1;
	}
	return 0;
}
//if(evalmov(7,6,5,5)==1)p[xa][ya]=p[xd][yd]; p[xd][yd]=0;
/*


clouage(){
		int av= p[xa][ya],ap=p[xd][yd];
        p[xa][ya]=p[xd][yd];
        if(check()){
        return 0;
		}
		 p[xa][ya]=av;
		return 1;
}
*/
int Plateau::evalmov(int xd,int yd,int xa,int ya)
{
	int res;
	//if(clouage()=1){cout<<"invalid mouve" return 0};
	
	switch (p[xd][yd])
	{
		case 1 : res = evalPionB(xd,yd,xa,ya); break;	
		case -1 : res = evalPionN(xd,yd,xa,ya); break;
		
		case 3 : res = evalCavalB(xd,yd,xa,ya); break;
		case -3 : res = evalCavalN(xd,yd,xa,ya); break;
		
		case 4 : res = evalFouB(xd,yd,xa,ya); break;
		case -4 : res = evalFouN(xd,yd,xa,ya); break;
		
		case 2 : res = evalTourB(xd,yd,xa,ya); break;
		case -2 : res = evalTourN(xd,yd,xa,ya); break;
		
		case 5 : res = evalDameB(xd,yd,xa,ya); break;
		case -5 : res = evalDameN(xd,yd,xa,ya); break;
		
		case 6 : res = evalRoiB(xd,yd,xa,ya); break;
		case -6 : res = evalRoiN(xd,yd,xa,ya); break;
	}
	if(res==1)
	{
		return 1;
	}
	return 0;
}


void Plateau::ia()
{
	std::vector<coord> vdep;
	std::vector<coordDA> vda;
	coord c;
	coordDA cda;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(p[i][j]<0)
			{
				c.x=i;
				c.y=j;
				vdep.push_back(c);
			}
		}
	}
	
	for(int z=0;z<vdep.size();z++)
	{
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				if(p[i][j]>=0)
				{
					cda.xa=i;
					cda.ya=j;
					cda.xd=vdep[z].x;
					cda.yd=vdep[z].y;
					int a=evalmov(cda.xd,cda.yd,cda.xa,cda.ya);
					if(a==1)
					{
						vda.push_back(cda);						
					}
				}
			}
		}
	}
	
	p[vda[0].xa][vda[0].ya]=p[vda[0].xd][vda[0].yd];
	p[vda[0].xd][vda[0].yd]=0;	
}

int Plateau::finPartie()
{
	return 1;
}
void Plateau::getroi(int couleur,int &x,int &y)
{
	int roi;
	if (couleur == 0)
    {
        roi = 6; 
    }
    else
    {
        roi = -6; 
    }
    for(int i=0;i>8;i++)
    {
    	for(int j=0;j>8;i++)
    	{
    		if(p[i][j]==roi)
    		{
    			x=i;
    			y=j;
			}
		}
	}
}
bool Plateau::check(int x, int y)
{
    int roi = p[x][y];
    bool roiBlanc = (roi > 0);
    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int piece = p[i][j];

            // Check if the piece belongs to the opponent
            if ((roiBlanc && piece < 0) || (!roiBlanc && piece > 0))
            {
                if (evalmov(i, j, x, y) == 1)
                {
                    return true; // Enemy can attack the king
                }
            }
        }
    }
    return false; // King is safe
}


