package main

import "fmt"

func xor(bit0 int, bit1 int) int {
	if bit0 == bit1 {
		return 0
	} else {
		return 1
	}
}
func main() {
	g := [4]int{1, 0, 0, 1}       //get from file load into array
	d := [6]int{1, 0, 1, 1, 1, 0} //get from file load into array
	given_r := [3]int{0, 1, 1}    //get from file load into array
	//g_len := len(g)
	//d_len := len(d)
	//r_len := len(given_r)
	//result_len := r_len + d_len	//use this to set length of result array does not work in go for some reason
	//fmt.Println(result_len)
	var result [9]int
	for i := 0; i < len(result); i++ {
		if i < len(d) {
			result[i] = d[i]
		} else {
			result[i] = 0
		}
	}
	//fmt.Print(result[9])
	//for i := 0; i < len(result); i++ { // check result

	//	fmt.Print(result[i])
	//}
	//fmt.Println(" ")

	//var p int;
	for i := 0; i < len(d); i++ {
		if result[i] == 1 {
			for j := 0; j < len(g); j++ {
				result[i+j] = xor(result[i+j], g[j])
			}
		}
		//for k := 0; k < len(result); k++ { // check result
		//	fmt.Print(result[k])
		//}
		//fmt.Println(" ")
	}

	//fmt.Println("")
	matches := true
	for i := len(given_r) - 1; i >= 0; i-- {
		//fmt.Print(result[i+len(result)-len(given_r)])
		//.Print(" ")
		//fmt.Println(given_r[i])
		if given_r[i] != result[i+len(result)-len(given_r)] {
			matches = false
		}
	}
	if matches {
		fmt.Println("Yes")
	} else {
		fmt.Println("No")
	}

}
