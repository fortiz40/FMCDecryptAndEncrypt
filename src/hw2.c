// Francisco Ortiz
// ortizf

#include "morsecode.h"
#include "hw2.h"

char* MorseCode[] = {MorseExclamation, MorseDblQoute, MorseHashtag, Morse$, MorsePercent, MorseAmp, MorseSglQoute, MorseOParen, MorseCParen, MorseStar, MorsePlus, MorseComma, MorseDash, MorsePeriod, MorseFSlash, Morse0, Morse1, Morse2, Morse3, Morse4, Morse5, Morse6, Morse7, Morse8, Morse9, MorseColon, MorseSemiColon, MorseLT, MorseEQ, MorseGT, MorseQuestion, MorseAt, MorseA, MorseB, MorseC, MorseD, MorseE, MorseF, MorseG, MorseH, MorseI, MorseJ, MorseK, MorseL, MorseM, MorseN, MorseO, MorseP, MorseQ, MorseR, MorseS, MorseT, MorseU, MorseV, MorseW, MorseX, MorseY, MorseZ};

/* Part 1 Functions */
int toMorse(FILE *instream, char **mcmsg_ptr){
        // Insert code here

	int size = sizeof(char)*100;
	char * buf  = (char*)malloc(size);
	*(mcmsg_ptr) = buf;
	
	char a;

	int index = 0;

	while(1)
	{
		a = fgetc(instream);
		if (a == EOF) 
		{
			if (*(buf + index - 2) != 'x') *(buf + index) = 'x';
			//*(buf + index + 1) = '\0';
			*(mcmsg_ptr) = buf;
			break;
		}
		if (a == ' ')
		{
		//	addWordSeparator();
			if ( index > 0)
			{
				if ( *(buf + index - 2) != 'x')
				{
					*(buf + index) = 'x';
					index++;
				}
			}
			
		}
		if ( a >= '!' && a <= 'z' && a != ' ')
		{
		//	addChar();
			if ( a >= 'a' && a <= 'z') a = a - 32;
			char * x = *(MorseCode + a - 33);
			char y;
			int z = 0;
			while( *(x + z) != '\0')
			{
				*(buf + index) = *(x + z);
				z++;
				index++;
			}
			*(buf + index) = 'x';
			index++;
		}

		if ( (index * sizeof(char) + 30) >= size)
		{
			size = size + 200;
			char * new_buf = (char*)realloc(buf, size);
			if (new_buf  == NULL) return -1;
			buf = new_buf;
		}
	}

        return 1;
}

void createKey(char* keyphrase, char* key){
	char a;
	
	int index = 0;
	int k_ind = 0;
	//char * foo = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char * foo = (char*)malloc(sizeof(char) * 26);
	int y;
	int z = 65;
	for ( y = 0; y < 26; y++)
	{
		*(foo + y) = z;
		z++;
	}

	int n;
	while(1)
	{
		a = *(keyphrase + index);
		if (a == '\0') break;

		if (a >= 'a' && a <= 'z') a = a - 32;

		if (a >= 'A' && a <= 'Z')
		{
			if ( *(foo + a - 65) != 'x')
			{
				*(key + k_ind) = a;
				k_ind++;
				n = (int)a;
				*(foo + n - 65) = 'x';
			}
		}
		index++;
	}

	int x;
	for (x = 0; x < 26; x++)
	{
		if ( *(foo + x) != 'x')
		{
			*(key + k_ind) = *(foo + x);
			k_ind++;
		}
	}
	
	//key = buf;

}

char morseToKey(char* mcmsg, char* key){
    char* FMCarray = ".....-..x.-..--.-x.x..x-.xx-..-.--.x--.-----x-x.-x--xxx..x.-x.xx-.x--x-xxx.xx-";
	
	int index = 0;
	char a;
	char b;
	char c;

	while (1)
	{
		a = *(FMCarray + index * 3);
		b = *(FMCarray + index * 3 + 1);
		c = *(FMCarray + index * 3 + 2);
		if (a == '\0' || b == '\0' || c == '\0') break;
		if ( a == *(mcmsg) && b == *(mcmsg + 1) && c == *(mcmsg + 2))
		{
			return *(key + index);
		}

		index++;

		
	}
 
        return -1;
}

