This header file is used to parse the argument as python arg_parse in C/C++.
The usage is like this :

@code begin{

#include "stdafx.h"
#include <stdio.h>

#define ARGS_PARSER_FILEDS \
ARGS_NORM(input_file, "It is a norm arg which must set a value.") \
ARGS_OPT(default_thre, "0.32", "It is a optinal arg, optinal arg should have a default value.") \
ARGS_NOARG(b_fast, "It is a arg without parameter.") 

#include "arg_parser.h"

ARG_PARSER arg_parser;

int main(int argc, char *argv[])
{
	int ret_val;
	ret_val = arg_parser_init(&arg_parser, argc, argv);
	if (ret_val != ARGS_PARSE_OK)
	{
		return ret_val;
	}
#define PRINT_ELEM(element) printf("%s = %s\r\n", #element, element)
	PRINT_ELEM(arg_parser.input_file);
	PRINT_ELEM(arg_parser.default_thre);
	if (arg_parser.b_fast)
	{
		printf("use fast process!\r\n");
	}

    return 0;
}
}@code end