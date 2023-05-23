#include <mbed.h>
#include <threadLvgl.h>

#include "demos/lv_demos.h"
#include <cstdio>

// #include "FATFileSystem.h"
// #include "SDMMCBlockDevice.h"

// SDMMCBlockDevice bd;
// FATFileSystem fs("fs");

ThreadLvgl threadLvgl(30);

int main() {
    // put your setup code here, to run once:
    // int error = fs.mount(&bd);
    // printf("Erreur %d\n", error);
    
    // FILE *fichier;
    // char data[100];

    // printf("fopen\n");
    // fichier = fopen("/fs/essai.txt", "r");
    // if (!fichier) {
    //     printf("Pas de fichier essai.txt\n");
    // } else {
    //     fgets(data, 100, fichier);
    //     printf("%s", data);
    //     fclose(fichier);
    // }

    // printf("fopen write\n");
    // fichier = fopen("/fs/test1.txt", "w");
    // if (!fichier) {
    //     printf("Pas d'ouverture en écriture\n");
    // } else {
    //     printf("Ecriture coucou\n");
    //     fprintf(fichier, "Coucou\nBonjour\n");
    //     fclose(fichier);
    // }

    // lv_fs_stdio_init();

    threadLvgl.lock();
    // lv_obj_t *btn = lv_btn_create(lv_scr_act());
    // lv_obj_t *label = lv_label_create(btn);
    // lv_label_set_text(label, "LPRO Mecse à Cachan 2023");
    // lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -10);
    // lv_obj_t *img1 = lv_img_create(lv_scr_act());
    // lv_img_set_src(img1, "A:/minion.bin");
    // lv_obj_align(img1, LV_ALIGN_TOP_MID, 0, 10);
    // lv_obj_set_size(img1, 200, 200);
    lv_demo_widgets();
    // lv_demo_benchmark();
    threadLvgl.unlock();

    // ThisThread::sleep_for(5s);

    // threadLvgl.lock();
    // lv_obj_t *btn1 = lv_btn_create(lv_scr_act());
    // lv_obj_t *label1 = lv_label_create(btn1);
    // lv_label_set_text(label1, "IUT de Cachan");
    // lv_obj_align(btn1, LV_ALIGN_TOP_MID, 0, 10);
    // threadLvgl.unlock();

    while (1) {
        // put your main code here, to run repeatedly:
        ThisThread::sleep_for(10ms);
    }
}