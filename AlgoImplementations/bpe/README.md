## BYTE PAIR ENCODING

BPE is a type of sub word tokenisation. It can be useful for compression. 
Goal is to represent most frequently occuring charsets with tokens and
break down rare words into those tokens

[ref](https://towardsdatascience.com/byte-pair-encoding-subword-based-tokenization-algorithm-77828a70bee0)

**Algorithm** 

(basic bpe)

- convert input to a int[], where every char becomes its ascii_val (ids)
- instantiate a vocab of size 256 covering all the 256 ascii vals (vocab)
- find the 2 top most freq in vocab and merge them and add as a new key in vocab
- replace all occurence of the pair in the input
- iterate until token/iteration limit is reached


**To implement**

- terminal symbol
- encoding and decoding

 **RUN**

 `$ go run main.go`
