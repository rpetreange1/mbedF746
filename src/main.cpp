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
/*
static void event_cb(lv_event_t * e)
    {
        lv_obj_t * obj = lv_event_get_current_target(e);
        LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
    }

    void msgbox_pause(void)
    {
        static const char * btns[] = {"Apply", "Close", ""};

        lv_obj_t * mbox1 = lv_msgbox_create(NULL, "JE VEUX JOUER", btns, true);
        lv_obj_add_event_cb(mbox1, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
        lv_obj_center(mbox1);
    } */
/*
// Déclare les 3 images pour l'animation de la voiture 
    LV_IMG_DECLARE(voiture1)
    LV_IMG_DECLARE(voiture2)
    LV_IMG_DECLARE(voiture3)
    
// Met les 3 images dans un tableau pour pouvoir les utiliser de façon plus dynamique
static const lv_img_dsc_t * anim_imgs[3] = {
    &voiture1,
    &voiture2,
    &voiture3,
    };

// Fonction pour l'animation de la voiture 
void lv_anim_voiture(void)
{
    lv_obj_t * animvoit = lv_animimg_create(lv_scr_act());
    lv_obj_center(animvoit);
    lv_animimg_set_src(animvoit, const_cast<lv_img_dsc_t **>(anim_imgs), 3);
    lv_img_set_zoom(animvoit, 96);
    lv_img_set_angle(animvoit, 900);
    lv_obj_align(animvoit, LV_ALIGN_CENTER, -150, 0);
    lv_obj_set_size(animvoit, 210, 124);
    lv_animimg_set_duration(animvoit, 500);
    lv_animimg_set_repeat_count(animvoit, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(animvoit);
}
*/
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

    threadLvgl.unlock();

    while (1) {
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
        
        threadLvgl.lock();

        lv_obj_align(line, LV_ALIGN_CENTER, pos_x_ligne,0);  // Pour que la ligne bouge 
        lv_obj_align(imgtree, LV_ALIGN_OUT_LEFT_MID, pos_x_arbre, 130);
        pos_x_ligne = pos_x_ligne -10;  // On fait reculer la ligne de 10
        pos_x_arbre = pos_x_arbre -10;  // On fait reculer la ligne de 10
        line_points_taille1[1].y += 10;  // La largeur de la ligne augmente de 
        largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
        lv_img_set_zoom(imgtree, largeur_arbre);
        ThisThread::sleep_for(55ms);  // Pour aller plus vite 
        
        if (pos_x_ligne <= -90)
        {
            lv_obj_align(line, LV_ALIGN_CENTER, pos_x_ligne,0);  // Pour que la ligne bouge 
            lv_obj_align(imgtree, LV_ALIGN_OUT_LEFT_MID, pos_x_arbre, 130);
            pos_x_arbre = pos_x_arbre -10;  // On fait reculer la ligne de 10
            pos_x_ligne = pos_x_ligne -10;  // On fait reculer la ligne de 10
            line_points_taille1[1].y += 10;  // La largeur de la ligne augmente de 10
            largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
            lv_img_set_zoom(imgtree, largeur_arbre);
        }

        if (pos_x_ligne <= -190)
        {
            lv_obj_align(line, LV_ALIGN_CENTER, pos_x_ligne,0);  // Pour que la ligne bouge 
            lv_obj_align(imgtree, LV_ALIGN_OUT_LEFT_MID, pos_x_arbre, 130);
            pos_x_arbre = pos_x_arbre -10;  // On fait reculer l'arbre de 10
            pos_x_ligne = pos_x_ligne -10;  // On fait reculer la ligne de 10
            line_points_taille1[1].y += 10;  // La largeur de la ligne augmente de 10
            largeur_arbre += 10;  // La largeur de l'arbre augmente de 10
            lv_img_set_zoom(imgtree, largeur_arbre);
        } 

        if (pos_x_ligne <= -270)
        {
            pos_x_ligne = 8;
            pos_x_arbre = 220;
            largeur_arbre = 80;  // La largeur de l'arbre est remise à sa valeur initiale
            lv_obj_align(line, LV_ALIGN_CENTER, pos_x_ligne,0);  // Pour que la ligne bouge 
            lv_obj_align(imgtree, LV_ALIGN_OUT_LEFT_MID, pos_x_arbre, 130);
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
            //msgbox_pause();

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
