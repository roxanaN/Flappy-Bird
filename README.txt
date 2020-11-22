Nemulescu Roxana-Elena 332CA
EGC - Tema1 : Flappy Bird

	Pentru implementarea temei, am ales laboratorul 3 drept schelet.
	Pentru a desena pasarea:
		-Am retinut coordonatele fiecarei parti care alcatuieste pasarea,
		 atat pentru axa OX (xBird), cat si pentru axa OY (yBird), dar si
		 dimensiunile fiecarei componente. Valorile au fost stabilite in
		 functia Init(). Am calculat atat lunginea, cat si latimea pasarii,
		 pentru a ma ajuta de valori in verificarea coliziunilor.


		-In functia Update(), am aplicat gravitatia asupra fiecarei componente
		 si am translatat si rotit elementele, pentru ca pasarea sa aiba miscari
		 fluide.

		-Initial, pana la apasarea tastei SPACE, pasarea are o pozitie fixa.
		 Dupa apasarea tastei SPACE, responsabila pentru impulsul necesar
		 zborului, asupra pasarii incepe sa actioneze gravitatia, iar pasarea
		 inecepe sa cada. La atingerea solului sau a limitei superioare a ferestrei,
		 jocul se incheie.

		-Pentru saritura, am adunat la coordonatele de pe axa OY, valoarea din
		 variabila jump, valoare care se scade, in momentul eliberarii tastei SPACE.
		 Pentru rotatie, este responsabila variabila angle.

	Pentru a realiza mediul in care se deplaseaza pasarea:
		-Am desenat un singur dreptunghi, de latime fixa, pe care l-am randat la
		 pe axa OY la pozitii alese random, dintr-un vector initial, care contine
		 valori care au sens. Conductele stalacmite, sunt randate la o
		 distanta egala fata de conducetele stalactite.

		-Pentru deplasarea pipe-urilor, am scazut coordonata OX, astfel incat
		 pipe-urile sa se deplaseze spre stanga. La parasirea ferestrei,
		 conducta este randata la pozitia initiala, ceea ce realizeaza o miscare
		 ciclica, pentru 

	Pentru coliziuni:
		-Daca pasarea nu se afla in afara zonei dintre pipe-uri,
         si pozitia ei pe axa OX se suprapune cu pozitia conductei, jocul se incheie.

	GameOver:
		-Daca jocul se incheie, pasarea moare (cade la pamant, lipsita de gravitatie - si speranta),
		 iar conductele se opresc din a se mai deplasa. Se afiseaza in consola un mesaj
		 corespunzator si scorul obtinut.