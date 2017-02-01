#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

void affiche_grille(SDL_Surface *ecran,SDL_Surface *grille);

int pause(SDL_Surface *grille,SDL_Surface *surface_case);

void positionne_pion(int *joueur,int tour,SDL_Surface *ecran, SDL_Surface *surface_case);
void enregistre_pion(SDL_Event *event,int *joueur);
void affiche_pion(SDL_Surface *ecran,SDL_Surface *Surface_case);
void joue_ordinateur(SDL_Surface *ecran,int *joueur);
void test_gagnant(SDL_Surface *ecran,SDL_Surface *Surface_case);

#endif // MAIN_H_INCLUDED
