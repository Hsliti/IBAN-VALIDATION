
/*
 ============================================================================
 Name        	        :IBAN2.c
 Kurzbeschreibung       :Program soll die Kontonummern (IBAN) generieren
 EingabeParameter       :VOID
 Rückgabeparameter      : 1 (Programm beenden )
 Author            	    :Hamza Sliti
 Mat.Nr                 :11131474
 Version          	    :2
 Datum letzte Änderung  :20.11.2020
 ============================================================================
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



/*
 ============================================================================
// Funktionsname: Txt_einlesen_ausgeben
// Kurzbeschreibung der Aufgabe der Funktion: Bankleitzahlen und Filialbezeichnungen aus  BLZ.txt einlesen und die Bankleitzahlen und Filialbezeichnungen zeilenweise auf dem Bildschirm ausgeben
// Eingabeparameter : VOID
// Rückgabeparameter : VOID
 ============================================================================
 */

void Txt_einlesen_ausgeben (void){

	 FILE *fp; // File pointer deklarieren
	        char Linie[50];

	        fp = fopen("/home/pi/workspace/IBAN2/BLZ.txt", "r"); // die Textdatei mit der Funktion fopen () öffnen
	        if (fp == NULL){
	            printf("Konnte die Datei nicht öffnen ");
	            return ;
	        }
	        while (fgets(Linie, 50, fp) != NULL) // Text aus der Datei  lesen und als String  speichern

	            printf("%s\n", Linie);  // Linie ausgeben
	        fclose(fp);


}

/*
 ============================================================================
// Funktionsname: mod
// Kurzbeschreibung der Aufgabe der Funktion: berechnet das Modulo eines Strings
// Eingabeparameter :  char IBAN , int a
// Rückgabeparameter : ergebnis ( = IBAN % a )
 ============================================================================
 */

int mod(char* IBAN, int a)
{

    int i,ergebnis = 0;

    // Nacheinander alle Ziffern von 'IBAN' verarbeiten
    for ( i = 0; i < strlen(IBAN); i++)
         ergebnis = (ergebnis*10 + IBAN[i] - '0') %a;

    return ergebnis; // Ergebnis = IBAN % a
}


/*
 ============================================================================
// Funktionsname: BLZpruefer
// Kurzbeschreibung der Aufgabe der Funktion:  auf korrekte BLZ Nummer prüfen
// Eingabeparameter : BLZnummer
// Rückgabeparameter : 1 (BLZnummer ist richtig )
                      -1 (BLZnummer ist falsch  )
 ============================================================================
 */

int BLZpruefer(char* BLZnummer) {
	 int laenge=strlen(BLZnummer); //Länge der eingelesenen Kontonummer rausfinden
	 int i; // Zählvariable
    for ( i = laenge - 1; i >= 0; i--) {
    	//prüfen , ob  die Nummer falsche Zeichen enthält oder die Länge der BLZNummer != 8
    	if (BLZnummer[i] < 48 || BLZnummer[i] > 57 || laenge != 8 )
        {
           return(-1);
        }


}
    return(1);
}
/*
 ============================================================================
// Funktionsname: Filialepruefer
// Kurzbeschreibung der Aufgabe der Funktion: die Filialbezeichnung aus der Filialliste heraussuchen und eine Fehlermeldung auf dem Bildschirm ausgeben, falls die Bankfiliale nicht enthalten ist
// Eingabeparameter : kontonummer
// Rückgabeparameter :  1 (BLZnummer ist richtig )
                       -1 (BLZnummer ist falsch  )
 ============================================================================
 */

int Filialepruefer (char* BLZnummer){

	        FILE *fp; // File pointer deklarieren
	    	int Suchergebnis = 0;
	    	char Linie[50];

	    	    if((fp = fopen("/home/pi/workspace/IBAN2/BLZ.txt", "r")) == NULL) // die Textdatei mit der Funktion fopen () öffnen
	    	    {
	    		return(-1);
	    	     }

	    	while(fgets(Linie, 50, fp) != NULL) // Text aus der Datei  lesen und als String  speichern
	    	{
	    		if((strstr(Linie, BLZnummer)) != NULL) // die Filialbezeichnung aus der Filialliste heraussuchen
	    		{

	    			printf("\n%s\n", Linie); // Linie ausgeben
	    			Suchergebnis++; // Suchergebnis nimmt 1 , wenn die Filiale gefunden ist
	    		}

	    	}

	    	if(Suchergebnis == 0) { // die Filiale nicht gefunden

	    		return (-1);
	    	}

	    	//  die Datei schließen, falls sie noch geöffnet ist.
	    	if(fp) {
	    		fclose(fp);
	    	}

return 0;
}

/*
 ============================================================================
// Funktionsname: Kontopruefer
// Kurzbeschreibung der Aufgabe der Funktion:  auf korrekte Kontonummer prüfen
// Eingabeparameter : kontonummer
// Rückgabeparameter : 1 (kontonummer ist richtig )
                      -1 (kontonummer ist falsch  )
 ============================================================================
 */

