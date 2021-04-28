#include "libft.h"

/*
**	@brief	create new list, where each content is result successive applied
**			of the function to content element of old list
**	
**	@param	lst		pointer to the old list
**	@param	f		function for create new content
**	@param	del		function for delete content in new list if create fail
**	@return	t_list*	pointer to new list or NULL
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),	void (*del)(void *))
{
	t_list	*begin;
	t_list	*cur;
	t_list	*new;

	begin = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		if (begin)
			ft_lstadd_back(&cur, new);
		else
		{
			begin = new;
			cur = new;
		}
		lst = lst->next;
	}
	return (begin);
}
