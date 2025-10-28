package main

import (
	"fmt"
	"strings"
)


func StackPush(s *[]string, val string) {
	*s = append(*s, val)
}

func StackPop(s *[]string) string {
	if len(*s) == 0 {
		return ""
	}
	l := len(*s)
	v := (*s)[l-1]
	*s = (*s)[:l-1]
	return v
}

func StackPrint(s []string) {
	for _, v := range s {
		fmt.Print(v, " ")
	}
	fmt.Println()
}

func StackSerialize(s []string) string {
	return strings.Join(s, ",")
}

func StackDeserialize(s *[]string, str string) {
	*s = nil
	if strings.TrimSpace(str) == "" {
		return
	}
	parts := strings.Split(str, ",")
	for _, p := range parts {
		if p == "" {
			continue
		}
		*s = append(*s, p)
	}
}
