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
		// If file doesn't exist or can't be read, start with empty DB (but print error)
		// We'll still try to run command on empty DB.
		// fmt.Println("Warning loading file:", err)
	}

	changed, err := HandleCommand(*query, &db)
	if err != nil {
		// Print error but continue (many commands simply print themselves)
		fmt.Println("ERROR:", err)
	}

	if changed {
		if err := SaveToFile(*file, &db); err != nil {
			fmt.Println("Error saving:", err)
		}
	}
}
