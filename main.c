#include "Menu.h"
#include "Option.h"
#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		/* Needed if linking in external compiler; harmless otherwise */
#include <userint.h>
#include <math.h> 
#include "Angry birds.h"
#include <stdlib.h>
#include <time.h>
#include "Acceuil.h"
#include "credits.h"
//---------------- DEFINE -------------------------------------------------------------------------------

//valeurs changeables : ------------------------------------------------

#define Xt 10 //abscisse de la tour (en matricielle)
#define width 400
#define height 300
#define sizeCASE 20

//Valeurs invariantes : ------------------------------------------------

#define Nbx	width/sizeCASE
#define Nby	height/sizeCASE

#define pi 3.1415  
#define g 9.8

// type de la tour : 
#define beton colorB/*colorG*/
#define bois colorV/*colorM*/
// score :
#define VALoisN 3
#define VALoisA 5
#define VALoisE 20
#define VALbois 5
#define VALbet 10
// mes fonctions al�atoires
#define Hauteur rand()%Nby
#define Largeur rand()%(Nbx-debutX)
#define PileOuFace rand()%2

//-------------- PROTOTYPAGE --------------------------------------------------------------------------

void DrawBird(int x, int y, int color);
void Construction(int i, int j, int coul);
void Matrice(void); 
void DrawBirds(int coul);
int SCOREconstruct(int bt, int bs);
int SCOREoiseau(int i, int j, int k);

void initialisationVglobales (void);  
void BitMapTypeOiseau(void); 
void DrawArrierePlan (void);
void DrawTour (void);
void DrawCOCH (void);  
void AffichageEcran (void);

//----------------------------------------------------------------------------------------------------
//VARIABLES GLOBALES

// variables r�cup�r�es avec Get
int NbrO;
int typeO;
int Niveau; 
int light; 
int trace;
float V0, alpha;
float vent;

// Variables pour Set
int score; 

// Variables normales
int posX0, posY0, debutX;
int posX[3], posY[3]; //pour 3 oiseaux // 
int indice[3]={0,0,0};

float Vx0, Vy0, currentTIME, deltaT;
float Vx01, Vy01,alpha1;
float Vx02, Vy02, alpha2;

int color, colorCOCH, colorR, colorN, colorT, colorY, colorV, colorB, fond ,typeTOUR; 
int Mat[Nbx][Nby];// l'air de jeu

int bmp;
float Yt;
int tailleTOUR;

int scoreO;
int scoreS;


//----------------------------------------------------------------------------------------------------
//PROGRAMME 

static int panelHandle;
static int mode; 
static int menu;
static int accueil;  
static int credits;

int main (int argc, char *argv[])
{
	//d�claration variables locales
	time_t date;
	srand(time(&date));

				if (InitCVIRTE (0, argv, 0) == 0)	/* Needed if linking in external compiler; harmless otherwise */
					return -1;	/* out of memory */
	
				if ((panelHandle = LoadPanel (0, "Angry birds.uir", PANEL)) < 0)
					return -1;
		
				if ((mode = LoadPanel (0, "Option.uir", MODE)) < 0)
					return -1;
	
				if ((menu = LoadPanel (0, "Menu.uir", MENU)) < 0)
					return -1;
			
				if ((accueil = LoadPanel (0, "Acceuil.uir", ACCUEIL)) < 0)
					return -1;
					
				if ((credits = LoadPanel (0, "credits.uir", CREDITS)) < 0)
					return -1;
		
	//initialisation globales & D�finition taille Canvas & Couleurs & timer
	initialisationVglobales ();
	
	// image de l'oiseau en fonction de l'oiseau
	BitMapTypeOiseau();
	
	DrawArrierePlan ();

	DrawTour ();  // aleatoire
	
	DrawCOCH ();  // aleatoire
	
	AffichageEcran ();
	
	DisplayPanel (accueil);

	
	RunUserInterface ();
	return 0;
}


