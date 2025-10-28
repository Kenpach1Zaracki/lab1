package main

import (
	"fmt"
	"strings"
)

func QueuePush(q *[]string, val string) {
	*q = append(*q, val)
}

func QueuePop(q *[]string) string {
	if len(*q) == 0 {
		return ""
	}
	v := (*q)[0]
	*q = (*q)[1:]
	return v
}

func QueuePrint(q []string) {
	for _, v := range q {
		fmt.Print(v, " ")
	}
	fmt.Println()
}

func QueueSerialize(q []string) string {
	return strings.Join(q, ",")
}

func QueueDeserialize(q *[]string, str string) {
	*q = nil
	if strings.TrimSpace(str) == "" {
		return
	}
	parts := strings.Split(str, ",")
	for _, p := range parts {
		if p == "" {
			continue
		}
		*q = append(*q, p)
	}
}
