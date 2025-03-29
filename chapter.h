#ifndef CHAPTER_H
#define CHAPTER_H

#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>

#include "word_counter.h"
#include "verse.h"


class Chapter {
    private:
        std::vector<Verse> verses;
        WordCounter chapter_total;
        std::string title;
    public:
        Chapter(std::string title){
            this -> title = title;
        }

        WordCounter getChapterTotal() const{
            return chapter_total;
        }

        std::string getTitle() const{
            return title;
        }
        void addVersesFromText(const std::string&text){
            std::istringstream ss(text);
            std::string line;
            std::string verseTitle = "Summary";
            std::string previousLine = "";
            while(getline(ss, line)){
                Verse verse(verseTitle);
                if(!previousLine.empty()){
                    verse.addWords(previousLine);
                }
                verseTitle = "";
                previousLine = "";
                do{
                    if(!line.empty() && std::ispunct(line.at(line.length() - 1)) && std::isdigit(line.at(0))){
                        std::istringstream lineStream(line);  
                        lineStream >> verseTitle;
                        std::ostringstream verseContent;
                        std::string temp;
                        while(lineStream >> temp){
                            verseContent << temp << " ";
                        }
                        previousLine = verseContent.str();
                        break;
                    }
                    else{
                        verse.addWords(line);
                    }
                }while(getline(ss, line));
                chapter_total.processSubstats(verse.getCounter());
                verses.push_back(verse);
            }
            if(!verseTitle.empty() && !previousLine.empty()){
                Verse verse(verseTitle);
                verse.addWords(previousLine);
                chapter_total.processSubstats(verse.getCounter());
                verses.push_back(verse);
            }
        }

        void addVerse(const Verse& verse){
            verses.push_back(verse);
            chapter_total.processSubstats(verse.getCounter());
        }

        std::string toString() const {
            std::ostringstream out;
            out << title << ":" << std::endl;
            
            if(verses.size() > 1){
                out << "Verses:" << std::endl;
                for(const auto& verse : verses){
                    out << verse.toString() << std::endl;
                }
                out << "Chapter Total:" << std::endl;
            }
            out << chapter_total.toString() << std::endl;
            return out.str();
        }
};

#endif