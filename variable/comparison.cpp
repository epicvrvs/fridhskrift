#include <fridh/symbol.hpp>

namespace fridh
{
#define NUMERIC_COMPARISON(name, description, operator) \
	void variable::name(variable const & argument, variable & output) const \
	{ \
		if(is_numeric_type() && argument.is_numeric_type()) \
		{ \
			if(is_floating_point_operation(argument)) \
				output.new_boolean(get_floating_point_value() operator argument.get_floating_point_value()); \
			else if(type == variable_type_identifier::unsigned_integer && argument.type == variable_type_identifier::signed_integer) \
				output.new_boolean(unsigned_integer operator argument.unsigned_integer); \
			else \
				output.new_boolean(signed_integer operator argument.signed_integer); \
		} \
		else \
			binary_argument_type_error(description, type, argument.type); \
	}

	NUMERIC_COMPARISON(less_than, "Less than", <)
	NUMERIC_COMPARISON(less_than_or_equal, "Less than", <=)
	NUMERIC_COMPARISON(greater_than, "Less than", >)
	NUMERIC_COMPARISON(greater_than_or_equal, "Less than", >=)

	void variable::not_equal(variable const & argument, variable & output) const
	{
		output.new_boolean(operator!=(argument));
	}

	void variable::equal(variable const & argument, variable & output) const
	{
		output.new_boolean(operator==(argument));
	}

	void variable::logical_not(variable & output) const
	{
		output.new_boolean(!get_boolean_value());
	}
}
