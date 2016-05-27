void backupSave(char* saveFile){
	//Backup bankg
	FILE* fpBak=fopen("/pk/bank/bankgb.bak","wb");
	int z=0;
	while(z<0x8e00){
		fwrite(&saveFile[z],1,1,fpBak);
		z++;
	}
	fclose(fpBak);
}

char* saveOpen(void){
	FILE* fp;
	fp = fopen("/pk/bank/bankgb","rb");
	if(fp == NULL){
		printf("%s","Error opening bankgb\n");
		return "Error";
	} else {
		fseek(fp, 0, SEEK_END);
		unsigned int fsize = 0x8dff;
		fseek(fp, 0, SEEK_SET);
		char *saveFile = malloc(fsize+1);
		fread(saveFile, fsize, 1, fp);
		printf("%s","Opened bankgb!\n");
		return saveFile;
	}
	fclose(fp);
}
