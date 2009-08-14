#include <frith/variable.hpp>

namespace frith
{
	unary_argument::unary_argument(variable & output, std::string & error_message):
		output(output),
		error_message(error_message)
	{
	}

	binary_argument::binary_argument(variable const & other, variable & output, std::string & error_message)
		other(other),
		output(output),
		error_message(error_message)
	{
	}

	variable::variable():
		type(variable_type::undefined)
	{
	}

	variable::variable(variable const & other):
		type(other.type)
	{
		switch(type)
		{
		case variable_type::boolean:
			boolean = other.boolean;
			break;

		case variable_type::signed_integer:
			signed_integer = other.signed_integer;
			break;

		case variable_type::unsigned_integer:
			unsigned_integer = other.unsigned_integer;
			break;

		case variable_type::floating_point_value:
			floating_point_value = other.floating_point_value;
			break;

		case variable_type::string:
			string = new string(*other.string);
			break;

		case variable_type::array:
			array = new variable_vector(*other.array);
			break;

		case variable_type::map:
			map = new variable_map(*other.map);
			break;
		}
	}

	variable::~variable()
	{
		switch(type)
		{
		case variable_type::string:
			delete string;
			break;

		case variable_type::array:
			delete array;
			break;

		case variable_type::map:
			delete map;
			break;
		}
	}

	variable_type variable::get_type() const
	{
		return type;
	}

	void variable::nil()
	{
		type = variable_type::nil;
	}

	void variable::new_boolean(types::boolean new_boolean)
	{
		type = variable_type::boolean;
		boolean = new_boolean;
	}

	void variable::new_signed_integer(types::signed_integer new_signed_integer)
	{
		type = variable_type::signed_integer;
		signed_integer = new_signed_integer;
	}

	void variable::new_unsigned_integer(types::unsigned_integer new_unsigned_integer)
	{
		type = variable_type::unsigned_integer;
		unsigned_integer = new_unsigned_integer;
	}

	void variable::new_floating_point_value(types::floating_point_value new_floating_point_value)
	{
		type = variable_type::floating_point_value;
		floating_point_value = new_floating_point_value;
	}

	void variable::new_string(types::string const & new_string)
	{
		type = variable_type::string;
		string = new std::string(new_string);
	}

	void variable::new_array()
	{
		type = variable_type::array;
		array = new variable_vector();
	}

	void variable::new_map()
	{
		type = variable_type::map;
		map = new variable_map();
	}

	bool variable::addition(binary_argument & argument) const
	{
		std::string const name_of_operation = "Addition";

		if(is_floating_point_operation(argument))
		{
			types::floating_point_value
				left,
				right;
			if(get_floating_point_value(left) && argument.other.get_floating_point_value(right))
				argument.output.new_floating_point_value(left + right);
			else
			{
				argument.error_message = get_binary_argument_type_error(name_of_operation, type, argument.other.type);
				return false;
			}
		}
		else
		{
			argument.output = *this;

			switch(type)
			{
				case variable_type::signed_integer:
				case variable_type::unsigned_integer:
					switch(argument.other.type)
					{
						case variable_type::signed_integer:
						case variable_type::unsigned_integer:
							argument.output.unsigned_integer += argument.other.unsigned_integer;
							break;

						default:
							argument.error_message = get_binary_argument_type_error(name_of_operation, type, argument.other.type);
							return false;
					}
					break;

				case variable_type::floating_point_value:
					argument.output.floating_point_value += argument.other.floating_point_value;
					break;

				case variable_type::string:
					//oh ffs

				case variable_type::array:
					argument.output.array->push_back(argument.other);
					break;

				default:
					argument.error_message = get_binary_argument_type_error(name_of_operation, type, argument.other.type);
					return false;
			}
		}

		return true;
	}

	bool variable::subtraction(binary_argument & argument) const
	{
	}

	bool variable::multiplication(binary_argument & argument) const
	{
	}

	bool variable::division(binary_argument & argument) const
	{
	}

	bool variable::modulo(binary_argument & argument) const
	{
	}


	bool variable::negative(unary_argument & argument) const
	{
	}


	bool variable::less_than(binary_argument & argument) const
	{
	}

	bool variable::less_than_or_equal(binary_argument & argument) const
	{
	}

	bool variable::greater_than(binary_argument & argument) const
	{
	}

	bool variable::greater_than_or_equal(binary_argument & argument) const
	{
	}

	bool variable::unequal(binary_argument & argument) const
	{
	}

	bool variable::equal(binary_argument & argument) const
	{
	}

	bool variable::logical_not(unary_argument & argument) const
	{
	}

	bool variable::logical_and(binary_argument & argument) const
	{
	}

	bool variable::logical_or(binary_argument & argument) const
	{
	}

	bool variable::shift_left(binary_argument & argument) const
	{
	}

	bool variable::shift_right(binary_argument & argument) const
	{
	}

	bool variable::binary_and(binary_argument & argument) const
	{
	}

	bool variable::binary_or(binary_argument & argument) const
	{
	}

	bool variable::binary_xor(binary_argument & argument) const
	{
	}

	bool variable::binary_not(unary_argument & argument) const
	{
	}

	bool variabe::is_floating_point_operation(binary_argument & argument)
	{
		return type == variable_type::floating_point_value || argument.other.type == variable_type::floating_point_value;
	}

	bool variable::get_floating_point_value(types::floating_point_value & output)
	{
		switch(type)
		{
		case variable_type::signed_integer:
			output = signed_integer;
			break;

		case variable_type::unsigned_integer:
			output = unsigned_integer;
			break;

		case variable_type::floating_point_value:
			output = floating_point_value;
			break;

		default:
			return false;
		}

		return true;
	}

	std::string get_type_string(variable_type type)
	{
		switch(type)
		{
		case variable_type::undefined:
			return "undefined";

		case variable_type::nil:
			return "nil";

		case variable_type::boolean:
			return "boolean";

		case variable_type::signed_integer:
			return "integer";

		case variable_type::unsigned_integer:
			return "unsigned-integer";

		case variable_type::floating_point_value:
			return "float";

		case variable_type::string:
			return "string";

		case variable_type::array:
			return "array";

		case variable_type::map:
			return "map";
		}

		return "unknown";
	}

	std::string get_binary_argument_type_error(std::string const & operation, variable_type left, variable_type right)
	{
		return operation + ": Invalid argument types \"" + get_type_string(left) + "\", \"" + get_type_string(right);
	}
}
