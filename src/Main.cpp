#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <stdio.h>
#include <iostream>
#include <experimental/filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <stdint.h>
#include <stdlib.h>

namespace fs = std::experimental::filesystem;

#define printl(x) std::cout << x << std::endl

int main(int argc, char* argv[]) {
	std::string dp_name;
	std::string dp_mcversion;

	// Optional param vars
	bool dp_resource_flag = false; // unused :(
	bool dp_description_record = false;
	bool dp_gen_all_dirs = false;
	std::string dp_description = "Generated base datapack!";

	std::string cmd;

	if (argc < 2) {
		printl("No name/version provided...");
		return 0;
	}

	for (int i = 0; i < argc; i++) {
		//printf("argv[%d]: %s\n", i, argv[i]);
		std::string arg = argv[i];
		if (i == 0) {
			continue; // to skip the first pramiter as its just the programs file path.
		}

		if (i == 1) {
			dp_name = arg;
			continue;
		}

		if (i == 2) {
			dp_mcversion = arg;
			continue;
		}

		// Optional prams
		if (arg == "-resource") {
			dp_resource_flag = true;
			continue;
		}

		if (arg == "-description") {
			dp_description_record = true;
			continue;
		}

		if (arg == "-gen-all") {
			dp_gen_all_dirs = true;
			continue;
		}

		if (dp_description_record) {
			dp_description = arg;
			dp_description_record = false;
			continue;
		}
	}

	std::string versionId;

	// TODO: read from a list of entries to ditermine what version id is used.
	if (dp_mcversion == "1.13" || dp_mcversion == "1.13.1" || dp_mcversion == "1.13.2" || dp_mcversion == "1.14" || dp_mcversion == "1.14.1" || dp_mcversion == "1.14.2" || dp_mcversion == "1.14.3" || dp_mcversion == "1.14.4") { versionId = "4"; }
	else if (dp_mcversion == "1.15" || dp_mcversion == "1.15.1" || dp_mcversion == "1.15.2" || dp_mcversion == "1.16" || dp_mcversion == "1.16.1") { versionId = "5"; }
	else if (dp_mcversion == "1.16.2" || dp_mcversion == "1.16.3" || dp_mcversion == "1.16.4" || dp_mcversion == "1.16.5") { versionId = "6"; }
	else if (dp_mcversion == "1.17" || dp_mcversion == "1.17.1") { versionId = "7"; }
	else if (dp_mcversion == "1.18" || dp_mcversion == "1.18.1") { versionId = "8"; }
	else if (dp_mcversion == "1.18.2") { versionId = 9; } // 1.18.2+
	else { printf("Error: the provided version has no version ID..."); return 0; }

	fs::create_directories("generated_pack");

	std::ofstream mcmeta("generated_pack/pack.mcmeta");
	mcmeta << "{\n";
	mcmeta << "	\"pack\": {\n";
	mcmeta << "		\"pack_format\": " + versionId + ",\n";
	mcmeta << "		\"description\": \"" + dp_description + "\"\n";
	mcmeta << "	}\n";
	mcmeta << "}\n";

	mcmeta.close();

	fs::create_directories(std::string("generated_pack/data/" + dp_name + "/functions").c_str());
	fs::create_directories(std::string("generated_pack/data/minecraft/tags/functions").c_str());

	if (dp_gen_all_dirs) {
		// custom items in custom namespace
		fs::create_directories(std::string("generated_pack/data/" + dp_name + "/loot_tables").c_str());
		fs::create_directories(std::string("generated_pack/data/" + dp_name + "/predicates").c_str());
		fs::create_directories(std::string("generated_pack/data/" + dp_name + "/recipes").c_str());
		fs::create_directories(std::string("generated_pack/data/" + dp_name + "/advancements").c_str());
		fs::create_directories(std::string("generated_pack/data/" + dp_name + "/tags").c_str());

		// minecraft overrides

	}

	std::ofstream loadmcf("generated_pack/data/" + dp_name + "/functions/load.mcfunction");
	loadmcf << "tellraw @a [{\"text\":\"" + dp_name + "\",\"color\":\"yellow\"},{\"text\":\" has successfully loaded\",\"color\":\"dark_green\"}]";
	loadmcf.close();

	std::ofstream tickmcf("generated_pack/data/" + dp_name + "/functions/tick.mcfunction");
	tickmcf << "";
	tickmcf.close();

	std::ofstream tickptr("generated_pack/data/minecraft/tags/functions/tick.json");
	tickptr << "{\n";
	tickptr << "	\"values\": [\n";
	tickptr << "		\"" + dp_name + ":tick\"\n";
	tickptr << "	]\n";
	tickptr << "}\n";
	tickptr.close();

	std::ofstream loadptr("generated_pack/data/minecraft/tags/functions/load.json");
	loadptr << "{\n";
	loadptr << "	\"values\": [\n";
	loadptr << "		\"" + dp_name + ":load\"\n";
	loadptr << "	]\n";
	loadptr << "}\n";
	loadptr.close();
}