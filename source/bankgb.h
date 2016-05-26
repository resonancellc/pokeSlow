#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "pokeFind.h"
#include "indexList.h"
#include <stdlib.h>
#include <unistd.h>
#include "exp.h"

void evMax(char* saveFile,int pokeIndex){
        printf("%s","Writing new EVs...\n");
        remove("/pk/bank/bankgb");
        unsigned int fsize=0x8dff;
        FILE* fp=fopen("/pk/bank/bankgb","ab");
        if(fp==NULL){
                printf("%s","Error opening file\n");
        } else {
                printf("%s","Writing bankgb...\n");
        }
        //Write until Pokemon EVs
        int y=0;
        int pokeStart=pokeIndex;
        int ivStart=pokeStart+0x11;
        while(y<ivStart){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        //Write new Pokemon EVs
        int maxEVs=0xFFFF;
	int i=0;
	while(i<5){
	        fwrite(&maxEVs,2,1,fp);
		i++;
	}
        //Write the end of bankgb
        y+=10;
        while(y<fsize+1){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        fclose(fp);
        printf("%s","\nDone!");
}

void ivMax(char* saveFile,int pokeIndex){
        printf("%s","Writing new IVs...\n");
        remove("/pk/bank/bankgb");
        unsigned int fsize=0x8dff;
        FILE* fp=fopen("/pk/bank/bankgb","ab");
        if(fp==NULL){
                printf("%s","Error opening file\n");
        } else {
                printf("%s","Writing bankgb...\n");
        }
	//Write until Pokemon IVs
        int y=0;
        int pokeStart=pokeIndex;
        int ivStart=pokeStart+0x1B;
        while(y<ivStart){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        //Write new Pokemon IVs
	int maxIVs=0xFFFF;
        fwrite(&maxIVs,2,1,fp);
        //Write the end of bankgb
        y+=2;
        while(y<fsize+1){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        fclose(fp);
        printf("%s","\nDone!");
}

bool inArray(const char* array[],const char* item,int size){
	int i=0;
	printf("%s%d%s","Size of array = ",size,"\n");
	while((i<size)&&(array[i]!=item)){
		i++;
	}
	if(i!=size){
		return true;
	} else {
		return false;
	}
}

int power(int base, unsigned int exp) {
	int i=0;
	int result=1;
	while(i<exp){
		result *= base;
		i++;
	}
	return result;
}

void expCalc(int pokeIndex, int newLevel, FILE* fp){
	int32_t expHex=0x01;
	const char* pokeName=pokeSpec[pokeIndex];
	if(inArray(expType1,pokeName,26)==true){
		expHex = (power(newLevel,3)) * 1.25;
	} else if(inArray(expType2,pokeName,80)==true){
		expHex = power(newLevel,3);
	} else if(inArray(expType3,pokeName,40)==true){
		expHex = ((1.2 * power(newLevel,3)) - (15 * (power(newLevel,2))) + (100 * newLevel - 140));
	} else if(inArray(expType4,pokeName,5)==true){
		expHex = (power(newLevel,3)) * 0.8;
	}
        FILE* fpExp=fopen("/pk/bank/exp","ab");
	fwrite(&expHex,3,1,fpExp);
	fclose(fpExp);
	FILE* fpExpRead=fopen("/pk/bank/exp","rb");
        fseek(fpExpRead, 0, SEEK_END);
        unsigned int fsize = 0x03;
        fseek(fpExpRead, 0, SEEK_SET);
        char *exp = malloc(fsize+1);
        fread(exp, fsize, 1, fpExpRead);
        fclose(fpExpRead);
	fwrite(&exp[2],1,1,fp);
	fwrite(&exp[1],1,1,fp);
	fwrite(&exp[0],1,1,fp);
	remove("/pk/bank/exp");
	free(exp);
}

int levelEdit(char* saveFile,int pokeIndex,int newLevel){
	printf("%s","Writing new Level...\n");
	remove("/pk/bank/bankgb");
        unsigned int fsize=0x8dff;
        FILE* fp=fopen("/pk/bank/bankgb","ab");
        if(fp==NULL){
                printf("%s","Error opening file\n");
        } else {
                printf("%s","Writing bankgb...\n");
        }
        //Write until Pokemon level
        int y=0;
	int pokeStart=pokeIndex;
        int levelStart=pokeStart+0x03;
        while(y<levelStart){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        //Write new Pokemon Level
	fwrite(&newLevel,1,1,fp);
	//Write until exp
	y++;
	while(y<pokeStart+0x0E){
		fwrite(&saveFile[y],1,1,fp);
		y++;
	}
	//Write exp
	expCalc((int)saveFile[pokeIndex],newLevel,fp);
        //Write the end of bankgb
	y+=3;
        while(y<fsize+1){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        fclose(fp);
        printf("%s","\nDone!");
	return 0;
}
int pokeLetter(const char* name,int letterNum){
        int letter=(int)name[letterNum];
        return (int)toupper(letter)+0x3F;
}
int fixPokeName(char* saveFile,int pokeIndex){
	printf("%s","Fixing the Pokemon's name.\n");
	unsigned int fsize=0x8dff;
	remove("/pk/bank/bankgb");
        FILE* fp=fopen("/pk/bank/bankgb","ab");
        if(fp==NULL){
                printf("%s","Error opening file\n");
        } else {
                printf("%s","Writing bankgb...\n");
        }
        //Write until Pokemon name
        int y=0;
	int pokeNum=saveFile[0x100+pokeIndex];
	const char* name=pokeSpec[pokeNum];
        int nameStart=0x6A2+(11*(pokeIndex-1));
        while(y<nameStart){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        //Write new Pokemon Name
        int letterTracker=0;
        int letterVal=0x50;
        int extra=11-strlen(name);
        while(letterTracker<strlen(name)){
                letterVal=pokeLetter(name,letterTracker);
                fwrite(&letterVal,1,1,fp);
                letterTracker++;
        }
        letterTracker=0;
        letterVal=0x50;
        while(letterTracker<extra){
                fwrite(&letterVal,1,1,fp);
                letterTracker++;
        }
        //Write the end of bankgb
        y=nameStart+11;
        while(y<fsize+1){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }

        fclose(fp);
        printf("%s","\nDone!");
	return 0;
}

int pokeSpecEdit(char* saveFile,int pokeIndex, int* newSpecIndex){
	int Mew=0x15;
	int Rhydon=0x01;
	if(newSpecIndex==&Mew){
		newSpecIndex=&Rhydon;
	}
        printf("%s","Writing new Pokemon.\n");
        unsigned int fsize = 0x8dff;
        int start=pokeIndex;
        int sub=33;
        while(start>=0x122){
                start=start-sub;
                sub=sub-1;
        }
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
	start=pokeStartFind(pokeIndex-0x100);
        //Write bankgb until pokemon start
        y++;
        while(y<start){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        //Write new Pokemon Species
        fwrite(newSpecIndex,1,1,fp);
        //Write the end of bankgb
        y++;
        while(y<fsize+1){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        fclose(fp);
	saveFile=saveOpen();
	fixPokeName(saveFile,pokeIndex-0x100);
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
