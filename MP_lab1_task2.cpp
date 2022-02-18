﻿
#include <iostream>
#include <fstream>
#include <string>



struct Token {
	int count;
	int lastPage;
	int* pages;
	std::string word;
};



Token* vocabulary = new Token[10000];
std::string* stopWords = new std::string[200];
int rowsOnPage = 45;
std::string fileName = "C:\\Code\\try\\asd1.txt";
std::string stopWordsFileName = "C:\\Code\\try\\stop.txt";



int main() {
	std::fstream inFile(fileName);
	std::fstream stopWordsInFile(stopWordsFileName);
	std::string line = "";
	std::string word = "";
	bool isStopWord = false;
	int currentPage = 0;
	int currentLine = 0;
	int topN = 0;
	int wordPosition = -1;
	int wordsCount = 0;
	int stopWordsCount = 0;
	int wordToPrint = 0;
	int out = 0;
	int in = 0;
	int j;
	int i;

	std::cout << "How many words you want to be printed?" << std::endl;
	std::cin >> topN;

	if (!inFile.is_open())
		std::cout << "Failed to open file" << std::endl;
	if (!stopWordsInFile.is_open())
		std::cout << "Failed to open file" << std::endl;



Reading: 
	i = 0;
	if (!std::getline(inFile, line)) goto _Reading;
	currentLine++;
	word = "";

	if (currentLine == rowsOnPage)
	{
		currentPage++;
		currentLine = 0;
	}

	goto ParsingLine;
_ParsingLine:

	goto Reading;
_Reading:

ReadingStopWords:
	if (!std::getline(stopWordsInFile, line)) goto _ReadingStopWords;
	stopWords[stopWordsCount] = line;
	stopWordsCount++;
	goto ReadingStopWords;
_ReadingStopWords:

Sorting: 
OutterLoop:
	in = 1;
InnerLoop:
	if (vocabulary[in - 1].count < vocabulary[in].count)
	{
		Token temp = vocabulary[in - 1];
		vocabulary[in - 1] = vocabulary[in];
		vocabulary[in] = temp;
	}
	in++;
	if (in < wordsCount - out) goto InnerLoop;
	out++;
	if (out < wordsCount - 1) goto OutterLoop;
_Sorting:

PrintingResult: 
	wordToPrint++;
	isStopWord = false;
	i = 0;
	goto CheckStopWord;
_CheckStopWord:

	if (!isStopWord && vocabulary[wordToPrint].count <= 100)
	{
		topN--;
		std::cout << vocabulary[wordToPrint].word << ": [";

		j = 0;

	PagePrintLoop:
		std::cout << " " << vocabulary[wordToPrint].pages[j];

		j++;
		if (j < vocabulary[wordToPrint].lastPage)
		{
			std::cout << ",";
			goto PagePrintLoop;
		}
		std::cout << " ]\n";
	}

	if (wordToPrint < wordsCount && topN) goto PrintingResult;
_PrintingResult:

	inFile.close();
	stopWordsInFile.close();

	return 0;

	

ParsingLine: 
	if (line[i] >= 'A' && line[i] <= 'Z') {
		word.push_back(line[i] + 32);
	}
	else if (line[i] >= 'a' && line[i] <= 'z' || (line[i] == '-' || line[i] == '\'') && word.size() != 0) {
		word.push_back(line[i]);
	}
	else if ((line[i] == ' ' || line[i] == ',' || line[i] == '.' || i == line.size() - 1) && !word.empty()) {

		goto UpdatingVocabulary;
	_UpdatingVocabulary:
		word = "";
	}
	i++;
	if (i < line.size()) goto ParsingLine;
	goto _ParsingLine;

UpdatingVocabulary: 
	wordPosition = -1;
	goto findWord;
_findWord:
	if (wordPosition == -1) {
		vocabulary[wordsCount] = { 1, 1, new int[100], word };
		vocabulary[wordsCount].pages[0] = currentPage;

		wordsCount++;
	}
	else {
		vocabulary[wordPosition].count++;
		if (vocabulary[wordPosition].count <= 100) {
			if (vocabulary[wordPosition].pages[vocabulary[wordPosition].lastPage - 1] != currentPage)
			{
				vocabulary[wordPosition].pages[vocabulary[wordPosition].lastPage] = currentPage;
				vocabulary[wordPosition].lastPage++;
			}
			vocabulary[wordPosition].count++;
		}
	}
	goto _UpdatingVocabulary;

findWord: 
	j = 0;
loop:
	if (vocabulary[j].word == word) {
		wordPosition = j;
		j = wordsCount;
	}
	j++;
	if (j < wordsCount) goto loop;
	goto _findWord;

CheckStopWord: 
	if (vocabulary[wordToPrint].word == stopWords[i])
	{
		isStopWord = true;
		goto _CheckStopWord;
	}
	i++;
	if (i < stopWordsCount) goto CheckStopWord;
	goto _CheckStopWord;
}