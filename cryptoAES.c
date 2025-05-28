#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "AES_128_CBC.h"

// Taille d'un bloc AES et d'une clé AES
#define BLOCK_SIZE 16
#define KEY_SIZE 16

// Fonction pour ajouter le padding PKCS#7
uint8_t* add_padding(const char* input, int* padded_length) {
    int input_length = strlen(input);
    int padding_needed = BLOCK_SIZE - (input_length % BLOCK_SIZE);
    *padded_length = input_length + padding_needed;
    
    // Allouer un nouveau buffer pour le texte avec padding
    uint8_t* padded = (uint8_t*)malloc(*padded_length);
    if (padded == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }
    
    // Copier le texte d'origine
    memcpy(padded, input, input_length);
    
    // Ajouter le padding PKCS#7
    for (int i = input_length; i < *padded_length; i++) {
        padded[i] = (uint8_t)padding_needed;
    }
    
    return padded;
}

// Fonction pour supprimer le padding PKCS#7
int remove_padding(uint8_t* input, int length) {
    if (length == 0) return 0;
    
    uint8_t padding_value = input[length - 1];
    
    // Vérifier que la valeur de padding est valide
    if (padding_value == 0 || padding_value > BLOCK_SIZE) {
        return length; // Padding invalide, retourner la longueur originale
    }
    
    // Vérifier que tous les octets de padding sont identiques
    for (int i = length - padding_value; i < length; i++) {
        if (input[i] != padding_value) {
            return length; // Padding invalide
        }
    }
    
    return length - padding_value;
}

// Programme principal
int main() {
    // Déclaration de variables
    char plaintext[128];
    int padded_length;
    
    // Clé et IV
    uint8_t key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8_t iv[16] = {161, 178, 195, 212, 229, 246, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    // Saisir le texte
    printf("Entrez le texte à chiffrer : ");
    if (fgets(plaintext, sizeof(plaintext), stdin) == NULL) {
        printf("Erreur de lecture\n");
        return 1;
    }
    plaintext[strcspn(plaintext, "\n")] = '\0';
    
    // Ajouter le padding
    uint8_t* padded_text = add_padding(plaintext, &padded_length);
    if (padded_text == NULL) {
        return 1;
    }
    
    // Contexte de chiffrement
    AES_CTX ctx_enc;
    AES_EncryptInit(&ctx_enc, key, iv);
    
    // Chiffrement des données bloc par bloc
    uint8_t* encrypted = (uint8_t*)malloc(padded_length);
    if (encrypted == NULL) {
        printf("Erreur d'allocation mémoire pour le chiffrement\n");
        free(padded_text);
        return 1;
    }
    
    for (int i = 0; i < padded_length; i += BLOCK_SIZE) {
        AES_Encrypt(&ctx_enc, padded_text + i, encrypted + i);
    }
    
    printf("Encrypted text (hex): ");
    for (int i = 0; i < padded_length; i++) {
        printf("%02X ", encrypted[i]);
    }
    printf("\n");
    
    // Contexte de déchiffrement
    AES_CTX ctx_dec;
    AES_DecryptInit(&ctx_dec, key, iv);
    
    // Déchiffrement des données bloc par bloc
    uint8_t* decrypted = (uint8_t*)malloc(padded_length);
    if (decrypted == NULL) {
        printf("Erreur d'allocation mémoire pour le déchiffrement\n");
        free(padded_text);
        free(encrypted);
        return 1;
    }
    
    for (int i = 0; i < padded_length; i += BLOCK_SIZE) {
        AES_Decrypt(&ctx_dec, encrypted + i, decrypted + i);
    }
    
    // Supprimer le padding
    int decrypted_length = remove_padding(decrypted, padded_length);
    decrypted[decrypted_length] = '\0';
    
    printf("Decrypted text: %s\n", decrypted);
    
    // Libération de mémoire
    free(padded_text);
    free(encrypted);
    free(decrypted);
    
    return 0;
}