int FMCEncrypt(FILE *instream, char* key, FILE *outstream){
        
	int bi = 0;
	int size = 100;
	char ** buf = (char**)malloc(sizeof(char));;
	int x = toMorse(instream, buf);
	if (x == -1) return -1; // Ran out of memory
	//
	char * b = *buf;
	//fprintf(outstream, "%c\n", **buf);
	int q;
	int y = 0;
	while(1)
	{
		q = morseToKey( b, key);
		if (q != -1)
		{
			fprintf(outstream, "%c", (char)q);
		}
		b = b + 3;
		if ( *(b) == '\0') break;
		y++;
	}
	//fprintf(outstream, "%s\n", *buf);
	//fprintf(outstream, "HELLOWORLD\n");
	//fclose(outstream);
	
	//fprintf(outstream, "%c\n", 'D');
	return 1;
}

/* Part 2 Functions */
int fromMorse(char *mcmsg, FILE* outstream){

	char * buf = (char *)malloc(sizeof(char) * 10);

	char a;
	int msg_i = 0;
	int buf_i = 0;
	//fprintf(outstream, "HELLO\n");
	while(1)
	{
		//fprintf(outstream, "No way!");
		a = *(mcmsg + msg_i);
		//fprintf(outstream, "%c", a + 65);
		if (a == '\0' || *(mcmsg + msg_i + 1) == '\0' )
		{	
		//	fprintf(outstream, "BREAKING");
			break;
		}
		if ( a != 'x')
		{
			*(buf + buf_i) = a;
			buf_i++;
			msg_i++;
		}

		else if ( a == 'x')
		{
			//fprintf(outstream, "%c" , 'P');
		
			if ( *(mcmsg + msg_i - 1) == 'x')
			{
				
				fprintf(outstream, "%c", ' ');
				msg_i++;
				
			}
			else{
			*(buf + buf_i) = '\0';
			int k;
			int match;
			int m;
			for (k = 0; k < 58; k++)
			{
				char * x = *(MorseCode + k);

				match = 1;
				m = 0;
				while(1)
				{
					if ( *(buf + m) == '\0' && *(x + m) == '\0') break;
					if ( *(buf + m) != *(x + m) )
					{
						match = 0;
						break;
					}
					m++;
				}



				if ( match == 1 )
				{	
					fprintf(outstream, "%c", (char)(k + 33));
					break;
				}
			}
			
			buf_i = 0;
			int f;
			msg_i++;
			/*	
			msg_i++;

			if ( *(mcmsg + msg_i) == 'x')
			{
				if ( (*mcmsg + msg_i + 1) == '\0') break;
				else
				{
					fprintf(outstream, "%c", ' ');
					msg_i++;
				}
			} */
			}
		}


	}

        return 1;
}

int FMCDecrypt(FILE *instream, char* key, FILE *outstream){
	char* FMCarray = ".....-..x.-..--.-x.x..x-.xx-..-.--.x--.-----x-x.-x--xxx..x.-x.xx-.x--x-xxx.xx-";
	
	char * buf = (char *)malloc(sizeof(char) * 200);
	char a;
	int size = 200;
	int i = 0;
	//a = fgetc(instream);
	//fprintf(outstream, "%c", a);
	int x;
	while ( (a = fgetc(instream)) != EOF)
	{	
		//fprintf(outstream, "%c", a);

		for ( x = 0; x < 26; x++)
		{
			if ( *(key + x) == a) break;
		}
		
		*(buf + i) = *(FMCarray + (x * 3));
		*(buf + i + 1) = *(FMCarray + (x*3) + 1);
		*(buf + i + 2) = *(FMCarray + (x*3) + 2);
		i = i + 3;
		
		if ( (i + 30) >= size)
		{
			size = size + sizeof(char)* 100;
			char * temp = (char*)realloc(buf, size);
			if ( temp == NULL) return -1;
			buf = temp;
		} 	
	}
	
	*(buf + i) = 'x';
	i++;
	*(buf + i) = 'x';
	i++;
	*(buf + i) = '\0';


	fromMorse(buf, outstream);
        return 1;
}

