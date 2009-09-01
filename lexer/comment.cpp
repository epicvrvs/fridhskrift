#include <frith/lexer.hpp>

namespace frith
{
		bool lexer::parse_comment(std::string & error_message)
	{
		std::string const
			multi_line_comment = ";;",
			nested_comment_start = ";.",
			nested_comment_end = ".;",

			multiline_comment_prefix = "In multi-line comment: ",
			nested_comment_prefix = "In nested comment: ";

		uword start_of_comment = line;

		if(string_match(multi_line_comment))
		{
			bool got_end = false;
			for(i += multi_line_comment.size(); !got_end && i < end;)
			{
				char byte = input[i];
				switch(byte)
				{
					case '\n':
						process_newline();
						continue;

					case ';':
						if(string_match(multi_line_comment))
						{
							got_end = true;
							i++;
						}
						break;
				}
				i++;
			}
			if(!got_end)
			{
				error_message = lexer_error("Unable to find the end of a multi-line comment", start_of_comment);
				return false;
			}
		}
		else if(string_match(nested_comment_start))
		{
			uword comment_depth = 1;
			for(i += nested_comment_start.size(); comment_depth > 0 && i < end;)
			{
				char byte = input[i];
				if(byte == '\n')
				{
					process_newline();
					continue;
				}
				else if(string_match(nested_comment_start))
				{
					comment_depth++;
					i += nested_comment_start.size();
					continue;
				}
				else if(string_match(nested_comment_end))
				{
					comment_depth--;
					i += nested_comment_end.size();
					continue;
				}
				i++;
			}

			if(comment_depth != 0)
			{
				error_message = lexer_error("Unable to find the end of a nested comment", start_of_comment);
				return false;
			}
		}
		else
		{
			std::size_t offset = input.find('\n', i);
			if(offset == std::string::npos)
			{
				error_message = lexer_error("Unable to find the end of a multi-line comment", start_of_comment);
				return false;
			}
			i = offset;
			process_newline();
		}
		return true;
	}
}