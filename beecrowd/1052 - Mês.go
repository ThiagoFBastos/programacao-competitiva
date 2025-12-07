package main

import "fmt"

func main() {

	var month int32

	month_speechs := map[int32]string{
		1:  "January",
		2:  "February",
		3:  "March",
		4:  "April",
		5:  "May",
		6:  "June",
		7:  "July",
		8:  "August",
		9:  "September",
		10: "October",
		11: "November",
		12: "December",
	}

	fmt.Scan(&month)

	speech := month_speechs[month]

	fmt.Println(speech)
}