//--------------------------------------------------------------------------------------------   
//Nos FONCTIONS  
//--------------------------------------------------------------------------------------------   


void DrawBird(int x, int y, int coul)
{
	//SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, coul);
	//SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, coul); 
	//CanvasDrawOval (panelHandle, PANEL_CANVAS, MakeRect(y,x,15,15), VAL_DRAW_FRAME_AND_INTERIOR); */
	CanvasDrawBitmap (panelHandle, PANEL_CANVAS, coul, VAL_ENTIRE_OBJECT, MakeRect(y,x,sizeCASE,sizeCASE) );
	
	//GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\fond.bmp", &color); 
}

//-------------------------------

void Construction(int i, int j, int coul)
{
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_COLOR, coul);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_PEN_FILL_COLOR, coul); 
	CanvasDrawRect (panelHandle, PANEL_CANVAS, MakeRect(j*sizeCASE,i*sizeCASE,sizeCASE,sizeCASE), VAL_DRAW_FRAME_AND_INTERIOR); 
}

//-------------------------------

void Matrice(void)
{
	int i, j;
	for (j=0; j<Nby; j++)
	{
		for (i=0; i<Nbx; i++)
		{
			Construction(i, j, Mat [i][j]);
			
		}
	}
}	 

//-------------------------------

void DrawBirds(int coul)
{
	if (NbrO==1)
	{
		if ((indice[0]!=1) || (posX[0] <= width) || (posY[0] <= height))
			DrawBird(posX[0], posY[0], coul);
	}
	if (NbrO==2)
	{
		if ((indice[0]!=1) || (posX[0] <= width) || (posY[0] <= height))
			DrawBird(posX[0], posY[0], coul);
		if ((indice[1]!=1) || (posX[1] <= width) || (posY[1] <= height))
			DrawBird(posX[1], posY[1], coul);
	}
	if (NbrO==3)
	{
		if ((indice[0]!=1) || (posX[0] <= width) || (posY[0] <= height))
			DrawBird(posX[0], posY[0], coul);
		if ((indice[1]!=1) || (posX[1] <= width) || (posY[1] <= height))
			DrawBird(posX[1], posY[1], coul);
		if ((indice[2]!=1) || (posX[2] <= width) || (posY[2] <= height))
			DrawBird(posX[2], posY[2], coul);
	}
}

//-------------------------------   

int SCOREoiseau(int i, int j, int k) //nombre de boule normal(3pts), Agressive(5) et explosive(10) // 
{
	scoreO=scoreO-i*VALoisN-j*VALoisA-k*VALoisE;
	return scoreO;
}

//-------------------------------  

int SCOREconstruct(int bt, int bs)	  //nombre de b�ton, bois //score brique : b�ton (10) bois(5)  
{
	scoreS=scoreS+bt*VALbet+bs*VALbois;
	return scoreS;
}

//------------------------------- 
//------------------------------- 
//------------------------------- 

void initialisationVglobales (void)
{
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_WIDTH, width);
	SetCtrlAttribute (panelHandle, PANEL_CANVAS, ATTR_HEIGHT, height);
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0); 
	

	vent = 0;
	V0 = 50;
	alpha = 45;
	NbrO = 1;
	trace = 0;
	typeO = 0;
	Niveau = 1;
	score=0;
	scoreO=0;
	scoreS=0;
	
	posX0=0;
	posY0=height-1-15;//- taille du cercle(carr�);
	
	posX[0]=posX0;
	posY[0]=posY0;
	posX[1]=posX0;
	posY[1]=posY0;
	posX[2]=posX0;
	posY[1]=posY0;
	
	debutX=5;
	
	//couleurs 
	colorN = VAL_BLACK;
	colorY = VAL_YELLOW;
	colorR = VAL_RED;
	colorT = VAL_TRANSPARENT;

	colorV = VAL_GREEN;
	colorB = VAL_BLUE;

	//choix du fond
	fond=colorT;
	
	//choix du cochon
	colorCOCH = colorR; 
}

