# Diffusion du son :

| Ecouteurs/Casque          | Sono               | Enceinte DiY          |
| ------------------------- | ------------------ | --------------------- |
| hygiene / prix / jeu solo | lours, cables      | Piles,  pas de basses |
| autonomie                 | Qualité, diffusion | Autonomie             |

# Syncronisation du tempo

Utilisation de ableton link sur toutes les machines.

Ce qui pose de question :

* Comment gérer proprement le réseau

* Comment indiquer proprement le tempo quand on fait des boucles

* Tout le monde à le droit de changer le tempo ? si oui, time stretch

* Indication visuel du tempo grâce au leds

* Est ce que le tempo est toujours démarré ?

# Interaction au toucher

choix des boutons :

* Ouverture d'une bank de sauvegarde

* activation d'un effet

* Touche de piano, de pad, démarrage de boucle

Pour l'ouverture d'une bank, ou l'activation d'un effet, avoir un vrai bouton mécanique évite les fausses érreur. 

Mais un bouton de type pad, on cherche plutot la facilité et le confort du toucher.

Le capacitif est une bonne solution pour ça , mais a plusieurs problèmes :

* latence qui se sent un peu ( voir gestion de la latence )

* Choix du module ( mpr121 nécessite d'une branchement un peu plus compliqué)

* Choix du bouton métallique sur lequel on appuie. 

Sans utiliser le mpr121, à l'heure actuelle le nombre de boutons diponible est de :

**10 Boutons** ( en considérant que 1 est reservé ) 

Ce qui est peu mais acceptable

# Gestion de la latence

Carte son usb par cher [lien](%5Bhttps://www.aliexpress.com/item/32972984249.html?spm=a2g0o.productlist.0.0.169736d0yP4Y2a&algo_pvid=9966d7ae-060d-4cc7-90e6-f7dec51031e7&algo_expid=9966d7ae-060d-4cc7-90e6-f7dec51031e7-27&btsid=0ab6fa8115866311846853772ed0c7&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_%5D(https://www.aliexpress.com/item/32972984249.html?spm=a2g0o.productlist.0.0.169736d0yP4Y2a&algo_pvid=9966d7ae-060d-4cc7-90e6-f7dec51031e7&algo_expid=9966d7ae-060d-4cc7-90e6-f7dec51031e7-27&btsid=0ab6fa8115866311846853772ed0c7&ws_ab_test=searchweb0_0,searchweb201602_,searchweb201603_)

En gardant le principe le clé usb pas cher, et en utilisant une jack.

On arrive à une latence théorique de :

( 256 / 48000 ) * 2 = 10.6666666667 ms

( 512 / 48000 ) * 2 = 21.3333333333 ms

Un peu moins, vu que on est sur du 44.1 KHz

Il faudrait bien sur mesurer précisemment.

La latence va bien entendu en lien avec la question du rythme.

Or, latence audio ou pas latence audio, il est compliqué de :

* Faire jouer du pad en rythme

* Faire démarrer et arreter proprement les boucles

* Mélanger les 2 :

La solution pour cela, est d'enlever cette contrainte là aux utilisateurs, en fixant un tempo. 

1. Dans le cas du pad ( batterie, synthé). On est toujours en rythme, même si l'on appui un peu en avance ou un peu en retard

2. Pédale de boucle, toujours syncro avec un rythme initial. Quid : métronome à la ableton live ? et si on tape juste après ?

# Mélodie, Harmonie

Comme vu précedemment, une lucibox contient au maximum 10 boutons. C'est peu limité pour un clavier, ou un pad.

Cependant, dans le cas où l'on cherche à faire jouer des gens qui ne connaissent pas la musique, en clavier de 54 touches n'a pas d'interêt.

L'idée serait donc d'avoir un tempo commun, une tonalité commune ( comme sur Incredibox), voir une gamme commune

De ceci, un touche "musicale" correspond à :

* un note de la gamme

* un accord de la gamme

* une note si on appui sur une touche, et un accord sur plusieurs touches

Pour ceci en reprend directement la logique utiliser par [https://www.automatonism.com/](https://www.automatonism.com/)

# Microphone, captation audio

La captation peut être réalisé par la petite carte son, par le biais de son entrée mini jack :

* Par un micro electret genre mini micro de skype ( par cher )

* Par un micro electret, caché dans un vrai/faux microphone ( par cher)

* Par un vrai micro xlr , par le biais d'une pré-amp ( cher)

Les micro electret de sont pas cardioide , et c'est leur gros défaut.
