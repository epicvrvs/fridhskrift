#include <frith/symbol.hpp>

namespace frith
{
	parse_tree_node::parse_tree_node()
	{
	}

	parse_tree_node::parse_tree_node(variable * variable_pointer):
		type(parse_tree_node_type::variable),
		variable_pointer(variable_pointer)
	{
	}

	parse_tree_node::parse_tree_node(unary_operator_type::type unary_operator):
		type(parse_tree_node::unary_operator)
	{
		unary_operator_pointer = new parse_tree_unary_operator_node;
		unary_operator_pointer->type = unary_operator;
	}

	parse_tree_node::parse_tree_node(binary_operator_type::type binary_operator)
		type(parse_tree_node::binary_operator)
	{
		binary_operator_pointer = new parse_tree_binary_operator_node;
		binary_operator_pointer->type = binary_operator;
	}
}
