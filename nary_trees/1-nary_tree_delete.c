#include "nary_trees.h"

/**
 * nary_tree_delete - Delete a N-ary tree
 * @tree: Pointer to the root node of the tree to delete
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *node;
	nary_tree_t *next;

	if (tree == NULL)
		return;

	node = tree->children;
	while (node)
	{
		next = node->next;
		nary_tree_delete(node);
		node = next;
	}
	free(tree->content);
	free(tree);
}
