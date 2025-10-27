## Project 3 - Huffman Trees

## Student Information
Parker Tennier  
ID: 008768156  
https://github.com/tennierp/huffman-trees

## Collaboration & Sources
Dr. Ali A. Kooshesh provided the foundational building blocks (Scanner, BinSearchTree, PriorityQueue, Utils) and scripts to run the project on blue.

## Implementation Details
This project is a fully functional Huffman Tree. It will take any ‘.txt’ file as an input and parse it into four separate files: `.tokens`, `.freq`, `.hdr`, and `.code`. 
The program reads in the input text and separates it into lowercase tokens. Tokens include only the letters and necessary apostrophes, 
and each token is written on its own line in the `.tokens` file. Each inque word is inserted into a Binary Search tree that uses a frequency 
to track how many times each word appears in the `.txt` file. The frequencies are then written into the `.freq` file, and sorted by a descending 
frequency. If two words have the same frequency, they are ordered alphabetically. Each line in this file shows the frequency followed by the 
word (it is also right-aligned with width 10). Once all word counts are gathered, a Huffman tree is built using a priority queue. Each leaf 
node represents a word and its own frequency. The Huffman tree uses an algorithm to assign `0` and `1` bits to specific nodes to Encode the 
provided `.txt` file given.


## Testing & Status
Using g++ -std=c++20 -Wall *.cpp -o huffman and then running the program with ./huffman input_file_name.txt. The program now generates four output 
files: .tokens, .freq .code, .hdr. Testing this on the blue server using the final test scripts provided by Dr. Ali Kooshesh shows all test files 
passing with 44 matches and 0 differences when compared to Dr. Ali. A. Kooshesh's outputs. All BST properties, Total Tokens, and Min/Max frequencies print 
correctly to the terminal when the program is run.
