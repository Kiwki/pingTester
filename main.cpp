#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

void ping(char ip[50]);
void writeLogs(int choix, ...);

int main (int argc, char *argv[])
{
    if(argc != 4)
    {
        fprintf(stdout, "%s [hostIP] [time in seconds] [interval]\n", argv[0]);
        exit(1);
    }

    int nbreConvertDur=atoi(argv[2]), nbreConvertInter=atoi(argv[3]), i=0;
    char ip[50];

    if(nbreConvertDur==0 || nbreConvertInter==0)
    {
        fprintf(stdout, "Please enter the correct duration or interval\n");
        exit(2);
    }

    writeLogs(115, nbreConvertDur, nbreConvertInter);
    strcpy (ip, argv[1]);

    while(i < nbreConvertDur/nbreConvertInter)
    {
        ping(ip);
        fprintf(stdout, "Je vais bien ! Ping %d\n", i+1);
        if(i == nbreConvertDur/nbreConvertInter-1)
            break;
        i++;
        sleep(nbreConvertInter);
    }
    writeLogs(101);

    return 0;
}

void writeLogs(int choix, ...)
{
    va_list ap;
    va_start(ap, choix);
    time_t now;
    time(&now);
    FILE * temp;
    temp = fopen("ping.log", "a");
    switch(choix)
    {
        case 's':
            fprintf(temp, "Start : %sDuration : %d ", ctime(&now), va_arg(ap, int));
            fprintf(temp, "Interval : %d \n", va_arg(ap, int));
            break;
        case 'p':
            fprintf(temp, "\n ------------------------------------------------------------------------- \n %s", ctime(&now));
            break;
        case 'e':
            fprintf(temp, "\n ------------------------------------------------------------------------- \nEnd : %s \n ------------------------------------------------------------------------- \n ------------------------------------------------------------------------- \n\n", ctime(&now));
            break;
    }
    fclose(temp);
    va_end(ap);
}

void ping(char ip[50])
{
    char commande[100];
    writeLogs(112);

    strcpy (commande,"ping ");
    strcat (commande,ip);
    strcat (commande, " -n 1 >> ping.log");
    system(commande);
}
