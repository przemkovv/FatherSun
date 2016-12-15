
//#include <fmt/format.h>

#include <spdlog/spdlog.h>

int main()
{

	fmt::print("Hello World\n");
	fmt::print("Mam {} lat\n", 42);

	auto logger = spdlog::stdout_logger_mt("FatherSun", true);
	logger->set_level(spdlog::level::debug);
	logger->info("Dzisiaj techday");
	logger->debug("M�wimy o C++");
	logger->error("Mieli�my op�nienie");
	return 0;
}