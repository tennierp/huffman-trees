## Project 3 - Huffman Trees

## Student Information
Parker Tennier  
ID: 008768156  
https://github.com/tennierp/huffman-trees

## Collaboration & Sources
Dr. Ali A. Kooshesh provided the foundational building blocks (Scanner, BinSearchTree, PriorityQueue, and Utils) and scripts to run the project on blue.

## Implementation Details
This project is a fully functional Huffman Tree. It takes any `.txt` file as input and parses it into four separate files: `.tokens`, `.freq`, `.hdr`, and `.code`.

The program reads the input text and separates it into lowercase tokens. Tokens include only characters and the necessary apostrophes, and each token is written on 
its own line in the `.tokens` file. Each unique word is inserted into a Binary Search Tree that tracks how many times each word appears in the input text. The frequencies 
are then written to the `.freq` file and sorted by descending frequency. If two words have the same frequency, they are ordered alphabetically. Each line in this file 
shows the frequency followed by the word (right-aligned with width 10). Once all the word counts are found, a Huffman Tree is built using a priority queue. The `.hdr` 
file is generated using an algorithm from the Huffman Tree built, listing each word followed by its binary code. The `.code` file contains the full encoded bits for the text, 
made with `0` and `1` bits. The program uses the error types defined in `utils.hpp` for file handling.



## Testing & Status
Using g++ -std=c++20 -Wall *.cpp -o huffman and then running the program with ./huffman input_file_name.txt. The program now generates four output 
files: .tokens, .freq .code, .hdr. Testing this on the blue server using the final test scripts provided by Dr. Ali Kooshesh shows all test files 
passing with 44 matches and 0 differences when compared to Dr. Ali. A. Kooshesh's outputs. All BST properties, Total Tokens, and Min/Max frequencies print 
correctly to the terminal when the program is run.
