package main

import (
	"fmt"
)

func ArrayPushBack(arr *[]string, val string) {
	*arr = append(*arr, val)
}

func ArrayInsertAt(arr *[]string, idx int, val string) {
	if idx < 0 {
		idx = 0
	}
	if idx >= len(*arr) {
		*arr = append(*arr, val)
		return
	}
	a := *arr
	a = append(a[:idx+1], a[idx:]...)
	a[idx] = val
	*arr = a
}

func ArrayEraseAt(arr *[]string, idx int) {
	if idx < 0 || idx >= len(*arr) {
		return
	}
	a := *arr
	a = append(a[:idx], a[idx+1:]...)
	*arr = a
}

func ArrayGet(arr []string, idx int) string {
	if idx < 0 || idx >= len(arr) {
		return ""
	}
	return arr[idx]
}

func ArrayPrint(arr []string) {
	for _, v := range arr {
		fmt.Print(v, " ")
	}
	fmt.Println()
}
