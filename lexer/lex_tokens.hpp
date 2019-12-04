#pragma once

enum class septype {
	Error = -1,
	None = 0,
	Space = 1,
	Newline,
	Comment,
	EndStream
};

// optype represents an operator class
enum class optype {
	Error = -1,
	None = 0,
	Int8 = (int)septype::EndStream + 1,
	Int16,
	Int32,
	Float,
	Double,
};
#define IS_OP(x) ((x >= (int)optype::Int8) && (x <= (int)optype::Double))

// commandtype is an asvm command
enum class commandtype {
	Error = -1,
	None = 0,
	Exit = (int)optype::Double + 1,
	Push,
	Pop,
	Dump,
	Assert,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Print
};
#define IS_COMMAND(x) ((x >= (int)commandtype::Exit) && (x <= (int)commandtype::Print))