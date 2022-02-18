#include <iostream>
#include <string>
#include <fstream>
int main() {
    // -------------------------------------------------- //
    std::ifstream fin("C:\\Code\\try\\asd.txt");
    if (!fin)
        std::cerr << "FAIL opeening" << '\n';

    std::string line, word;
    struct pair {
        std::string word;
        int counter;
    };
    pair dictionary[10000];
    int dictionarySize = 0, n = 10;
    bool flag = true;

    std::ifstream stopWords("C:\\Code\\try\\stop.txt");
    if (!stopWords)
        std::cerr << "FAIL opeening" << '\n';

    std::string stopWord;
    std::string stopWordsList[200];
    int stopWordIter = 0;
    bool stopFlag = true;

SkipWORDS:
    getline(stopWords, stopWord);
    stopWordsList[stopWordIter] = stopWord;
    stopWordIter += 1;
    if (!stopWords.eof())
        goto SkipWORDS;

READ_FILE:
    getline(fin, line);
    int i = 0;
READ_WORD:
    if ((int(line[i]) > 64 && int(line[i]) < 91) || (int(line[i]) > 96 && int(line[i]) < 123)) {
        char cymbol = line[i];
        if (int(cymbol) >= 64 && int(cymbol) <= 90)
            cymbol = char(int(cymbol) + 32);
        word += cymbol;
    }
    if (line[i] == ' ' || i + 1 == line.size())
    {
        int h = 0;
    CHECK_for_STOP:
        if (word == stopWordsList[h]) {
            h = stopWordIter;
            stopFlag = false;
        }
        h += 1;
        if (h < stopWordIter)
            goto CHECK_for_STOP;

        if (word != "" && stopFlag)
        {
            int j = 0;
        DICT:
            if (dictionary[j].word == word) {
                dictionary[j].counter += 1;
                flag = false;
            }
            j++;
            if (j < dictionarySize && flag == true)
                goto DICT;

            if (flag == true)
            {
                dictionary[dictionarySize].word = word;
                dictionary[dictionarySize].counter = 1;
                dictionarySize += 1;
            }
        }
        stopFlag = true;
        word = "";
        flag = true;
    }

    i += 1;
    if (i < line.size())
        goto READ_WORD;
    if (!fin.eof())
        goto READ_FILE;

    if (n > dictionarySize)
        n = dictionarySize;

    int m = 0;
    pair temp;
RE_NEW:
    int t = 0;
COUNT:

    if (dictionary[t].counter < dictionary[t + 1].counter) {
        temp = dictionary[t];
        dictionary[t] = dictionary[t + 1];
        dictionary[t + 1] = temp;
    }
    t += 1;
    if (t < dictionarySize - m - 1)
        goto COUNT;
    m += 1;
    if (m < dictionarySize - 1)
        goto RE_NEW;

    int k = 0;
COUT:
    std::cout << dictionary[k].word << ":" << dictionary[k].counter << '\n';
    k++;
    if (k < n)
        goto COUT;
    return 0;
    }
