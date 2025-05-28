#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to count the occurrences of a character (case insensitive)
int NbOccurence( char *text, char c){
    int cp=0;
    for (int i=0; text[i]!='\0' ; i++){
        if (tolower(text[i])==c){
            cp+=1;
        }
    }
    return cp;
}
int main() {
    char *text = NULL;
    int taille = 0;
    int capacite = 10;
    char c;

    // Dynamically allocate memory for the text
    text = (char *)malloc(capacite * sizeof(char));
    if (text == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        return 1;
    }

    printf("Entrez votre texte :\n");

    // Read input text from the user until newline or EOF is encountered
    while ((c = getchar()) != '\n' && c != EOF) {
        text[taille++] = c; // Store the character in the text
        // If text exceeds current capacity, reallocate memory
        if (taille >= capacite - 1) {
            capacite += 10;
            text = (char *)realloc(text, capacite * sizeof(char));
            if (text == NULL) {
                printf("Erreur d'allocation de mémoire.\n");
                return 1;
            }
        }
 
    }

    text[taille] = '\0';
 
    int n=strlen(text);
    int t=0;
    // Count alphabetic characters in the text
    for (int i=0; i<n ; i++){
        if (isalpha(text[i])){
            t++;
        }
    }
    // Cryptoanalysis of the text
    if (n!=0 || t!=0){

         // Array to hold unique alphabetic characters
        char *abc ;
        abc = (char*)malloc(sizeof(char)*26);
        if (abc == NULL) {
            printf("Erreur d'allocation de mémoire pour abc.\n");
            return 1;
            }

        // Array to store probability for each character
        double *prob ;
        prob = (double*)malloc(sizeof(double)*26);
        if (prob == NULL){
            printf("Erreue d'alloction de mémoire pour prob");
            return 1;
        }

        // Array to store the occurrence count for each character
        int *Occ ;
        Occ = (int*)malloc(sizeof(int)*26);
        if (Occ == NULL){
            printf("Erreue d'alloction de mémoire pour Occ");
            return 1;
        }
        int occuredonce[26] = {0}; // Array to track if a character has already been processed
        int symboleindex = 0;
        for (int i=0; i<n ; i++){ 
            if (isalpha(text[i])){
                char car = tolower(text[i]);
                int index = car - 'a';
                if (occuredonce[index]==0){ // Process character if it's not already done
                    int NbOcc= NbOccurence(text, car);
                    double proba = (double)NbOcc/t ;
                    abc[symboleindex] = car;
                    prob[symboleindex] = proba;
                    Occ[symboleindex] = NbOcc;
                    printf("Symbole %d : %c NbOccurence: %d Proba: %.4lf \n" ,symboleindex,car,NbOcc,proba);
                    occuredonce[index]=1; // Mark the character as processed
                    symboleindex++;
                }
            }    
        }
        // Sort the characters by frequency in descending order
        int test;
        do{
            test =1;
            for(int i=0 ;i<symboleindex-1; i++){
                if(Occ[i]<Occ[i+1]){
                    double a = prob[i];
                    prob[i]=prob[i+1];
                    prob[i+1]=a;
                    char b = abc[i];
                    abc[i]=abc[i+1];
                    abc[i+1]=b;
                    int c = Occ[i];
                    Occ[i]=Occ[i+1];
                    Occ[i+1]=c;
                    test=0;
                    }
            }
        }while(test ==0);

        printf("\nSymboles triés par fréquence décroissante :\n");
        for (int i = 0; i < symboleindex; i++) {
            printf("Symbole %d : %c NbOccurence: %d Proba: %.4lf\n" ,i,abc[i],Occ[i],prob[i]);
        }

        // 
        char tab[4] = {'e' , 's', 'a', 'n'};
        for (int i=0; i<4; i++){
            printf("\nSymbole %d : %c Proba: %.4lf Decalage avec %c",i , abc[i],prob[i] ,tab[i]);
        }
        free(abc);
        free(prob);
        free(Occ);
    }
    free(text);
    return 0;
}