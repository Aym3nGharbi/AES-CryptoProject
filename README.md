# Projet de Cryptographie en C

Ce projet regroupe plusieurs programmes en langage C permettant d'explorer des techniques de cryptographie, notamment :

- **Analyse de fréquence** des lettres dans un texte.
- **Chiffrement et déchiffrement avec le chiffrement de César**.
- **Chiffrement et déchiffrement AES-128 en mode CBC** avec padding PKCS#7.

---

## 📁 Fichiers du projet

```
.
├── cryptoanalyse.c # Analyse de fréquence des lettres dans un texte
├── cryptographie.c # Chiffrement/Déchiffrement par César
├── AEScrypto.c # Chiffrement/Déchiffrement AES-128 CBC
├── AES_128_CBC.h # En-tête pour l’implémentation AES (à fournir)
└── README.md # Ce fichier de description
```

---

## 🚀 Utilisation

### I. Analyse de Fréquence (`./cryptoanalyse`)

1. Saisis un texte.
2. Le programme affiche les lettres trouvées, leur fréquence, et un classement.

### II. Chiffrement / Déchiffrement César (`./cryptographie`)

1. Saisis un texte à chiffrer ou déchiffrer.
2. Indique une clé entière entre 1 et 25.
3. Choisis `c` pour crypter ou `d` pour décrypter.
4. Le programme applique la transformation et affiche le résultat.

### III. Chiffrement / Déchiffrement AES-128 CBC (`./AEScrypto`)

1. Saisis un texte court (moins de 128 caractères).
2. Le texte est automatiquement paddé, chiffré avec AES-128 (clé et IV statiques), puis déchiffré.
3. Le programme affiche le texte chiffré (en hexadécimal) et le texte déchiffré final.

---

## ⚠️ Remarques

- Ce projet est **pédagogique** et **non destiné à un usage sécurisé réel**.
- Pour un usage professionnel ou critique, privilégiez des bibliothèques cryptographiques standards comme **OpenSSL** ou **libsodium**.
