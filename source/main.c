#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "sav.h"
#include "bankgb.h"
#include <3ds.h>
#include "moves.h"
#include "menu.h"
#include "mainMenu.h"

int errorCheck(char* saveFile){
	int error=2;
	if(strcmp(saveFile,"Error")==0){
		printf("%s","Error opening save file.\nPress Start to exit.\n");
		bool exit=false;
		while(!exit){
			hidScanInput();
			u32 kDown=hidKeysDown();
			if(kDown & KEY_START){
				error=0;
				exit=true;
			}
		}
	} else {
		error=1;
	}
	return error;
}
int main(int argc, char **argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	char* saveFile=malloc(0x8E00);
	saveFile=saveOpen();
	if(errorCheck(saveFile)==0){
		return 0;
	}
	int job=100;
	int oldIndex=0;
	backupSave(saveFile);
	while (aptMainLoop())
	{
		if(job==100){
			job=mainMenu();
		} else if(job==0){
			saveFile=saveOpen();
			oldIndex=indexSelectMenu(saveFile);
                	int newIndex=newSpecMenu(saveFile);
			newIndex=pokeIndexFind(192,pokeIndex[newIndex]);
                	pokeSpecEdit(saveFile,oldIndex,&newIndex);
			job=100;
		} else if(job==1){
			saveFile=saveOpen();
			oldIndex=indexSelectMenu(saveFile);
			oldIndex=pokeStartFind(oldIndex-0x100);
	                int oldAtkIndex=oldAttackIndex(saveFile,oldIndex);
	                int newAtkIndex=newAttackIndex();
	                attackEdit(saveFile,oldAtkIndex,newAtkIndex);
			job=100;
		} else if(job==2){
			saveFile=saveOpen();
                        oldIndex=indexSelectMenu(saveFile);
                        oldIndex=pokeStartFind(oldIndex-0x100);
                        int level=levelSelect();
                        levelEdit(saveFile,oldIndex,level);
                        job=100;
		} else if(job==3){
			saveFile=saveOpen();
                        oldIndex=indexSelectMenu(saveFile);
                        oldIndex=pokeStartFind(oldIndex-0x100);
                        ivMax(saveFile,oldIndex);
			job=100;
		} else if(job==4){
			saveFile=saveOpen();
			oldIndex=indexSelectMenu(saveFile);
			oldIndex=pokeStartFind(oldIndex-0x100);
			evMax(saveFile,oldIndex);
			job=100;
		} else if(job==5){
			saveFile=saveOpen();
			pokeSlow(saveFile);
			job=100;
		} else if(job==6){
			break;
		}
	}

	gfxExit();
	return 0;
}
