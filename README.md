# BLOSUM
BLOSUM for sequence alignment of proteins.

### Introduction
This C program (`BLOSUM.c`) calculates the alignment score between two protein sequences using the BLOSUM50 substitution matrix. The BLOSUM (BLOcks SUbstitution Matrix) matrices are commonly used in bioinformatics to score the likelihood of amino acid substitutions during sequence alignments.

### Features
- **Scoring Function:** The program provides a `rescore` function that calculates the score of aligning two amino acids based on the BLOSUM50 matrix.
- **File Input:** Reads two protein sequences from the input file (`1.txt`) and the BLOSUM50 matrix from the file `blosum50.txt`.
- **Dynamic Programming:** Utilizes dynamic programming to compute the global alignment score and traceback information for the optimal alignment.
- **Output:** Outputs the aligned sequences, the BLOSUM50 matrix, the dynamic programming matrix (`G`), and the traceback information.

### Usage
1. Prepare an input file (1.txt) with two protein sequences separated by a line containing '$'.
2. Compile the program:
   ```sh
   gcc BLOSUM.c -o BLOSUM_Scorer
   ```
3. Run the program:
   ```sh
   ./BLOSUM_Scorer
   ```
4. The program will display the aligned sequences, BLOSUM50 matrix, dynamic programming matrix, and traceback information.

### Input Format
The input file (`1.txt`) should contain two protein sequences separated by a line containing '$'. For example:
```sh
ATCG$
AGCT$
```

### BLOSUM Matrix Format
The BLOSUM50 matrix is read from the file `blosum50.txt`. Ensure the matrix is in the correct format for accurate scoring.

### Output
The program generates an output file (output.txt) containing the aligned sequences, BLOSUM50 matrix, dynamic programming matrix (G), and traceback information.

### Note
- The program performs global alignment, where the entire length of both sequences is considered.
- The output includes lowercase letters for residues not included in the optimal alignment.

### Conclusion
This BLOSUM Alignment Scorer is a useful tool for assessing the similarity of protein sequences based on the BLOSUM50 substitution matrix. The output provides detailed information about the alignment and can be used for further analysis.
