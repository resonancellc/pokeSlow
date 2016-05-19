int pokeStartFind(int pokeNum){
        int pokeStart = 0x122;
        int result = pokeStart + ((pokeNum-1) * 33);
        return result;
}


int pokeEndFind(int pokeNum){
        int pokeStart = pokeStartFind(pokeNum);
	int result = pokeStart+32;
        return result;
}

int pokeSpecFind(char* saveFile,int pokeNum){
	int pokeIndex='\0';
	int pokeStart = pokeStartFind(pokeNum);
	pokeIndex=saveFile[pokeStart];
	printf("%02X",pokeIndex);
	return pokeIndex;
}
