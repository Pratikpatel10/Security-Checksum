//Steve Louis 

# include<stdlib.h>
# include<stdio.h>

int VALID_SIZE_1 = 8;
int VALID_SIZE_2 = 16;
int VALID_SIZE_3 = 32;

int main(int argc,char **argv){

	int i;
	for(i = 2; i < argc; i += 2;){
		
		readFile(argv[i - 1], argv[i]);
	}
}

void readFile(char *fileName, int checkSumSize){
	
	int i, chunkSize, messgeSize, padding;
	char buffer, *message;
	FILE *ifp, *ofp;
	
	if((checkSumSize != VALID_SIZE_1) && (checkSumSize != VALID_SIZE_2) && (checkSumSize != VALID_SIZE_3)){
		
		fprintf(stderr,"Valid checksum sizes are 8, 16, or 32\n");
	}
	
	ifp = fopen(fileName, "r");
	
	i = 0;
	while((buffer = fgetc(ifp)) != EOF){
		
		i++;
	}
	
	messageSize = i;

	chunkSize = checkSumSize \ VALID_SIZE_1;

	padding = (messageSize % chunkSize)
	messageSize = messageSize + padding ;

	message = malloc((messageSize + 1) * sizeof (char));
	message[messageSize] = '\0';

	for(i = 0; i < messageSize; i++){
		
		message[i] = 'X';
	}
	
	fclose(ifp);
	
	ifp = fopen(fileName, "r");
	
	for(i = 0; ((buffer = fgetc(ifp)) != EOF); i++){
		
		if((i + 1) % 80 == 0){
			
			printf("\n");
		}
		printf("%c", buffer);
		message[i] = buffer;		
	}	
	checkSumCalc(message, checkSumSize, messageSize,chunkSize,);
}

void checkSumCalc(char *message, int checkSumSize, int messageSize, int chunkSize){
	
	int chunkSize = checkSumSize / 8;


}

int myPow(int base,int exponent){

	if(exponent == 0)
		return 1;

	return (base * myPow(base, exponent - 1));
}	
	