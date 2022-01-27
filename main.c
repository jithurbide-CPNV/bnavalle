#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOMBRE_SCORE_MAX 10
#define MAX_CHAR_NAME 50
// structure permetant de stocker le score ainsi que le nom
typedef struct {
    int score;
    char name[MAX_CHAR_NAME] ;
} t_score;
// tableau pour affichier 10 résultats
t_score scores[] = {
        { 0,"None"},
        { 0,"None"},
        { 0,"None"},
        { 0,"None"},
        { 0,"None"},
        { 0,"None"},
        { 0,"None"},
        { 0,"None"},
        { 0,"None"},
        { 0,"None"}
};

void add_user(char name[MAX_CHAR_NAME] , int score) {
    int i = 0;
    int old_score = 0;
    char old_name[MAX_CHAR_NAME];

    while (scores[i].score > score) {
        i++;
    }
    // sauvegarde des informations à la position i
    strncpy(old_name, scores[i].name, MAX_CHAR_NAME);
    old_score = scores[i].score;
    printf("Backup : %s %d\n",old_name, old_score);

    // copie des nouvelles valeurs à la position i
    strncpy(scores[i].name, name, MAX_CHAR_NAME);
    scores[i].score = score;
    i++;
    // Supprime la dernière valeur et décale toute les valeurs
    // en dessous du nouveau score
    for(int y =NOMBRE_SCORE_MAX-1; y>i;y-- ){
        scores[y].score= scores[y-1].score;
        strncpy(scores[y].name, scores[y-1].name, MAX_CHAR_NAME);
    }
    // restore la valeur sauvegardée
    scores[i].score = old_score;
    strncpy(scores[i].name, old_name, MAX_CHAR_NAME);
}

// Ecriture de la structure dans un fichier
void write_file() {
    FILE *fp;
    fp = fopen("resultats.txt", "w");

    if(fp == NULL) {
        printf("Impossible d'écrire le fichier\n");
        exit(1);
    }
    fwrite(&scores,sizeof( t_score),NOMBRE_SCORE_MAX,fp);

    fclose(fp);
}
// lecture du fichier et restoration du tableau
void read_file(){
    FILE *fp;
    fp = fopen("resultats.txt", "r");

    if(fp != NULL) {
        printf("Will read file\n");
        fread(&scores, sizeof( t_score), NOMBRE_SCORE_MAX, fp);
        fclose(fp);
        printf("end of read file\n");
    }

}

// affiche le tableau à l'écran de information/debug
void print_tab() {
    for (int i = 0; i < NOMBRE_SCORE_MAX; i++) {
        //fprintf(fp, "Name: %s\t score: %d \n", scores[i].name, scores[i].score);
        printf ("Name : %s score : %d \n",scores[i].name, scores[i].score);
    }
}
int main(int argc, char *argv[]) {

    int temp_score = -1;
    char temp_name[MAX_CHAR_NAME] ;
    int quitter = 0;

    while (quitter == 0) {
        read_file();
        print_tab();
        fflush(stdin);
        printf("Merci de donner votre nom : ");
        scanf("%s",temp_name);
        printf("Merci de donner un nouveau score : ");
        scanf("%d",&temp_score);
        add_user(temp_name,temp_score);
        print_tab();
        write_file();
        printf("\nPour quitter taper 1\n");
        scanf("%d",&quitter);
    }


    return 0;
}