#include "rb_trees.h"

/**
 * swap_colors - Swap the colors of two nodes.
 * @parent: Pointer to the first node.
 * @grandparent: Pointer to the second node.
 */
void swap_colors(rb_tree_t *parent, rb_tree_t *grandparent)
{
	rb_color_t temp = parent->color;

	parent->color = grandparent->color;
	grandparent->color = temp;
}

/**
 * rotate_left - Perform a left rotation on the given nodes.
 * @tree: Double pointer to the root node of the tree.
 * @parent: Pointer to the parent node to rotate.
 */
void rotate_left(rb_tree_t **tree, rb_tree_t *parent)
{
	rb_tree_t *right_child = parent->right; /* future new parent */

	/* little son become son... */
	parent->right = right_child->left;
	/* ...and then his grandpa become parent if exists */
	if (parent->right)
		parent->right->parent = parent;

	/* modify grandpa */
	right_child->parent = parent->parent;
	if (!parent->parent) /* no grandpa */
		*tree = right_child;
	else if (parent == parent->parent->left) /* left child of grandpa */
		parent->parent->left = right_child;
	else
		parent->parent->right = right_child; /* right child of grandpa */
	/* modify left child */
	right_child->left = parent;
	/* parent of old head is now old right child */
	parent->parent = right_child;
}

/**
 * rotate_right - Perform a right rotation on the given nodes.
 * @tree: Double pointer to the root node of the tree.
 * @grandparent: Pointer to the grandparent node to rotate.
 */
void rotate_right(rb_tree_t **tree, rb_tree_t *grandparent)
{
	rb_tree_t *parent = grandparent->left;

	grandparent->left = parent->right;

	if (parent->right)
		parent->right->parent = grandparent;

	parent->parent = grandparent->parent;

	if (!grandparent->parent)
		*tree = parent;
	else if (grandparent == grandparent->parent->left)
		grandparent->parent->left = parent;
	else
		grandparent->parent->right = parent;

	parent->right = grandparent;
	grandparent->parent = parent;
}

/**
 * rotate_cases - handle all cases to fix red-black tree
 * @tree: Double pointer to the root node of the tree.
 * @new_node: Double pointer to new node.
 * @parent: Pointer to the parent node to rotate.
 * @grandparent: Pointer to the grandparent node to rotate.
 * @is_right: Boolean to select direction of the rotation
 */
void rotate_cases(rb_tree_t **tree, rb_tree_t **new_node, rb_tree_t *parent,
				rb_tree_t *grandparent, int is_right)
{
	rb_tree_t *uncle = NULL;

	uncle = is_right ? grandparent->left : grandparent->right;

	/* Case 1: Uncle is RED */
	if (uncle && uncle->color == RED)
	{
		grandparent->color = RED;
		parent->color = BLACK;
		uncle->color = BLACK;
		*new_node = grandparent;
	}
	else
	{
		/* Case 2: Uncle is BLACK and new_node is the right child */
		if (!is_right && (*new_node == parent->right))
		{
			rotate_left(tree, parent);
			*new_node = parent;
			parent = (*new_node)->parent;
		}
		if (is_right && (*new_node == parent->left))
		{
			rotate_right(tree, parent);
			*new_node = parent;
			parent = (*new_node)->parent;
		}

		/* Case 3: Uncle is BLACK and new_node is the left child */
		is_right ? rotate_left(tree, grandparent) : rotate_right(tree, grandparent);
		swap_colors(parent, grandparent);
		*new_node = parent;
	}
}

/**
 * fix_rb_insert - fix red-black tree after new node inserted.
 * @tree: Double pointer to the root node of the tree.
 * @new_node: new node inserted.
 */
void fix_rb_insert(rb_tree_t **tree, rb_tree_t *new_node)
{
	rb_tree_t *parent = NULL;
	rb_tree_t *grandparent = NULL;

	while (new_node != *tree && new_node->color == RED
			&& new_node->parent->color == RED)
	{
		parent = new_node->parent;
		grandparent = parent->parent;
		rotate_cases(tree, &new_node, parent, grandparent, !(parent == grandparent->left));
	}

	(*tree)->color = BLACK;
}

/**
 * rb_tree_insert - insert a new node in a red-black tree.
 * @tree: Double pointer to the root node of the tree.
 * @value: value of new node.
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node = rb_tree_node(NULL, value, RED);
	rb_tree_t *current = *tree;
	rb_tree_t *parent = NULL;

	if (!new_node)
		return (NULL);

	if (*tree == NULL)
	{
		new_node->color = BLACK;
		*tree = new_node;
		return (new_node);
	}

	while (current != NULL)
	{
		parent = current;
		if (value == current->n)
		{
			free(new_node);
			return (NULL);
		}
		else if (value < current->n)
			current = current->left;
		else
			current = current->right;
	}

	new_node->parent = parent;
	if (value < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;

	fix_rb_insert(tree, new_node);

	return (new_node);
}
