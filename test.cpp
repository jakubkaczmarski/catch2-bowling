#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch_amalgamated.hpp"
SCENARIO("Ideal Game", "[idealGame]") {
    GIVEN("all pines missed") {
        std::vector<int> v(20, 0);
        int score = 0;
        WHEN("expected score after game  should equal 0") {
            int expected = 0;
            THEN("score is equal 0") {
                REQUIRE(score == expected);
            }
            THEN("numberOfGames is equal to 20") {
                expected = 20;
                REQUIRE(v.size() == expected);
            }
        }
    }
    GIVEN("All the pines shot down first time") {
        std::vector<int> v(12, 10);
        int score = 300;
        WHEN("expected score after game should equeal 300") {
            int expected = 300;
            THEN("Score is equal 300") {
                REQUIRE(score == expected);
            }
            THEN("numberOfGames is equal to 10") {
                expected = 12;
                REQUIRE(v.size() == expected);
            }
            THEN("There are two bonus balls") {
                expected = 12;
                REQUIRE(v.size() == expected);
            }
        }
    }
    GIVEN("All the pines shot down second time") {
        std::vector<int> v = {0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0};
        int score = 100;

        WHEN("expected score after game should equal 100") {
            int expected = 100;
            THEN("There is one bonus ball") {
                expected = 21;
                REQUIRE(v.size() == expected);
            }
            THEN("Score is equal 100") {
                REQUIRE(score == expected);
            }
            THEN("numberOfGames is equal to 21") {
                expected = 21;
                REQUIRE(v.size() == expected);
            }
        }
    }
}
SCENARIO("Any given scenerio") {
    GIVEN("Number of rounds and score") {
        int score = 200;
        // std::vector<std::vector<int>> {{10,0}, {2,3}, {3,2}}
        std::vector<int> v(20, 3);
        WHEN("score is less than or equal to 300 and bigger or equal to 0") {
            REQUIRE(score <= 300);
            REQUIRE(score >= 0);
            THEN("number of rounds is less or equal to 21 and bigger or equal to 10") {
                int expected = 21;
                REQUIRE(v.size() <= expected);
            }
        }
        WHEN("Score taken from frame") {
            THEN("Score needs to be less than 11 and bigger than 0") {
                bool pair{false};
                for (int i = 0; i < v.size(); i++) {
                    if (pair) {
                        if (v[i] == 10) {
                            continue;
                        } else if (i > 0) {
                            REQUIRE(v[i] + v[i - 1] <= 10);
                        }
                    }
                    pair = !pair;
                }
            }
        }
    }
}
