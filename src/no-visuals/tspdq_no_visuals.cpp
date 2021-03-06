#include <algorithm>
#include <array>
#include <cmath>
#include <fmt/format.hpp>
#include <vector>

struct OCity
{
	uint16_t x;
	uint16_t y;
	OCity(const uint16_t t_x, const uint16_t t_y) : x(t_x), y(t_y) {}
};

float totalDistanceX(const std::vector<OCity>& route, const size_t size)
{
	float sum = 0.f;
	for(size_t x = 0; x < size - 1; ++x)
	{
		sum += std::sqrt(std::pow(route[x + 1].x - route[x].x, 2) +
						 std::pow(route[x + 1].y - route[x].y, 2));
	}

	return sum;
}

void printCountryX(const std::vector<OCity>& route)
{
	std::for_each(route.cbegin(), route.cend(), [&route, i = 1ULL](const OCity& city) mutable {
		fmt::print("Route {} -> x: {} y: {}\n", i++, city.x, city.y);
	});
}

void changeRouteX(std::vector<OCity>& route, const size_t indexf, const size_t indexs)
{
	// Is this just std::swap(route[indexf], route[indexs]); ?
	OCity temp = route[indexf];
	route.at(indexf) = route[indexs];
	route.at(indexs) = temp;
}

std::vector<OCity> shortestForThreeX(std::vector<OCity>& route)
{
	std::vector<OCity> rCity = route;

	float record = totalDistanceX(route, route.size());
	changeRouteX(route, 1, 2);

	if(totalDistanceX(route, 3) < record)
	{
		rCity = route;
		record = totalDistanceX(route, 3);
	}

	changeRouteX(route, 0, 1);
	changeRouteX(route, 0, 2);

	if(totalDistanceX(route, 3) < record)
	{
		rCity = route;
		record = totalDistanceX(route, 3);
	}

	return rCity;
}

std::vector<std::vector<OCity>> possibleRoutes(const std::vector<OCity>& country)
{
	std::vector<std::vector<OCity>> allPossibleRoutes;
	std::vector<OCity> temp;
	std::vector<OCity> a;
	std::vector<OCity> b;

	size_t len = country.size();

	for(size_t s = 0; s < len; ++s)
	{
		a = std::vector<OCity>(country.begin() + s, country.end());
		b = std::vector<OCity>(country.begin(), country.begin() + s);

		temp.reserve(a.size() + b.size());

		// Assignment erases reserve
		temp = a;
		temp.insert(temp.end(), b.begin(), b.end());

		allPossibleRoutes.push_back(temp);
	}

	return allPossibleRoutes;
}

std::vector<OCity> combineTwoRoutes(const std::vector<OCity>& route1,
									const std::vector<OCity>& route2)
{
	std::vector<OCity> final_route(route1);
	final_route.insert(final_route.end(), route2.begin(), route2.end());
	return final_route;
}

std::vector<OCity> joinTwoRoutes(const std::vector<OCity>& route1, const std::vector<OCity>& route2)
{
	std::vector<OCity> combinedRoute;
	std::vector<OCity> combinedRouteAlt;
	std::vector<OCity> reversedRoute;
	std::vector<OCity> routeToBeReturned;
	std::vector<std::vector<OCity>> routesForFormer;
	std::vector<std::vector<OCity>> routesForLatter;

	combinedRoute = combineTwoRoutes(route1, route2);
	routeToBeReturned = combinedRoute;

	routesForFormer = possibleRoutes(route1);
	routesForLatter = possibleRoutes(route2);

	float shortestDistance = totalDistanceX(combinedRoute, combinedRoute.size());
	for(size_t a = 0; a < route1.size(); ++a)
	{
		for(size_t b = 0; b < route2.size(); ++b)
		{
			combinedRoute = combineTwoRoutes(routesForFormer[a], routesForLatter[b]);
			reversedRoute =
				std::vector<OCity>(routesForLatter[b].rbegin(), routesForLatter[b].rend());
			combinedRouteAlt = combineTwoRoutes(routesForFormer[a], reversedRoute);

			if(totalDistanceX(combinedRouteAlt, combinedRouteAlt.size()) <
			   totalDistanceX(combinedRoute, combinedRoute.size()))
			{
				combinedRoute = combinedRouteAlt;
			}

			if(totalDistanceX(combinedRoute, combinedRoute.size()) < shortestDistance)
			{
				shortestDistance = totalDistanceX(combinedRoute, combinedRoute.size());
				routeToBeReturned = combinedRoute;
			}
		}
	}

	return routeToBeReturned;
}

