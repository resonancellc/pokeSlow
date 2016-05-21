#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "sav.h"
#include "bankgb.h"
#include <3ds.h>
#include "menu.h"

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
	char* saveFile=saveOpen();
	if(errorCheck(saveFile)==0){
		return 0;
	}
	backupSave(saveFile);
	int oldPokeIndex=1;
	int job=menu(1,saveFile);
	while (aptMainLoop())
	{
		//Main Menu
		if(job==2){
			//Closes App
			break;
		} else if(job==0){
			saveFile=saveOpen();
			//Changes One Pokemon Species
			job=menu(2,saveFile);
			if(job==1){
				//Back to Main Menu
				job=menu(1,saveFile);
			} else if(job==0){
				//Select Index Pokemon to edit
				oldPokeIndex=menu(4,saveFile);
				//Select New Pokemon Species
				int newSpec=pokeIndexFind(192,pokeIndex[menu(5,saveFile)]);
				saveFile=saveOpen();
				if(errorCheck(saveFile)!=0){
					pokeSpecEdit(saveFile,oldPokeIndex+1,&newSpec);
					printf("%s","Opened save.\n");
				} else {
					break;
				}
				//Back to Main Menu
				job=menu(1,saveFile);
			}
		} else if(job==1){
			//Converts All Pokemon to Slowpoke
			job=menu(3,saveFile);
			if(job==2){
				//Back to Main Menu
				job=menu(1,saveFile);
			} else if(job==0){
				//Activate pokeSlow(); and back to Main Menu
				saveFile=saveOpen();
				if(errorCheck(saveFile)!=0){
					pokeSlow(saveFile);
				} else {
					break;
				}
				job=menu(1,saveFile);
			}
		}
	}

	gfxExit();
	return 0;
}
