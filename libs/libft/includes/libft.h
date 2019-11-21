/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:41:19 by jblack-b          #+#    #+#             */
/*   Updated: 2019/11/08 19:51:49 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# define TRUE 1
# define FALSE 0
# define VECTOR_INIT_CAPACITY 4
# define BZERO(a)		ft_bzero(&a, sizeof(a))
# define MEMCHR(a, b)	ft_memchr((a), (b), sizeof(a) - 1)
# define VSPLIT(v, x)	ft_nsplit((v).data, (v).used, x, sizeof(x) - 1)
# define STRTOB10(s, x)	fmt_atoi(s, (unsigned long *)&x, 10, 0)
# define MIN(a,b)	((a <= b) ? a : b)
# define MAX(a,b)	((a > b) ? a : b)
# define ABS(x)		(((x) < 0) ? (-x) : (x))

typedef struct s_vector	t_vector;
typedef void			(*t_f_vector_add)(t_vector *v, void * item);
typedef void			(*t_f_vector_set)(t_vector *v, int id, void * item);
typedef void			*(*t_f_vector_get)(t_vector *v, int id);
typedef void			(*t_f_vector_delete)(t_vector *v, int id);
typedef int				(*t_f_vector_total)(t_vector *v);
typedef void			(*t_f_vector_free)(t_vector *v);

struct					s_vector
{
	void				**items;
	int					capacity;
	int					total;
	t_f_vector_add		add;
	t_f_vector_set		set;
	t_f_vector_get		get;
	t_f_vector_delete	del;
	t_f_vector_total	length;
	t_f_vector_free		free;
};

enum					e_rb_color
{
	RB_BLACK,
	RB_RED
};

typedef struct			s_rb_node
{
	struct s_rb_node	*parent;
	struct s_rb_node	*left;
	struct s_rb_node	*right;
	void				*data;
	enum e_rb_color		color;
}						t_rb_node;

typedef struct			s_btree
{
	struct s_btree		*left;
	struct s_btree		*right;
	void				*item;
}						t_btree;

typedef struct			s_queue
{
	struct s_queue		*next;
	struct s_btree		*node;
	int					current_level;
	int					is_first_elem;
}						t_queue;

typedef struct			s_list
{
	void				*content;
	int					content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_list2w
{
	void				*content;
	int					content_size;
	struct s_list2w		*next;
	struct s_list2w		*before;
}						t_list2w;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_stack
{
	t_list				*top;
	size_t				size;
}						t_stack;
void					*ft_memset(void *b, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src,
int c, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
size_t					ft_strlen(const char *s);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strdup(const char *s1);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnstr(const char *haystack, const char *needle,
size_t len);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s,
unsigned int start, size_t len);
char					*ft_strtrim(char const *s);
char					*ft_strjoin(char const *s1, char const *s2);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa(int n);
void					ft_putchar(int c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst,
void (*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					*ft_realloc(void *ptr, size_t size);
void					ft_lstprint(t_list *list);
int						ft_arraymax(int *array, size_t length);
int						ft_arraymin(int *array, size_t length);
void					ft_swap_int(int *a, int *b);
void					ft_arrayprint(int *array, size_t length);
void					ft_arraysort(int *array, size_t length);
void					ft_lstclean(t_list **begin);
void					ft_lstdel_u(t_list **list);
int						ft_lstdelmid(t_list **begin, t_list **list);
int						get_next_line(const int fd, char **line);
void					ft_printmap(char **map);
int						ft_2darrayclean(char ***dst);
char					**ft_2darraynew(size_t y, size_t x, char c);
t_point					*ft_point_new(int x, int y);
size_t					ft_lstcount(t_list *lst);
void					ft_lstrev(t_list **alst);
int						ft_is_space(char c);
size_t					ft_countwords(char *str, char sep);
char					*ft_strnewch(size_t n, char c);
int						ft_sign(double n);
void					ft_stack_print(t_stack *stack);
t_stack					*ft_stack_create(void *content, size_t content_size);
void					ft_stack_push(t_stack *stack, void *content,
size_t content_size);
t_list					*ft_stack_pop(t_stack *stack);
t_list					*ft_stack_peek(t_stack *stack);
void					ft_lst2w_pushback(t_list2w *begin, t_list2w *new);
t_list2w				*ft_lst2w_new(void *content, size_t content_size);
void					ft_memprint(void *s, size_t n);
void					ft_print_node(void *item);
t_btree					*ft_btree_create_node(void *item);
void					ft_btree_apply_prefix(t_btree *root,
void (*applyf)(void *));
void					ft_btree_apply_infix(t_btree *root,
void (*applyf)(void*));
void					ft_btree_apply_suffix(t_btree *root,
void (*applyf)(void*));
void					ft_btree_insert_data(t_btree **root,
void *item, int (*cmpf)(void *, void *));
void					*ft_btree_search_item(t_btree *root,
void *data_ref, int (*cmpf)(void *, void *));
int						ft_btree_level_count(t_btree *root);
void					ft_queue_push(t_queue **queue, t_btree *root,
int current_level);
t_queue					*ft_queue_pop(t_queue **queue);
void					ft_btree_apply_by_level(t_btree *root,
void (*applyf)(void *item, int current_level, int is_first_elem));
void					ft_btree_print(t_btree *root, int spaces);
t_rb_node				*ft_rb_node_create(void *data);
void					ft_rb_insert(t_rb_node **root,
void *data, int (*cmpf)(void *, void *));
void					ft_rb_node_print(t_rb_node *root, int spaces);
void					vector_init(t_vector *a);
int						vector_total(t_vector *a);
void					vector_resize(t_vector *a, int b);
void					vector_add(t_vector *a, void *b);
void					vector_set(t_vector *a, int b, void *c);
void					*vector_get(t_vector *a, int b);
void					vector_delete(t_vector *a, int b);
void					vector_free(t_vector *a);
void					vector_resize(t_vector *v, int capacity);
char					*read_file(int fd, size_t *size);
void					ft_malloc_err(size_t size, const char *func,
const char *file, int line);
unsigned char			**ft_nsplit(void *s, size_t n1, void *match, size_t n2);
unsigned char			*ft_word(void **p, size_t *n1, void *match, size_t n2);
void					*ft_mempcpy(void *dest, const void *src, size_t n);
void					ft_2darray_uchar_free(unsigned char ***tab);
void					ft_terminate(char *str);
#endif
