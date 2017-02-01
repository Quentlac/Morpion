#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "main.h"


    int case_grille[][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,0}
    };


int main(int argc, char *argv[]){
    int continuer = 1;
    int joueur = 1;
    int tour = 1;


    SDL_Surface *surface_case;




    SDL_Surface *ecran = NULL;
    SDL_Surface *grille = NULL;


    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Le jeu du Morpion",NULL);
    ecran = SDL_SetVideoMode(350,350,32,SDL_HWSURFACE | SDL_DOUBLEBUF);//creation de la surface principale

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
    if(ecran == NULL){
        fprintf(stderr,"Erreur lors de la creation de la surface ecran: %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    while(continuer){
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));//efface l'ecran
        affiche_grille(ecran,grille);
        affiche_pion(ecran,surface_case);
        positionne_pion(&joueur,tour,ecran,surface_case);
        test_gagnant(ecran,surface_case);

        if(joueur == 2){
            joue_ordinateur(ecran,&joueur);
        }
        test_gagnant(ecran,surface_case);
        SDL_Flip(ecran);
        continuer = pause(grille,surface_case);

    }

    SDL_FreeSurface(grille);
    SDL_Quit();

}


void affiche_grille(SDL_Surface *ecran,SDL_Surface *grille){

    SDL_Rect pos_grille;

    pos_grille.x = 60;
    pos_grille.y = 50;

    grille = SDL_LoadBMP("grille.bmp");
    SDL_SetAlpha(grille,SDL_SRCALPHA,128);
    SDL_BlitSurface(grille,NULL,ecran,&pos_grille);


}

