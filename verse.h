#ifndef VERSE_H
#define VERSE_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "word_counter.h"

class Verse{
    private:
        WordCounter word_counter;
        std::string title;
    public:
        
        Verse(std::string title){
            this -> title = title;
        }
        
        void addWords(std::string words){
            word_counter.stringProcessor(words);
        }

        WordCounter getCounter() const{
            return word_counter;
        }

        std::string toString() const {
            std::ostringstream out;
            out << title << ": " << std::endl;
            out << word_counter.toString();
            return out.str();
        }
        

};

#endif
