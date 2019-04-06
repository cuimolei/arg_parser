/*
Copyright (c) 2019-4-6 <cuimolei@yeah.net>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef __ARG_PARSER_H__
#define __ARG_PARSER_H__
#include <stdio.h>
#include <string.h>

#define ARGS_PARSE_OK 0
#define ARGS_PARSE_FAIL -1

#define ARGS_NORM(args_name, comment)
#define ARGS_OPT(args_name, def_val, comment) 
#define ARGS_NOARG(args_name, comment)

//define this macro like these 
#ifndef ARGS_PARSER_FILEDS
#define ARGS_PARSER_FILEDS \
ARGS_NORM(args_name1, "It is a norm arg which must set a value.") \
ARGS_OPT(args_name2, "default_value", "It is a optinal arg, optinal arg should have a default value.") \
ARGS_NOARG(args_name3, "It is a arg without parameter.") 
#endif




typedef struct _ARG_PARSER
{
#define ARGS_NORM(args_name, comment) char * args_name;
#define ARGS_OPT(args_name, def_val, comment) char * args_name;
#define ARGS_NOARG(args_name, def_val, comment) char * args_name;
ARGS_PARSER_FILEDS
#undef ARGS_NORM
#undef ARGS_OPT
}ARG_PARSER;

static int arg_parser_help(char * process_name)
{
	if (process_name)
	{
		printf("%s ", process_name);
	}
	else
	{
		printf("process");
	}

#undef ARGS_NORM
#undef ARGS_OPT
#undef ARGS_NOARG
#define ARGS_NORM(args_name, comment) printf("%s ", #args_name);
#define ARGS_OPT(args_name, def_val, comment)
#define ARGS_NOARG(args_name, comment)
	ARGS_PARSER_FILEDS

#undef ARGS_NORM
#undef ARGS_OPT
#undef ARGS_NOARG
#define ARGS_NORM(args_name, comment) 
#define ARGS_OPT(args_name, def_val, comment) 
#define ARGS_NOARG(args_name, comment) printf("[-%s] ", #args_name);
		ARGS_PARSER_FILEDS

#undef ARGS_NORM
#undef ARGS_OPT
#undef ARGS_NOARG
#define ARGS_NORM(args_name, comment) 
#define ARGS_OPT(args_name, def_val, comment) printf("[-%s %s] ", #args_name, def_val);
#define ARGS_NOARG(args_name, comment) 
		ARGS_PARSER_FILEDS
	printf("\r\n");
#undef ARGS_NORM
#undef ARGS_OPT
#undef ARGS_NOARG
#define ARGS_NORM(args_name, comment) printf("\t%s: %s\r\n", #args_name, comment);
#define ARGS_OPT(args_name, def_val, comment)
#define ARGS_NOARG(args_name, comment)
	ARGS_PARSER_FILEDS

#undef ARGS_NORM
#undef ARGS_OPT
#undef ARGS_NOARG
#define ARGS_NORM(args_name, comment) printf("\t%s: %s\r\n", #args_name, comment);
#define ARGS_OPT(args_name, def_val, comment) printf("\t%s: %s\r\n\t\tdefault value is %s.\r\n", #args_name, comment, def_val);
#define ARGS_NOARG(args_name, comment)
		ARGS_PARSER_FILEDS

	return ARGS_PARSE_OK;
}


static int arg_parser_init(ARG_PARSER *args_parser, int argc, char * argv[])
{
	int i;

#undef ARGS_NORM
#undef ARGS_OPT
#undef ARGS_NOARG
#define ARGS_NORM(args_name, comment) args_parser->args_name = NULL;
#define ARGS_OPT(args_name, def_val, comment) args_parser->args_name = def_val;
#define ARGS_NOARG(args_name, comment) args_parser->args_name = NULL;
	ARGS_PARSER_FILEDS


	for (i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i], "-help") && strcmp(argv[i], "-h")) == 0)
		{
			goto FAILED;
		}
#undef ARGS_NORM
#undef ARGS_OPT
#undef ARGS_NOARG
#define ARGS_NORM(args_name, comment) 
#define ARGS_OPT(args_name, def_val, comment) if(strcmp(argv[i], "-"#args_name) == 0){if(i + 1 >= argc) goto FAILED; args_parser->args_name = argv[i+1];}
#define ARGS_NOARG(args_name, comment) if(strcmp(argv[i], "-"#args_name) == 0){ args_parser->args_name = "";} 
		ARGS_PARSER_FILEDS

#undef ARGS_NORM
#undef ARGS_OPT
#undef ARGS_NOARG
#define ARGS_NORM(args_name, comment) if(args_parser->args_name == NULL){args_parser->args_name = argv[i];}
#define ARGS_OPT(args_name, def_val, comment) 
#define ARGS_NOARG(args_name, comment) 
		ARGS_PARSER_FILEDS

	}

#undef ARGS_NORM
#undef ARGS_OPT
#undef ARGS_NOARG
#define ARGS_NORM(args_name, comment) if(args_parser->args_name == NULL){ printf("Input argument %s not set!\r\n", #args_name); goto FAILED;}
#define ARGS_OPT(args_name, def_val, comment) 
#define ARGS_NOARG(args_name, comment) 
	ARGS_PARSER_FILEDS

	return ARGS_PARSE_OK;

FAILED:
	arg_parser_help(argv[0]);
	return ARGS_PARSE_FAIL;
}

#endif
