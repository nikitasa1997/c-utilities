#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "bin_tree.h"

typedef struct bin_tree_node BinTreeNode;

struct bin_tree_node
{
	BinTreeNode *parent;
	BinTreeNode *left;
	BinTreeNode *right;
	uint_least8_t data[];
};

struct bin_tree
{
	BinTreeNode *root;
	void (*destructor)(void *);
	int (*cmp)(const void *, const void *);
	size_t size;
	size_t count;
};

#define _BIN_TREE_H_SAVE_

int bin_tree_create(BinTree ** restrict tree_ptr, size_t size, void (*destructor)(void *), int (*cmp)(const void *, const void *))
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree_ptr == NULL || !size || cmp == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	register BinTree *temp = aligned_alloc(alignof(BinTree), sizeof(BinTree));
	if (temp == NULL)
	{
		return BIN_TREE_NO_MEMORY;
	}

	temp->root = NULL;
	temp->destructor = destructor;
	temp->cmp = cmp;
	temp->size = size;
	temp->count = 0u;

	*tree_ptr = temp;

	return BIN_TREE_SUCCESS;
}

void bin_tree_destroy(BinTree * restrict tree)
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	for (register BinTreeNode *node_ptr = tree->root; node_ptr != NULL;)
	{
		while (node_ptr->left != NULL || node_ptr->right != NULL)
		{
			if (node_ptr->left != NULL)
			{
				node_ptr = node_ptr->left;
			}
			else
			{
				node_ptr = node_ptr->right;
			}
		}

		if (node_ptr->parent != NULL)
		{
			if (node_ptr->parent->left == node_ptr)
			{
				node_ptr->parent->left = NULL;
			}
			else
			{
				node_ptr->parent->right = NULL;
			}
		}

		register BinTreeNode *temp = node_ptr;
		node_ptr = node_ptr->parent;
		if (tree->destructor != NULL)
		{
			tree->destructor(temp->data);
		}
		free(temp);
	}

	free(tree);
}

void bin_tree_clear(BinTree * restrict tree)
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	for (register BinTreeNode *node_ptr = tree->root; node_ptr != NULL;)
	{
		while (node_ptr->left != NULL && node_ptr->right != NULL)
		{
			if (node_ptr->left != NULL)
			{
				node_ptr = node_ptr->left;
			}
			else
			{
				node_ptr = node_ptr->right;
			}
		}

		if (node_ptr->parent != NULL)
		{
			if (node_ptr->parent->left == node_ptr)
			{
				node_ptr->parent->left = NULL;
			}
			else
			{
				node_ptr->parent->right = NULL;
			}
		}

		register BinTreeNode *temp = node_ptr;
		node_ptr = node_ptr->parent;
		if (tree->destructor != NULL)
		{
			tree->destructor(temp->data);
		}
		free(temp);
	}

	tree->root = NULL;
	tree->size = 0u;
}

size_t bin_tree_sizeof(register const BinTree * restrict tree)
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	return tree->size;
}

bool bin_tree_empty(register const BinTree * restrict tree)
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	return !tree->count;
}

size_t bin_tree_size(register const BinTree * restrict tree)
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	return tree->count;
}

int bin_tree_insert(BinTree * restrict tree, const void * restrict value)
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree == NULL || value == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	register BinTreeNode *node_ptr = tree->root, **link_ptr = &tree->root, *parent_ptr = NULL;
	while (node_ptr != NULL)
	{
		register int cmp_result = tree->cmp(value, node_ptr->data);
		parent_ptr = node_ptr;
		if (cmp_result < 0)
		{
			link_ptr = &node_ptr->left;
			node_ptr = node_ptr->left;
		}
		else if (cmp_result > 0)
		{
			link_ptr = &node_ptr->right;
			node_ptr = node_ptr->right;
		}
		else
		{
			return BIN_TREE_ALREADY_EXIST;
		}
	}

	node_ptr = aligned_alloc(alignof(BinTreeNode), sizeof(BinTreeNode) + tree->size);
	if (node_ptr == NULL)
	{
		return BIN_TREE_NO_MEMORY;
	}

	node_ptr->parent = parent_ptr;
	node_ptr->left = node_ptr->right = NULL;
	memcpy(node_ptr->data, value, tree->size);

	*link_ptr = node_ptr;

	++tree->count;

	return BIN_TREE_SUCCESS;
}

int bin_tree_find(const BinTree * restrict tree, const void *value, void *buffer)
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree == NULL || value == NULL || buffer == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	for (register const BinTreeNode *node_ptr = tree->root; node_ptr != NULL;)
	{
		register int cmp_result = tree->cmp(value, node_ptr->data);
		if (cmp_result < 0)
		{
			node_ptr = node_ptr->left;
		}
		else if (cmp_result > 0)
		{
			node_ptr = node_ptr->right;
		}
		else
		{
			memcpy(buffer, node_ptr->data, tree->size);

			return BIN_TREE_SUCCESS;
		}
	}

	return BIN_TREE_NOT_EXIST;
}

const void *bin_tree_at(const BinTree * restrict tree, const void * restrict value)
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree == NULL || value == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	for (register const BinTreeNode *node_ptr = tree->root; node_ptr != NULL;)
	{
		register int cmp_result = tree->cmp(value, node_ptr->data);
		if (cmp_result < 0)
		{
			node_ptr = node_ptr->left;
		}
		else if (cmp_result > 0)
		{
			node_ptr = node_ptr->right;
		}
		else
		{
			return node_ptr->data;
		}
	}

	return NULL;
}

int bin_tree_erase(BinTree * restrict tree, const void * restrict value)
{
#	ifdef _BIN_TREE_H_SAVE_
	if (tree == NULL || value == NULL)
	{
		exit(EXIT_FAILURE);
	}
#	endif

	register BinTreeNode *node_ptr = tree->root, *parent_ptr = NULL, **link_ptr = &tree->root;
	while (node_ptr != NULL)
	{
		register int cmp_result = tree->cmp(value, node_ptr->data);
		if (cmp_result < 0)
		{
			parent_ptr = node_ptr;
			link_ptr = &node_ptr->left;
			node_ptr = node_ptr->left;
		}
		else if (cmp_result > 0)
		{
			parent_ptr = node_ptr;
			link_ptr = &node_ptr->right;
			node_ptr = node_ptr->right;
		}
		else
		{
			break;
		}
	}

	if (node_ptr == NULL)
	{
		return BIN_TREE_NOT_EXIST;
	}

	if (tree->destructor != NULL)
	{
		tree->destructor(node_ptr->data);
	}
	if (node_ptr->left != NULL && node_ptr->right != NULL)
	{
		void *data = node_ptr->data;

		parent_ptr = node_ptr;
		link_ptr = &node_ptr->right;
		node_ptr = node_ptr->right;
		while (node_ptr->left != NULL)
		{
			parent_ptr = node_ptr;
			link_ptr = &node_ptr->left;
			node_ptr = node_ptr->left;
		}

		*link_ptr = node_ptr->right;
		if (node_ptr->right != NULL)
		{
			node_ptr->right->parent = parent_ptr;
		}
		memcpy(data, node_ptr->data, tree->size);
	}
	else
	{
		if (node_ptr->left != NULL)
		{
			*link_ptr = node_ptr->left;
			node_ptr->left->parent = parent_ptr;
		}
		else if (node_ptr->right != NULL)
		{
			*link_ptr = node_ptr->right;
			node_ptr->right->parent = parent_ptr;
		}
		else
		{
			*link_ptr = NULL;
		}
	}
	free(node_ptr);

	--tree->count;

	return BIN_TREE_SUCCESS;
}
