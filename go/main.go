package main

import (
	"flag"
	"fmt"
)

func printHelp() {
	fmt.Println("Usage:")
	fmt.Println("./dbms --file file.data --query \"COMMAND params\"")
	fmt.Println("Example: ./dbms --file file.data --query \"TINSERT mytree 42\"")
}

func main() {
	file := flag.String("file", "", "data file")
	query := flag.String("query", "", "single query string")
	flag.Parse()

	if *file == "" || *query == "" {
		printHelp()
		return
	}

	var db DataBase
	err := LoadFromFile(*file, &db)
	if err != nil {
		
	}

	changed, err := HandleCommand(*query, &db)
	if err != nil {
		fmt.Println("ERROR:", err)
	}

	if changed {
		if err := SaveToFile(*file, &db); err != nil {
			fmt.Println("Error saving:", err)
		}
	}
}
