void mewOT(FILE* fp){
	const char* ot="YOSHIRB";
	int i=0;
	while(i<7){
		int letter=pokeLetter(ot,i);
		fwrite(&letter,1,1,fp);
		i++;
	}
	int end=0x50;
	int blank=0x0000;
	fwrite(&end,1,1,fp);
	fwrite(&blank,2,1,fp);
	fwrite(&end,1,1,fp);
}

int importPkm(char* saveFile,int pokeIndex){
	int pkmSize=33;
	char* pkmFile=malloc(pkmSize+1);
	FILE* pkm=fopen("/pk/bank/pokemon.pkm","rb");
	if(pkm==NULL){
		printf("%s","Can't open pokemon.pkm");
	} else {
		fread(pkmFile, pkmSize, 1, pkm);
		int spec=pkmFile[0];
	        printf("%s","Injecting pkm...\n");
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
	        //Write new pkm Species to listings
	        fwrite(&spec,1,1,fp);
	        start=pokeStartFind(pokeIndex-0x100);
	        //Write bankgb until pokemon start
	        y++;
	        while(y<start){
	                fwrite(&saveFile[y],1,1,fp);
	                y++;
	        }
	        //Write pkm
		fwrite(&spec,1,1,fp);
		int i=1;
		while(i<pkmSize){
	        	fwrite(&pkmFile[i],1,1,fp);
			i++;
		}
		y+=pkmSize;
		if(pkmFile[0]==0x15){
			//Write until Mew OT
			while(y<(0x542+(11*(pokeIndex-0x101)))){
				fwrite(&saveFile[y],1,1,fp);
				y++;
			}
			mewOT(fp);
			y+=11;
		}
	        //Write the end of bankgb
	        while(y<fsize+1){
	                fwrite(&saveFile[y],1,1,fp);
	                y++;
	        }
	        fclose(fp);
		free(saveFile);
	        saveFile=saveOpen();
	        fixPokeName(saveFile,pokeIndex-0x100);
	        printf("%s","\nDone!");
		free(saveFile);
	}
	fclose(pkm);
	free(pkmFile);
        return 0;
}
