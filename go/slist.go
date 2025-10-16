package main

import (
	"fmt"
	"strings"
)

// Node for singly linked list (string values)
type Node struct {
	Value string
	Next  *Node
}

// push front O(1)
func SListPushFront(head **Node, val string) {
	n := &Node{Value: val, Next: *head}
	*head = n
}

// push back O(n)
func SListPushBack(head **Node, val string) {
	if *head == nil {
		*head = &Node{Value: val, Next: nil}
		return
	}
	cur := *head
	for cur.Next != nil {
		cur = cur.Next
	}
	cur.Next = &Node{Value: val, Next: nil}
}

// find by value O(n)
func SListFind(head *Node, val string) *Node {
	for cur := head; cur != nil; cur = cur.Next {
		if cur.Value == val {
			return cur
		}
	}
	return nil
}

// insert after given node O(1)
func SListInsertAfter(node *Node, val string) {
	if node == nil {
		return
	}
	n := &Node{Value: val, Next: node.Next}
	node.Next = n
}

// insert before given node O(n) (we need previous)
func SListInsertBefore(head **Node, node *Node, val string) {
	if node == nil {
		return
	}
	if *head == node {
		SListPushFront(head, val)
		return
	}
	prev := *head
	for prev != nil && prev.Next != node {
		prev = prev.Next
	}
	if prev == nil {
		return
	}
	n := &Node{Value: val, Next: node}
	prev.Next = n
}

// remove first occurrence of value O(n)
func SListRemoveValue(head **Node, val string) {
	if *head == nil {
		return
	}
	if (*head).Value == val {
		*head = (*head).Next
		return
	}
	cur := *head
	for cur.Next != nil && cur.Next.Value != val {
		cur = cur.Next
	}
	if cur.Next != nil {
		cur.Next = cur.Next.Next
	}
}

// remove node after node with given value (find node with value, delete node->next)
func SListRemoveAfter(head *Node, val string) {
	cur := head
	for cur != nil && cur.Value != val {
		cur = cur.Next
	}
	if cur != nil && cur.Next != nil {
		cur.Next = cur.Next.Next
	}
}

func SListPrint(head *Node) {
	for cur := head; cur != nil; cur = cur.Next {
		fmt.Print(cur.Value, " ")
	}
	fmt.Println()
}

func SListSerialize(head *Node) string {
	var parts []string
	for cur := head; cur != nil; cur = cur.Next {
		parts = append(parts, cur.Value)
	}
	return strings.Join(parts, ",")
}

func SListDeserialize(head **Node, s string) {
	// clear existing
	*head = nil
	if strings.TrimSpace(s) == "" {
		return
	}
	parts := strings.Split(s, ",")
	for _, p := range parts {
		if p == "" {
			continue
		}
		SListPushBack(head, p)
	}
}
