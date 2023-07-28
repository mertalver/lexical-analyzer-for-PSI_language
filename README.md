# Lexical Analyzer for PSI++ Language
The Lexical Analyzer is a tool designed to analyze source code written in the C language for using PSI++ language. <br>
Analyzer accepts a source file called ‘code.psi’ and outputs a text file named as ‘code.lex’ that contains all the tokens.

# Features
### Tokenization:
The lexical analyzer breaks the input PSI++ source code into individual tokens, such as keywords, identifiers,brackets and operators.
### Error Handling: 
The lexical analyzer can detect and report lexical errors in the source code, aiding developers in identifying and resolving issues early in the development process.
### Customizable:
The PSI++ Lexical Analyzer can be easily extended and customized to support additional language features and variations.

# Lexical rules for the programming language Psi++ are as follows
### 1- Identifiers:  
Maximum identifier size is 30 characters. If you use an identifier larger than that, the lexical analyzer issues an error message. <br> 
Psi++ language is not case sensitive and all the identifier names are standardized as lower case. <br>
Identifiers start with an alphabetic character (a letter) and are composed of one or more letters/digits/_ (underscore) <br> 
Example Token: Identifier(my_var_1) 

### 2- Integer constants 
Maximum integer size is 10 digits. If you use an integer value longer than that, the lexical analyzer issues an error message. <br>
Negative values are not supported. <br>
Example Token: IntConst(1290) 

### 3- Operators 
Valid operators of the language are +,-,*,/,++,--,:= <br>
Example Token: Operator(++) <br>

### 4- Brackets 
LeftPar: (       			RightPar: ) <br>
LeftSquareBracket: [		RightSquareBracket: ] <br>
LeftCurlyBracket:  {		RightCurlyBracket:  } <br>
Example Token: LeftCurlyBracket 

### 5- String constants 
String constants of Psi++ are delimited by double quotes (ASCII code 34)as in “this is a string” <br>
String constants have unlimited size <br>
String constants cannot contain the double quote character. when you reach one, the string terminates. <br>
If a string constant cannot terminate before the file end, there should be a lexical error issued. <br>

### 6- Keywords: 
Keywords are: break,case,char,const,continue,do,else,enum,float,for,goto,if,int, <br>
long,record,return,static,while <br>
Psi++ language is not case sensitive and all the keywords are standardized as lower case. You can write the same word as “while” OR “While” OR “WHILE” and they all generate <br>
Example Token: Keyword(while) 

### 7- End of line:
(;) 
Example Token: EndOfLine <br> 

### 8- Comments: 
(Anything between /* and */ is a comment.) 
If a comment cannot terminate before the file end, there should be a lexical error issued. <br> 
Comments are just like blank space and they provide no tokens. <br> 