int Kontopruefer(char* kontonummer) {
    int laenge=strlen(kontonummer); //Länge der eingelesenen Kontonummer rausfinden
    int i; // Zählvariable
    for ( i = laenge - 1; i >= 0; i--) {
    	//prüfen , ob  die Nummer falsche Zeichen enthält oder die Länge der Kontonummer > 10
        if (kontonummer[i] < 48 || kontonummer[i] > 57  || laenge > 10 )
        {

           return(-1);

        }

    }



    return(1);
}
/*
 ============================================================================
// Funktionsname: Nulladdieren
// Kurzbeschreibung der Aufgabe der Funktion: füllt die eingelesene Kontonummer vorne mit Nullen auf
// Eingabeparameter : kontonummer , neuKontonummer
// Rückgabeparameter : VOID
 ============================================================================
 */

void Nulladdieren(char* kontonummer,char* neuKontonummer) {
int  laenge=strlen(kontonummer); //Länge der eingelesenen Kontonummer rausfinden
char Null[10]={"0"};
char NullAnzahl[10]={"0"};
int  Anzahl=10-laenge; // Anzahl der fehlenden Ziffern
int i; // Zählvariable

        	   for ( i=0 ;i<Anzahl-1;i++)
        	   {
        		   strcat(NullAnzahl, Null); // NullAnzahl nimmt Null ( 0 0 .. )

           }
        	   strcat(NullAnzahl, kontonummer); // NullAnzahl nimmt Kontonummer ( 0 .. KKK. )


        	   strcpy(neuKontonummer,NullAnzahl);  // // neuKontonummer nimmt NullAnzahl






}






int main(void)
{
    char BLZ[8];  // BLZ Array mit 8 char-Elementen
    char Kontonummer[10]; // Kontonummer Array mit 10 char-Elementen
    char IBAN[24]={};  // IBAN Array mit 24 char-Elementen
    char DE[6]={"131400"};  // DE Array mit 24 char-Elementen Ländercode für Deutschland + Prüfziffer
    char neuKontoNummer[10]; // neuKontonummer Array mit 10 char-Elementen
    int Kontogueltig, BLZgueltig , Filialegueltig;
    int  laenge;  //Länge der Kontonummer
    int Rest; //
    int PP; // Prüfziffer


    Txt_einlesen_ausgeben();  //Aufruf der Funktion, die  die Bankleitzahlen und Filialbezeichnungen zeilenweise auf dem Bildschirm ausgibt





    //In dieser Schleife wird der Nutzer aufgefordert seine BLZ und Kontonummer zu korrigieren fals diese ungültig sind
    while(1) {
        printf("\n\nBitte BLZ eingeben: "); //Aufforderung zum eingeben BLZ-Nummer
        scanf("%s", BLZ);  // einlesen der eingegebenen BLZ als String

         BLZgueltig = BLZpruefer(BLZ); // BLZgueltig nimmt den rückgabewert der Funktion BLZpruefer
                if (BLZgueltig == -1) {
          printf("\nFehlerhafte Eingabe!\n");   //Fehlermeldung, wenn die Nummer falsche Zeichen enthält oder die Länge der BLZNummer != 8
                           continue;
                       }

                 Filialegueltig = Filialepruefer(BLZ); // Filialegueltig nimmt den rückgabewert der Funktion Filialepruefer
                if (Filialegueltig == -1) {
                         printf("\ndie Bankfiliale nicht gefunden!\n");   //Fehlermeldung, , falls die Bankfiliale nicht enthalten ist

                                          continue;
                                      }

        printf("Bitte Kontonummer eingeben: ");  //Aufforderung zum eingeben Kontonummer
        scanf("%s", Kontonummer); // einlesen der eingegebenen Kontonummer als String
        Kontogueltig = Kontopruefer(Kontonummer);   // Kontogueltig nimmt den rückgabewert der Funktion Kontopruefer
        if (Kontogueltig == -1) {
            printf("\nFehlerhafte Eingabe!\n"); //Fehlermeldung, wenn die Nummer falsche Zeichen enthält oder die Länge der Kontonummer > 10
            continue;
        }

        laenge=strlen(Kontonummer);   //Länge der eingelesenen Kontonummer rausfinden
        if (laenge<10){            // wenn die Länge der Kontonummer < 10
        Nulladdieren(Kontonummer,neuKontoNummer); // Funktion Nulladdieren aufrufen
        strcpy (Kontonummer,neuKontoNummer); // Kontonummer nimmt neuKontoNummer
        }


        printf("\nBLZ\t\t\tKontonummer\t\t\t nIBAN\n%s\t\t%s\t\t %s%s%s\n", BLZ,Kontonummer,BLZ,Kontonummer,DE);  //BLZ , Kontonummer und nIBAN  ausgeben

        strcat(IBAN, BLZ);   //  IBAN nimmt BLZ  ( IBAN = BBBBBBBB )
        strcat(IBAN, Kontonummer); //  IBAN nimmt Kontonummer  ( IBAN = BBBBBBBBNNNNNNNNNN )
        strcat(IBAN, DE);  // //  IBAN nimmt DE  ( IBAN = BBBBBBBBNNNNNNNNNN131400 )



         Rest = mod(IBAN,97);  // Rest nimmt den rückgabewert der  Funktion mod
         PP=98-Rest;       // PP nimmt 98 - Rest
        printf("IBAN : DE%d%s%s",PP,BLZ,Kontonummer); // IBAN ausgeben
        printf("\n\n");
        return 1;   // Programm beenden
    }

}
