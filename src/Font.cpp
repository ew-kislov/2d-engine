#pragma once

#include "Font.hpp"

Font::Font(string source, int size, map<char, shared_ptr<Character> > characters) {
    this->source = source;
    this->size = size;
    this->characters = characters;
}

shared_ptr<Character> Font::getCharacter(char c) {
    return this->characters[c];
}

int Font::getSize() {
    return size;
}