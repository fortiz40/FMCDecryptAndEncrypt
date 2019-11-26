#include <hw2.h>
#include <unistd.h>

#include <stdio.h>
extern int opterr;
extern char* optarg;

void mcopy(char* src, char* dest, size_t n);

int main(int argc, char* argv[]){

    //default key definition
    char* key = malloc(26);
    mcopy("--------------------------", key, 26);

    int c;
    char* keyphrase = NULL;
    char* outfile_name = NULL;
    char eflag = 0, dflag = 0;
    char* infile_name = NULL;

    FILE* infile = stdin;
    FILE* outfile = stdout;

    opterr = 0;

    while ((c = getopt (argc, argv, "k:O:ed")) != -1){
        switch (c){
            case 'k':
                keyphrase = optarg;
                break;
            case 'O':
                outfile_name = optarg;
                break;
            case 'e':
                if(dflag) {
                    fprintf (stderr, "Both options -e and -d cannot be specified.\n");
                    return -1; //Both d and e options specified
                }
                eflag = 1;
                break;
            case 'd':
                if(eflag) {
                    fprintf (stderr, "Both options -e and -d cannot be specified.\n");
                    return -1; //Both d and e options specified
                }
                dflag = 1;
                break;
            case ':':
                if (optopt == 'k'| optopt == 'O')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                    return -1;
            case '?':    
                if (optopt)
                    fprintf (stderr, "Unknown option specified.\n");
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return -1;
            default:
                return -1;
        }
    }
    
    // FILE argument must be the only positional argument in the args list
    if (argc-optind == 1) {  // FILE specified
        infile_name = argv[optind];
    } else if(argc-optind > 1){ // More arguments than FILE specified
        fprintf (stderr,"Too many positional arguments specified.\n");
        return -1;
    }

    if(!eflag && !dflag){
        fprintf (stderr, "Option -e or -d must be specified.\n");
        return -1;
    }
    // ARG PARSING COMPLETE
    


    // INSERT YOUR CODE HERE
    
	if (outfile_name != NULL)
	{
		outfile = fopen(outfile_name, "w");
		if ( outfile = NULL) return 3;
	}
	if (infile_name != NULL)
	{
		infile = fopen(infile_name, "r");
		if (infile == NULL) return 2;
	}
	createKey(keyphrase, key);

	if (eflag)
	{
		int  x = FMCEncrypt(infile, key, outfile);
		fclose(outfile);
		if (x == 1) return 0;
		if (x == -1) return 4;
	}
	if (dflag)
	{
		int x = FMCDecrypt(infile, key, outfile);
		fclose(outfile);
		if (x == 1) return 0;
		if (x == -1) return 4;
	}
 
//    char * key = (char*)malloc(sizeof(char) * 26);
    /*
    createKey(key, key);

    int x;
    for (x = 0; x < 1; x++)
    {
		printf("%c\n", *(key));
    }
    */

}

void mcopy(char* src, char* dest, size_t n) {
    int i;
    for (i=0; i<n; i++) 
        *(dest+i) = *(src+i); 
}