//------------------------------- 

void BitMapTypeOiseau(void)
{
	if (typeO==0)
	{
		GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\bebebird.bmp", &color);  
	}
	if (typeO==1)
	{
		GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\agressivebird.bmp", &color);;		
	}
	if (typeO==2)
	{
		GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\poweredbird.bmp", &color);;	
	}	
}

//------------------------------- 

void DrawArrierePlan (void)
{
	int i, j;
	for (j=0; j<Nby; j++)
	{
		for (i=0; i<Nbx; i++)
		{
				Mat [i][j]=fond;
		}
	}	
}

//------------------------------- 

void DrawTour (void)
{
	int i, j;
	for (i=debutX; i<Nbx; i++)
	{
		if (PileOuFace==1)
		{
			tailleTOUR=Hauteur; 
			if (PileOuFace==1)
			{
				typeTOUR=beton;
			}
			else 
				typeTOUR=bois;
			for (j=0; j<tailleTOUR; j++)
			{
				Mat[i][Nby-j-1]=typeTOUR;
			}
		}
	}	
}

 //-------------------------------   

void DrawCOCH (void)

{
	int i, j, NbrC, NbrCp; 
	int PCx, PCy; 
	NbrCp=0;
	
	Cls(); 
	printf("Nombre de cochons :\n");
	scanf("%d", &NbrC);
	
	while(NbrCp<NbrC) 
	{
        PCy=Hauteur;
        PCx=Largeur;
        if (Mat[PCx][PCy]!=colorCOCH)
        {
            for (i=PCy; i<Nby; i++)
            {
                PCy=i;
				
                if (i+1>(Nby-1))
                {
                    NbrCp++;
                    break;
                } 
                else 
                {
                    if (Mat[PCx][i+1]!=fond)
                    {
                        NbrCp++;
                        break;
                    }
                }
            }
            Mat[PCx][PCy]=colorCOCH;
        }
    }   

}

//------------------------------- 

void AffichageEcran (void)
{
	SetCtrlVal (panelHandle, PANEL_SCORE, score); 
	
	Matrice ();
	DrawBirds(color); 
}

//----------------------------------------------------------------------------------------------------  
// Nos BOUTONS
//---------------------------------------------------------------------------------------------------- 


//----------- FIRE ----------------------------------------------------------------------------- 
int CVICALLBACK ON_FIRE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int n, a, e, k;

	switch (event)
		{
		case EVENT_COMMIT:
		
			// image de l'oiseau en fonction de l'oiseau
				if (typeO==0)
				{
					GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\bebebird.bmp", &color);  
					//color = VAL_RED;		
				}
				if (typeO==1)
				{
					GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\agressivebird.bmp", &color);;		
				}
				if (typeO==2)
				{
					GetBitmapFromFile ("c:\\Users\\Dorian\\Desktop\\Projet info\\poweredbird.bmp", &color);;	
				}
	
			if (typeO==0)
				n=NbrO;
				a=0;
				e=0;
			if (typeO==1)
				n=0;
				a=NbrO;
				e=0;
			if (typeO=2)
				n=0;
				a=0;
				e=NbrO;
			SCOREoiseau(n, a, e);
			
			//calcule de deltaT
			Vx0=V0*cos(alpha*pi/180)-vent;
			Vy0=-V0*sin(alpha*pi/180);
			
			if (alpha>85)
			{
				alpha1=90;
			}else alpha1=alpha+5;
			
			Vx01=V0*cos(alpha1*pi/180);
			Vy01=-V0*sin(alpha1*pi/180);
			
			if (alpha<5)
			{
				alpha2=0;
			}
			alpha2=alpha-5;
			
			Vx02=V0*cos(alpha2*pi/180);
			Vy02=-V0*sin(alpha2*pi/180);
			
			deltaT=5./(V0+1);
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_INTERVAL, deltaT);  
			currentTIME=0;
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
			SetCtrlAttribute (panelHandle, PANEL_Angle, ATTR_DIMMED,1);
	     	SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED,1); 
	      	SetCtrlAttribute (panelHandle, PANEL_FIRE, ATTR_DIMMED,1); 

			break;
		}
	return 0;
}


