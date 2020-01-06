/*
 * project_1
 *
 * file: delimiters.cpp
 * author: Cindy Huang
 * date: Oct. 3, 2019
 *
 * parameters: a delimiter character
 * return: Two functions:
 *
 *         does_delimiter_match(...) and do_delimiters_nest(...) each
 *         return a boolean value.
 *
 *         does_delimiter_match(...) returns true if there are an equal
 *         number of opening delimiters and their corresponding closing
 *         delimiters
 *
 *         do_delimiters_nest(...) returns true if all the delimiters nest
 *
 * DESCRIPTION:
 * This program reads blocks of text containing opening and closing delimiters
 * '(', '[', '{', ')', ']', and '}' and determines whether the delimiters match
 * and whether the delimiters nest. The program prints the text to be read, and
 * prints 'Unmatched' or 'Missing' if a closing delimiter with no matching opening
 * delimiter or an opening delimiter with no matching closing delimiter is found,
 * respectively.
 */

#include <iostream>
#include "project_1.hpp"

int main();
void print_program();
bool does_delimiter_match(char delimiter);
bool do_delimiters_nest();


int main() {
	print_program();
	std::cout << does_delimiter_match( '(' ) << std::endl;
	std::cout << does_delimiter_match( '[' ) << std::endl;
	std::cout << does_delimiter_match( '{' ) << std::endl;
	std::cout << do_delimiters_nest() << std::endl;

	return 0;
}
/*
 * print_program() reads text-containing file, and prints the text in the console
 */

void print_program() {
	ece150::start_reading_file();
	while (ece150::at_eof() == false) {
		std::cout << ece150::get_next_character();
	}
}

/*
 * does_delimiter_match() returns a true or false boolean value depending on whether
 * there is an equal number of matching opening and closing delimiters of the same type
 *
 * Algorithm:
 * 		1. Initializes variables to represent counter for opening and closing delimiters
 * 		   and closing delimiter that matches function argument
 * 		2. Assigns closing_delimiter a closing delimiter character corresponding with function argument
 * 		3. Starts reading file
 * 		4. While there are still characters to read in the file:
 * 				a. checks if character matches opening delimiter argument or closing_delimiter value
 * 				b. increases counter for opening/closing delimiter depending on above condition
 *		5. Checks the number of opening and closing delimiters:
 *				a. If there are an equal number of opening and closing delimiters, returns true
 *				b. If there are more opening delimiters, prints that closing delimiter is missing
 *				c. If there are more closing delimiters, prints that closing delimiter is unmatched
 *		6. Returns false
 */

bool does_delimiter_match(char delimiter) {
	int count_open = 0;
	int count_close = 0;
	char closing_delimiter;

	if (delimiter == '(') {
		closing_delimiter = ')';
	}
	else if (delimiter == '[') {
		closing_delimiter = ']';
	}
	else {
		closing_delimiter = '}';
	}

	ece150::start_reading_file();

	while (ece150::at_eof() == false) {
		char next = ece150::get_next_character();
		if (next == delimiter) {
			count_open++;
		}
		else if (next == closing_delimiter) {
			count_close++;
		}
	}

	if (count_open == count_close) {
		return true;
	}
	else if (count_open > count_close) {
		int difference = count_open - count_close;
		for (unsigned int k = 0; k < difference; k++) {
			std::cout << "Missing " << closing_delimiter << std::endl;
		}
		return false;
	}
	else {
		int difference = count_close - count_open;
		for (unsigned int k = 0; k < difference; k++) {
			std::cout << "Unmatched " << closing_delimiter << std::endl;
		}
		return false;
	}
}

/*
 * do_delimiters_nest() returns a true or false boolean value depending on whether the
 * delimiters in the file are nested or not
 *
 * Algorithm:
 * 		1. Initializes variables for next character, closing delimiter, the right-most character in the table,
 * 		   and a counter for the unmatched delimiters
 * 		2. Starts reading file
 * 		3. Initializes table
 * 		4. While there are still characters to read in the file:
 * 				a. Assigns the next character to variable "next"
 * 				b. Checks the value of the next character:
 * 						i.   If the next character is an opening delimiter, place it in the right-most
 * 				   			 position in the table
 * 				   		ii.  If the next character is a closing delimiter:
 * 				   				1. If the table is not empty:
 * 				   						a. Assigns "last" variable as value of right-most character in table
 * 				   						b. Assigns closing_delimiter value of corresponding closing delimiter
 * 				   						c. Checks if the next character is the matching closing delimiter of
 * 				   						   the opening delimiter in the right-most position in the table
 * 				   						   		i. If true, erases last character in table
 * 				   						   		i. If false, prints that the closing delimiter is unmatched
 * 				   				2. If the table is empty:
 * 				   						a. Print that the closing delimiter is unmatched
 *		5. Checks if the table is empty and if there are any unmatched delimiters:
 *				a. If the table is empty, there are no unmatched or non-nested delimiters, so the
 *				   function returns true
 * 				b. Checks if the table is empty
 * 						i. If the table is not empty:
 * 								1. Print "Missing"
 * 								2. While the table is not empty:
 * 										a. Assigns "last" variable as value of right-most character in table
 * 										b. Checks type of right-most opening delimiter in table and assigns
 * 							 			   closing_delimiter variable as the value of the corresponding delimiter
 * 										c. Prints value of closing delimiter
 * 										d. Erases right-most character
 * 		6. Returns false
 */

bool do_delimiters_nest() {
	char next;
	char closing_delimiter;
	char last;
	int unmatched_counter = 0;

	ece150::start_reading_file();
	ece150::initialize_table();

	while (ece150::at_eof() == false) {
		next = ece150::get_next_character();
		if (next == '(' || next == '[' || next == '{') {
			ece150::place_character(next);
		}
		else if (next == ')' || next == ']' || next == '}') {
			if (ece150::is_table_empty() == false) {
				last = ece150::get_right_most_character();
				if (last == '(') {
					closing_delimiter = ')';
				}
				else if (last == '[') {
					closing_delimiter = ']';
				}
				else {
					closing_delimiter = '}';
				}
				if (next == closing_delimiter) {
					ece150::erase_right_most_character();
				}
				else {
					unmatched_counter++;
					std::cout << "Unmatched " << next << std::endl;
				}
			}
			else {
				unmatched_counter++;
				std::cout << "Unmatched " << next << std::endl;
			}
		}
		else {

		}
	}

	if ((ece150::is_table_empty() == true) && (unmatched_counter == 0)) {
		return true;
	}

	else {
		if (ece150::is_table_empty() != true) {
			std::cout << "Missing ";
			while (ece150::is_table_empty() == false) {
				last = ece150::get_right_most_character();
					if (last == '(') {
						closing_delimiter = ')';
					}
					else if (last == '[') {
						closing_delimiter = ']';
					}
					else {
						closing_delimiter = '}';
					}
					std::cout << closing_delimiter;
					ece150::erase_right_most_character();
			}
			std::cout << std::endl;
		}
	}
	return false;
}

