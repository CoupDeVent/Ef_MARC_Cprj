# MARC
![image](/image/rover.png)

## Installation

Vous pouvez retrouver notre code sur GitHub en suivant [ce lien](https://github.com/CoupDeVent/MARC_Eytan_Guernigou)

## Configuration

Le programme nécessite un interpréteur de langage C pouvant accéder à des fichiers (Ex : CLion)

## Configuration

Le programme nécessite un interpréteur de langage C pouvant accéder à des fichiers (Ex : CLion)

## Utilisation :

L'utilisation de notre code se fait depuis le fichier main.c par un interpréteur compatible.

<br>V0 : Prototype
<br>V1 : Programme intermédiaire comprenant les fonctions de bases
<br>V2 : Programme complet comprenant l'ensemble des fonctions attendues
<br>V3 : Programme comprenant les commentaires associées aux fonctions et instructions

----------------------------------------------------------------------------------------------------------------------------------------------------

## Contexte de la mission

En 2028, une tempête solaire intense a endommagé le rover MARC (MArs Rover Cartograph), perturbant ses systèmes de programmation, de guidage et de mouvement. L'ESTF (Efrei Space Task Force) recrute des experts pour concevoir un nouveau logiciel de déplacement afin de ramener MARC à une station de base pour réparation.

## Description du rover MARC

- **Système**: Linux
- **Langage de programmation**: C
- **Orientation**: Nord, Sud, Est, Ouest
- **Fonctionnalités**: Radar et gyroscope opérationnels

## Mouvements possibles

- Avancer de 10m
- Avancer de 20m
- Avancer de 30m
- Reculer de 10m
- Tourner d'un quart de tour à gauche
- Tourner d'un quart de tour à droite
- Faire demi-tour

## Disponibilités des mouvements

| Type de mouvement                    | Disponibilités initiales |
|--------------------------------------|--------------------------|
| Avancer de 10m                       | 22                       |
| Avancer de 20m                       | 15                       |
| Avancer de 30m                       | 7                        |
| Reculer de 10m                       | 7                        |
| Tourner d'un quart de tour à gauche  | 21                       |
| Tourner d'un quart de tour à droite  | 21                       |
| Faire demi-tour                      | 7                        |

## Carte de Mars

- **Unité**: Cases de 10m x 10m
- **Types de sol**:
  - Plaine: aucune influence
  - Erg: diminue le prochain mouvement de 1
  - Reg: limite à 4 mouvements dans la phase suivante
  - Crevasse: fin du rover

## Objectif

Programmer le meilleur parcours pour que MARC atteigne la station de base en minimisant les déplacements, en tenant compte des différents terrains.

## Fonction de coût

Chaque case de la carte est associée à un coût, reflétant la difficulté de la traverser. Le programme doit chercher à atteindre les cases de coût minimal.

## Étapes de réalisation

1. **Tester le code fourni** pour les cartes et les déplacements individuels de MARC.
2. **Définir les structures de données** pour l'arbre de sélection des déplacements.
3. **Créer un arbre simplifié** pour tester les algorithmes de construction et de recherche du chemin optimal.
4. **Augmenter progressivement la complexité** pour arriver au choix de 5 mouvements parmi 9 possibilités.

----------------------------------------------------------------------------------------------------------------------------------------------------

## Projet réalisé par

- [Eytan Guernigou](https://github.com/CoupDeVent)
- [Frédéric Jalaguier](https://github.com/Fido-Midou)
- [Tim Nguyen-Menu](https://github.com/TimNeM)

## Crédits et Remerciements :

Nous remercions l'école d'ingénieur l'EFREI ainsi que l'équipe enseignante de nous avoir donné les ressources nécessaires à la réalisation du projet

## Contribution :

Vous pouvez nous soutenir en signalant tout potentiel bug dans notre programme afin de l'améliorer

## Fin

Merci d'avoir pris le temps de lire et bonne utilisation de notre éditeur de tableau ! 
