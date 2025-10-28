package main

import (
	"fmt"
	"strings"
)

type DNode struct {
	Value string
	Next  *DNode
	Prev  *DNode
}

func DListPushFront(head **DNode, tail **DNode, val string) {
	n := &DNode{Value: val, Next: *head, Prev: nil}
	if *head != nil {
		(*head).Prev = n
	}
	*head = n
	if *tail == nil {
		*tail = n
	}
}

func DListPushBack(head **DNode, tail **DNode, val string) {
	n := &DNode{Value: val, Next: nil, Prev: *tail}
	if *tail != nil {
		(*tail).Next = n
	}
	*tail = n
	if *head == nil {
		*head = n
	}
}

func DListFind(head *DNode, val string) *DNode {
	for cur := head; cur != nil; cur = cur.Next {
		if cur.Value == val {
			return cur
		}
	}
	return nil
}

func DListInsertAfter(head **DNode, tail **DNode, afterVal, val string) {
	cur := DListFind(*head, afterVal)
	if cur == nil {
		return
	}
	n := &DNode{Value: val, Next: cur.Next, Prev: cur}
	if cur.Next != nil {
		cur.Next.Prev = n
	}
	cur.Next = n
	if *tail == cur {
		*tail = n
	}
}

func DListInsertBefore(head **DNode, tail **DNode, beforeVal, val string) {
	cur := DListFind(*head, beforeVal)
	if cur == nil {
		return
	}
	n := &DNode{Value: val, Next: cur, Prev: cur.Prev}
	if cur.Prev != nil {
		cur.Prev.Next = n
	}
	cur.Prev = n
	if *head == cur {
		*head = n
	}
}

func DListRemoveValue(head **DNode, tail **DNode, val string) {
	cur := DListFind(*head, val)
	if cur == nil {
		return
	}
	if cur.Prev != nil {
		cur.Prev.Next = cur.Next
	} else {
		*head = cur.Next
	}
	if cur.Next != nil {
		cur.Next.Prev = cur.Prev
	} else {
		*tail = cur.Prev
	}
}

func DListRemoveAfter(head **DNode, tail **DNode, afterVal string) {
	cur := DListFind(*head, afterVal)
	if cur == nil || cur.Next == nil {
		return
	}
	t := cur.Next
	cur.Next = t.Next
	if t.Next != nil {
		t.Next.Prev = cur
	} else {
		*tail = cur
	}
}

func DListRemoveBefore(head **DNode, tail **DNode, beforeVal string) {
	cur := DListFind(*head, beforeVal)
	if cur == nil || cur.Prev == nil {
		return
	}
	t := cur.Prev
	if t.Prev != nil {
		t.Prev.Next = cur
	} else {
		*head = cur
	}
	cur.Prev = t.Prev
}

func DListPrintForward(head *DNode) {
	for cur := head; cur != nil; cur = cur.Next {
		fmt.Print(cur.Value, " ")
	}
	fmt.Println()
}

func DListPrintBackward(tail *DNode) {
	for cur := tail; cur != nil; cur = cur.Prev {
		fmt.Print(cur.Value, " ")
	}
	fmt.Println()
}

func DListSerialize(head *DNode) string {
	var parts []string
	for cur := head; cur != nil; cur = cur.Next {
		parts = append(parts, cur.Value)
	}
	return strings.Join(parts, ",")
}

func DListDeserialize(head **DNode, tail **DNode, s string) {
	*head = nil
	*tail = nil
	if strings.TrimSpace(s) == "" {
		return
	}
	parts := strings.Split(s, ",")
	for _, p := range parts {
		if p == "" {
			continue
		}
		DListPushBack(head, tail, p)
	}
}

