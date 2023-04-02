/* This file is part of onnx2c.
 */
#include <iostream>
#include <fstream>

#include "onnx.pb.h"

#include "graph.h"
#include "options.h"
#include "tensor.h"

int main(int argc, const char *argv[])
{
	onnx::ModelProto onnx_model;

	parse_cmdline_options(argc, argv);

	std::ifstream input(options.input_file);
	if (!input.good()) {
		std::cerr << "Error opening input file: \"" << options.input_file << "\""  << std::endl;
		exit(1); //TODO: check out error numbers for a more accurate one
	}
	onnx_model.ParseFromIstream(&input);

	std::cout.precision(20);
	toC::Graph toCgraph(onnx_model);
	if( options.opt_unionize )
		toCgraph.unionize_tensors();
	toCgraph.print_source(std::cout);
}

