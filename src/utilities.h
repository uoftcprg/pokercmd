#ifndef POKERCMD_UTILITIES_H
#define POKERCMD_UTILITIES_H

namespace pokercmd {

	struct Arguments {
		double standard_deviation;
	};

	Arguments parse_args(int argc, char* argv[]);

}

#endif
