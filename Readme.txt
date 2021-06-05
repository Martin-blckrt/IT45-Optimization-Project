Architecture du projet :
Un fichier java InstanceGenerator permettant de modifier les instances générées. Ce fichier a été modifié par rapport à l'original 
afin d'être plus facilement implémenté dans notre programme. Dorénavant, ce programme sépare les données entre les constantes
préprocesseurs (fichier constants.h) et les données "brutes" générées (les formations, interfaces et centres, dans le fichier donnees.c). 
Dans le fichier donnees.c, des variables globales ont également été ajoutés pour des simplicités d'implémentation.

La solution générée par notre programme se fait grâce à le fichier solution.c
En effet, sa fonction est simple : générer une solution initiale, l'améliorer grâce à une heuristique, puis l'améliorer grâce à un
algorithme génétique. De ce fait, ce fichier contient toutes les fonctions relatives à ces éléments.
Ensuite, le fichier interface.c contient toutes les fonctions relatives aux manipulations/modificiations sur les interfaces.
Finalement, deux fichiers .c btree.c, dintegerarray.c qui sont de simples implémentations de structures de données (arbre binaire
et tableau dynamique) ainsi qu'un fichier tri.c qui contient nos différents critères de tri.

Lancer le projet :
-Pour générer une nouvelle instance, aller dans le fichier src et taper la commande
javac InstaceGenerator.java
java InstanceGenerator

-Pour lancer le programme sur une instance déjà générée, taper la commande
make
puis ./executable
Pour modifier le compilateur, les flags ou autre, voir le makefile


Paramétrer le projet : 
Modifier les constantes préprocesseur dans le fichier solutions.c :
DEPTH : profondeur de l'arbre de recherche de solution à l'aide de la première heuristique
INFLUENCE_STANDARD : influence la direction que prend l'arbre (plus la valeur est haute, plus on améliore l'écart type au profit 
du fcorr et de la pénalité)
INFLUENCE_PENALITE : pareil que INFLUENCE_STANDARD mais pour les pénalités des interfaces