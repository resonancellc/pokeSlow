void mainPrints(int i){
	printf("%s","Welcome to the Matrix\n");
        switch(i)
        {
            case 0: printf("%s","Change a Pokemon's Species\n");
                break;
            case 1: printf("%s","Change a Pokemon's Attacks\n");
                break;
            case 2: printf("%s","Edit the Level of a Pokemon\n");
                break;
            case 3: printf("%s","Max a Pokemon's IVs\n");
                break;
	    case 4: printf("%s","Max a Pokemon's EVs\n");
		break;
	    case 5: printf("%s","Convert All Pokemon to Slowpokes\n");
		break;
	    case 6: printf("%s","Import pokemon.pkm from SD\n");
		break;
            case 7: printf("%s","Exit\n");
                break;
        }
}

int mainMenu(){
    int i=0;
    bool exit=false;
    consoleClear();
    printf("%s","Welcome to the Matrix\n");
    printf("%s","Change a Pokemon's Species\n");
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
		if(i<7){
			i++;
			consoleClear();
			mainPrints(i);
		}
	}
	if(kDown & KEY_UP){
		if(i>1){
			i=i-1;
			consoleClear();
			mainPrints(i);
		}
	}
    } while(!exit);
	return i;
}
