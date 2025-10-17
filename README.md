## Project 3 - Huffman Trees

## Student Information
Parker Tennier  
ID: 008768156  
https://github.com/tennierp/huffman-trees

## Collaboration & Sources
Dr. Ali A. Kooshesh provided the foundational building blocks to create a scanner and tokenization classes, 
which tokenize text files into .tokens files, separating content by words.

## Implementation Details
(Updated for part 2 -- this will continue to be updated until project finished.)

In this project, text will be tokenized, word frequencies will be counted, a Huffman tree will be constructed 
using the counts, a codebook will be created, and text will be encoded and decoded.

For Part 1 we have a scanner that can read .txt files with chapters of words that will then be tokenized into 
a separate .tokens file with the rules given to the tokenize functions. These rules include lowercasing all word 
tokens, and treating digits, numbers, whitespaces, punctuation and symbols as separators. Apostrophes will have 
a unique case allowing words such as "camp's", but if the apostrophe doesn't have a character after it, it will be 
treated as a separator.

For Part 2, we have created a frequency counting and sorting. After the file has been tokenized,
we build a Binary Search Tree (BST) to count word frequencies with an O(log n) average insertion time.
The BST performs an in-order traversal to create a sorted list of word & count pairs. We then use the
PriorityQueue class based on a sorted vector to order the words by frequency in a decending order. The program then outputs a .freq file that contains the frequency count and word pairs. The program will also output into the terminal the BST Height, Unique word count, total token count, minimum frequency, and maximum frequency.

## Testing & Status
Using g++ -std=c++20 -Wall *.cpp -o huffman_part1 and then running the code with ./huffman_part2 input_file_name.txt. The program now generates two output files: .tokens and .freq. Testing this on the blue server using the provided test script (compile_and_test_project3_part2.bash) shows all 11 test files passing with 22 matches and 0 differences when compared to Dr. Ali. A. Kooshesh's outputs. All BST properties print correctly to the terminal when the program is ran.
