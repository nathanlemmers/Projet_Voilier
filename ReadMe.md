### NE PAS UTILISER UART 2

### Tableau d'utilisation des pins :
https://docs.google.com/spreadsheets/d/1FeegPGEJXE2erZf9Mmz8QHtwiJrAz9IVcwBRSWizvc8/edit?usp=sharing

### Fonctions :
*******************
*** Girouette : ***
*******************


int compteurGirouette(GPIOA.8 et GPIOA.7)
{
    Si le disque tourne vers la droite, +1
    Si le disque tourne vers la gauche, -1
    O sinon
    Déterminer la direction en utilisant le déphasage

    Si A_précédent fermé && B_précédent fermé
        Si A ouvert : +1
        Si B ouvert : -1
    Si A_précédent ouvert && B_précédent fermé :
        Si B ouvert : +1
        Si A fermé : -1
    Si A_précédent ouvert && B_précédent ouvert :
        Si A fermé : +1
        Si B fermé : -1
    Si A_précédent fermé && B_précédent ouvert :
        Si B fermé : +1
        Si A ouvert : -1
	
	On retient l'état (A, B) précédent et on compare à chaque appel
}




int orientationVent()
{
    1/4° * compteurGirouette();
}

*******************
***** Voiles : ****
*******************
TIMER 2 PWM : CHANNEL 1 : A0 :

void ajusterVoile(int angle)
{
	Convertir l'angle en ratio PWM et fixer l'angle du servomoteur
	Si !surRoulis()
		On ajuste normalement
	Sinon
		lacherVoile();
}

*******************
**** Plateau : ****
*******************
TIMER 3 : CHANNEL 3 : PIN BO 
void changerCap(GPIO commande)
{
	Récupérer le sens et la force à travers le GPIO
	Actionner les moteurs proportionnellement à la force de la commande
	Utiliser PWM pour régler l'intensité des moteurs
}

*********************
** Accéléromètre : **
*********************

boolean surRoulis(GPIO accéléromètre)
{
	Renvoie true si l'angle du mat dépasse 40°
	ou false sinon 
}

void lacherVoile(boolean surRoulis) {
	if surRoulis() relache la voile ;
}

********************
** Télécommande : **
********************