//-------------- TIMER ------------------------------------------------------------------------- 

int CVICALLBACK ON_TIMER (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
		int i,j,a; 
		int k;
		switch (event)
		{
			case EVENT_TIMER_TICK:
		
				/*if (light==1)
					{
						fond=colorN;
						colorCOCH=colorN;
						colorV=colorN;
						colorB=colorN;
					} */
				//dessine le bon nombre de boule
				if (NbrO==1)
				{
					indice[1]=1;
					indice[2]=1;
				}	
				if (NbrO==2)
				{
					indice[2]=1;
				}
			
			
				currentTIME=currentTIME+deltaT; 
				
				//Trace ou pas ?
				for (k=0; k<=NbrO-1; k++)
				{
					if (trace==0)
						//ca marchait, fait chier
						//CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bmp, VAL_ENTIRE_OBJECT, MakeRect(0, 0, height, width));
						GetBitmapFromFile("fond.bmp", &bmp);
						CanvasDrawBitmap (panelHandle, PANEL_CANVAS, bmp, VAL_ENTIRE_OBJECT, MakeRect(0, 0, height, width));
						Matrice();
					// si marche pas mettre en main
						//CanvasClear(panelHandle, MakeRect(posY[k], posX[k], sizeCASE, sizeCASE));
						
						//=> fond Blanc du Canvas = lumi�re 
						//CanvasClear (panelHandle, PANEL_CANVAS, VAL_ENTIRE_OBJECT);
					
					if (trace==1)
						DrawBirds(VAL_WHITE);
				}
				
				//Equations de mouvement
				posX[0]=Vx0*currentTIME+posX0;
				posY[0]=Vy0*currentTIME+0.5*g*currentTIME*currentTIME+posY0;
        
				posX[1]=Vx01*currentTIME+posX0;
				posY[1]=Vy01*currentTIME+0.5*g*currentTIME*currentTIME+posY0;
	        
				posX[2]=Vx02*currentTIME+posX0;
				posY[2]=Vy02*currentTIME+0.5*g*currentTIME*currentTIME+posY0;
				
				DrawBirds(color);
			
				if (	((posX[0] <= width) || (posY[0] <= height)) ||
					((posX[1] <= width) || (posY[1] <= height)) ||
					((posX[2] <= width) || (posY[2] <= height))	)
				{//verifier la condition pcq bug apres que la premiere boule sorte de la map
					
					for (k=0;k<=NbrO-1;k++)
					{
						i=posX[k]/sizeCASE;
						j=posY[k]/sizeCASE;
						if (Mat[i][j]==fond)  //pb de taille 
							SCOREconstruct(0,0);
						//collision
						if (Mat[i][j]!=fond)
						{
							if (Mat[i][j]==beton)
								SCOREconstruct(1, 0);
							if (Mat[i][j]==bois)
								SCOREconstruct(0, 1);

							for (a=j; a>1; a--)
							{
								Mat[i][j]=Mat[i][j-1];
								Mat[i][0]=fond;
								j--;
								indice[k]=1;
								//*(indice+k)=1;
								//indice[k]=1;
								//*(indice+k)=1;
							}
							Matrice();
						} 
						score=score + scoreS + scoreO;
						SetCtrlVal (panelHandle, PANEL_SCORE, score);
						
					}

				}  //if de condition
				else
				{
					SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0); 
					SetCtrlAttribute (panelHandle, PANEL_Angle, ATTR_DIMMED,0);
					SetCtrlAttribute (panelHandle, PANEL_PUISSANCE, ATTR_DIMMED,0); 
					SetCtrlAttribute (panelHandle, PANEL_FIRE, ATTR_DIMMED,0); 
				}
				
			break;
			
		}  //switch
		return 0;
}


