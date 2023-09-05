# computor_v2 with BONUS

This project is the first of a serie to renew your relationship to mathematics, it will be very useful, essential even, for many more projects.
- check: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./computor_v2

## Command:
- show - display variables
- history - display log
- help - show this
- change_mod - radians on/off
- test - start test
- draw - draw the curve (need to read about SFML)
- quit - for exit

## BONUS:
- Function curve display - git submodule add https://github.com/glfw/glfw.git external/glfw
- Added usual functions:
	- exponential
	- square root
	- sine / cosine / tangent / cotangent
	- ln / log
	- absolute value
- Radian computation for angles
- Function Composition
- Norm computation
- Display of the list of stored variables and their values
- History of commands with results
- An extension of the matrix computation applied to the vector computation (vector = matrix with 1 row or column)
- Matrix inversion (matrix ^ (-1))

## table type
|               |    Rational   |    Complex    |    Matrix     |    Function   |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| Rational +    |       ✅      |       ✅     |       ✅      |      ✅      |
| Rational -    |       ✅      |       ✅     |       ✅      |      ✅      |
| Rational *    |       ✅      |       ✅     |       ✅      |      ✅      |
| Rational /    |       ✅      |       ✅     |       ✅      |      ✅      |
| Rational %    |       ✅      |       no     |       no      |      ✅       |
| Rational ^    |       ✅      |       no     |       no      |      ✅       |
| Rational **   |       no       |       no     |       no      |       no      |
| Complex +     |       ✅      |       ✅     |       no      |      ✅      |
| Complex -     |       ✅      |       ✅     |       no      |      ✅      |
| Complex *     |       ✅      |       ✅     |       no      |      ✅      |
| Complex /     |       ✅      |       ✅     |       no      |      ✅      |
| Complex %     |       no       |       no     |       no      |      no       |
| Complex ^     |       ✅      |       no     |       no      |      ✅       |
| Complex **    |       no       |       no     |       no      |       no      |
| Matrix +      |       ✅      |       no      |       ✅      |      ✅      |
| Matrix -      |       ✅      |       no      |       ✅      |      no      |
| Matrix *      |       ✅      |       no     |       ✅      |      no      |
| Matrix /      |       ✅      |       no     |       no      |      no      |
| Matrix %      |       no       |       no     |       no      |      no       |
| Matrix ^      |       ✅      |       no     |       no      |      no       |
| Matrix **     |       no       |       no     |       ✅      |       no      |
| Function +    |       ✅      |       ✅     |       ✅      |      ✅      |
| Function -    |       ✅      |       ✅     |       no      |      ✅      |
| Function *    |       ✅      |       ✅     |       no      |      ✅      |
| Function /    |       ✅      |       ✅     |       no      |      ✅      |
| Function %    |       ✅      |      ✅      |       no      |      ✅       |
| Function ^    |       ✅      |      ✅      |       no      |      ✅       |
| Function **   |       no       |       no     |       no      |       no      |
