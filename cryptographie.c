#include "AES_128_CBC.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//fonction de cryptage
char *crypt(char *text,int n){
    //declaration de variables
    char *crypted;
    int i=0, diff_low, diff_up;
    //allocation de mémoire
    crypted = (char *)malloc(sizeof(char) * (strlen(text)+1));
    if (crypted == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }
    //instructions
    while (text[i] != '\0'){
        if ('a' <= text[i] && text[i] <= 'z'){
            diff_low = 'z' - text[i];
            if (diff_low >= n)
                crypted[i] = text[i] + n;
            else
                crypted[i] = 'a' + n - diff_low - 1;
        }
        else if ('A' <= text[i] && text[i] <= 'Z'){
            diff_up = 'Z' - text[i];
            if(diff_up >= n)
                crypted[i] = text[i] + n;
            else
                crypted[i] = 'A' + n - diff_up - 1;
        }
        else
            crypted[i] = text[i];
        i++;
    }
    crypted[i] = '\0';
    return crypted;
}

//fonction de decryptage
char *decrypt(char *text, int n) {
    //declaration de variables
    char *decrypted;
    int i = 0, diff_low, diff_up;
    //allocation de mémoire
    decrypted = (char *)malloc(sizeof(char) * (strlen(text) + 1));
    if (decrypted == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }
    //instructions
    while (text[i] != '\0') {
        if ('a' <= text[i] && text[i] <= 'z') {
            diff_low = text[i] - 'a';
            if (diff_low >= n)
                decrypted[i] = text[i] - n;
            else 
                decrypted[i] = 'z' - (n - diff_low - 1);
        } 
        else if ('A' <= text[i] && text[i] <= 'Z') {
            diff_up = text[i] - 'A';
            if (diff_up >= n)
                decrypted[i] = text[i] - n;
            else
                decrypted[i] = 'Z' - (n - diff_up - 1);
        } 
        else
            decrypted[i] = text[i];
        i++;
    }
    decrypted[i] = '\0';
    return decrypted;
}

//programme principal
int main(){
    //déclaration de variables
    char text[10000];
    int n;
    char c;
    //saisie du text
    printf("Saisir le code a crypter/decrypter : ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';
    //saisie de la clé 
    do{
        printf("Saisir la cle : ");
        scanf("%d",&n);
    }while (!(0<n<26));
    //choix de l'option (cryptage/decryptage)
    char *crypted = crypt(text,n);
    char *decrypted = decrypt(text,n);
    printf("Choisir c pour crypter d pour decrypter : ");
    scanf("%s",&c);
    //cryptage du text saisi
    if (c == 'c' || c == 'C'){
        if (crypted != NULL){
            printf("%s",crypted);
            free(crypted);
        }
    }
    //décryptage du text saisi
    else if (c == 'd' || c == 'D'){
        if (decrypted != NULL){
            printf("%s",decrypted);
        free(decrypted);
    }
    }
    return 0;
}