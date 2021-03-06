
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
//#include <fmt/format.h>

#include "json.h"
#include "crow_all.h"
#include <spdlog/spdlog.h>

#include <chrono>
#include <thread>
#include <map>

#include <boost/optional.hpp>


using FibonacciNumbers = std::map<int, int64_t>;

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
	//std::this_thread::sleep_for(3s);
	return f2;
}


boost::optional<int64_t> find_fibonnaci_number(FibonacciNumbers &f_numbers, int n)
{

	auto it = std::find_if(f_numbers.begin(), f_numbers.end(),
		[&n](const auto &para)
	{
		return (para.first == n);
	});

	if (it == f_numbers.end())
	{
		return{};
	}
	else
	{
		return it->second;
	}
}

std::string get_all_numbers(const FibonacciNumbers &fibonnaci_numbers)
{
	nlohmann::json all_numbers;

	for (const auto & number : fibonnaci_numbers)
	{
		all_numbers.push_back({
			{ "n", number.first },
			{ "number", number.second }
		});
	}

	return all_numbers.dump(2);

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

	CROW_ROUTE(app, "/fibo_numbers/").methods("POST"_method, "GET"_method) (
		//[&](const crow::request& req)
		[&logger, &fibonnaci_numbers](const crow::request& req)
	{
		if (req.method == "POST"_method)
		{
			logger->debug("Cialo wiadomosc: {}", req.body);
			nlohmann::json body = nlohmann::json::parse(req.body);
			for (const auto& elem : body)
			{
				int n = elem["n"].get<int>();
				fibonnaci_numbers[n] = fibonnacci_number(n);
			}

			return crow::response(200);
		}
		else if (req.method == "GET"_method) {
			auto lista_wszystkich = get_all_numbers(fibonnaci_numbers);
			return crow::response(200, lista_wszystkich);
		}
		else
		{
			return crow::response(404);

		}
	}

	);
	CROW_ROUTE(app, "/fibo_numbers/<int>")(
		[&fibonnaci_numbers](int n)
	{
		auto number = find_fibonnaci_number(fibonnaci_numbers, n);
		if (number)
		{
			auto response = fmt::format("{}", number.get());
			return crow::response(200, response);
		}
		else
		{
			return crow::response(404);
		}
	}
	);


	app.port(8080).multithreaded().run();

	return 0;
}