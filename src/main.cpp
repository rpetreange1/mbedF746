#include <mbed.h>
#include <threadLvgl.h>

#include "demos/lv_demos.h"
#include <cstdio>

ThreadLvgl threadLvgl(30);

DigitalIn  btnGauche(PF_10); // Initialisation des 4 boutons 
DigitalIn  btnDroite(PF_8);
DigitalIn  btnHaut(PA_8);
DigitalIn  btnBas(PB_14);
/*
// Déclare les 3 images pour l'animation de la voiture 
    LV_IMG_DECLARE(animvoiture1)
    LV_IMG_DECLARE(animvoiture2)
    LV_IMG_DECLARE(animvoiture3)
    
// Met les 3 images dans un tableau pour pouvoir les utilsier de façon plus dynamique
static const lv_img_dsc_t * anim_imgs[3] = {
    &animvoiture1,
    &animvoiture2,
    &animvoiture3,
    };
// Fonction pour l'animation de la voiture 
void lv_anim_voiture(void)
{
    lv_obj_t * animvoit = lv_animimg_create(lv_scr_act());
    lv_obj_center(animvoit);
    //lv_animimg_set_src(animvoit, (const void **) anim_imgs, 3);
    lv_animimg_set_duration(animvoit, 500);
    lv_animimg_set_repeat_count(animvoit, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(animvoit);
}
*/

int main() {
    threadLvgl.lock();
    
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE); // Désactive la scrollbar et empêche l'utilisateur de scrollé
    
    /*Style de la ligne*/
    static lv_point_t line_points[] = {{0,0}, {490, 0}}; // Coordonnées des 2 points pour faire une grande ligne
    static lv_point_t line_points_small[] = {{0,0}, {95, 0}}; // Coordonnées des 2 points pour faire une petite ligne
    static lv_style_t style_line;
    int pos_x_ligne1 = 200;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 8);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_BLUE_GREY));
    //lv_style_set_line_rounded(&style_line, false); // Donner un style arrondi à la ligne

/*Crée la ligne1 en haut de l'écran et applique le style*/
    lv_obj_t * line1;
    line1 = lv_line_create(lv_scr_act());
    lv_line_set_points(line1, line_points, 2);  // Nombres de points pour la ligne
    lv_obj_add_style(line1, &style_line, 0);
    lv_obj_align(line1, LV_ALIGN_TOP_MID, 0,30);

    /*Crée la ligne2 au milieu l'écran et applique le style*/
    lv_obj_t * line2;
    line2 = lv_line_create(lv_scr_act());
    lv_line_set_points(line2, line_points_small, 2);  // Nombres de points pour la ligne
    lv_obj_add_style(line2, &style_line, 0);

    /*Crée la ligne3 en bas de l'écran et applique le style*/
    lv_obj_t * line3;
    line3 = lv_line_create(lv_scr_act());
    lv_line_set_points(line3, line_points, 2);  // Nombres de points pour la ligne
    lv_obj_add_style(line3, &style_line, 0);
    lv_obj_align(line3, LV_ALIGN_BOTTOM_MID, 0,-20);

    LV_IMG_DECLARE(car);
    lv_obj_t * imgcar = lv_img_create(lv_scr_act());
    lv_img_set_src(imgcar, &car);
    lv_obj_align(imgcar, LV_ALIGN_CENTER, 0, -20);
    lv_obj_set_size(imgcar, 80, 70);

    threadLvgl.unlock();

    while (1) {
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
        
        threadLvgl.lock();
        //lv_anim_voiture();

        if (pos_x_ligne1 < -290)
        {
            pos_x_ligne1 = 290;
            lv_obj_align(line2, LV_ALIGN_CENTER, pos_x_ligne1,10);
        }

        else
        {
            lv_obj_align(line2, LV_ALIGN_CENTER, pos_x_ligne1,10);
            pos_x_ligne1 = pos_x_ligne1 - 8;
        }
        
        threadLvgl.unlock();
    }
}
