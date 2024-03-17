## BYTE PAIR ENCODING

BPE is a type of sub word tokenisation. It can be useful for compression.
Goal is to represent most frequently occuring charsets with tokens and
break down rare words into those tokens

[ref](https://towardsdatascience.com/byte-pair-encoding-subword-based-tokenization-algorithm-77828a70bee0)

> Algorithm 

- pretokenisation, space based, add somekind of terminal symbol to identify end of token
 - create char count mapping from the tokens in the step above, with the terminal symbol having the highest occurence = no. of tokens  
 - for every pair of chars starting from the most freq chars add most freq occuring pair to table 256 + cur, for chars being merged subtract the count of common occ
 - repeat until limit of tokens/iterations is reached, cleanup table remove 0 cnt char
 - encoding
 - decoding
