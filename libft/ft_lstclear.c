#include "libft.h"

/*
**	@brief	deletes and frees the given element and every successor of that element
**	
**	@param	lst		the addres of a pointer to the list
**	@param	del		function , used to delete content
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
}
