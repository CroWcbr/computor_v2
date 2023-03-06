# computor_v2 with BONUS

# NEED clear display info (not clear yet, may be upgrade programm and operation in future)

This project is the first of a serie to renew your relationship to mathematics, it will be very useful, essential even, for many more projects.
- check: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./computor_v2

## Command:
- show - display variables
- history - display log
- help - show this
- change_mod - radians on/off
- test - start test
- draw - draw the curve (need to read about SFML)

## BONUS:
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
- An extension of the matrix computation applied to the vector computation
- Matrix inversion (matrix ^ (-1))

## table type
|               |    Rational   |    Complex    |    Matrix     |    Function   |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| Rational +    |       ✅      |       ✅     |       no      |      ✅      |
| Rational -    |       ✅      |       ✅     |       no      |      ✅      |
| Rational *    |       ✅      |       ✅     |       ✅      |      ✅      |
| Rational /    |       ✅      |       ✅     |       no      |      ✅      |
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



