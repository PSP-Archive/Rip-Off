//tool for converting textures to a bin file
//The input is a .txt file, obtained from a PSP
//specific format. The output is saved in myFile.bin.
//See readme.txt for details.


#include <fstream>
#include <stdio.h>
#include <iostream>
using namespace std;


int main(int argc, char **argv){


	ifstream file;
	string name;


	if ((argc)<2)
		name="a.txt";
	else name=argv[1];
	file.open(name.c_str());
	if (!file.is_open()){
		cout<<"failed to open file\n";
		return -1;
	}


	FILE * pFile;
	pFile = fopen ( "myFile.bin" , "wb" );
	if (!pFile) return -1;

	int format;
	int iNumber;
	unsigned int uiNumber;
	unsigned short usNumber, usVal;
	file>>format;
	fwrite(&format, 1, sizeof(int), pFile);

	//width
	file>>iNumber;
	fwrite(&iNumber, 1, sizeof(int), pFile);

	//height
	file>>iNumber;
	fwrite(&iNumber, 1, sizeof(int), pFile);

	char c;

	switch(format){
		case 5551:
			while((file>>hex>>usNumber)){
				fwrite(&usNumber, 1, sizeof(unsigned short), pFile);
				file>>c;
			}
			break;
		case 4444:
			while((file>>hex>>usNumber)){
				fwrite(&usNumber, 1, sizeof(unsigned short), pFile);
				file>>c;
			}
			break;
		case 5650:
			while((file>>hex>>usNumber)){
				fwrite(&usNumber, 1, sizeof(unsigned short), pFile);
				file>>c;
			}
			break;
		case 8888:
			while((file>>hex>>uiNumber)){
				fwrite(&uiNumber, 1, sizeof(unsigned short), pFile);
				file>>c;
			}
			break;
	}


	fclose (pFile);

}