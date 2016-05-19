#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <3ds.h>
#include "pokeFind.h"
#include "indexList.h"
#include <stdlib.h>
#include <unistd.h>

int pokeSlow(void){
	FILE* fp;
	fp = fopen("/pk/bank/bankgb","rb");
	if(fp == NULL){
		printf("%s","Error opening bankgb\n");
	} else {
		printf("%s","Opened bankgb!\n");
		fseek(fp, 0, SEEK_END);
		unsigned int fsize = 0x8dff;
		fseek(fp, 0, SEEK_SET);
		char *saveFile = malloc(fsize+1);
		fread(saveFile, fsize, 1, fp);
		fclose(fp);
		int r = 37;
		printf("%s%s%s","Pokemon are changing into ",pokeSpec[r],"\n");
		FILE* fpBak = fopen("/pk/bank/bankgb.bak","wb");
		//Backup bankgb
		int z=0;
		while(z<fsize){
			fwrite(&saveFile[z],1,1,fpBak);
			z++;
		}
		fclose(fpBak);
		int numberOfPokes = saveFile[0x100];
		if(numberOfPokes>32){
			numberOfPokes=32;
		}
		printf("%s%d","Number of Pokes changing: ",numberOfPokes);
		unlink("/pk/bank/bankgb");
		FILE* fpSlow = fopen("/pk/bank/bankgb","ab");
		//Write begining of bankgb
		int y=0;
		while(y<0x101){
			fwrite(&saveFile[y],1,1,fpSlow);
			y++;
		}
		//Write Slowpoke species on all pokemon listings
		y=0;
		while(y<numberOfPokes){
			fwrite(&r,1,1,fpSlow);
			y++;
		}
		//Write bankgb until pokemon start
		int start=0x101+numberOfPokes;
		y=0;
		int tracker=start;
		while(tracker<pokeStartFind(1)){
			fwrite(&saveFile[y+start],1,1,fpSlow);
			y++;
			tracker++;
		}
		//Rewrite the pokemon
		int x=1;
		int w='\0';
		int pokeEnd='\0';
		tracker='\0';
		while(x<numberOfPokes+1){
			w=1;
			pokeEnd=pokeEndFind(x);
			fwrite(&r,1,1,fpSlow);
			start=pokeStartFind(x);
			tracker=start;
			while(tracker<pokeEnd){
				fwrite(&saveFile[w+start],1,1,fpSlow);
				w++;
				tracker++;
			}
			x++;
		}
		//Write the end of bankgb
		y=pokeEndFind(numberOfPokes)+1;
		while(y<fsize+1){
			fwrite(&saveFile[y],1,1,fpSlow);
			y++;
		}
		fclose(fpSlow);
	}
	printf("%s","\nDone!");
	return 0;
}
