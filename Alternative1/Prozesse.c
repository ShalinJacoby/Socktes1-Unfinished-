#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
// Erzeugung von Prozessen

int main()
{
    int childproc_conv = fork();
    if (childproc_conv == 0) // Hier ist der Kindprozess conv!
    {
        printf("Conv: PID: %i\n", getpid());
        // Endlosschleife
       
        // 5 Zufallszahlen zw. 0 und 99
        int i, r;
        srand(time(NULL));
        printf("Zufallszahlen: ");
        int zufallszahlen[10];
        for (i = 0; i < 10; i++)
        {
            printf("%d ", zufallszahlen[i] = rand() % 100);
        }
        printf("\n");

        int childproc_stat = fork();
        if (childproc_stat == 0) // Hier ist der Kindprozess stat!
        {
            printf("Stat: PID: %i\n", getpid());
            // Summe der Zufallszahlen
            int i, zufallszahlen[i];
            float summe = 0, mittelwert;
            for (i = 0; i < 10; i++)
            {
                summe += zufallszahlen[i];
            }
            // Mittelwert der ZUfallszahlen
            mittelwert = summe / 10;
            // Ausgabe

            int childproc_log = fork();
            if (childproc_log == 0) // Hier ist der Kindprozess log!
            {
                printf("Log: PID: %i\n", getpid());
                // Datei zum Schreiben öffnen
                FILE *lokal_file;
                lokal_file = fopen("log", "w"); // Datei öffnen für Schreibzugriff
                if (lokal_file == 0)            // Prüft, ob Datei erfolgreich geöffnet wurde
                {
                    printf("Fehler beim Öffnen der Datei. \n");
                    exit(1);
                }
                for (i = 0; i < 10; i++)
                {
                    fprintf(lokal_file, "Test %d\n", zufallszahlen[i]); // Schreibt in Datei ein
                }
                fclose(lokal_file); // Datei schließen
            }

            int childproc_report = fork();
            if (childproc_report == 0) // Hier ist der Kindprozess report!
            {
                printf("Report: PID: %i\n", getpid());
                // Ausgabe Shell:
                printf("\n");
                printf("Summe der Zufallszahlen: %.2f\n", summe);
                printf("Mittelwert der Zufallszahlen: %.2f\n", mittelwert);
            }

            printf("\n");
            return 0;
        }
    }
}
