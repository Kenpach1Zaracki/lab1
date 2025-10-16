package main

import (
	"bufio"
	"errors"
	"os"
	"strings"
)

// DataBase holds all structures by name.
type DataBase struct {
	Arrays     map[string][]string
	SLists     map[string]*Node
	DListsHead map[string]*DNode
	DListsTail map[string]*DNode
	Stacks     map[string][]string
	Queues     map[string][]string
	Trees      map[string]*FullBinaryTree
}

func newDataBase() *DataBase {
	return &DataBase{
		Arrays:     make(map[string][]string),
		SLists:     make(map[string]*Node),
		DListsHead: make(map[string]*DNode),
		DListsTail: make(map[string]*DNode),
		Stacks:     make(map[string][]string),
		Queues:     make(map[string][]string),
		Trees:      make(map[string]*FullBinaryTree),
	}
}

// LoadFromFile reads the file and populates db
// Format: type:name:data
func LoadFromFile(filename string, db *DataBase) error {
	// If db is nil, create a new one
	if db == nil {
		return errors.New("nil db")
	}
	// Ensure maps exist
	if db.Arrays == nil {
		*db = *newDataBase()
	}

	f, err := os.Open(filename)
	if err != nil {
		// return err to allow caller to decide; caller may treat missing file as empty DB
		return err
	}
	defer f.Close()

	sc := bufio.NewScanner(f)
	for sc.Scan() {
		line := sc.Text()
		if strings.TrimSpace(line) == "" {
			continue
		}
		parts := strings.SplitN(line, ":", 3)
		if len(parts) < 3 {
			continue
		}
		typ := parts[0]
		name := parts[1]
		data := parts[2]

		switch typ {
		case "array":
			db.Arrays[name] = deserializeCSV(data)
		case "slist":
			var head *Node
			SListDeserialize(&head, data)
			db.SLists[name] = head
		case "dlist":
			var head *DNode
			var tail *DNode
			DListDeserialize(&head, &tail, data)
			db.DListsHead[name] = head
			db.DListsTail[name] = tail
		case "stack":
			db.Stacks[name] = deserializeCSV(data)
		case "queue":
			db.Queues[name] = deserializeCSV(data)
		case "tree":
			t := &FullBinaryTree{}
			TreeInit(t)
			TreeDeserialize(t, data)
			db.Trees[name] = t
		default:
			// ignore unknown
		}
	}
	return sc.Err()
}

// SaveToFile writes DB to file in the same format
func SaveToFile(filename string, db *DataBase) error {
	if db == nil {
		return errors.New("nil db")
	}
	f, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	w := bufio.NewWriter(f)

	for name, arr := range db.Arrays {
		w.WriteString("array:" + name + ":" + serializeCSV(arr) + "\n")
	}
	for name, head := range db.SLists {
		w.WriteString("slist:" + name + ":" + SListSerialize(head) + "\n")
	}
	for name, head := range db.DListsHead {
		w.WriteString("dlist:" + name + ":" + DListSerialize(head) + "\n")
	}
	for name, st := range db.Stacks {
		w.WriteString("stack:" + name + ":" + serializeCSV(st) + "\n")
	}
	for name, q := range db.Queues {
		w.WriteString("queue:" + name + ":" + serializeCSV(q) + "\n")
	}
	for name, t := range db.Trees {
		w.WriteString("tree:" + name + ":" + TreeSerialize(t) + "\n")
	}

	return w.Flush()
}

func serializeCSV(items []string) string {
	// Note: assumes items do not contain commas.
	return strings.Join(items, ",")
}

func deserializeCSV(s string) []string {
	if strings.TrimSpace(s) == "" {
		return []string{}
	}
	parts := strings.Split(s, ",")
	// filter possible empty tokens? Keep as is (original did skip empty)
	out := make([]string, 0, len(parts))
	for _, p := range parts {
		if p == "" {
			continue
		}
		out = append(out, p)
	}
	return out
}
