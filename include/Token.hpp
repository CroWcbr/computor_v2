#pragma once

# include "main_library.hpp"

class Value;

class Token
{
private:
	std::string		_lexeme;
	token_type		_type;
	int				_rang;

private:
	void				_which_token_type(std::string const &lexeme);
	bool				_is_digit(std::string const &lexeme) const;
	bool				_is_func(std::string const &lexeme) const;
	bool				_is_str(std::string const &lexeme) const;
	void 				_setRang();

public:
	Token() = delete;
	Token(std::string const &lexeme, \
			std::map<std::string, Value*> const &val);
	Token(std::string const &lexeme, \
			token_type const &type);
	~Token();
	Token(Token const &copy);
	Token &operator=(Token const &copy);

	std::string const	&getLexem() const	{ return _lexeme; }
	token_type const	&getType() const	{ return _type; }
	int const 			&getRang() const	{ return _rang; }
};
