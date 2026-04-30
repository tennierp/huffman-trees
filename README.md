# Huffman Trees

A C++ implementation of word-level Huffman coding. Takes any `.txt` file as input and produces a complete encoder pipeline: tokenized text, frequency analysis, a Huffman code table, and the final encoded bitstream.

## How it works

The program runs in four stages:

1. **Tokenize** — Reads the input text and splits it into lowercase tokens (letters and apostrophes only), one per line, written to `.tokens`.
2. **Count frequencies** — Inserts each unique token into a Binary Search Tree that tracks occurrence counts. Frequencies are written to `.freq`, sorted by descending frequency with alphabetical tie-breaking, right-aligned to width 10.
3. **Build the Huffman tree** — Constructs the tree from the frequency data using a priority queue, then walks the tree to assign a binary code to each token. The token-to-code mapping is written to `.hdr`.
4. **Encode** — Emits the full encoded bitstream as a sequence of `0` and `1` characters to `.code`.

File I/O errors are handled through the error types defined in `utils.hpp`.

## Build and run

```bash
g++ -std=c++20 -Wall *.cpp -o huffman
./huffman input.txt
```

This produces `input.tokens`, `input.freq`, `input.hdr`, and `input.code` alongside the input file. The program also prints BST properties, total token count, and min/max frequencies to the terminal.

## Testing

Validated against a reference test suite of 44 cases covering tokenization, frequency ordering, header generation, and encoding output. All cases pass with zero diffs against expected outputs.

## Related

A companion decoder that reverses this pipeline (`.hdr` + `.code` → original `.tokens`) lives in [huffman-tree-decoder](https://github.com/tennierp/huffman-tree-decoder).
