#ifndef POKERCMD_UTILITIES_H
#define POKERCMD_UTILITIES_H

namespace pokercmd {

	struct Arguments {
		double duration;
	};

	Arguments parse_args(int argc, char* argv[]);

}

#endif
