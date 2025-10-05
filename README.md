## Project 3 - Huffman Trees

## Student Information
Parker Tennier  
ID: 008768156  
https://github.com/tennierp/huffman-trees

## Collaboration & Sources
Dr. Ali A. Kooshesh provided the foundational building blocks to create the scanner and token classes, 
which tokenize text files into .tokens files, separating content by words.

## Implementation Details
(Currently only for part 1 -- this will be updated.)

In this project, text will be tokenized, word frequencies will be counted, a Huffman tree will be constructed 
using the counts, a codebook will be created, and text will be encoded and decoded.

For Part 1 we have a scanner class that can read .txt files with chapters of words that will then be tokenized into 
a separate .tokens file with the rules given to the tokenize functions. These rules include lowercasing all word 
tokens, and treating digits, numbers, whitespaces, punctuation and symbols as separators. Apostrophes will have 
a unique case allowing words such as "camp's", but if the apostrophe doesn't have a character after it, it will be 
treated as a separator.

## Testing & Status
Using g++ -std=c++20 -Wall *.cpp -o huffman_part1 and then running the code with ./huffman_part1 input_file_name.text 
the program outputs a .tokens file with the same base name as the input file. The resulting file contains the tokenized 
version of the input text, generated according to the rules described above.
