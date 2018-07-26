// Steve Louis 
// CIS 3360 Checksum
// 7/27/2018

# include<stdlib.h>
# include<stdio.h>
# include <string.h>

void readFile(char *fileName, char *checkSumSize1);
void checkSumCalc(char *message, int checkSumSize, int messageSize, int chunkSize);
int myPow(int base, int exponent);

int main(int argc, char **argv){

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

	if((padding = (messageSize % chunkSize)) != 0){

		padding = chunkSize - padding;
	}

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

	fclose(ifp);

	checkSumCalc(message, checkSumSize, messageSize, chunkSize);
}

void checkSumCalc(char *message, int checkSumSize, int messageSize, int chunkSize){
	
	int i, j;
	unsigned long int answer = 0;

	for(i = 0; i < messageSize; i += chunkSize){

		for(j = 0; j < chunkSize ; j++){

			answer += (unsigned long int)message[ i + j] * myPow(2, ((chunkSize - j - 1) * 8));
		}
	}
	
	switch(checkSumSize){

		case 8:
			answer = answer & 0xff;
		break;

		case 16:
			answer = answer & 0xffff;
		break;

		case 32:
			answer = answer & 0xffffffff;
		break;
	}

	printf("\n");
	for(i = 0; i < messageSize; i++){

		printf("%c", message[i]);

		if((i + 1) % 80 == 0){
			
			printf("\n");
		}
		
	}
	printf("\n");

	printf("%2d bit checksum is %8lx for all %4d chars\n",checkSumSize, answer, messageSize);
}

int myPow(int base, int exponent){

	int m;

	if(exponent == 0){
		return 1;
	}

	if (exponent % 2 == 0) {
        m = myPow(base, exponent / 2);
        return m * m;
    }

    else{
    	return (base * myPow(base, exponent - 1));
    }	
}		