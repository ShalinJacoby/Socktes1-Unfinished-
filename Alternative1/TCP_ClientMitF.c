// Portfolioprüfung – Werkstück A – Alternative 1
// Interprozesskommunikation mit TCP Sockets
// 
// 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

		//#include "Prozesse.c"
		//#include "TH_ServerMitF.c"


#define PORT 50000

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

	//	/// @brief 
	//	/// @param argc 
	//	/// @param argv 
	//	/// @return 
int main(int argc, char *argv[])

// Host Adress abfrage
{
    char hostname[256];
    char ip_address[INET_ADDRSTRLEN];

    // Hostname abfragen
    if (gethostname(hostname, sizeof(hostname)) == -1)
    {
        perror("Fehler beim Abrufen des Hostnamens");
        exit(EXIT_FAILURE);
    }

    printf("Hostname: %s\n", hostname);

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // IP-Adresse abfragen
    if (getaddrinfo(hostname, NULL, &hints, &res) != 0)
    {
        perror("Fehler beim Abrufen der IP-Adresse");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
    if (inet_ntop(AF_INET, &(addr->sin_addr), ip_address, INET_ADDRSTRLEN) == NULL)
    {
        perror("Fehler beim Konvertieren der IP-Adresse");
        exit(EXIT_FAILURE);
    }

    printf("IP-Adresse: %s\n", ip_address);

    // Hier kannst du die IP-Adresse für die Socket-Kommunikation verwenden

    freeaddrinfo(res);

    return 0;




	int sockfd;
	int valread;
	struct sockaddr_in adresse;

	// Wenn IP Adresse fehlt
	if (argc < 2)
	{
		error("Ip adresse fehlt\n");
	}
	// While-Schleife für Endlosschleife
	while (1)
	{
		// Socket erstellen
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			error("Error opening Socket");
		}
		else
		{
			printf("Socket was created\n");
		}

		// Speicher von sockaddr_im mit Nullen füllen
		memset(&adresse, 0, sizeof(adresse));

		// Socket adresse in sockaddr_ in speichern
		adresse.sin_family = AF_INET;
		adresse.sin_port = htons(PORT);
		adresse.sin_addr.s_addr = inet_addr("127.0.0.1");

		if (connect(sockfd, (struct sockaddr *)&adresse, sizeof(adresse)) < 0)
		{
			error("Verbindung fehlgeschlagen");
		}
		else
		{
			printf("Verbindung zu Server erfolgreich.\n");
		}

		int anzahlZahlen = 10;
		int i;
		int summe = 0;
		int array[10];
		float mittelwert;

		valread = read(sockfd, array, sizeof(array));
		if (valread < 0)
		{
			error("Fehler beim Lesen");
		}

		valread = read(sockfd, &anzahlZahlen, sizeof(anzahlZahlen));
		if (valread < 0)
		{
			error("Fehler beim Lesen");
		}

		printf("We are process LOG\n");
		
		FILE *lokaleDatei;
		lokaleDatei = fopen("log", "w");
		if (lokaleDatei == 0)
		{
			error("Fehler beim erstellen der Datei. \n");
		}

		for (i = 0; i < anzahlZahlen; i++)
		{
			fprintf(lokaleDatei, "%d\t", array[i]);
		}

		fclose(lokaleDatei);
		printf("Datei erstellt. \n");

		printf("We are process STAT\n");

		for (int i = 0; i < anzahlZahlen; i++)
		{
			summe += array[i];
		}
		mittelwert = (float)summe / anzahlZahlen;

		printf("Verwendete Zahlen: ");

		for (int i = 0; i < anzahlZahlen; i++)
		{
			printf("%d ", array[i]);
		}
		printf("\n");
		printf("Anzahl verwendeter Zahlen: %d \n", anzahlZahlen);

		printf("We are process REPORT\n");
		printf("Summe: %d \n", summe);
		printf("Mittelwert: %f\n", mittelwert);

		close(sockfd);
		sleep(3);
	}

	return 0;
}