package main

import (
	"fmt"
	"strconv"
	"strings"
)

// HandleCommand executes a single query against db.
// Returns changed=true if DB modified (so caller can save).
func HandleCommand(query string, db *DataBase) (bool, error) {
	if db == nil {
		// initialize if nil
		ndb := newDataBase()
		db = ndb
	}
	// ensure maps exist
	if db.Arrays == nil {
		*db = *newDataBase()
	}

	// tokenize by space (no support for quoted strings)
	tokens := splitTokens(query)
	if len(tokens) == 0 {
		return false, nil
	}
	cmd := strings.ToUpper(tokens[0])

	switch cmd {
	// ARRAY
	case "MPUSH":
		// MPUSH name value
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		value := tokens[2]
		db.Arrays[name] = append(db.Arrays[name], value)
		fmt.Println("OK")
		return true, nil

	case "MPUSHAT", "FPUSH":
		// MPUSHAT name idx value
		if len(tokens) < 4 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		idx, err := strconv.Atoi(tokens[2])
		if err != nil {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		value := tokens[3]
		arr := db.Arrays[name]
		if idx < 0 {
			idx = 0
		}
		if idx >= len(arr) {
			arr = append(arr, value)
		} else {
			// insert
			arr = append(arr[:idx+1], arr[idx:]...)
			arr[idx] = value
		}
		db.Arrays[name] = arr
		fmt.Println("OK")
		return true, nil

	case "MDEL":
		// MDEL name idx
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		idx, err := strconv.Atoi(tokens[2])
		if err != nil {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		arr := db.Arrays[name]
		if idx >= 0 && idx < len(arr) {
			arr = append(arr[:idx], arr[idx+1:]...)
			db.Arrays[name] = arr
		}
		fmt.Println("OK")
		return true, nil

	case "MGET":
		// MGET name idx
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		idx, err := strconv.Atoi(tokens[2])
		if err != nil {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		arr, ok := db.Arrays[name]
		if !ok {
			fmt.Println("NOT FOUND")
			return false, nil
		}
		if idx < 0 || idx >= len(arr) {
			fmt.Println("NOT FOUND")
			return false, nil
		}
		fmt.Println(arr[idx])
		return false, nil

	// SLIST (F*)
	case "FADD_HEAD":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		head := db.SLists[name]
		SListPushFront(&head, val)
		db.SLists[name] = head
		fmt.Println("OK")
		return true, nil

	case "FADD_TAIL":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		head := db.SLists[name]
		SListPushBack(&head, val)
		db.SLists[name] = head
		fmt.Println("OK")
		return true, nil

	case "FADD_AFTER":
		if len(tokens) < 4 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		target := tokens[2]
		newval := tokens[3]
		head := db.SLists[name]
		node := SListFind(head, target)
		if node != nil {
			SListInsertAfter(node, newval)
		}
		db.SLists[name] = head
		fmt.Println("OK")
		return true, nil

	case "FADD_BEFORE":
		if len(tokens) < 4 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		target := tokens[2]
		newval := tokens[3]
		head := db.SLists[name]
		node := SListFind(head, target)
		if node != nil {
			SListInsertBefore(&head, node, newval)
		}
		db.SLists[name] = head
		fmt.Println("OK")
		return true, nil

	case "FDEL_VALUE":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		head := db.SLists[name]
		SListRemoveValue(&head, val)
		db.SLists[name] = head
		fmt.Println("OK")
		return true, nil

	case "FGET":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		head := db.SLists[name]
		if SListFind(head, val) != nil {
			fmt.Println("TRUE")
		} else {
			fmt.Println("FALSE")
		}
		return false, nil

	// DLIST (L*)
	case "LADD_HEAD":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		head := db.DListsHead[name]
		tail := db.DListsTail[name]
		DListPushFront(&head, &tail, val)
		db.DListsHead[name] = head
		db.DListsTail[name] = tail
		fmt.Println("OK")
		return true, nil

	case "LADD_TAIL":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		head := db.DListsHead[name]
		tail := db.DListsTail[name]
		DListPushBack(&head, &tail, val)
		db.DListsHead[name] = head
		db.DListsTail[name] = tail
		fmt.Println("OK")
		return true, nil

	case "LADD_AFTER":
		if len(tokens) < 4 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		target := tokens[2]
		val := tokens[3]
		head := db.DListsHead[name]
		tail := db.DListsTail[name]
		DListInsertAfter(&head, &tail, target, val)
		db.DListsHead[name] = head
		db.DListsTail[name] = tail
		fmt.Println("OK")
		return true, nil

	case "LADD_BEFORE":
		if len(tokens) < 4 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		target := tokens[2]
		val := tokens[3]
		head := db.DListsHead[name]
		tail := db.DListsTail[name]
		DListInsertBefore(&head, &tail, target, val)
		db.DListsHead[name] = head
		db.DListsTail[name] = tail
		fmt.Println("OK")
		return true, nil

	case "LDEL_VALUE":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		head := db.DListsHead[name]
		tail := db.DListsTail[name]
		DListRemoveValue(&head, &tail, val)
		db.DListsHead[name] = head
		db.DListsTail[name] = tail
		fmt.Println("OK")
		return true, nil

	case "LGET":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		head := db.DListsHead[name]
		if DListFind(head, val) != nil {
			fmt.Println("TRUE")
		} else {
			fmt.Println("FALSE")
		}
		return false, nil

	// STACK
	case "SPUSH":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		st := db.Stacks[name]
		StackPush(&st, val)
		db.Stacks[name] = st
		fmt.Println("OK")
		return true, nil

	case "SPOP":
		if len(tokens) < 2 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		st := db.Stacks[name]
		v := StackPop(&st)
		db.Stacks[name] = st
		if v == "" {
			fmt.Println("EMPTY")
		} else {
			fmt.Println(v)
		}
		return true, nil

	// QUEUE
	case "QPUSH":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		val := tokens[2]
		q := db.Queues[name]
		QueuePush(&q, val)
		db.Queues[name] = q
		fmt.Println("OK")
		return true, nil

	case "QPOP":
		if len(tokens) < 2 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		q := db.Queues[name]
		v := QueuePop(&q)
		db.Queues[name] = q
		if v == "" {
			fmt.Println("EMPTY")
		} else {
			fmt.Println(v)
		}
		return true, nil

	// TREE
	case "TINSERT":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		ival, err := strconv.Atoi(tokens[2])
		if err != nil {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		t := db.Trees[name]
		if t == nil {
			t = &FullBinaryTree{}
			TreeInit(t)
		}
		TreeInsert(t, ival)
		db.Trees[name] = t
		fmt.Println("OK")
		return true, nil

	case "TGET":
		if len(tokens) < 3 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		ival, err := strconv.Atoi(tokens[2])
		if err != nil {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		t := db.Trees[name]
		if t == nil {
			fmt.Println("FALSE")
			return false, nil
		}
		if TreeFind(t, ival) {
			fmt.Println("TRUE")
		} else {
			fmt.Println("FALSE")
		}
		return false, nil

	case "TISFULL":
		if len(tokens) < 2 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		t := db.Trees[name]
		if t == nil {
			fmt.Println("TRUE")
			return false, nil
		}
		if TreeIsFull(t) {
			fmt.Println("TRUE")
		} else {
			fmt.Println("FALSE")
		}
		return false, nil

	// PRINT
	case "PRINT":
		if len(tokens) < 2 {
			fmt.Println("BAD ARGS")
			return false, nil
		}
		name := tokens[1]
		if arr, ok := db.Arrays[name]; ok {
			ArrayPrint(arr)
			return false, nil
		} else if head, ok := db.SLists[name]; ok {
			SListPrint(head)
			return false, nil
		} else if head, ok := db.DListsHead[name]; ok {
			DListPrintForward(head)
			return false, nil
		} else if st, ok := db.Stacks[name]; ok {
			StackPrint(st)
			return false, nil
		} else if q, ok := db.Queues[name]; ok {
			QueuePrint(q)
			return false, nil
		} else if t, ok := db.Trees[name]; ok {
			TreePrint(t)
			return false, nil
		} else {
			fmt.Println("NOT FOUND")
			return false, nil
		}

	default:
		fmt.Println("UNKNOWN COMMAND")
		return false, nil
	}
}

// splitTokens splits by whitespace. Values with spaces are not supported.
func splitTokens(s string) []string {
	fields := strings.Fields(s)
	return fields
}
