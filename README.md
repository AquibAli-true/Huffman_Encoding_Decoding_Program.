# Huffman_Encoding_Decoding_Program.
Author-Aquib Ali.

This is a C++ implementation of the Huffman Coding Algorithm, a popular lossless data compression technique. This project reads a text file, compresses it into a binary format, and then demonstrates decompression to recover the original text.

This project follows the standard Huffman compression workflow:
1. **Frequency Map:** Scans the input file and maps each character to its frequency.
2. **Min-Heap:** Inserts all characters into a priority queue.
3. **Tree Building:** Repeatedly extracts the two smallest nodes and joins them until a single root remains.
4. **Code Generation:** Traverses the tree to assign a unique prefix-free binary code to each character (left = 0, right = 1).
5. **Compression:** Replaces original characters with Huffman codes and writes them to a binary file using bitwise operations.
6. **Decompression:** Reads the binary file bit-by-bit, traversing the tree to retrieve the original characters.

Prerequisites
1. A C++ compiler (GCC/G++, Clang, or MSVC).
2. An input file named sampletextFileForFileHandling.txt in the same directory.

To compile and run the program, use:
```bash
g++ HuffmanProjectALGO.cpp -o huffman

./huffman
```  

Output:

1. **Codes:** A list of generated Huffman codes will be printed to the console.
2. **encoded.bin:** The compressed binary representation of your text.
3. **decoded.txt:** The result of decompressing encoded.bin.
