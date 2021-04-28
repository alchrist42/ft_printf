#include "libft.h"

/*
**	@brief	deletes and free one element of the list
**	
**	@param	lst		pointer to element of the list
**	@param	del		function, used to delete content
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}