//----------- FERMER FENETRE -----------------------------------------------------------------------------   

// Quitter Acceuil (user interface)
int CVICALLBACK ON_QUITTE (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK ON_QUITTER (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}


//Quitter Cr�dits (hide)
int CVICALLBACK ON_QUITTERCREDITS (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (credits);
			DisplayPanel (accueil);
			break;
	}
	return 0;
}


//Quitter panelHandle (hide)
int CVICALLBACK ON_QUITTERJEUX (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (panelHandle);
			DisplayPanel (accueil);
			break;
	}
	return 0;
}


//Quitter option de tir (hide)
int CVICALLBACK ON_QUITTEROPTION (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  HidePanel (mode);
			  DisplayPanel (panelHandle);  
			break;
		}
	return 0;
}

int CVICALLBACK ON_EXIT (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel (mode);
			DisplayPanel (panelHandle);
			break;
		}
	return 0;
}


//Quitter Menu (hide)
int CVICALLBACK ON_QUITMENU (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  HidePanel (menu);
			  DisplayPanel (panelHandle);
			break;
		}
	return 0;
}

 int CVICALLBACK ON_QUMENU (int panel, int control, int event,
	void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			HidePanel (menu);
			DisplayPanel (panelHandle); 
			break;
		}
	return 0;
}

//----------- Display Panel -----------------------------------------------------------------------------  
 
 int CVICALLBACK ON_CONTROLE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DisplayPanel (mode);
			HidePanel (panelHandle); 
		break;
		}
	return 0;
}
 
 int CVICALLBACK ON_MENU (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			DisplayPanel (menu);
			HidePanel (panelHandle);
			break;
		}
	return 0;
}

 int CVICALLBACK ON_JOUER (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DisplayPanel (panelHandle);
			HidePanel (accueil);
			break;
	}
	return 0;
}

 int CVICALLBACK ON_CREDIT (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (accueil);
			DisplayPanel (credits);
			break;
	}
	return 0;
}

 //----------- Get & Set CtrlVal ----------------------------------------------------------------------------- 

//GetCtrlVal
 int CVICALLBACK ON_NIVEAU (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (accueil, ACCUEIL_NIVEAU, &Niveau);
			break;
	}
	return 0;
}
 
int CVICALLBACK ON_LIGHT (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   int i, j;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (mode, MODE_LUMIERE, &light);
			if (light==1)
							{
								for (j=0; j<Nby; j++)
								{
									for (i=0; i<Nbx; i++)
									{
										fond=colorN;
										colorCOCH = colorN;  
										colorV = colorN;
										colorB = colorN;
									}
								}

							}
			break;
		}
	return 0;
}
 
int CVICALLBACK ON_VENT (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (mode, MODE_VENT, &vent);
			break;
	}
	return 0;
}

int CVICALLBACK ON_TRACE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (mode, MODE_Trace, &trace);
			break;
	}
	return 0;
}

int CVICALLBACK ON_NOMBRE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (mode, MODE_NbreOiseau, &NbrO);
	
			break;
		}
	return 0;
}

int CVICALLBACK ON_AGRESSIVE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		
			GetCtrlVal (mode, MODE_Agressivite, &typeO);
			
			break;
		}
	return 0;
}

int CVICALLBACK ON_PUISSANCE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_PUISSANCE, &V0);

			break;
		}
	return 0;
}

int CVICALLBACK ON_ANGLE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_Angle, &alpha);
			break;
		}
	return 0;
}

//SetCtrlVal

int CVICALLBACK ON_SCORE (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			SetCtrlVal (mode, PANEL_SCORE, score);
			break;
		}
	return 0;
}





