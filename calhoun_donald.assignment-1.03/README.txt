This is my Terrian Generation c code for 1.01, which meets all of the specified requirements as follows:
	- The map is 80x21 units so that it can fit in terminal
	- There are at least two paths, one N-S and one E-W. Tho I made it possible for more than two to spawn. Shown as red #
	- There is a PokeCenter and PokeMart located on a path represented by purple 2x2 M or 2x2 C
	- There is at least 2 patches of Tall Grass with possibility of more, represented by green :
	- The border is represented as boulders with a %
	- There are clearings represented by green .
	- Also allowed random generation of Trees(Yellow ") and boulders(%)

This is my Terrian Generation c code for 1.02, which meets all of the specified requirements as follows:
	- Has the inputs n, s, e, w, f x y, and q
	- Prints error message and then reprints last grid if invalid input
	- Has 399x399 maps of size 21x80
	- Has Probabilities to make PokeCenters/Marts less likely the farther you go
	- All path entrances and exits line up when going to tangent map
	- World edges have no exits
	- All visited maps are saved in a 4d array and do not get re generated