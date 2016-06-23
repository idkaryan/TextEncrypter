#include "iostream"
#include "fstream"
#include "string"
#include "cstdio"
#include "conio.h"
#include "random"
#include "ctime"

using namespace std;
void encrypt();
void decrypt();

const int ENCRYPTION_SIZE_IN_BITS = 16;
const int minChange = 1;
const int maxChange = 5;
string sourceFile = "";
string targetFile = "";
ifstream tin;
ofstream to;
default_random_engine randomEngine(time(NULL));
uniform_int_distribution<int> roll(1111, 9999);

int main() {

	char input;
	printf("\n");
	printf(" ##########################\n");
	printf(" # Aryan's File Encrypter #\n");
	printf(" ##########################\n");
	printf("\n");
	printf("\t\t [#] This program uses 256 bit encryption and a 4 digit encryption key.\n\n");
	printf("\t\t [#] Input the source file name WITH extensions(.txt/.cpp/etc).\n");
	printf("\t\t     It's imperative for better encryption quality.\n\n");
	printf("\t\t ~ (c)tyrantRulez 2016\n");
	printf("\t\t   Contact_Info : idkaryan@gmail.com\n\n");
	while (true) {
		printf("\n");
		printf("\t .-----[ CHOOSE ]-----.\n");
		printf("\t |                    |\n");
		printf("\t |  1. Encrypt File   |\n");
		printf("\t |  2. Decrypt File   |\n");
		printf("\t |  3. Exit Program   |\n");
		printf("\t `--------------------`\n");
		printf("\n \t Your Choice : ");
		input = _getch();
		cout << input;
		switch (input) {
		case '1':
			encrypt();
			break;
		case '2':
			decrypt();
			break;
		case '3':
			return 1;
		default:
			printf("\t INVALID CHOICE\n\n");
		}
	}
	return 0;
}

void encrypt() {

	printf("\n\n");
	printf("  Enter the name of the source file : ");
	getline(cin, sourceFile);
	
	/* Getting the extension of source file:
	for (int i = sourceFile.size() - 1; i > 0; i--) {
		if (sourceFile[i] == '.') {
			while (i != sourceFile.size()) {
				sourceFileExtension.push_back(sourceFile[i]);
				i++;
			}
			break;
		}
	}
	// End of extension getter function.
	*/
	//Opened to check if it exists.
	tin.open(sourceFile);
	if (tin.fail()) {
		cout << endl << "  ";
		perror(sourceFile.c_str());
		char z = _getch();
		return;
	}
	tin.close();


	//Opened to check the size
	tin.open(sourceFile, ios_base::app | ios_base::ate);
	uint64_t fileSize = tin.tellg();
	tin.close();


	//Finally Opened for operation
	tin.open(sourceFile);

	printf("\n  Encrypting, please wait...\n");


	targetFile = sourceFile + "y";

	to.open(targetFile);

	int generatedCode = roll(randomEngine);

	static default_random_engine encrypter(generatedCode);
	uniform_int_distribution<int> change(minChange, maxChange);
	int encryptionKey[ENCRYPTION_SIZE_IN_BITS];

	for (int i = 0; i < ENCRYPTION_SIZE_IN_BITS; i++) {
		encryptionKey[i] = change(encrypter);
	}
	char bit = 0;
	

	while (tin.eof() == 0) {
			for (int i = 0; i < ENCRYPTION_SIZE_IN_BITS; i++) {					
				if (tin) {
					tin.get(bit);
					bit -= encryptionKey[i];
					to.put(bit);
					if (fileSize == tin.tellg()) {
						to.close();
					}
				}
			}
	}
	printf("\n  Encryption done.\n");
	printf("\n  Generated decryption key : %d ", generatedCode);
	printf("\n");
	to.close();
	tin.close();
}

void decrypt() {

	printf("\n\n");
	int decryptionCode = 0;
	char bit = 0;

	printf("\n  Enter the name of the source file for decryption : ");
	getline(cin, sourceFile);

	tin.open(sourceFile);
	if (tin.fail()) {
		cout << endl << "  ";
		perror(sourceFile.c_str());
		char z = _getch();
		return;
	}
	tin.close();

	tin.open(sourceFile, ios_base::app | ios_base::ate);
	uint64_t fileSize = tin.tellg();
	tin.close();
	
	/*Function to get sourceFileExtension from encrypted File
	tin.seekg(-1, ios::end);
	int fileEndPosition = tin.tellg();

	while (bit != '.') {
		tin.get(bit);
		tin.seekg(-2, ios::cur);
	}
	tin.get(bit);	//Right now , bit is " " so, this makes getPointer point right to "."
	
	while (tin.tellg() <= fileEndPosition) {
			tin.get(bit);
			sourceFileExtension.push_back(bit);
	}
	tin.seekg(0, ios::beg);
	// End of sourceFileExtension getter function*/

	tin.open(sourceFile);

	sourceFile.pop_back();

	string decryptedFile = sourceFile;

	to.open(decryptedFile);
	printf("\n  Enter the decryption key : ");
	cin >> decryptionCode;

	printf("\n  Decrypting, please wait...\n");
	static default_random_engine encrypter(decryptionCode);
	uniform_int_distribution<int> change(minChange, maxChange);
	int encryptionKey[ENCRYPTION_SIZE_IN_BITS];

	for (int i = 0; i < ENCRYPTION_SIZE_IN_BITS; i++) {
		encryptionKey[i] = change(encrypter);
	}

	
	while (tin) {
		for (int i = 0; i < ENCRYPTION_SIZE_IN_BITS; i++) {
			if (tin) {
				tin.get(bit);
				bit += encryptionKey[i];
				to.put(bit);
				if (fileSize == tin.tellg()) {
					to.close();
				}
			}
		}
	}
	
	printf("\n");
	printf("  Decryption done with key : %d \n\n", decryptionCode);
	printf("  Decrypted file is in the same folder as the source file. \n");


	tin.close();
	to.close();
}