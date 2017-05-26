# 42sh

Le but est de créer un shell plus complexe que le 21sh mais au sein d'un groupe de trois étudient.

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
* Agrégateur  `>&`
* Multi commande `;`
* Et `&&`
* Ou `||`
* Edition de ligne
* Autocomplétion
* Alias

## Bultin

* cd
* echo
* env
* setenv
* unsetenv
* history
* read

## Controle

* Mode de selection `esc`
* Copier `esc` sélectionner avec les fleches directionelles puis pressez `Alt + c`
* Couper `esc` sélectionner avec les fleches directionelles puis pressez `Alt + x`
* Coller `Alt + v`
* Autocompletion `Tab`
* Se déplacer de mot en mot `Alt + Fleche Droite,gauche`
* Se déplacer d'une ligne à l'autre `Alt + Fleche Haut,Bas`
* Naviguer dans l'historique `Fleche Haut,Bas`
