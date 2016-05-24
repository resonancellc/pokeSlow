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

int attackFind(char* saveFile, int index,int atkNum){
        return saveFile[index+8+atkNum];
}

int attackStart(int index, int atkNum){
	return pokeStartFind(index+1)+8+atkNum;
}

int attackIndexFind(size_t size,const char* attackName){
	int i=0;
	while((i<size)&&(movesIndex[i]!=attackName)){
		i++;
	}
	if(i<size){
		return i;
	} else {
		return -1;
	}
}

void attackEdit(char* saveFile,int oldAtkIndex,int newAtkForIndex){
	int newAtkIndex=attackIndexFind(165,movesAlpha[newAtkForIndex]);
        printf("%s","Writing new Attack.\n");
        unsigned int fsize = 0x8dff;
        int start=oldAtkIndex;
        remove("/pk/bank/bankgb");
        FILE* fp=fopen("/pk/bank/bankgb","ab");
        if(fp==NULL){
                printf("%s","Error opening file\n");
        } else {
                printf("%s","Writing bankgb...\n");
        }
        //Write until Attack
        int y=0;
        while(y<start){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        //Write new Attack
        fwrite(&newAtkIndex,1,1,fp);
	//Write pokemon until PP
	y=start+1;
	while(y<start+0x15){
		fwrite(&saveFile[y],1,1,fp);
		y++;
	}
	//Write new Attack PP
	fwrite(&movesPP[newAtkIndex],1,1,fp);
        //Write the end of bankgb
        y++;
        while(y<fsize+1){
                fwrite(&saveFile[y],1,1,fp);
                y++;
        }
        fclose(fp);
        printf("%s","\nDone!");
}

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

void menu123(int i,char* menuList[],char* message,int options){
	int arr=(sizeof(&menuList)/sizeof(*menuList))-1;
	menuCreate(i,options,&menuList[arr],message);
}

void menu4(int i,char* message,char* saveFile){
	consoleClear();
	int currentIndex=saveFile[0x101+i];
	printf("%s",message);
	printf("%s%d%s%s%s",">",i+1," ",pokeSpec[currentIndex],"\n");
}

void menu5(int i,char* message){
	consoleClear();
	printf("%s",message);
	printf("%s%s%s",">",pokeIndex[i],"\n");
}

void menu6(int i,char* message,char* saveFile){
	consoleClear();
	int currentIndex=saveFile[0x101+i];
	printf("%s",message);
	printf("%s%d%s%s%s",">",i+1," ",pokeSpec[currentIndex],"\n");
}

void menu7(int i,int var,char* message,char* saveFile){
	consoleClear();
	printf("%s",message);
	printf("%s%s%s",">",movesIndex[attackFind(saveFile,var,i)],"\n");
}

void menu8(int i,char* message){
	consoleClear();
	printf("%s",message);
	printf("%s%s%s",">",movesAlpha[i],"\n");
}

void menu9(int i,char* message){
	consoleClear();
	printf("%s",message);
	printf("%s%d%s",">",i,"\n");
}
