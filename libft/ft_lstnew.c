#include "libft.h"

/*
**	@brief	create new list element
**	
**	@param	content		element content
**	@return	t_list*	pointer to new element or NULL
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(*elem));
	if (elem)
	{
		elem->content = content;
		elem->next = NULL;
	}
	return (elem);
}
