package main

import (
	"fmt"
	"log"
	"os"
)

// returns a map with char pair in int form as key and cnt of their occ as val
func pair_freq_count(ids []int) map[[2]int]int {
	pfc := make(map[[2]int]int)
	for i := 1; i < len(ids); i++ {
		key := [2]int{ids[i-1], ids[i]}

		if _, ok := pfc[key]; ok {
			pfc[key]++
		} else {
			pfc[key] = 1
		}
	}
	return pfc
}

// replaces all the occ of the pair with the new index val resulting in compression
func merge(ids []int, mx_freq_p [2]int, new_idx int) []int {
	var merged_ids []int
	for i := 0; i < len(ids)-1; i++ {
		if ids[i] == mx_freq_p[0] && i < len(ids)-1 && ids[i+1] == mx_freq_p[1] {
			merged_ids = append(merged_ids, new_idx)
			i++
		} else {
			merged_ids = append(merged_ids, ids[i])
		}
	}
	return merged_ids
}

// main training func
func Train(text []byte, vocab_size int, verbose bool) {
	if vocab_size < 256 {
		panic("[ERR] vocab size too small")
	}

	num_merges := vocab_size - 256
	var ids []int
	for _, b := range text {
		ids = append(ids, int(b))
	}

	merges := make(map[[2]int]int)
	vocab := make(map[int][]byte)
	for i := 0; i < 256; i++ {
		vocab[i] = []byte{byte(i)}
	}

	for i := 0; i < num_merges; i++ {
		pfc := pair_freq_count(ids)
		// pair<ids in vocab>
		var mx_freq_p [2]int
		mx_freq := 0
		for k, v := range pfc {
			if v > mx_freq {
				mx_freq_p = k
				mx_freq = v
			}
		}
		new_idx := 256 + i
		ids = merge(ids, mx_freq_p, new_idx)
		merges[mx_freq_p] = new_idx
		vocab[new_idx] = []byte(string(vocab[mx_freq_p[0]]) + string(vocab[mx_freq_p[1]]))
		if verbose {
			fmt.Printf("merge %d/%d | %s (b=%d) & %s(b=%d) => %s\n",
				new_idx-256, num_merges,
				string(vocab[mx_freq_p[0]]), mx_freq_p[0],
				string(vocab[mx_freq_p[1]]), mx_freq_p[1],
				string(vocab[new_idx]))
		}
	}

}

func main() {
	// read from file
	content, err := os.ReadFile("taylorswift.txt")

	if err != nil {
		log.Fatal(err)
	}
	// print(string(content))
	Train(content, 512, true)

}
