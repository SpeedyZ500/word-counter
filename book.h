#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "chapter.h"
#include "word_counter.h"
#include <cctype>

class Book{
    private:
        std::string title;
        std::vector<Chapter> chapters;
        WordCounter book_total;

        bool isChapterTitle(const std::string& line) const{
            if (line.empty()){
                return false;
            }
            char lastChar = line.back();
            if(std::ispunct(lastChar)){
                return false;
            }

            std::istringstream ss(line);
            std::string firstWord;
            ss >> firstWord;
            if (std::isdigit(firstWord[0])){
                return firstWord.back() != '.';
            }
            return true;
        }
    
    public:
        Book() = default;
        
        void processText(const std::string& text) {
            std::istringstream ss(text);
            std::string line;

            if(std::getline(ss, line)){
                title = line;
            }
            std::string chapterTitle = "Preface";
            std::ostringstream chapterContent;
            while(std::getline(ss, line)){
                Chapter chapter(chapterTitle);
                do{
                    if(isChapterTitle(line)){
                        chapterTitle = line;
                        break;
                    }
                    else{
                        chapterContent << line << std::endl;
                    }
                }while(std::getline(ss, line));
                if(!chapterContent.str().empty()){
                    chapter.addVersesFromText(chapterContent.str());
                    chapterContent.str("");
                    chapterContent.clear();
                    book_total.processSubstats(chapter.getChapterTotal());
                    chapters.push_back(chapter);
                }
            }
        }

        std::string toString() const{
            std::ostringstream out;
            out << title << ":" << std::endl;
            if(chapters.size() > 1){
                out << "Chapters:" << std::endl;
                for(const auto& chapter : chapters){
                    out << chapter.toString() << std::endl;
                }
                out << "Grand Total:" << std::endl;
            }
            out << book_total.toString() << std::endl;
            return out.str();
        }

};

#endif