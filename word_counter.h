#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>


class WordCounter{
    private:
    std::map<std::string, int> word_count;
    int total;


    public:
        WordCounter(){
            total = 0;
        };
        void addWord(std::string word){
            total++;
            word_count[word]++;
        }
        int getTotal(){
            return total;
        }
        const std::map<std::string, int>& getWordCount() const { 
            return word_count; 
        }

        void stringProcessor(std::string str){
            std::istringstream ss(str);
            std::string word = ""; 
            while(ss >> word){
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
                addWord(word);
            }
        }

        std::string toString() const{
            std::vector<std::pair<std::string, int> > sortedWords(word_count.begin(), word_count.end());
            std::sort(sortedWords.begin(), sortedWords.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.second > b.second;  
            });
            std::ostringstream out;
            out << "Total Word Count: " << total << std::endl;
            for(const auto& word : sortedWords){
                std::string capitalizedWord = word.first;
                if (!capitalizedWord.empty()) {
                    capitalizedWord[0] = std::toupper(capitalizedWord[0]);
                }
                out << capitalizedWord << ": " << word.second << std::endl;
            }
            return out.str();
        }

        
};

#endif