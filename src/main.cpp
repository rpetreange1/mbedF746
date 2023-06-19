#include <mbed.h>
#include <threadLvgl.h>
#include "demos/lv_demos.h"
#include <cstdio>

#define Gauche 1
#define Droite 2
#define Haut 3
#define Bas 4
#define GaucheHaut 5
#define DroiteHaut 6

ThreadLvgl threadLvgl(30);

DigitalIn  btnHaut(PF_10); // Initialisation des 4 boutons du joystick
DigitalIn  btnDroite(PF_8);
DigitalIn  btnBas(PA_8);
DigitalIn  btnGauche(PB_14);

int main() {
    threadLvgl.lock();
    
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE); // Désactive la scrollbar et empêche l'utilisateur de scrollé

    /*Style de la ligne*/
    lv_point_t line_points_taille1[] = {{0,0}, {0, 10}}; // Ligne qui voit sa largeur s'incrémenter le static a été enlevé pour modifier la valeur
    static lv_style_t style_line;
    int pos_x_ligne = 8;  // Position de la ligne a son apparition sur l'écran
    int pos_x_arbre = 220;  // Position de l'arbre a son apparition sur l'écran
    int largeur_arbre = 80; // Largeur de l'arbre au début 
    int pos_X_voiture = 0;
    int pos_x_obs = 0;
    int pos_y_obs = 0;
    int Direction = 0;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 3);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_AMBER));  

    /*Met en place l'image en fond d'écran*/
    LV_IMG_DECLARE(fond);
    lv_obj_t * imgfond = lv_img_create(lv_scr_act());
    lv_img_set_src(imgfond, &fond);
    lv_img_set_angle(imgfond, 900);
    lv_obj_align(imgfond,LV_ALIGN_CENTER,0,0);
    lv_disp_set_bg_image(NULL, &fond);

    //Crée la ligne au milieu l'écran et applique le style
    lv_obj_t * line;
    line = lv_line_create(lv_scr_act());
    lv_line_set_points(line, line_points_taille1, 2);  // Nombres de points pour la ligne
    lv_obj_add_style(line, &style_line, 0);

    /*Met en place l'image de la voiture sur l'écran*/
    LV_IMG_DECLARE(car);
    lv_obj_t * imgcar = lv_img_create(lv_scr_act());
    lv_img_set_src(imgcar, &car);
    lv_img_set_zoom(imgcar, 96);
    lv_img_set_angle(imgcar, 900);
    lv_obj_align(imgcar, LV_ALIGN_CENTER, -150, 0);
    lv_obj_set_size(imgcar, 210, 124);

    /*Met en place l'image de l'arbre à droite sur l'écran*/
    LV_IMG_DECLARE(palm_tree);
    lv_obj_t * imgtree = lv_img_create(lv_scr_act());
    lv_img_set_src(imgtree, &palm_tree);
    lv_img_set_zoom(imgtree, largeur_arbre);
    lv_img_set_angle(imgtree, 900);
    lv_obj_align(imgtree, LV_ALIGN_OUT_LEFT_MID, pos_x_arbre, 130);
    lv_obj_set_size(imgtree, 134, 207);

    /*Met en place l'image de l'obstacle drapeau*/
    LV_IMG_DECLARE(obstacles);
    lv_obj_t * imgobst = lv_img_create(lv_scr_act());
    lv_img_set_src(imgobst, &obstacles);
    lv_img_set_zoom(imgobst, 128);
    lv_img_set_angle(imgobst, 900);
    lv_obj_align(imgobst, LV_ALIGN_CENTER, pos_y_obs, pos_x_obs);
    lv_obj_set_size(imgobst, 63, 51);

    /*Met en place l'image de l'écran d'accueil*/
    LV_IMG_DECLARE(press_start);
    lv_obj_t * imgstart = lv_img_create(lv_scr_act());
    lv_img_set_src(imgstart, &press_start);
    lv_img_set_zoom(imgstart, 256);
    lv_img_set_angle(imgstart, 900);
    lv_obj_align(imgstart, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(imgstart, 266, 33);
    lv_obj_add_flag(imgobst, LV_OBJ_FLAG_HIDDEN);

    threadLvgl.unlock();

    while (1) {
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
        
        threadLvgl.lock();

        lv_obj_align(line, LV_ALIGN_CENTER, pos_x_ligne,0);  // Pour que la ligne bouge 
        lv_obj_align(imgtree, LV_ALIGN_OUT_LEFT_MID, pos_x_arbre, 130);
        lv_obj_align(imgobst, LV_ALIGN_CENTER, pos_x_obs,pos_X_voiture);
        pos_x_ligne = pos_x_ligne -10;  // On fait reculer la ligne de 10
        pos_x_arbre = pos_x_arbre -10;  // On fait reculer la ligne de 10
        pos_x_obs = pos_x_obs -10;  // On fait reculer l'obstacle de 10
        line_points_taille1[1].y += 10;  // La largeur de la ligne augmente de 
        largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
        lv_img_set_zoom(imgtree, largeur_arbre);
        ThisThread::sleep_for(55ms);  // Pour aller plus vite 
        
        if (pos_x_ligne <= -90)
        {
            lv_obj_align(line, LV_ALIGN_CENTER, pos_x_ligne,0);  // Pour que la ligne bouge 
            lv_obj_align(imgtree, LV_ALIGN_OUT_LEFT_MID, pos_x_arbre, 130);
            lv_obj_align(imgobst, LV_ALIGN_CENTER, pos_x_obs,pos_X_voiture-2);
            pos_x_arbre = pos_x_arbre -10;  // On fait reculer la ligne de 10
            pos_x_ligne = pos_x_ligne -10;  // On fait reculer la ligne de 10
            pos_x_obs = pos_x_obs -10;  // On fait reculer l'obstacle de 10
            line_points_taille1[1].y += 10;  // La largeur de la ligne augmente de 10
            largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
            lv_img_set_zoom(imgtree, largeur_arbre);
        }

        if (pos_x_ligne <= -190)
        {
            lv_obj_align(line, LV_ALIGN_CENTER, pos_x_ligne,0);  // Pour que la ligne bouge 
            lv_obj_align(imgtree, LV_ALIGN_OUT_LEFT_MID, pos_x_arbre, 130);
            lv_obj_align(imgobst, LV_ALIGN_CENTER, pos_x_obs,pos_X_voiture-3);
            pos_x_arbre = pos_x_arbre -10;  // On fait reculer l'arbre de 10
            pos_x_ligne = pos_x_ligne -10;  // On fait reculer la ligne de 10
            pos_x_obs = pos_x_obs -10;  // On fait reculer l'obstacle de 10
            line_points_taille1[1].y += 10;  // La largeur de la ligne augmente de 10
            largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
            lv_img_set_zoom(imgtree, largeur_arbre);
        } 

        if (pos_x_ligne <= -270)
        {
            pos_x_ligne = 8;
            pos_x_arbre = 220;
            pos_x_obs = 0;
            largeur_arbre = 80;  // La largeur de l'arbre est remise à sa valeur initiale
            lv_obj_align(line, LV_ALIGN_CENTER, pos_x_ligne,0);  // Pour que la ligne bouge 
            lv_obj_align(imgtree, LV_ALIGN_OUT_LEFT_MID, pos_x_arbre, 130);
            lv_obj_align(imgobst, LV_ALIGN_CENTER, pos_x_obs,pos_X_voiture-5);
            line_points_taille1[1].y = 10;  // La largeur de la ligne retourne à sa valeur initiale
            largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
            lv_img_set_zoom(imgtree, largeur_arbre);
        }

        /*Switch pour l'action de chaque position du joystick */
        switch(Direction) 
        {
            case Gauche:
            pos_X_voiture -= 11;
            lv_obj_align(imgcar, LV_ALIGN_CENTER, -150, pos_X_voiture);
            if(pos_X_voiture <= -85)
                {
                    pos_X_voiture = -85;
                }
            Direction = 0;
            break;

            case Droite:
            pos_X_voiture += 11;
            lv_obj_align(imgcar, LV_ALIGN_CENTER, -150, pos_X_voiture);
            
            if(pos_X_voiture >= 60)
                {
                    pos_X_voiture = 60;
                }
            Direction = 0;
            break;

            case Haut:
            pos_x_arbre = pos_x_arbre -14;  // On fait reculer l'arbre de 10
            pos_x_ligne = pos_x_ligne -14;  // On fait reculer la ligne de 10
            line_points_taille1[1].y += 10;  // La largeur de la ligne retourne à sa valeur initiale
            largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
            Direction = 0;
            break;

            case Bas:
            lv_obj_add_flag(imgstart, LV_OBJ_FLAG_HIDDEN);  // Fait disparaitre le PRESS START
            lv_obj_clear_flag(imgobst, LV_OBJ_FLAG_HIDDEN); // Fait apparaitre le drapeau
            Direction = 0;
            break;

            case GaucheHaut:
            pos_X_voiture -= 11;
            lv_obj_align(imgcar, LV_ALIGN_CENTER, -150, pos_X_voiture);
            
            if(pos_X_voiture <= -85)
                {
                    pos_X_voiture = -85;
                }
            pos_x_arbre = pos_x_arbre -14;  // On fait reculer l'arbre de 10
            pos_x_ligne = pos_x_ligne -14;  // On fait reculer la ligne de 10
            line_points_taille1[1].y += 10;  // La largeur de la ligne retourne à sa valeur initiale
            largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
            Direction = 0;
            break;

            case DroiteHaut:
            pos_X_voiture += 11;
            lv_obj_align(imgcar, LV_ALIGN_CENTER, -150, pos_X_voiture);
            
            if(pos_X_voiture >= 60)
                {
                    pos_X_voiture = 60;
                }
            pos_x_arbre = pos_x_arbre -14;  // On fait reculer l'arbre de 10
            pos_x_ligne = pos_x_ligne -14;  // On fait reculer la ligne de 10
            line_points_taille1[1].y += 10;  // La largeur de la ligne retourne à sa valeur initiale
            largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
            Direction = 0;
            break;

            case 0:
            break;
        }

        /*Série de if pour récupérer chaque position du joystick pour le switch */
        if(btnGauche == 0 )
        {
            Direction = Gauche;

            if(btnHaut == 0)
            {
                Direction = GaucheHaut;
            }

        }

        if(btnHaut == 0)
        {
            Direction = Haut;

            if(btnGauche == 0)
            {
                Direction = GaucheHaut;
            }

        }

        if(btnDroite == 0)
        {
            Direction = Droite;

            if(btnHaut == 0)
        {
            Direction = DroiteHaut;
        }
        }
        
        if(btnBas == 0)
        {
            Direction = Bas;
        }

        threadLvgl.unlock();
    }
}
