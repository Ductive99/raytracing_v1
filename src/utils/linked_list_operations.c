/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:24:07 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/16 03:37:09 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * ft_lstnew - Allocates and initializes a new list node
 *
 * @content: Pointer to the data to store in the node
 *
 * Return: Pointer to the new node, or NULL if allocation fails
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->obj = content;
	new->next = NULL;
	return (new);
}

/**
 * ft_lstadd_back - Adds a new node at the end of the list
 *
 * @lst: Address of the pointer to the first node of the list
 * @new: Pointer to the new node to add
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

/**
 * ft_lstclear - Deletes and frees all nodes of a list
 *
 * @lst: Address of the pointer to the first node of the list
 * @del: Function to delete the content of each node
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->obj);
		free(*lst);
		*lst = tmp;
	}
}

/**
 * del_obj - Frees a generic object
 *
 * @obj: Pointer to the object to free
 */
void	del_obj(void *obj)
{
	if (obj)
		free(obj);
}
