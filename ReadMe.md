### NE PAS UTILISER UART 2

### Tableau d'utilisation des pins :
https://docs.google.com/spreadsheets/d/1FeegPGEJXE2erZf9Mmz8QHtwiJrAz9IVcwBRSWizvc8/edit?usp=sharing

### Fonctions :
*******************
*** Girouette : ***
*******************


int codeurIncremental()
{
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

*******************
* Accéléromètre : *
*******************

boolean surRoulis(GPIO accéléromètre)
{
	Renvoie true si l'angle du mat dépasse 40°
	ou false sinon 
}

void lacherVoile(boolean surRoulis) {
	if surRoulis() relache la voile ;
}

*******************
** Télécommande : *
*******************
