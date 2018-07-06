//Steve Louis 

# include<stdlib.h>
# include<stdio.h>
# include <string.h>

void readFile(char *fileName, char *checkSumSize1);
void checkSumCalc(char *message, int checkSumSize, int messageSize, int chunkSize);
int myPow(int base, int exponent);

int main(int argc,char **argv){

	int i;
	for(i = 2; i < argc; i += 2){
		
		readFile(argv[i - 1], argv[i]);
	}
}

void readFile(char *fileName, char *checkSumSize1){
	
	int i, checkSumSize, chunkSize, messageSize, padding;
	char buffer, *message;
	FILE *ifp, *ofp;
	
	checkSumSize = atoi(checkSumSize1);

	if((checkSumSize != 8) && (checkSumSize != 16) && (checkSumSize != 32)){
		
		fprintf(stderr,"Valid checksum sizes are 8, 16, or 32\n");
	}
	
	ifp = fopen(fileName, "r");
	
	i = 0;
	while((buffer = fgetc(ifp)) != EOF){
		
		i++;
	}
	
	messageSize = i;

	chunkSize = (checkSumSize / 8);

	padding = (messageSize % chunkSize);
	messageSize = messageSize + padding ;

	message = malloc((messageSize + 1) * sizeof (char));
	message[messageSize] = '\0';

	for(i = 0; i < messageSize; i++){
		
		message[i] = 'X';
	}
	
	fclose(ifp);
	
	ifp = fopen(fileName, "r");
	
	for(i = 0; ((buffer = fgetc(ifp)) != EOF); i++){
		
		message[i] = buffer;		
	}	

	checkSumCalc(message, checkSumSize, messageSize, chunkSize);
}

void checkSumCalc(char *message, int checkSumSize, int messageSize, int chunkSize){
	
	int i, j, answer = 0;

	for(i = 0; i < messageSize; i++){

		for(i = 0; i < chunkSize; i++){

			answer += (int)message[ i + j];

			if(chunkSize > 0){

				answer += myPow(2, (j * 4)) - 1;
			}
		}
	}
	
	switch(checkSumSize){

		case 8:
			answer = answer & 0xFF;
		break;

		case 16:
			answer = answer & 0xFFFF;
		break;

		case 32:
			answer = answer & 0xFFFFFFFF;
		break;
	}

	for(i = 0; i < messageSize; i++){

		if((i == 0) || ((i + 1) % 80 == 0)){
			
			printf("\n");
		}
		printf("%c", message[i]);
	}
	printf("\n");

	printf("checkSumSize: %d\n", checkSumSize);
	printf("messageSize: %d\n", messageSize);
	printf("ANSWER: %d\n", answer);
}

int myPow(int base, int exponent){

	if(exponent == 0)
		return 1;

	return (base * myPow(base, exponent - 1));
}	
	