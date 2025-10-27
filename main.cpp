#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <optional>
#include "Scanner.hpp"
#include "utils.hpp"
#include "BinSearchTree.hpp"
#include "PriorityQueue.hpp"
#include "HuffmanTree.hpp"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName = std::string("input_output");
    const std::string inputFileNameArg = std::string(argv[1]);
    const std::string inputFileName = dirName + "/" + inputFileNameArg;
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileNameArg);

    // build the path to the .tokens output file.
    const std::string wordTokensFileName = dirName + "/" + inputFileBaseName + ".tokens";
    const std::string freqFileName = dirName + "/" + inputFileBaseName + ".freq";

    // The next several if-statement make sure that the input file, the directory exist
    // and that the output file is writeable.
     if( error_type status; (status = regularFileExistsAndIsAvailable(inputFileName)) != NO_ERROR )
        exitOnError(status, inputFileName);

    if (error_type status; (status = directoryExists(dirName)) != NO_ERROR )
        exitOnError(status, dirName);

    if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    if (error_type status; (status = canOpenForWriting(freqFileName)) != NO_ERROR)
        exitOnError(status, freqFileName);

    std::vector<std::string> words;
    namespace fs = std::filesystem;
    fs::path tokensFilePath(wordTokensFileName); // create a file system path using the output file.

    auto fileToWords = Scanner(inputFileName);
    if( error_type status; (status = fileToWords.tokenize(words)) != NO_ERROR)
	    exitOnError(status, inputFileName);

    if (error_type status; (status = writeVectorToFile(wordTokensFileName, words)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    // Build the tree
    BinSearchTree bst;
    bst.bulkInsert(words);

    std::vector<std::pair<std::string, int>> frequencies;
    bst.inorderCollect(frequencies);

    size_t totalTokens = words.size();
    size_t uniqueWords = bst.size();
    unsigned bstHeight = bst.height();

    int minFreq = 0;
    int maxFreq = 0;

    if (!frequencies.empty()) {
        minFreq = frequencies.at(0).second;
        maxFreq = frequencies.at(0).second;

        for (size_t i = 0; i < frequencies.size(); ++i) {
            std::string word = frequencies.at(i).first;
            int count = frequencies.at(i).second;

            if (count < minFreq) {
                minFreq = count;
            }

            if (count > maxFreq) {
                maxFreq = count;
            }
        }
    }

    std::cout << "BST height: " << bstHeight << '\n';
    std::cout << "BST unique words: " << uniqueWords << '\n';
    std::cout << "Total tokens: " << totalTokens << '\n';
    std::cout << "Min frequency: " << minFreq << '\n';
    std::cout << "Max frequency: " << maxFreq << '\n';

    //Priority Queue
    std::vector<TreeNode*> nodes;

    for (size_t i = 0; i < frequencies.size(); ++i) {
        std::string word = frequencies.at(i).first;
        int count = frequencies.at(i).second;

        nodes.push_back(new TreeNode(word, count));
    }

    PriorityQueue pq(nodes);

    // clean up before exiting
    std::ofstream out(freqFileName);
    if (!out) {
        for (TreeNode* n : nodes) delete n;
        exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, freqFileName);
    }

    pq.print(out);
    out.close();

    // Clean up the nodes used for printing frequencies
    for (TreeNode* n : nodes) {
        delete n;
    }
    nodes.clear();

    HuffmanTree huffTree;
    huffTree.buildFromCounts(frequencies);

    const std::string hdrFileName = dirName + "/" + inputFileBaseName + ".hdr";
    if (error_type status; (status = canOpenForWriting(hdrFileName)) != NO_ERROR)
        exitOnError(status, hdrFileName);

    std::ofstream hdrOut(hdrFileName);
    if (!hdrOut) {
        exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, hdrFileName);
    }

    if (error_type status; (status = huffTree.writeHeader(hdrOut)) != NO_ERROR) {
        exitOnError(status, hdrFileName);
    }
    hdrOut.close();

    // Encode and write .code file
    const std::string codeFileName = dirName + "/" + inputFileBaseName + ".code";
    if (error_type status; (status = canOpenForWriting(codeFileName)) != NO_ERROR)
        exitOnError(status, codeFileName);

    std::ofstream codeOutput(codeFileName);
    if (!codeOutput) {
        exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, codeFileName);
    }

    if (error_type status; (status = huffTree.encode(words, codeOutput, 80)) != NO_ERROR) {
        exitOnError(status, codeFileName);
    }

    codeOutput.close();
    return 0;
}