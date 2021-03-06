#pragma once

#include <string>
#include <vector>
#include <ail/types.hpp>
#include <fridh/symbol.hpp>
#include <fridh/lexer.hpp>

namespace fridh
{
	namespace statement_processing
	{
		enum type
		{
			unrestricted,
			atomic_only
		};
	}

	struct sorted_binary_operator_entry
	{

		std::size_t index;
	};

	class parser
	{
	public:
		parser();
		bool process_module(std::string const & path, std::string const & name, module & output, std::string & error_message);

	private:
		bool running;

		std::size_t
			line_offset,
			line_end;

		uword indentation_level;

		std::size_t
			lexeme_offset,
			lexeme_end;

		uword nested_class_level;

		lines_of_code lines;

		symbol_tree_node * current_node;

		bool name_is_used(std::string const & name);
		std::string const & get_declaration_name();
		void name_collision_check();
		symbol_tree_node & add_name(symbol::type symbol_type);

		void process_body(executable_units * output = 0, bool increment = true, bool is_anonymous_function = false);

		void process_atomic_statement(lexeme_container & lexemes, std::size_t & offset, parse_tree_nodes & output, bool allow_multi_statements = false, lexeme_type::type terminator = lexeme_type::non_terminating_placeholder, bool allow_empty_statements = false);
		void process_offset_atomic_statement(parse_tree_node & output, std::size_t offset = 0);
		void process_composite_term(parse_tree_node & output);

		bool is_if_statement();

		bool process_if(executable_unit & output);
		bool process_while(executable_unit & output);
		bool process_for(executable_unit & output);
		bool process_return(executable_unit & output);

		bool process_class();
		bool process_function(function * output = 0);
		void process_statement(executable_unit & output);
		bool process_line(executable_unit * output = 0, bool is_anonymous_function = false);

		bool translate_data(module & target_module, std::string const & data, std::string const & module_name, std::string & error_message_output);

		lexeme_container & get_lexemes();

		void error(std::string const & message);
		void single_lexeme_error(std::string const & message, std::size_t offset);
		void double_lexeme_error(std::string const & message, std::size_t offset);

		void process_node_group(parse_tree_nodes & arguments, parse_tree_nodes & output);
		void operator_resolution(parse_tree_nodes & input, parse_tree_node & output);

		void scope_up();
	};

	void lexeme_to_argument_node(lexeme & input, parse_tree_node & output);
	void lexeme_to_unary_operator_node(lexeme & input, parse_tree_node & output);
	void lexeme_to_binary_operator_node(lexeme & input, parse_tree_node & output);

	word get_unary_operator_precedence(unary_operator_type::type input);
	word get_binary_operator_precedence(binary_operator_type::type input);
	bool get_parse_tree_node_precedence(parse_tree_node & input, word & output);

	bool is_right_to_left_operator(parse_tree_node & input);

	bool is_unary_post_fix_operator(lexeme_type::type input);
}