uint16_t extentX(const std::vector<uint16_t>& nums)
{
	const uint16_t min = *std::min_element(nums.begin(), nums.end());
	const uint16_t max = *std::max_element(nums.begin(), nums.end());

	return max - min;
}

std::vector<std::vector<OCity>> splitCities(std::vector<OCity>& route)
{
	std::vector<uint16_t> xValues;
	std::vector<uint16_t> yValues;
	std::vector<OCity> sortedCity;
	std::vector<OCity> firstHalf;
	std::vector<OCity> secondHalf;
	std::vector<std::vector<OCity>> twoSplitCities;

	size_t len = route.size();
	uint16_t smallestX = route[0].x;
	uint16_t smallestY = route[0].y;
	size_t indexOfSmallest;

	for(size_t s = 0; s < route.size(); s++)
	{
		xValues.push_back(route[s].x);
		yValues.push_back(route[s].y);
	}

	if(extentX(xValues) > extentX(yValues))
	{
		for(size_t s = 0; s < len; s++)
		{
			for(size_t d = 0; d < route.size(); d++)
			{
				if(route.size() == 1)
				{
					indexOfSmallest = d;
				}
				else if(route[d].x <= smallestX)
				{
					indexOfSmallest = d;
					smallestX = route[d].x;
				}
			}

			sortedCity.push_back(route[indexOfSmallest]);
			route.erase(route.begin() + indexOfSmallest);
			smallestX = route[0].x;
		}
	}
	else
	{
		for(size_t s = 0; s < len; s++)
		{
			for(size_t d = 0; d < route.size(); d++)
			{
				if(route.size() == 1)
				{
					indexOfSmallest = d;
				}
				else if(route[d].y <= smallestY)
				{
					indexOfSmallest = d;
					smallestY = route[d].y;
				}
			}
			sortedCity.push_back(route[indexOfSmallest]);
			route.erase(route.begin() + indexOfSmallest);
			smallestY = route[0].y;
		}
	}

	firstHalf = std::vector<OCity>(sortedCity.begin(), sortedCity.end() - (sortedCity.size() / 2));
	secondHalf = std::vector<OCity>(sortedCity.begin() + (sortedCity.size() / 2), sortedCity.end());

	twoSplitCities.push_back(firstHalf);
	twoSplitCities.push_back(secondHalf);

	return twoSplitCities;
}

std::vector<OCity> divideAndConquer(std::vector<OCity>& country, const size_t n)
{
	if(country.size() <= n)
	{
		return shortestForThreeX(country);
	}
	else
	{
		std::vector<std::vector<OCity>> twoHalves = splitCities(country);

		std::vector<OCity> half1 = twoHalves.front();
		std::vector<OCity> half2 = twoHalves.back();

		return joinTwoRoutes(divideAndConquer(half1, n), divideAndConquer(half2, n));
	}
}

#if 0
int main()
{
	std::vector<OCity> conversion{
		OCity(6734, 1453), OCity(2233, 10),	  OCity(5530, 1424), OCity(401, 841),
		OCity(3082, 1644), OCity(7608, 4458), OCity(7573, 3716), OCity(7265, 1268),
		OCity(6898, 1885), OCity(1112, 2049), OCity(5468, 2606), OCity(5989, 2873),
		OCity(4706, 2674), OCity(4612, 2035), OCity(6347, 2683), OCity(6107, 669),
		OCity(7611, 5184), OCity(7462, 3590), OCity(7732, 4723), OCity(5900, 3561),
		OCity(4483, 3369), OCity(6101, 1110), OCity(5199, 2182), OCity(1633, 2809),
		OCity(4307, 2322), OCity(675, 1006),  OCity(7555, 4819), OCity(7541, 3981),
		OCity(3177, 756),  OCity(7352, 4506), OCity(7545, 2801), OCity(3245, 3305),
		OCity(6426, 3173), OCity(4608, 1198), OCity(23, 2216),	 OCity(7248, 3779),
		OCity(7762, 4595), OCity(7392, 2244), OCity(3484, 2829), OCity(6271, 2135),
		OCity(4985, 140),  OCity(1916, 1569), OCity(7280, 4899), OCity(7509, 3239),
		OCity(10, 2676),   OCity(6807, 2993), OCity(5185, 3258), OCity(3023, 1942)};

	std::vector<OCity> citiesPro = divideAndConquer(conversion, 3);
	printCountryX(citiesPro);
	fmt::print("\nDistance: {}\n", totalDistanceX(citiesPro, citiesPro.size()));

	return 0;
}

#endif
