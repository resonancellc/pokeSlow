#include "pokeIndex.h"
#include "menuFunc.h"

int levelSelect(){
	int i=1;
	bool exit=false;
	consoleClear();
	printf("%s","Select new Level\n");
	printf("%d%s",i,"\n");
            do{
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
        hidScanInput();
        u32 kDown=hidKeysDown();
        if(kDown & KEY_A){
                exit=true;
        }
        if(kDown & KEY_DOWN){
                if(i<100){
                        i++;
                        consoleClear();
			printf("%s","Select new Level\n");
                        printf("%d%s",i,"\n");
                }
        }
        if(kDown & KEY_UP){
                if(i>1){
                        i=i-1;
                        consoleClear();
			printf("%s","Select new Level\n");
                        printf("%d%s",i,"\n");
                }
        }
    } while(!exit);
        return i;
}

int newAttackIndex(){
	int i=0;
	bool exit=false;
	consoleClear();
	printf("%s","Select new Attack\n");
	printf("%s%s",movesAlpha[i],"\n");
	    do{
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
        hidScanInput();
        u32 kDown=hidKeysDown();
        if(kDown & KEY_A){
                exit=true;
        }
        if(kDown & KEY_DOWN){
                if(i<166){
                        i++;
                        consoleClear();
			printf("%s","Select new Attack\n");
                        printf("%s%s",movesAlpha[i],"\n");
                }
        }
        if(kDown & KEY_UP){
                if(i>=1){
                        i=i-1;
                        consoleClear();
			printf("%s","Select new Attack\n");
                        printf("%s%s",movesAlpha[i],"\n");
                }
        }
    } while(!exit);
        return i;
}

int oldAttackIndex(char* saveFile,int pokeIndex){
	int i=0;
	bool exit=false;
	consoleClear();
	printf("%s","Which Attack would you like to change?\n");
	printf("%s%s",movesIndex[(int)saveFile[pokeIndex+8+i]],"\n");
    do{
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
        hidScanInput();
        u32 kDown=hidKeysDown();
        if(kDown & KEY_A){
                exit=true;
        }
        if(kDown & KEY_DOWN){
                if(i<3){
                        i++;
                        consoleClear();
			printf("%s","Which Attack would you like to change?\n");
                        printf("%s%s",movesIndex[(int)saveFile[pokeIndex+8+i]],"\n");
                }
        }
        if(kDown & KEY_UP){
                if(i>=1){
                        i=i-1;
                        consoleClear();
			printf("%s","Which Attack would you like to change?\n");
                        printf("%s%s",movesIndex[(int)saveFile[pokeIndex+8+i]],"\n");
                }
        }
    } while(!exit);
        return pokeIndex+8+i;
}

int newSpecMenu(char* saveFile){
	int i=0;
	bool exit=false;
	consoleClear();
	printf("%s","Select New Pokemon Species\n");
	printf("%s%s",pokeIndex[i],"\n");
    do{
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
        hidScanInput();
        u32 kDown=hidKeysDown();
        if(kDown & KEY_A){
                exit=true;
        }
        if(kDown & KEY_DOWN){
                if(i<151){
                        i++;
                        consoleClear();
			printf("%s","Select New Pokemon Species\n");
                        printf("%s%s",pokeIndex[i],"\n");
                }
        }
        if(kDown & KEY_UP){
                if(i>=1){
                        i=i-1;
                        consoleClear();
			printf("%s","Select New Pokemon Species\n");
                        printf("%s%s",pokeIndex[i],"\n");
                }
        }
    } while(!exit);
        return i;
}
int indexSelectMenu(char* saveFile){
	int i=0x101;
	int options=(int)saveFile[0x100];
	bool exit=false;
	consoleClear();
	printf("%s","Which Pokemon do you want to edit?\n");
	printf("%d%s%s%s",i-0x100," ",pokeSpec[(int)saveFile[i]],"\n");
    do{
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
        hidScanInput();
        u32 kDown=hidKeysDown();
        if(kDown & KEY_A){
                exit=true;
        }
        if(kDown & KEY_DOWN){
                if(i-0x100<options){
                        i++;
                        consoleClear();
			printf("%s","Which Pokemon do you want to edit?\n");
			printf("%d%s%s%s",i-0x100," ",pokeSpec[(int)saveFile[i]],"\n");
                }
        }
        if(kDown & KEY_UP){
                if(i-0x100>1){
                        i=i-1;
                        consoleClear();
			printf("%s","Which Pokemon do you want to edit?\n");
			printf("%d%s%s%s",i-0x100," ",pokeSpec[(int)saveFile[i]],"\n");
                }
        }
    } while(!exit);
        return i;
}
