# 42sh

Le but était de crée un shell plus complexe que le 21sh mais en groupe cet fois si.

* Dhervy
* Tbertojo
* Vde-la-s

## Compiling

executer `make`, un exécutable nommé `42sh` devrait compiler directement.

## Usgae

`~ ./42sh`

```c
$> ls | cat -e // on va executer `ls` puis envoyer la sortit standard vers l'entrée stendard de `cat -e`
$> echo "$PATH" > path.txt // on va ecrire cat -e ne recla valeur de PATH dans path.txt
$> env -i ls -G
$> cd ../test
$> cat << EOF | cat -e
>ceci sera envoyer a `cat -e`
>EOF ou CTRL + D
`ceci sera envoyer a `cat -e`$`
$> mkdir
$> chmod 777 ../test/fichier
$> echo Bonjour > test.txt ; echo Aurevoir >> test.txt ; cat -e test.txt
Bonjour$
Aurevoir$
$> ls -l 1>&2 | cat -e // la sortit de `ls` est rediriger vers la sortit d'erreur, le `pipe` lui recupere la sortit stendard qui est vide donc `cat -e` ne recupere aucune entrée
```
## Feature

* Pipe `|`
* Heredoc `<<`
* Double redirection `>>`
* Redirection `<` et `>`
* Agregateur  `>&`
* Multi commande `;`
* Et `&&`
* Ou `||`
* Edittion de ligne 
* Allias

## Bultin

* cd
* echo
* env
* setenv
* unsetenv
* history
* read

## Controle

* mode de selection `esc`
* Copier `esc` selectionner avec les fleche directionel puis pressez `Alt + c`
* Couper `esc` selectionner avec les fleche directionel puis pressez `Alt + x`
* Coller `Alt + v`
* se deplacer de mots en mots `Alt + Fleche Droite,gauche`
* se deplacer d'une ligne a l'autre `Alt + Fleche Haut,Bas`
* naviguer dans l'historique `Fleche Haut,Bas`
