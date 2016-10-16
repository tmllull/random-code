#include <iostream>
#include <sys/time.h>
#include <fstream>

using namespace std;

struct timeval tv0, tv1;
double secs;
int res;

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("USAGE: introduir el path del fitxer, seguit del tamany en bytes\n");
        printf("./rendiment PATH tamany_en_bytes\n");
        return 0;
    }
    const char *path=argv[1];
    ofstream myfile (path);
    if (myfile.is_open()){
        res = gettimeofday(&tv0, NULL);
        if (res < 0) perror ("gettimeofday");

        for (int i = 0; i < atoi(argv[2]); i = i+8){
            myfile << i << "\n";
        };    
        res = gettimeofday(&tv1, NULL);
        if (res < 0) perror ("gettimeofday");
        myfile.close();
    }
    else printf("ERROR OPEN FILE\n");
    
    secs = (((double)tv1.tv_sec*1000000.0 + (double)tv1.tv_usec) - 
        ((double)tv0.tv_sec*1000000.0 + (double)tv0.tv_usec))/1000000.0;
    
    printf ("temps %lf segons\n", secs);
    printf ("Informació escrita: %d Kbytes\n", atoi(argv[2])/1024);
    printf ("Bandwidth: %.2lf MBps\n", (atoi(argv[2])/secs)/1000000.0);
    return 0;
}
