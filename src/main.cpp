#include "boost_util.h"

#include <string>

#include <boost/program_options.hpp>

using namespace std;
using namespace boost::program_options;

string arg_log_level;
int arg_log_file;
string arg_string;
int arg_int;

bool parse_args(int argc, char** argv)
{
	options_description opt("opt");
	opt.add_options()
		("log_level", value<string>()->default_value("debug"), "log level")
		("log_file", value<int>()->default_value(0), "flag output log to file")
		("arg_string", value<string>()->default_value(""), "string")
		("arg_int", value<int>()->required(), "int")
	;
	variables_map vm;
	try{
		store(parse_command_line(argc, argv, opt), vm);
		//ifstream ifs("config.txt");
		//store(parse_config_file(ifs, opt), vm);
		notify(vm);
		//if(vm.count("log_level") == 1);
		arg_log_level = vm["log_level"].as<string>();
		arg_log_file = vm["log_file"].as<int>();
		arg_string = vm["arg_string"].as<string>();
		arg_int = vm["arg_int"].as<int>();
	}catch(exception& e){
		BOOST_LOG_TRIVIAL(error) << "error_parse_args:" << e.what();
		return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	if(!parse_args(argc, argv)){
		return 1;
	}
	boost_util::set_log_level(arg_log_level, arg_log_file);

	_li << "arg_string:" << arg_string;
	_li << "arg_int:" << arg_int;

	return 0;
}
