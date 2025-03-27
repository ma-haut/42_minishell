/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:52:42 by arbaudou          #+#    #+#             */
/*   Updated: 2025/03/27 13:21:28 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "global.h"
# include "libft.h"
# include <stdio.h>

/*  PARSING  */

t_token		*tokenize(char *input);
t_ast		*parse(t_token **tokens);
t_ast		*parse_command(t_token **tokens);
t_ast		*parse_word(t_token **tokens, t_ast *left);
t_ast		*parse_pipe(t_token **tokens, t_ast *left);
t_ast		*parse_logical_operator(t_token **tokens, t_ast *left);
int			handle_and(char *input, int i, t_token **tokens);
int			handle_or(char *input, int i, t_token **tokens);
int			handle_pipe(char *input, int i, t_token **tokens);
int			handle_redirection_out(char *input, int i, t_token **tokens);
int			handle_redirection_in(char *input, int i, t_token **tokens);
void		parsing(char *input, t_shell *shell);
int			check_error(t_token **tokens);
t_ast		*parse_redir(t_token **tokens, t_ast *node);
t_ast		*process_command(t_token **tokens);

/* FREE */
void		free_tokens(t_token *tokens);
void		free_ast(t_ast *ast);

/*  NODES  */
t_ast		*create_command_node(t_token **tokens, t_ast *node);
t_ast		*create_operator_node(t_ast_type type, t_ast *left, t_ast *right);
t_ast		*init_ast(t_ast *node);
void		get_arguments(t_token **tokens, t_ast *node);

/*  UTILS  */

t_token		*create_token(t_token_type type, char *value);
t_token		*add_token(t_token **head, t_token_type type, char *value);
int			is_space(char c);
int			is_redirection(t_token *token);
const char	*get_ast_type_str(t_ast_type type);
const char	*get_token_type_str(t_token_type type);
int			count_args(t_token *tokens);
int			is_operator(char *word);
int			is_pipe_or_logical(t_token *tokens);
t_ast		*add_argument_to_command(t_ast *cmd_node, char *arg);
t_ast_type	get_redir_type(t_token *token);
void		free_all(t_ast *ast, t_token *tokens);
int			print_error(t_token *tokens);
void		print_errors(int i);
void		quote_switch(char c, int *single_quote, int *double_quote);

#endif