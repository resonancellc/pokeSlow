#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "pokeFind.h"
#include "indexList.h"
#include <stdlib.h>
#include <unistd.h>

int pokeSpecEdit(char* saveFile,int pokeIndex, int* newSpecIndex){
	printf("%s","Writing new Pokemon.\n");
        unsigned int fsize = 0x8dff;
        int start=0x100+pokeIndex;
	remove("/pk/bank/bankgb");
        FILE* fp=fopen("/pk/bank/bankgb","ab");
	if(fp==NULL){
		printf("%s","Error opening file\n");
	} else {
		printf("%s","Writing bankgb...\n");
	}
        //Write begining of bankgb
        int y=0;
        while(y<start){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        //Write new Pokemon Species to listings
        fwrite(newSpecIndex,1,1,fp);
        //Write bankgb until pokemon start
        y=1;
        int tracker=start+1;
        while(tracker<pokeStartFind(pokeIndex)){
                fwrite(&saveFile[y+start],1,1,fp);
                y++;
                tracker++;
        }
        //Write new Pokemon Species
        fwrite(newSpecIndex,1,1,fp);
        //Write the end of bankgb
        y=y+start+1;
        while(y<fsize+1){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        fclose(fp);
        printf("%s","\nDone!");
        return 0;
}

int pokeSlow(char* saveFile){
	unsigned int fsize = 0x8dff;
	int r=37;
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
	printf("%s","\nDone!");
	return 0;
}
