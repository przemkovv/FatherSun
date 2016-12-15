
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
//#include <fmt/format.h>

#include <spdlog/spdlog.h>
#include "crow_all.h"


int64_t fibonnacci_number(int n)
{
	int64_t f0 = 0;
	int64_t f1 = 1;
	int64_t f2 = f1;

	for (int i = 0; i < n; i++)
	{
		f2 = f1 + f0;
		f0 = f1;
		f1 = f2;;
		}
	return f2;
}

int main()
{

	fmt::print("Hello World\n");
	fmt::print("Mam {} lat\n", 42);

	auto logger = spdlog::stdout_logger_mt("FatherSun", true);
	logger->set_level(spdlog::level::debug);
	logger->info("Dzisiaj techday");
	logger->debug("Mówimy o C++");
	logger->error("Mieliœmy opóŸnienie");
	logger->info("{}", fibonnacci_number(0));

	crow::SimpleApp app;

	CROW_ROUTE(app, "/hello")(
		[]()
	{
		return fibonnacci_number(5);
	}
	);

	CROW_ROUTE(app, "/hello/<int>")(
		[](int n)
	{
		return fibonnacci_number(n);
	}
	);

	app.port(8080).multithreaded().run();

	return 0;
}