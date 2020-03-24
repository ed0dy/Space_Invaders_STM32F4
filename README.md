# Rapport de projet Space Invaders sur STM32F4 Discovery

### BARRON Jean-Pascal B3 AERO Ynov Campus Bordeaux

https://github.com/ed0dy/Space_Invaders_STM32F4

# Mode d'emploi pour le lancement du jeu

1. Clonnez le projet sur votre pc : git clone https://github.com/ed0dy/Space_Invaders_STM32F4

2. Ouvrez le projet avec Atolic True Studio

3. Lancez le debug pour transférer le programme sur la STM32F4 Discovery

4. Stoppez le debug

5. Ouvrez un terminal et installez "screen" : sudo apt install screen

6. Dans le terminal tapez : screen /dev/ttyUSB0 115200
   
Le "USB0" peut être different sur votre pc

Vous devriez enfin arriver sur cette fenetre : 

![Menu principal](Menu.png)

Comme indiqué sur la fenetre : appuyez sur Espace pour jouer, Q pour aller à gauche, D pour aller à droite et Espace pour tirer

# Les difficultés rencontrées

## Le stockage de toutes les données de enemies

Je ne voyais pas comment stocker la position en X et Y de chaque enemies. En commençant le projet je ne connaissais pas les structures et c'est grâce à ça que j'ai pu régler mon problème.

## Le déplacement des enemies

Je n'ai pas réussi à finaliser cette partie. Je pense qu'il ne manque pas grand chose pour que ma fonction "enemies" fonctionne.

## Le tir du vaisseau

Ma fonction de tire fonctionne mais on n'est obligé d'appuyer sur escpace à chaque fois pour que le missile s'incrémente

# Les notions apprises et peaufinées

## Notions apprises

1. typedef, structures, static, extern
2. #define
3. les pointeurs
   
## Notions peaufinées

1. Tous les types de variables
2. Les fonctions
3. #include

# Retour d'experience

Je suis globalemet trés satisfait de ce projet qui m'a permis de découvrir et d'approfondir plein de notions du language C. Je ne suis pas forcément très bon en programmation et je préfère plus le côté électronique mais j'avoue que ce projet m'a permis de m'intéresser beaucoup plus à la programmation et pour cela je remercie beaucoup M.POULAILLEAU Vincent pour toutes ces explications et le temps qu'il à passé avec nous.
