
//#include <fmt/format.h>

#include <spdlog/spdlog.h>

int main()
{

	fmt::print("Hello World\n");
	fmt::print("Mam {} lat\n", 42);

	auto logger = spdlog::stdout_logger_mt("FatherSun", true);
	logger->set_level(spdlog::level::debug);
	logger->info("Dzisiaj techday");
	logger->debug("Mówimy o C++");
	logger->error("Mieliœmy opóŸnienie");
	return 0;
}