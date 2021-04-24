//program used to convert from
//a psp image file to a binary file


//USAGE:
//typing TxtToBin.exe [filename] in cmd
//will place the result in myFile.bin.



//the psp image file (input) can be obtained with
//psp image converter (../psp/devsdk/tool/imgconverter);

//The psp image file that will be used as
//input for the current app
//must have the format:
[format]
[width]
[height]
[... hex data .... ]

//note that the file is not the current output of the imgConverter;
//use the option -F prag and process to a txt file with the needed format;

//[format] can be 5551, 4444, 5650 and 8888

//The output is a binary file conatining:
[_format]
[_width]
[_height]
[.... hex data ....]

//where forma,width and height are ints;
//hex data is unsigned short for 5551, 5650 and 4444, 
//and unsigned int for 8888.

//See samples folder for a sample .txt file.