void positionne_pion(int *joueur,int tour,SDL_Surface *ecran, SDL_Surface *surface_case){
    SDL_Event event;
    SDL_Rect position;

    surface_case = SDL_LoadBMP("rond.bmp");



    if(surface_case == NULL){
        fprintf(stderr,"ERREUR lors de la creation de surface_case: %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WaitEvent(&event);
    if(event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN){
        enregistre_pion(&event,joueur);

    }
    position.x = event.button.x;
    position.y = event.button.y;
    SDL_SetColorKey(surface_case,SDL_SRCCOLORKEY,SDL_MapRGB(surface_case->format,255,255,255));
    SDL_BlitSurface(surface_case,NULL,ecran,&position);





}

void enregistre_pion(SDL_Event *event,int *joueur){
int x,y;
if((*event).button.x > 60 && (*event).button.x < 135){
    x = 0;
}

if((*event).button.x > 135 && (*event).button.x < 210){
    x = 1;
}

if((*event).button.x > 210 && (*event).button.x < 285){
    x = 2;
}


if((*event).button.y > 50 && (*event).button.y < 125){
    y = 0;
}

if((*event).button.y > 125 && (*event).button.y < 200){
    y = 1;
}

if((*event).button.y > 200 && (*event).button.y < 275){
    y = 2;
}

if(case_grille[y][x] == 0){

    case_grille[y][x] = 1;
    *joueur = 2;


}




}


int pause(SDL_Surface *grille,SDL_Surface *surface_case){
    SDL_Event event;
    int continuer = 1;

    SDL_WaitEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            continuer = 0;
            SDL_FreeSurface(surface_case);
            SDL_FreeSurface(grille);
            SDL_Quit();
            break;

        }
    return continuer;

}
void affiche_pion(SDL_Surface *ecran,SDL_Surface *Surface_case){
    int x;
    int y;
    for(y = 0;y < 3; y++){
        for(x = 0;x<3;x++){
            if(case_grille[y][x] != 0)
            {   SDL_Surface *Pion;

                if(case_grille[y][x] == 1){
                    Pion = SDL_LoadBMP("rond.bmp");
                }
                if(case_grille[y][x] == -1){
                    Pion = SDL_LoadBMP("croix.bmp");
                }


                SDL_Rect Pos_pion;

                switch(x){
                case 0:
                    Pos_pion.x = 62;
                    break;
                case 1:
                    Pos_pion.x = 137;
                    break;
                case 2:
                    Pos_pion.x = 209;
                    break;
                }

                switch(y){
                case 0:
                    Pos_pion.y = 53;
                    break;
                case 1:
                    Pos_pion.y = 126;
                    break;
                case 2:
                    Pos_pion.y = 204;
                    break;
                }
                SDL_SetColorKey(Pion,SDL_SRCCOLORKEY,SDL_MapRGB(Pion->format,255,255,255));
                SDL_BlitSurface(Pion,NULL,ecran,&Pos_pion);
                SDL_FreeSurface(Pion);

            }
        }


    }


}

void joue_ordinateur(SDL_Surface *ecran,int *joueur){
int joue = 0;
int ligne = 0;
int x = 0;
int y = 0;


//il test si il peut gagner
for(x = 0;x < 3;x++){
    ligne += case_grille[0][x];

}
if(ligne == -2){

    for(x = 0;x < 3;x++){
        if(case_grille[0][x] == 0){
            case_grille[0][x] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 2eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[1][x];

}
if(ligne == -2){
    for(x = 0;x < 3;x++){
        if(case_grille[1][x] == 0){
            case_grille[1][x] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 3eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[2][x];

}
if(ligne == -2){
    for(x = 0;x < 3;x++){
        if(case_grille[2][x] == 0){
            case_grille[2][x] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la premiere ligne vertical


ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][0];

}
if(ligne == -2){
    for(y = 0;y < 3;y++){
        if(case_grille[y][0] == 0){
            case_grille[y][0] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 2eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][1];

}
if(ligne == -2){
    for(y = 0;y < 3;y++){
        if(case_grille[y][1] == 0){
            case_grille[y][1] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 3eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][2];

}
if(ligne == -2){
    for(y = 0;y < 3;y++){
        if(case_grille[y][2] == 0){
            case_grille[y][2] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 1ere ligne diagonale
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][y];

}
if(ligne == -2){
    for(y = 0;y < 3;y++){
        if(case_grille[y][y] == 0){
            case_grille[y][y] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 2eme ligne diagonale
ligne = 0;
x=0;
for(y = 2;y > -1;y--){
    ligne += case_grille[y][x];

    x++;
}

if(ligne == -2){
    x=0;
    for(y = 2;y > -1;y--){
        if(case_grille[y][x] == 0){
            case_grille[y][x] = -1;
            *joueur = 1;
            return;
        }
        x++;
    }

}


ligne = 0;
//il se defend
//contre mesure de la strategy 1

if(case_grille[0][1] == 1 && case_grille[1][0] == 1 && case_grille[0][0] == 0){
    case_grille[0][0] = -1;
    *joueur = 1;
    return;
}

if(case_grille[0][1] == 1 && case_grille[1][2] == 1 && case_grille[0][2] == 0){
    case_grille[0][2] = -1;
    *joueur = 1;
    return;
}

if(case_grille[2][1] == 1 && case_grille[1][0] == 1 && case_grille[2][0] == 0){
    case_grille[2][0] = -1;
    *joueur = 1;
    return;
}

if(case_grille[2][1] == 1 && case_grille[1][2] == 1 && case_grille[2][2] == 0){
    case_grille[2][2] = -1;
    *joueur = 1;
    return;
}

//analyse de la premire ligne horizontal
for(x = 0;x < 3;x++){
    ligne += case_grille[0][x];

}
if(ligne == 2){
    for(x = 0;x < 3;x++){
        if(case_grille[0][x] == 0){
            case_grille[0][x] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 2eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[1][x];

}
if(ligne == 2){
    for(x = 0;x < 3;x++){
        if(case_grille[1][x] == 0){
            case_grille[1][x] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 3eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[2][x];

}
if(ligne == 2){
    for(x = 0;x < 3;x++){
        if(case_grille[2][x] == 0){
            case_grille[2][x] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la premiere ligne vertical


ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][0];

}
if(ligne == 2){
    for(y = 0;y < 3;y++){
        if(case_grille[y][0] == 0){
            case_grille[y][0] = -1;
            *joueur = 1;
            return;
        }

    }

}
//analyse de la 2eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][1];

}
if(ligne == 2){
    for(y = 0;y < 3;y++){
        if(case_grille[y][1] == 0){
            case_grille[y][1] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 3eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][2];

}
if(ligne == 2){
    for(y = 0;y < 3;y++){
        if(case_grille[y][2] == 0){
            case_grille[y][2] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 1ere ligne diagonale
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][y];

}
if(ligne == 2){
    for(y = 0;y < 3;y++){
        if(case_grille[y][y] == 0){
            case_grille[y][y] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 2eme ligne diagonale
ligne = 0;
x=0;
for(y = 2;y > -1;y--){
    ligne += case_grille[y][x];

    x++;
}

if(ligne == 2){
    x=0;
    for(y = 2;y > -1;y--){
        if(case_grille[y][x] == 0){
            case_grille[y][x] = -1;
            *joueur = 1;
            return;
        }
        x++;
    }

}

//attaque

//test si la case du milieur est prise
if(case_grille[1][1] == 0){
    case_grille[1][1] = -1;
    *joueur = 1;
    return;

}
else{
//strategy 1
if(case_grille[0][1] == 0){
    case_grille[0][1] = -1;
    *joueur = 1;
    return;

}

if(case_grille[0][1] == -1 && case_grille[1][0] == 0){
    case_grille[1][0] = -1;
    *joueur = 1;
    return;
}

if(case_grille[0][1] == -1 && case_grille[1][0] == -1 && case_grille[0][0] == 0){
    case_grille[0][0] = -1;
    *joueur = 1;
    return;
}

if(case_grille[0][1] == -1 && case_grille[1][0] == -1 && case_grille[1][2] == 0){
    case_grille[1][2] = -1;
    *joueur = 1;
    return;
}

if(case_grille[0][1] == -1 && case_grille[1][2] == -1 && case_grille[0][2] == 0){
    case_grille[0][2] = -1;
    *joueur = 1;
    return;
}


//end strategy 1
}




//en cas ou aucune strategie marche
//trouve une ligne + petit que 0
ligne = 0;
//analyse de la premire ligne horizontal
for(x = 0;x < 3;x++){
    ligne += case_grille[0][x];

}
if(ligne <= 0){
    for(x = 0;x < 3;x++){
        if(case_grille[0][x] == 0){
            case_grille[0][x] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 2eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[1][x];

}
if(ligne <= 0){
    for(x = 0;x < 3;x++){
        if(case_grille[1][x] == 0){
            case_grille[1][x] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 3eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[2][x];

}
if(ligne <= 0){
    for(x = 0;x < 3;x++){
        if(case_grille[2][x] == 0){
            case_grille[2][x] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la premiere ligne vertical


ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][0];

}
if(ligne <= 0){
    for(y = 0;y < 3;y++){
        if(case_grille[y][0] == 0){
            case_grille[y][0] = -1;
            *joueur = 1;
            return;
        }

    }

}
//analyse de la 2eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][1];

}
if(ligne <= 0){
    for(y = 0;y < 3;y++){
        if(case_grille[y][1] == 0){
            case_grille[y][1] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 3eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][2];

}
if(ligne <= 0){
    for(y = 0;y < 3;y++){
        if(case_grille[y][2] == 0){
            case_grille[y][2] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 1ere ligne diagonale
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][y];

}
if(ligne <= 0){
    for(y = 0;y < 3;y++){
        if(case_grille[y][y] == 0){
            case_grille[y][y] = -1;
            *joueur = 1;
            return;
        }

    }

}

//analyse la 2eme ligne diagonale
ligne = 0;
x=0;
for(y = 2;y > -1;y--){
    ligne += case_grille[y][x];

    x++;
}

if(ligne <= 0){
    x=0;
    for(y = 2;y > -1;y--){
        if(case_grille[y][x] == 0){
            case_grille[y][x] = -1;
            *joueur = 1;
            return;
        }
        x++;
    }

}

}



void test_gagnant(SDL_Surface *ecran,SDL_Surface *Surface_case){

SDL_Surface *texte;
SDL_Rect pos_text;

pos_text.x = 0;
pos_text.y = 0;

int ligne = 0;
int x = 0;
int y = 0;


//test si l'ordi gagne
for(x = 0;x < 3;x++){
    ligne += case_grille[0][x];

}
if(ligne == -3){

texte = SDL_LoadBMP("game_over.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}
}

//analyse la 2eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[1][x];

}
if(ligne == -3){

texte = SDL_LoadBMP("game_over.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}
}

//analyse la 3eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[2][x];

}
if(ligne == -3){

texte = SDL_LoadBMP("game_over.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}
}

//analyse la premiere ligne vertical


ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][0];

}
if(ligne == -3){

texte = SDL_LoadBMP("game_over.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}
}

//analyse la 2eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][1];

}
if(ligne == -3){

texte = SDL_LoadBMP("game_over.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

//analyse la 3eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][2];

}
if(ligne == -3){

texte = SDL_LoadBMP("game_over.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

//analyse la 1ere ligne diagonale
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][y];

}
if(ligne == -3){

texte = SDL_LoadBMP("game_over.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

//analyse la 2eme ligne diagonale
ligne = 0;
x=0;
for(y = 2;y > -1;y--){
    ligne += case_grille[y][x];

    x++;
}

if(ligne == -3){

texte = SDL_LoadBMP("game_over.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

ligne = 0;
//test si le joueur gagne

for(x = 0;x < 3;x++){
    ligne += case_grille[0][x];

}
if(ligne == 3){

texte = SDL_LoadBMP("you_win.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

//analyse la 2eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[1][x];

}
if(ligne == 3){

texte = SDL_LoadBMP("you_win.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

//analyse la 3eme ligne
ligne = 0;
for(x = 0;x < 3;x++){
    ligne += case_grille[2][x];

}
if(ligne == 3){

texte = SDL_LoadBMP("you_win.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

//analyse la premiere ligne vertical


ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][0];

}
if(ligne == 3){

texte = SDL_LoadBMP("you_win.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

//analyse la 2eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][1];

}
if(ligne == 3){

texte = SDL_LoadBMP("you_win.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

//analyse la 3eme ligne
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][2];

}
if(ligne == 3){

texte = SDL_LoadBMP("you_win.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}}

//analyse la 1ere ligne diagonale
ligne = 0;
for(y = 0;y < 3;y++){
    ligne += case_grille[y][y];

}
if(ligne == 3){

texte = SDL_LoadBMP("you_win.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}
}

//analyse la 2eme ligne diagonale
ligne = 0;
x=0;
for(y = 2;y > -1;y--){
    ligne += case_grille[y][x];

    x++;
}

if(ligne == 3){

texte = SDL_LoadBMP("you_win.bmp");
SDL_SetColorKey(texte,SDL_SRCCOLORKEY,SDL_MapRGB(texte->format,255,255,255));
affiche_pion(ecran,Surface_case);
SDL_BlitSurface(texte,NULL,ecran,&pos_text);
SDL_Flip(ecran);
int continuer = 1;
while(continuer){
    continuer = pause(Surface_case,NULL);
}
}





}




