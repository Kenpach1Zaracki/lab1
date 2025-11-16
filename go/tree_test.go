package main

import (
	"testing"
)

func TestTreeInit(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	if tree.Root != nil {
		t.Error("Expected tree root to be nil after init")
	}
}

func TestTreeInsertSingle(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	TreeInsert(tree, 10)
	
	if tree.Root == nil {
		t.Fatal("Expected tree root to not be nil after insert")
	}
	if tree.Root.Value != 10 {
		t.Errorf("Expected root value 10, got %d", tree.Root.Value)
	}
}

func TestTreeInsertMultiple(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	TreeInsert(tree, 10)
	TreeInsert(tree, 20)
	TreeInsert(tree, 30)
	
	if !TreeFind(tree, 10) {
		t.Error("Expected to find 10")
	}
	if !TreeFind(tree, 20) {
		t.Error("Expected to find 20")
	}
	if !TreeFind(tree, 30) {
		t.Error("Expected to find 30")
	}
}

func TestTreeFindExisting(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	TreeInsert(tree, 50)
	TreeInsert(tree, 30)
	TreeInsert(tree, 70)
	
	if !TreeFind(tree, 50) {
		t.Error("Expected to find 50")
	}
	if !TreeFind(tree, 30) {
		t.Error("Expected to find 30")
	}
	if !TreeFind(tree, 70) {
		t.Error("Expected to find 70")
	}
}

func TestTreeFindNonExisting(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	TreeInsert(tree, 50)
	
	if TreeFind(tree, 100) {
		t.Error("Did not expect to find 100")
	}
}

func TestTreeFindEmpty(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	
	if TreeFind(tree, 50) {
		t.Error("Did not expect to find anything in empty tree")
	}
}

func TestTreeIsFullEmpty(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	
	if !TreeIsFull(tree) {
		t.Error("Expected empty tree to be full")
	}
}

func TestTreeIsFullSingle(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	TreeInsert(tree, 10)
	
	if !TreeIsFull(tree) {
		t.Error("Expected single node tree to be full")
	}
}

func TestTreeIsFullThreeNodes(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	TreeInsert(tree, 10)
	TreeInsert(tree, 20)
	TreeInsert(tree, 30)
	
	if !TreeIsFull(tree) {
		t.Error("Expected three node tree to be full")
	}
}

func TestTreeClear(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	TreeInsert(tree, 10)
	TreeInsert(tree, 20)
	TreeClear(tree)
	
	if tree.Root != nil {
		t.Error("Expected tree root to be nil after clear")
	}
}

func TestTreeSerialize(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	TreeInsert(tree, 10)
	TreeInsert(tree, 20)
	TreeInsert(tree, 30)
	
	serialized := TreeSerialize(tree)
	if serialized == "" {
		t.Error("Expected non-empty serialization")
	}
}

func TestTreeSerializeEmpty(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	
	serialized := TreeSerialize(tree)
	if serialized != "" {
		t.Error("Expected empty serialization for empty tree")
	}
}

func TestTreeDeserialize(t *testing.T) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	TreeDeserialize(tree, "10,20,30")
	
	if !TreeFind(tree, 10) {
		t.Error("Expected to find 10 after deserialization")
	}
	if !TreeFind(tree, 20) {
		t.Error("Expected to find 20 after deserialization")
	}
	if !TreeFind(tree, 30) {
		t.Error("Expected to find 30 after deserialization")
	}
}

func TestTreeSerializeDeserialize(t *testing.T) {
	tree1 := &FullBinaryTree{}
	TreeInit(tree1)
	TreeInsert(tree1, 50)
	TreeInsert(tree1, 30)
	TreeInsert(tree1, 70)
	
	serialized := TreeSerialize(tree1)
	
	tree2 := &FullBinaryTree{}
	TreeInit(tree2)
	TreeDeserialize(tree2, serialized)
	
	if !TreeFind(tree2, 50) || !TreeFind(tree2, 30) || !TreeFind(tree2, 70) {
		t.Error("Deserialized tree does not match original")
	}
}

// Бенчмарки
func BenchmarkTreeInsert(b *testing.B) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		TreeInsert(tree, i)
	}
}

func BenchmarkTreeFind(b *testing.B) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	
	for i := 0; i < 1000; i++ {
		TreeInsert(tree, i)
	}
	
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		TreeFind(tree, i%1000)
	}
}

func BenchmarkTreeSerialize(b *testing.B) {
	tree := &FullBinaryTree{}
	TreeInit(tree)
	
	for i := 0; i < 100; i++ {
		TreeInsert(tree, i)
	}
	
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		TreeSerialize(tree)
	}
}
