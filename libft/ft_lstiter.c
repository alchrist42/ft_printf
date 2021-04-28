#include "libft.h"

/*
**	@brief	iterates the list and applies the function to the content
**	
**	@param	lst		pointer to the list
**	@param	f		function to change content
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
