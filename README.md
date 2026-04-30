# Huffman Trees

A C++ implementation of word-level Huffman coding. Takes any `.txt` file as input and produces a complete encoder pipeline: tokenized text, frequency analysis, a Huffman code table, and the final encoded bitstream.

## How it works

The program runs in four stages:

1. **Tokenize** — A custom `Scanner` reads the input character by character, lowercasing letters and preserving internal apostrophes (so `Poe's` becomes `poe's`, but a stray quote mark won't start a token). One token per line is written to `.tokens`.
2. **Count frequencies** — Tokens are inserted into a `BinSearchTree` keyed by word, with each node tracking its count. An inorder traversal yields words in alphabetical order — which doubles as the tie-breaker for the next stage. Frequencies are written to `.freq`, sorted by descending count with alphabetical ties, right-aligned to width 10.
3. **Build the Huffman tree** — A min-heap `PriorityQueue` repeatedly extracts the two lowest-frequency nodes and merges them, with the alphabetically-smaller key propagated up to keep tie-breaking deterministic. The token-to-code mapping is then walked out preorder and written to `.hdr`.
4. **Encode** — Each input token is replaced with its bitstring and emitted to `.code`, wrapped at 80 columns.

File I/O is gated by an `error_type` enum defined in `utils.hpp`, so every read/write goes through a consistent existence-and-permissions check before opening.

## Build and run

```bash
g++ -std=c++20 -Wall *.cpp -o huffman
./huffman TheBells.txt
```

Input files live in `input_output/`, and all four output files are written there alongside the input. The program also prints summary statistics to the terminal:

```
BST height: 11
BST unique words: 48
Total tokens: 82
Min frequency: 1
Max frequency: 11
```

## Example

Running on Poe's *The Bells* (`input_output/TheBells.txt`) produces:

```
TheBells.tokens          TheBells.freq         TheBells.hdr        TheBells.code
edgar                    11 bells              sledges 000000      0110100111100010...
allan                    11 the                silver 000001       0010011011111100...
poe's                    4 of                  of 0001             0010111110001100...
the                      3 a                   ...                 ...
bells                    3 time
```

## Testing

Validated against a reference test suite of 44 cases covering tokenization, frequency ordering, header generation, and encoded output. All cases pass with zero diffs against expected outputs.

## Related

A companion decoder that reverses this pipeline (`.hdr` + `.code` → original `.tokens`) lives in [huffman-tree-decoder](https://github.com/tennierp/huffman-tree-decoder).
