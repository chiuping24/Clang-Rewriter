# Building

	mkdir build
	cd build
	cmake ..
	make

# Run clang-tidy
First build the project using the instructions outlined in the previous paragraph. In order to detect missing braces run:

	./clang-tidy-analyze.sh

And then to automatically fix them:

	./clang-tidy-fix.sh

Note that the commands have to be run in the root of the repository.
