#define SPECIFICATION_SIZE 35
//important enumerations
//cant use 0 or 10
typedef enum token token;
enum token {
	NONE = 255, //special value for sentinals
	INTEGER_CONSTANT = 1,
	INTEGER_CONSTANT_END = 253,
	IDENTIFIER = 2,
	IDENTIFIER_END = 254,
	DATATYPE = 3,
	OPERATOR = 4,
	CONDITIONAL = 5,
	SPECIAL = 6
};

typedef enum datatype datatype;
enum datatype {
	INT = 10,
	FLOAT = 11,
	DOUBLE = 12,
	CHAR = 13,
	SIGNED = 253,
	UNSIGNED = 254
};

typedef enum conditional conditional;
enum conditional {
	IF = 10,
	WHILE = 11,
	FOR = 12,
	WITH = 13
};

typedef enum operator operator;
enum operator{
	ASSIGNMENT = 10,
	ADDITION = 11,
	SUBTRACTION = 12,
	MULTIPLIACTION = 13,
	DIVISION = 14,
	ROOT = 15,
	EXPONENT = 16,
	CONCATENATION = 17,
	TRUNCATION = 18,
	DATASIZE = 19,
	ARRAYSIZE = 20,
	ADDRESS = 21,
	IDENTIFER_NAME = 22,
	TYPE_NAME = 23,
	NOT = 24,
	AND = 25,
	OR = 26,
	GREATER = 27,
	LESS = 28,
	EQUALITY = 29
};
typedef enum special special;
enum special {
	LAMBDA = 10,
	BLOCK = 11,
	BLOCK_CLOSE = 12,
	LIST = 13,
	LIST_CLOSE = 14,
	PARENTHESIS = 15,
	PARENTHESIS_CLOSE = 16
};
typedef struct keyword keyword;
struct keyword {
	char* substr;
	//essientally just symbol but it is more inline to have it like this
	token tok;
	int specifier;
	UT_hash_handle hh;
};
typedef struct symbol symbol;
struct symbol {
	token tok;
	int specifier;
};

//keyword specification to be loaded into a hashmap at runtime
keyword specification[SPECIFICATION_SIZE] = {
	//CONDITIONALS
	{"if", CONDITIONAL, IF},
	{"while", CONDITIONAL, WHILE},
	{"for", CONDITIONAL, FOR},
	{"with", CONDITIONAL, WITH},
	//TYPES
	{"int", DATATYPE, INT},
	{"float", DATATYPE, FLOAT},
	{"double", DATATYPE, DOUBLE},
	{"char", DATATYPE, CHAR},
	//LAMBDA
	{"~", SPECIAL, LAMBDA},
	//SCOPE
	{"{", SPECIAL, BLOCK},
	{"}", SPECIAL, BLOCK_CLOSE},
	//SPECIAL
	{"[", SPECIAL, LIST},
	{"]", SPECIAL, LIST_CLOSE},
	{"(", SPECIAL, PARENTHESIS},
	{")", SPECIAL, PARENTHESIS_CLOSE},
	//OPERATORS
	{"=", OPERATOR, ASSIGNMENT},
	{"==", OPERATOR, EQUALITY},
	{">", OPERATOR, GREATER},
	{"<", OPERATOR, LESS},
	{"+", OPERATOR, ADDITION},
	{"-", OPERATOR, SUBTRACTION},
	{"*", OPERATOR, MULTIPLIACTION},
	{"/", OPERATOR, DIVISION},
	{"\\", OPERATOR, ROOT},
	{"^", OPERATOR, EXPONENT},
	{"++", OPERATOR, CONCATENATION},
	{"--", OPERATOR, TRUNCATION},
	{"@", OPERATOR, DATASIZE},
	{"#", OPERATOR, ARRAYSIZE},
	{"&", OPERATOR, ADDRESS},
	{"$", OPERATOR, IDENTIFER_NAME},
	{"!!", OPERATOR, TYPE_NAME},
	{"!", OPERATOR, NOT},
	{"&&", OPERATOR, AND},
	{"||", OPERATOR, OR}
};
keyword* keyword_patterns = NULL;