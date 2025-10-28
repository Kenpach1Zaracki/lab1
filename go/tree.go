package main

import (
	"fmt"
	"strconv"
	"strings"
)

type TNode struct {
	Value int
	Left  *TNode
	Right *TNode
}

type FullBinaryTree struct {
	Root *TNode
}

func TreeInit(t *FullBinaryTree) {
	t.Root = nil
}

func treeClearNode(node *TNode) {
	if node == nil {
		return
	}
	treeClearNode(node.Left)
	treeClearNode(node.Right)
}

func TreeClear(t *FullBinaryTree) {
	treeClearNode(t.Root)
	t.Root = nil
}

func TreeInsert(t *FullBinaryTree, value int) {
	n := &TNode{Value: value}
	if t.Root == nil {
		t.Root = n
		return
	}
	queue := []*TNode{t.Root}
	for len(queue) > 0 {
		cur := queue[0]
		queue = queue[1:]
		if cur.Left == nil {
			cur.Left = n
			return
		} else {
			queue = append(queue, cur.Left)
		}
		if cur.Right == nil {
			cur.Right = n
			return
		} else {
			queue = append(queue, cur.Right)
		}
	}
}

func TreeFind(t *FullBinaryTree, value int) bool {
	if t.Root == nil {
		return false
	}
	queue := []*TNode{t.Root}
	for len(queue) > 0 {
		cur := queue[0]
		queue = queue[1:]
		if cur.Value == value {
			return true
		}
		if cur.Left != nil {
			queue = append(queue, cur.Left)
		}
		if cur.Right != nil {
			queue = append(queue, cur.Right)
		}
	}
	return false
}

func TreeIsFull(t *FullBinaryTree) bool {
	if t.Root == nil {
		return true
	}
	queue := []*TNode{t.Root}
	for len(queue) > 0 {
		cur := queue[0]
		queue = queue[1:]
		if cur.Left == nil && cur.Right != nil {
			return false
		}
		if (cur.Left == nil && cur.Right != nil) || (cur.Left != nil && cur.Right == nil) {
			return false
		}
		if cur.Left != nil {
			queue = append(queue, cur.Left)
		}
		if cur.Right != nil {
			queue = append(queue, cur.Right)
		}
	}
	return true
}

func TreePrint(t *FullBinaryTree) {
	if t.Root == nil {
		fmt.Println("Tree is empty")
		return
	}
	queue := []*TNode{t.Root}
	for len(queue) > 0 {
		n := len(queue)
		for i := 0; i < n; i++ {
			cur := queue[0]
			queue = queue[1:]
			fmt.Print(cur.Value, " ")
			if cur.Left != nil {
				queue = append(queue, cur.Left)
			}
			if cur.Right != nil {
				queue = append(queue, cur.Right)
			}
		}
		fmt.Println()
	}
}

func TreeSerialize(t *FullBinaryTree) string {
	if t.Root == nil {
		return ""
	}
	var parts []string
	queue := []*TNode{t.Root}
	for len(queue) > 0 {
		cur := queue[0]
		queue = queue[1:]
		parts = append(parts, strconv.Itoa(cur.Value))
		if cur.Left != nil {
			queue = append(queue, cur.Left)
		}
		if cur.Right != nil {
			queue = append(queue, cur.Right)
		}
	}
	return strings.Join(parts, ",")
}

func TreeDeserialize(t *FullBinaryTree, s string) {
	TreeClear(t)
	if strings.TrimSpace(s) == "" {
		return
	}
	parts := strings.Split(s, ",")
	for _, p := range parts {
		if p == "" {
			continue
		}
		v, err := strconv.Atoi(p)
		if err != nil {
			continue
		}
		TreeInsert(t, v)
	}
}
