#include "pokeIndex.h"

int pokeIndexFind(size_t size,const char* pokeSpecName){
	int i=0;
	while((i<size)&&(pokeSpec[i]!=pokeSpecName)){
		i++;
	}
	if(i<size){
		return i;
	} else {
		return -1;
	}
}

char* selection(int tracker,int i){
	if(tracker==i){
		return ">";
	} else {
		return " ";
	}
}

int menuCreate(int i,int options,char* menuList[],char* message){
	int tracker=0;
	char* select=" ";
	consoleClear();
	printf("%s",message);
	while(tracker<options){
		select=selection(tracker,i);
		printf("%s%s%s",select,menuList[tracker],"\n");
		tracker++;
	}
	return i;
}

int menu(int menuNum,char* saveFile){
	consoleClear();
	int i=0;
	char* message=" ";
	int options=0;
	int numberOfPokes=saveFile[0x100]-1;
	if(numberOfPokes>32){
		numberOfPokes=32;
	}
	int currentIndex=saveFile[0x101];
	char* menuList[]={" "};
	char* mainMenu[3] = {"Change One Pokemon's Species","Convert All Pokemon to Slowpokes","Exit"};
	char* pokeMenu[2] = {"Select Pokemon to Change Species","Back"};
	char* pokeSlowMenu[3] = {"Yes","No","Back"};
	bool exit=false;
	if(menuNum==1){
		message="Welcome to The Matrix\n";
		printf("%s",message);
		printf("%s%s%s",">",mainMenu[0],"\n");
		printf("%s%s%s"," ",mainMenu[1],"\n");
		printf("%s%s%s"," ",mainMenu[2],"\n");
	} else if(menuNum==2){
		message="Pokemon Species Change\n";
		printf("%s",message);
		printf("%s%s%s",">",pokeMenu[0],"\n");
		printf("%s%s%s"," ",pokeMenu[1],"\n");
	} else if(menuNum==3){
		message="Are you sure you want all Slowpokes in Box 1?\n";
		printf("%s",message);
		printf("%s%s%s",">",pokeSlowMenu[0],"\n");
		printf("%s%s%s"," ",pokeSlowMenu[1],"\n");
		printf("%s%s%s"," ",pokeSlowMenu[2],"\n");
	} else if(menuNum==4){
		message="Which Pokemon do you want to edit?\n";
		printf("%s",message);
		options=numberOfPokes;
		printf("%s%d%s%s%s",">",1," ",pokeSpec[currentIndex],"\n");
	} else if(menuNum==5){
		message="Select New Species\n";
		options=151;
		printf("%s",message);
		printf("%s%s%s",">",pokeIndex[0],"\n");
	}
	while(!exit){
		if(menuNum==1){
			options=3;
			memcpy(&menuList, &mainMenu, sizeof(mainMenu));
		} else if(menuNum==2){
			options=2;
			memcpy(&menuList, &pokeMenu, sizeof(pokeMenu));
		} else if(menuNum==3){
			options=3;
			memcpy(&menuList, &pokeSlowMenu, sizeof(pokeSlowMenu));
		} else if(menuNum==4){
			options=numberOfPokes;
		}
		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
		hidScanInput();
		u32 kDown=hidKeysDown();
		if(kDown & KEY_A){
			exit=true;
		}
		int arr=(sizeof(menuList)/sizeof(*menuList))-1;
		if(kDown & KEY_DOWN){
			if(i<options){
				i++;
			}
			if(menuNum!=4 && menuNum!=5){
				i=menuCreate(i,options,&menuList[arr],message);
			} else if(menuNum==4){
				consoleClear();
				printf("%s",message);
				currentIndex=saveFile[0x101+i];
				printf("%s%d%s%s%s",">",i+1," ",pokeSpec[currentIndex],"\n");
			} else if(menuNum==5){
				consoleClear();
				printf("%s",message);
				printf("%s%s%s",">",pokeIndex[i],"\n");
			}
		}
		if(kDown & KEY_UP){
			if(i>=1){
				i=i-1;
			}
			if(menuNum!=4 && menuNum!=5){
				i=menuCreate(i,options,&menuList[arr],message);
			} else if(menuNum==4){
				consoleClear();
				currentIndex=saveFile[0x101+i];
				printf("%s",message);
				printf("%s%d%s%s%s",">",i+1," ",pokeSpec[currentIndex],"\n");
			} else if(menuNum==5){
				consoleClear();
				printf("%s",message);
				printf("%s%s%s",">",pokeIndex[i],"\n");
			}
		}
	}
	return i;
}
