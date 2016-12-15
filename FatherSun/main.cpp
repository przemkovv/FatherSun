
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
//#include <fmt/format.h>

#include <spdlog/spdlog.h>
#include "crow_all.h"
#include <chrono>
#include <thread>
#include <map>


int64_t fibonnacci_number(int n)
{
	using namespace std::chrono_literals;
	int64_t f0 = 0;
	int64_t f1 = 1;
	int64_t f2 = f1;

	for (int i = 0; i < n; i++)
	{
		f2 = f1 + f0;
		f0 = f1;
		f1 = f2;;
		}
	std::this_thread::sleep_for(3s);
	return f2;
}

int main()
{

	fmt::print("Hello World\n");
	fmt::print("Mam {} lat\n", 42);

	auto logger = spdlog::stdout_logger_mt("FatherSun", true);
	logger->set_level(spdlog::level::debug);
	logger->info("Dzisiaj techday");
	logger->debug("M�wimy o C++");
	logger->error("Mieli�my op�nienie");
	//logger->info("{}", fibonnacci_number(0));

	std::map<int, int64_t> fibonnaci_numbers;

	crow::SimpleApp app;

	CROW_ROUTE(app, "/fibo_numbers/").methods("POST"_method) (
		//[&](const crow::request& req)
		[&logger,&fibonnaci_numbers](const crow::request& req)
	{
		if (req.method == "POST"_method)
		{
			logger->debug("Cialo wiadomosc: {}", req.body);
			int n = stoi(req.body);
			fibonnaci_numbers[n] = fibonnacci_number(n);
			return crow::response(200);
		} else
		{
			return crow::response(404);

		}
	}
		
		);
	CROW_ROUTE(app, "/fibo_numbers/<int>")(
		[](int n)
	{

		return "";
	}
	);


	app.port(8080).multithreaded().run();

	return 0;
}