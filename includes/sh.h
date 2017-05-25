/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-la-s <vde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:40:03 by vde-la-s          #+#    #+#             */
/*   Updated: 2017/05/03 17:32:30 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH_H
# define FT_SH_H
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"
# include <unistd.h>
# include <sys/ioctl.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# include <stdio.h>

# define RED			"\033[31m"
# define NONE			42
# define CLOSE			43
# define OVER			44
# define ADD			45
# define T_CMD			0
# define T_PIPE			43
# define T_SCL			44
# define T_SRR			45
# define T_DRR			46
# define T_SLR			47
# define T_DLR			48
# define T_AND			49
# define T_OR			50
# define T_HDOC			51
# define WAIT			46
# define READ			47
# define WRITE			48
# define UP				4283163
# define DOWN			4348699
# define LEFT			4479771
# define RIGHT			4414235
# define CUP			71696882162459
# define CDOWN			72796393790235
# define CLEFT			74995417045787
# define CRIGHT			73895905418011
# define OUP			1096489755
# define ODOWN			1113266971
# define OLEFT			1146821403
# define ORIGHT			1130044187
# define HOME			4741915
# define END			4610843
# define DEL			127
# define ENTER			10
# define CL				12
# define TAB			9
# define ESC			27
# define SPC			32
# define OX				8948194
# define OC				42947
# define OV				10127586
# define HIDE			138
# define K_DEL			46
# define K_RE			47
# define W_MAX			900
# define NAV			42
# define EDIT			43
# define LINE			0
# define SEL			0
# define HDOC			1
# define DQUOT			2
# define SQUOT			3
# define BACKS			4

typedef struct			s_read
{
	char				*name;
	char				*value;
	struct s_read		*next;
}						t_read;

typedef struct			s_hist
{
	int					select;
	int					inlist;
	int					index;
	char				*name;
	struct s_hist		*prev;
	struct s_hist		*next;
}						t_hist;

typedef struct			s_afd
{
	char				*str;
	int					old;
	int					new;
	short				i_file;
	char				*file_name;
	char				special;
	short				type;
	struct s_afd		*next;
}						t_afd;

typedef struct			s_vec
{
	int					x;
	int					y;
}						t_vec;

typedef struct			s_cmd
{
	char				*name;
	char				**args;
	t_afd				*afd;
	int					ac;
	char				token;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_menv	t_me;

typedef struct			s_node
{
	t_cmd				*cmd;
	int					ret;
	int					(*handler)(struct s_menv*, struct s_node*);
	int					state;
	int					pid;
	int					pfd[2];
	int					mode;
	int					fd_out;
	short				is_hdoc;
	char				*thdoc;
	struct s_node		*parent;
	struct s_node		*left;
	struct s_node		*right;
	struct s_node		*back;
	struct s_node		*front;
	short				intent;
}						t_node;

typedef struct			s_edl
{
	int					type;
	int					ccmode;
	char				*line;
	char				*save;
	char				*t;
	char				*end;
	int					emode;
	t_vec				pos;
	int					spos;
	int					select[2];
	char				*clipboard;
	int					prompt_size;
}						t_edl;

struct					s_menv
{
	char				**oe;
	char				**e;
	char				**alias;
	char				**pe;
	char				**sh_c;
	char				**o_shc;
	t_cmd				*cmds;
	t_node				*tcu;
	t_node				*trees;
	t_node				*tc;
	short				go;
	char				*hout;
	char				*hdend;
	int					hdstop;
	int					fd_in;
	int					prank;
	char				*afds;
	char				**afd;
	t_afd				*a_fd;
	char				*name_term;
	struct termios		term;
	struct termios		save;
	int					fd;
	t_hist				*hi;
	t_hist				*l;
	t_edl				edl;
	int					stop_edl;
	int					pprompt;
	int					width;
	int					height;
	struct s_read		*var_read;
};

typedef	struct			s_auto
{
	char				*value;
	int					select;
	struct s_auto		*prev;
	struct s_auto		*next;
}						t_auto;

typedef struct			s_sig
{
	int					save_i;
	int					save_o;
	int					save_e;
	char				*fds_iu;
	t_me				*me;
	t_edl				*tmp;
}						t_sig;

t_sig					g_sigs;

int						ft_tablen(char **str);
char					*find_read_var(t_me *me, char *s);
char					*replace_read_variables(t_me *me, char *s);
void					ft_read(t_me *me, t_cmd *cmd);
char					*remplace_p_ex_line2(char *str, char *tmp, int i);
char					*tab_to_str(char **tabb);
void					remplace_last_hist(t_me *me, char *str);
char					*remplace_line(t_me *me, int nb);
char					*find_same_hist(char *str, t_me *me, int t, int nb);
char					*find_same_hist_return1(t_me *me, t_hist *tmp\
	, char *fin, int t);
char					*n_elem_hist(t_me *me, int num_param, char *str);
char					*find_same_hist_return2(t_me *me, t_hist *tmp,\
	char *fin, int nb);
void					find_cmp_option(int *t, int *nb, char **file, int r);
void					find_cmp(char **fin, char **file, char *str);
char					*find_last_param(t_me *me, char *str);
void					rm_last_elem_hist(t_me *me);
char					*find_param(t_me *me, char *str);
char					*last_elem_hist(t_me *me);
char					*n_elem_hist_find_end(char *line, char *tmp, int i);
void					history_w(t_me *me, char *name, int i);
void					rm_history(t_me *me, int nb);
int						usage_history(void);
int						is_c(char **tabb);
void					affi_history(t_me *me, int r, int fd, int affindex);
void					affi_end_history(t_me *me, int r, int fd, int affindex);
t_hist					*affi_end_history2(t_hist *tmp, int r);
void					clean_history(t_me *me);
void					affi_hist_index(t_hist *tmp, int i, int fd);
void					find_index_max(t_me *me, int *i);
int						intlen(long int nbr);
void					down_hist2(t_me *me, t_edl *edl, t_hist *t, int c);
void					execute_qenter_init(t_me *me, t_edl *edl);
char					*last_one(t_me *me, t_edl *edl, char *s, char **qtype);
void					execute_qenter_do(t_me *me, t_edl *edl);
void					rm_list_elem(t_me *me, t_hist *tmp, int *i);
void					history_2(t_me *me, t_node *curs, int res);
int						p_ex(char **args);
char					*ft_strjoinfree(char const *s1, char const *s2, int i);
void					remplace_p_ex(t_me *me, t_node *curs);
char					*find_hist_file(t_me *me);
void					history_a(t_me *me, char *name, int i);
void					history_r(t_me *me, char *name, int i);
void					history(t_me *me, t_node *curs);
void					restor_select(t_me *me);
void					middle_write(t_me *me, t_edl *edl, char key);
int						char_isnot(char c, char *s, int i);
char					*string_del(char *r, int i);
int						nescape(char *s, int i);
int						isin_squote(char *s, int i);
t_hist					*get_hist_match(t_me *me, t_edl *edl, long int key);
int						switch_history_end(t_hist *t, t_me *me, t_edl *edl,\
long int key);
int						var_name_size(char *s);
void					init_mcmd(t_cmd *new, char *name);
void					end_execute_enter(t_me *me, t_edl *edl);
void					init_core_end(t_me *me);
t_hist					*hi_end(t_hist *start);
int						str_headmatch(char *s1, char *head);
void					import_config(t_me *me);
char					**tab_nset(char **t, int n);
void					clean_cmd_data(char **t, int i);
char					*replace_variables(t_me *me, char *s);
void					create_trees(t_me *me);
t_node					*prepare_exec(t_me *me, t_node *curs);
void					execute_select(t_me *me, t_edl *edl, long int key);
void					switch_history(t_me *me, t_edl *edl, int key);
void					execute_enter_key(t_me *me, t_edl *edl);
int						is_ok_quote(char *s);
char					*msub_string(char *s, int start, int end);
char					*cut_clipboard(t_edl *edl);
void					sig_int_quote(int sig);
void					sig_int(int sig);
t_afd					*create_afd_list(char **afd);
t_node					*prepare_exec(t_me *me, t_node *curs);
int						valid_tree(t_node *curs);
void					cmd_create(t_me *me);
int						add_iufd(int fd);
void					sig_exit_signal(t_me *me);
void					pass_chars(t_me *me, t_edl *edl, long int key);
char					**tab_add(char **tb, char *str);
int						tab_nfree(char **t, int n);
char					*clean_quotes(char *line);
char					*clean_equot(char *s);
int						init_term(t_me *me);
int						exit_term(t_me *me);
char					*dquote_gnl(t_me *me, char **qtype);
void					delete_char(t_me *me, t_edl *edl);
char					*check_dquotes(t_me *me, char *s);
char					**msplit(char *s, char c);
int						is_key(long int k);
char					*env_to_s(char **e);
void					edl_loop(t_me *me);
char					*join_free(char *a, char *b);
t_hist					*get_hist(t_me *me, int i);
void					print_hist(t_me *me);
int						push_hist(t_me *me, char *s);
void					prepare_mline(t_me *me, int n, int o);
void					prompt_end(t_me *me, t_edl *edl);
void					prompt_start(t_me *me, t_edl *edl);
char					*delete_key(char *r, int i);
void					restore_pos(t_me *me, t_vec pos);
void					refresh_prompt(t_me *me);
void					refresh_pprompt(t_me *me, t_edl *edl);
void					execute_line(t_me *me);
int						get_wterm(t_me *me);
int						insert_key(t_me *me, t_edl *edl, char key);
int						insert_nkey(t_me *me, t_edl *edl, char key, int times);
void					execute_move(t_me *me, t_edl *edl, int key, int move);
int						get_key(t_me *me, char key[6]);
int						execute_key(t_me *me, t_edl *edl, long int key);
t_vec					get_cpos();
int						exec_tmode(t_me *me, char *s, int n);
int						exec_mode(t_me *me, char *s);
int						exec_to(int x, int y);
int						init(t_me *me);
void					mprompt(t_me *me, int type, int ok);
t_vec					vec_add(t_vec a, t_vec b);
void					ft_putistr(char *s, int start);
char					*add_key(char *r, char n, int i);
char					*string_inject(char *r, char *n, int i, int replace);
char					*cdel(char *s, int m);
void					ctab_print(char **s);
void					msetenv(t_me *me, t_cmd *a);
void					munset_env(t_me *me, t_cmd *a);
int						errors(int e, char *app, char *s, t_cmd *cmd);
void					print_env(char **e);
int						mlen(char *s, char a);
char					**env_sub(char **e, char *name);
char					*ssn(char *s, char *f);
char					**assign_env(char **e, char *a, int ov);
void					menv(t_me *me, t_cmd *a);
void					mcd(t_me *me, t_cmd *a);
char					**env_add(char **e, char *name, char *value);
char					**env_modif(char **e, char *name, char *value);
int						env_isin(char **e, char *s);
int						start_by(char *s, char *start);
int						execute_builtin(t_me *me, t_node *curs);
int						is_builtin(char *s);
int						fexit(t_me *me);
int						count_size(char const *str, int i, char c);
void					sig_hook_cz(int sig);
void					sig_catch(t_me *me);
void					sig_catch_child(t_me *me);
int						han_pid(t_me *me, int r);
int						merror(t_me *me, char *cmd, int keycode);
t_node					*node_new(t_cmd *cmd);
int						get_token(char *s);
int						read_kwo(t_me *me);
void					push_cmd(t_me *me, int i);
void					psc(char *s, char *c, int fd);
char					*fpath(char *path, char *dir);
char					*get_path(t_me *me, char *name);
char					*get_edt(char **e, char *data);
char					**env_cpy(char **e);
void					edl_default(t_edl *edl);
void					close_fds(t_node *curs);
void					wait_pipelines(t_me *me, t_node *curs);
int						exec_apipe(t_me *me, t_node *curs, int is_last);
void					set_handlers(t_node *curs);
int						exec_simple(t_me *me, t_node *curs);
int						exec_pipe(t_me *me, t_node *curs);
int						exec_sl_redir(t_me *me, t_node *curs);
void					heredoc_loop(t_me *me, t_node *curs);
void					exec_aleft_redir(t_me *me, t_node *curs);
int						exec_right_redir(t_me *me, t_node *curs);
int						mredir(t_me *me, t_node *curs);
char					**tab_dup(char **t);
int						tab_size(char **t);
int						tab_free(char **t);
char					*clean_line(char *line);
void					push_deli(t_me *me, char *cmd, int i);
char					**get_args(t_me *me, t_cmd *cmd, char **t, int i);
void					cmds_free(t_me *me);
int						is_afd(char *s);
char					**get_afds(t_me *me, char **s);
int						prepare_afds(t_afd *list);
int						process_afds(t_afd *list);
void					unload_afds(t_me *me);
void					print_afds(t_afd *c);
void					print_cmds(t_cmd *c);
void					free_afds(t_afd *list);
void					node_push(t_me *me, t_cmd *cmd);
void					push_tree(t_me *me, int i);
void					push_parent(t_me *me, t_node *n);
void					push_right(t_me *me, t_node *n);
int						prepare_tree(t_node *c);
void					tree_free(t_node *cur);
void					tree_print(t_node *curs);
void					trees_print(t_me *me);
int						tree_exec(t_me *me, t_node *curs);
void					trees_free(t_me *me);
void					tab_print(char **t);
char					**tab_inject(char **tb, int i, char *str);
char					**tab_extract(char **tb, int i);
int						ft_sii(char *s, char *e);
void					get_autocomplet(t_me *me, t_edl *edl);
char					*ft_auto_getname(t_auto **lsauto, char *debut);
void					ft_auto_free(t_auto **lsauto, char *string, char *path,\
char *debut);
int						ft_auto_getkey(t_auto **lsauto, t_me *me, t_edl *edl);
void					ft_auto_move_left(t_auto **lsauto);
int						ft_auto_cmp(char *cmp, char *name);
char					*ft_auto_get_debut(char *string);
char					*ft_auto_get_path(char *string);
char					*ft_auto_get_string(char *str, int index);
t_auto					*ft_init_auto(char *name);
int						ft_auto_get_nbrline(t_auto **lsauto, int columnlist);
void					ft_count_column(t_me *me);
int						ft_auto_sizemax(t_auto **lsauto);
int						ft_create_auto(t_auto **lsauto, char *path,\
char *debut);
void					ft_push_auto(t_auto **lsauto, char *name);
void					ft_auto_move_cursor(t_auto **lsauto, t_me *me, t_edl\
*edl, int columnlist);
void					ft_auto_print_color(char *str, int select);
void					ft_print_auto(t_auto **lsauto, t_me *me, t_edl *edl,\
int i);
void					ft_auto_move_right(t_auto **lsauto);
void					ft_putspace(int size);
void					ft_putcolor(char const *s, char *color);
void					move_updown(t_me *me, long int buf);
int						ft_move_left(t_me *me);
int						ft_check_bn(char *line, int pos_x);

#endif
