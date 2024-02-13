#include "nary_trees.h"

nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new_node;

	new_node = malloc(sizeof(nary_tree_t));
	if (new_node == NULL)
		return (NULL);
	new_node->content = strdup(str);
	if (new_node->content == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->parent = parent;
	new_node->nb_children = 0;
	new_node->children = NULL;
	new_node->next = NULL;
	if (parent != NULL)
	{
		new_node->next = parent->children;
		parent->children = new_node;
		parent->nb_children += 1;
	}
	return (new_node);
}
